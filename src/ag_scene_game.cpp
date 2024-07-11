#include "ag_scene_game.h"

#include "ag_bg_tiles.h"
#include "ag_default_levels.cpp.h"
#include "ag_return_top_tiles.cpp.h"

// extern variables
extern ag::scene::type next_scene;
extern bn::fixed g_sound_effect_wait;
extern int g_next_level;

namespace ag {

game::game():
    scene(scene::type::GAME),
    _ctrl_mode(ctrl_mode::CURSOR_MOVE),
    _prev_ctrl_mode(ctrl_mode::CURSOR_MOVE),
    _key_wait_time(0),
    _current_level_id(g_next_level - 1),
    _current_atom(AG_UNINITIALIZED),
    _mole_width(AG_UNINITIALIZED),
    _mole_completed(false),
    _mole_blink_time(AG_UNINITIALIZED),
    _mole_blink_on(false),
    _text_generator(common::variable_8x16_sprite_font,
                    bn::sprite_items::font_palette.palette_item()),
    _camera(bn::camera_ptr::create(0, 0)),
    _atom_count(AG_UNINITIALIZED),
    _return_top_cursor(bn::sprite_items::atomic.create_sprite(255-9*8, -256+9*8, 33)),
    _return_top_val(false)
{
    _init();

    bn::music_items::music001.play(1.0);

    set_stat(scene::stat::ACTIVE);
}

game::~game() {
    ag::bg_map_manager::destroy_bg_map();
}

void game::update() {
    if (_ctrl_mode == ctrl_mode::CURSOR_MOVE) {
        _ctrl_cursor_move();
    }
    else if (_ctrl_mode == ctrl_mode::ATOM_MOVE) {
        _ctrl_atom_move();
    }
    else if (_ctrl_mode == ctrl_mode::RETURN_TOP) {
        _ctrl_return_top();
    }

    if (_mole_completed) {
        g_sound_effect_wait -= 1;
        if (g_sound_effect_wait < 0) {
            // change scene to LEVEL_MENU
            g_next_level = (_current_level_id < 82) ? (_current_level_id +2) : (_current_level_id +1);
            next_scene = ag::scene::type::LEVEL_MENU;
            set_stat(scene::stat::DONE);
        }
    }
    else {
        if (_ctrl_mode != ctrl_mode::DISABLE) {
            // return top menu
            if (bn::keypad::start_pressed() && (_ctrl_mode != ctrl_mode::RETURN_TOP)) {
                _prev_ctrl_mode = _ctrl_mode;
                _ctrl_mode = ctrl_mode::RETURN_TOP;
                _cursor.set_enable(false);
                _set_return_top_cursor(false);
                _camera.set_position((255-6*16),(-256+3*16));
            }

            // display mole
            if (bn::keypad::select_pressed() && (_ctrl_mode != ctrl_mode::RETURN_TOP)) {
                _prev_ctrl_mode = _ctrl_mode;
                _ctrl_mode = ctrl_mode::DISABLE;
                _cursor.set_enable(false);
                _camera.set_position((-256+7*16),(-256+3*16));
            }
        }
        else {
            // return to game
            if (bn::keypad::select_pressed()) {
                _ctrl_mode = _prev_ctrl_mode;
                _cursor.set_enable(true);
                _set_camera(_cursor.index().x(),_cursor.index().y());
            }
        }
    }

    _update();
    bn::core::update();
}

void game::_init() {
    // clear _feld_stat
    for (int i = 0; i < AG_FELD_X_SIZE * AG_FELD_Y_SIZE; i++) {
        _feld_stat[i] = 0xFF;
    }

    _init_bg_map();
    _init_atom();
    _init_mole();
    _init_title();
    _init_return_top();

    // cursor
    bn::point start_pos = _atom[0]->index();
    _cursor.set_camera(_camera);
    _cursor.set_index(start_pos.x(),start_pos.y());

    // return_top_cursor
    _return_top_cursor.set_camera(_camera);

    _set_camera(start_pos.x(),start_pos.y());
}

void game::_update() {
    const int _mole_blink_time_max = 10;

    // blink _atom[]
    if (_mole_completed) {
        _mole_blink_time += 1;
        if (_mole_blink_time > _mole_blink_time_max) {
            _mole_blink_on = !_mole_blink_on;
            _mole_blink_time = 0;

            for (int i = 0; i < _atom_count; i++) {
                if (_mole_blink_on) {
                    _atom[i]->set_palette(bn::sprite_items::atomic_palette1.palette_item());
                }
                else {
                    _atom[i]->set_palette(bn::sprite_items::atomic.palette_item());
                }
            }
        }
    }

    ag::bg_map_manager::update();
}

void game::_init_bg_map() {
    // create bg_map init data
    bn::vector<struct ag::bg_map_manager::init_data_t, 600> tmp_init_data;
    char* current_feld = (char*)(all_level_data.feld_list[_current_level_id].data);
    int tmp_init_data_size = all_level_data.feld_list[_current_level_id].size;
    BN_ASSERT(tmp_init_data_size == AG_FELD_Y_SIZE, "Invalid feld_size");

    for (int feld_y = 0; feld_y < AG_FELD_Y_SIZE; feld_y++) {
        for (int feld_x = 0; feld_x < AG_FELD_X_SIZE; feld_x++) {
            char c = *(current_feld + (feld_y * AG_FELD_X_SIZE) + feld_x);
            if (0xFE == c) {
                int x0 = (feld_x -7)*2 + 32;
                int y0 = (feld_y -7)*2 + 32;
                int offset_x = 0;
                int offset_y = 0;
                struct ag::bg_map_manager::init_data_t tmp_data[4];

                tmp_data[0].x = x0 + offset_x;
                tmp_data[0].y = y0 + offset_y;
                tmp_data[0].tile_index = WALL_TILE1;
                tmp_init_data.push_back(tmp_data[0]);

                offset_x = 1;
                tmp_data[1].x = x0 + offset_x;
                tmp_data[1].y = y0 + offset_y;
                tmp_data[1].tile_index = WALL_TILE2;
                tmp_init_data.push_back(tmp_data[1]);

                offset_x = 0;
                offset_y = 1;
                tmp_data[2].x = x0 + offset_x;
                tmp_data[2].y = y0 + offset_y;
                tmp_data[2].tile_index = WALL_TILE3;
                tmp_init_data.push_back(tmp_data[2]);

                offset_x = 1;
                tmp_data[3].x = x0 + offset_x;
                tmp_data[3].y = y0 + offset_y;
                tmp_data[3].tile_index = WALL_TILE4;
                tmp_init_data.push_back(tmp_data[3]);

                // set _feld_stat
                _feld_stat[feld_y*AG_FELD_X_SIZE + feld_x] = 0xFE;
            }
        }
    }

    struct array_t<struct ag::bg_map_manager::init_data_t> tmp_bg_map_init_list;
    tmp_bg_map_init_list.data = &tmp_init_data[0];
    tmp_bg_map_init_list.size = tmp_init_data.size();

    // create bg_map
    ag::bg_map_manager::create_bg_map(bn::regular_bg_items::bg_tiles.tiles_item(),
                                      bn::regular_bg_items::bg_tiles.palette_item());
    ag::bg_map_manager::set_camera(_camera);
    ag::bg_map_manager::init_bg_map(&tmp_bg_map_init_list);
}

void game::_init_atom() {
    unsigned short* current_atom = (unsigned short*)(all_level_data.atom_list[_current_level_id].data);
    int tmp_init_data_size = all_level_data.atom_list[_current_level_id].size;
    BN_ASSERT(tmp_init_data_size < 32, "Invalid atom_size");

    // set _atom_list
    for (int i = 0; i < tmp_init_data_size; i++) {
        ag::atom_t tmp_atom;
        tmp_atom.id       = (current_atom + i * 2)[0];
        tmp_atom.conn_flg = (current_atom + i * 2)[1];
        _atom_list.push_back(tmp_atom);
    }

    // set _atom[]
    int add_atom_index = 0;
    char* current_feld = (char*)(all_level_data.feld_list[_current_level_id].data);
    for (int feld_y = 0; feld_y < AG_FELD_Y_SIZE; feld_y++) {
        for (int feld_x = 0; feld_x < AG_FELD_X_SIZE; feld_x++) {
            char c = *(current_feld + (feld_y * AG_FELD_X_SIZE) + feld_x);
            int index = (int)c - 1;
            if ((0 <= index) && (index < 32)) {
                BN_ASSERT(add_atom_index < 32, "invalid atom_index");

                // create atom
                _atom[add_atom_index].reset(new ag::atom(_atom_list[index]));
                _atom[add_atom_index]->set_camera(_camera);
                _atom[add_atom_index]->set_index(feld_x, feld_y);
                _feld_stat[feld_y*AG_FELD_X_SIZE + feld_x] = add_atom_index;
                add_atom_index += 1; 
            }
        }
    }
    _atom_count = add_atom_index;
}

void game::_init_mole() {
    // create _mole data
    char* current_mole = (char*)(all_level_data.mole_list[_current_level_id].data);
    int tmp_data_size = all_level_data.mole_list[_current_level_id].size;
    BN_ASSERT(tmp_data_size > 0, "Invalid mole_size");

    int m_idx = 0;
    int row_idx = 0;
    while (m_idx < 15*15) {
        char c = *(current_mole + m_idx);
        int atom_idx = (int)c;

        // line end
        if(atom_idx == 0) {
            if (_mole_width == AG_UNINITIALIZED) {
                _mole_width = m_idx;
            }
            // loop end
            if ((row_idx + 1) >= tmp_data_size) {
                break;
            }
            // next row
            row_idx += 1;
        }
        else {
            ag::atom_t tmp_atom;
            if (atom_idx == 0xFF) {
                tmp_atom.id = 0xFF;
                tmp_atom.conn_flg = 0x0000;
            }
            else {
                tmp_atom = _atom_list[(atom_idx - 1)];
            }
            _mole.push_back(tmp_atom);
        }
        m_idx++;
    }

    // create _mole_atom[]
    int add_mole_atom_index = 0;
    int mole_height = _mole.size()/_mole_width;
    int x_offset = (-256+14*16) - ((_mole_width + 1)/2)*16;
    int y_offset = (-256+10*16) - ((mole_height + 1)/2)*16;
    for (int y_idx = 0; y_idx < mole_height; y_idx++) {
        for (int x_idx = 0; x_idx < _mole_width; x_idx++) {
            ag::atom_t& init_data = _mole[y_idx*_mole_width + x_idx];
            if (init_data.id != 0xFF) {
                _mole_atom[add_mole_atom_index].reset(new ag::atom(init_data));
                _mole_atom[add_mole_atom_index]->set_camera(_camera);
                _mole_atom[add_mole_atom_index]->set_offset(x_offset,y_offset);
                _mole_atom[add_mole_atom_index]->set_index(x_idx, y_idx);
                add_mole_atom_index += 1;
            }
        }
    }
}

void game::_init_title() {
    // create title string
    char c_id_num[3];
    c_id_num[0] = '0' + ((_current_level_id+1) / 10);
    c_id_num[1] = '0' + ((_current_level_id+1) % 10);
    c_id_num[2] = '\0';
    bn::string<36> title_str = "Level";
    title_str += c_id_num;
    title_str += ": ";
    title_str += all_level_data.name_list[_current_level_id];

    // generate text sprites
    _text_generator.set_left_alignment();
    _text_generator.generate(-256, (-256-24), title_str.c_str(), _text_sprites);

    for (int i = 0; i < _text_sprites.size(); i++) {
        _text_sprites[i].set_camera(_camera);
    }
}

void game::_init_return_top() {
    ag::bg_map_manager::init_bg_map(&return_top_data.return_top_msg_init_list);
    ag::bg_map_manager::init_bg_map(&return_top_data.return_top_yes_init_list);
    ag::bg_map_manager::init_bg_map(&return_top_data.return_top_no_init_list);
    _set_return_top_cursor(false);
}

void game::_ctrl_cursor_move() {
    if (bn::keypad::a_pressed()) {
        bn::point cursor_pos = _cursor.index();

        int current_atom = _feld_stat[cursor_pos.y()*AG_FELD_X_SIZE + cursor_pos.x()];
        if ((0 <= current_atom) && (current_atom < 32)) {
            _set_movable(cursor_pos.x(), cursor_pos.y());
            _current_atom = current_atom;
            _ctrl_mode = ctrl_mode::ATOM_MOVE;
        }
    }

    // key wait
    if (_key_wait_time > 0) {
        _key_wait_time -= 1;
        return;
    }

    int x_move = 0;
    int y_move = 0;
    const int key_wait_init = 8;
    if (bn::keypad::up_held()) {
        y_move -= 1;
        _key_wait_time = key_wait_init;
    }
    if (bn::keypad::down_held()) {
        y_move += 1;
        _key_wait_time = key_wait_init;
    }
    if (bn::keypad::right_held()) {
        x_move += 1;
        _key_wait_time = key_wait_init;
    }
    if (bn::keypad::left_held()) {
        x_move -= 1;
        _key_wait_time = key_wait_init;
    }

    if ((x_move != 0) || (y_move != 0)) {
        bool dirt = false;
        bn::point current_index = _cursor.index();
        if (x_move != 0) {
            int new_x = current_index.x() + x_move;
            if (0 <= new_x && new_x < AG_FELD_X_SIZE) {
                current_index.set_x(new_x);
                dirt = true;
            }
        }
        if (y_move != 0) {
            int new_y = current_index.y() + y_move;
            if (0 <= new_y && new_y < AG_FELD_Y_SIZE) {
                current_index.set_y(new_y);
                dirt = true;
            }
        }
        if (dirt) {
            _cursor.set_index(current_index.x(), current_index.y());
            _set_camera(current_index.x(), current_index.y());
        }
    }
}

void game::_ctrl_atom_move() {
    if (bn::keypad::b_pressed()) {
        _cursor.set_enable_arrows(false);
        _ctrl_mode = ctrl_mode::CURSOR_MOVE;
    }

    bool dirt = false;
    int new_x;
    int new_y;
    if (bn::keypad::up_pressed()) {
        new_x = _movable[(int)ag::directions::UP].x();
        new_y = _movable[(int)ag::directions::UP].y();
        dirt = true;
    }
    else if (bn::keypad::down_pressed()) {
        new_x = _movable[(int)ag::directions::DOWN].x();
        new_y = _movable[(int)ag::directions::DOWN].y();
        dirt = true;
    }
    else if (bn::keypad::right_pressed()) {
        new_x = _movable[(int)ag::directions::RIGHT].x();
        new_y = _movable[(int)ag::directions::RIGHT].y();
        dirt = true;
    }
    else if (bn::keypad::left_pressed()) {
        new_x = _movable[(int)ag::directions::LEFT].x();
        new_y = _movable[(int)ag::directions::LEFT].y();
        dirt = true;
    }

    if (dirt) {
        if ((new_x != AG_UNINITIALIZED) && (new_y != AG_UNINITIALIZED)) {
            bn::point cursor_pos = _cursor.index();
            _feld_stat[cursor_pos.y()*AG_FELD_X_SIZE + cursor_pos.x()] = 0xFF;
            _feld_stat[new_y*AG_FELD_X_SIZE + new_x] = _current_atom;

            _atom[_current_atom]->set_index(new_x,new_y);
            _cursor.set_index(new_x,new_y);
            _cursor.set_enable_arrows(false);
            _set_camera(new_x,new_y);
            _set_movable(new_x,new_y);

            _check_mole_completed();
            if (_mole_completed) {
                _ctrl_mode = ctrl_mode::DISABLE;
                _cursor.set_enable(false);

                _mole_blink_time = 0;
                _mole_blink_on = false;

                bn::music::stop();
                bn::sound_items::complete.play();
                g_sound_effect_wait = 160;
            }
        }
    }
}

void game::_ctrl_return_top() {
    if (bn::keypad::right_pressed()) {
        bn::sound_items::click1.play();
        _set_return_top_cursor(!_return_top_val);
    }
    else if (bn::keypad::left_pressed()) {
        bn::sound_items::click1.play();
        _set_return_top_cursor(!_return_top_val);
    }

    if (bn::keypad::a_pressed()) {
        bn::sound_items::click1.play();
        if (_return_top_val) {
            // change scene to TOPMENU
            bn::music::stop();
            next_scene = ag::scene::type::TOPMENU;
            set_stat(scene::stat::DONE);
        }
        else {
            // return to game
            _ctrl_mode = _prev_ctrl_mode;
            _cursor.set_enable(true);
            _set_camera(_cursor.index().x(),_cursor.index().y());
        }
    }
}

void game::_set_camera(int x, int y) {
    int camera_x = 8;
    //if (x < 0) { camera_x = -2*16 + 8; }
    //else if (x > 14) { camera_x = 2*16 + 8; }
    BN_ASSERT((0 <= x) && (x <= 14), "Invalid x index");

    int camera_y = 0;
    if (y < 3) { camera_y = -2*16; }
    else if (y > 10) { camera_y = 3*16; }

    _camera.set_position(camera_x,camera_y);
}

void game::_set_movable(int x, int y) {
    int x0 = x;
    int y0 = y;

    // UP
    bool up_enable = false;
    if (y0 != 0) {
        for (int y_idx = y0-1; y_idx >= 0; y_idx--) {
            if (!up_enable) {
                if (_feld_stat[y_idx*AG_FELD_X_SIZE + x0] == 0xFF) {
                    up_enable = true;
                }
                else {
                    // unmovable
                    break;
                }
            }
            else {
                if (_feld_stat[y_idx*AG_FELD_X_SIZE + x0] != 0xFF) {
                    _movable[(int)ag::directions::UP].set_x(x0);
                    _movable[(int)ag::directions::UP].set_y(y_idx + 1);
                    break;
                }
            }
        }
    }

    if (up_enable) {
        _cursor.set_enable(ag::directions::UP, true);
    }
    else {
        _movable[(int)ag::directions::UP].set_x(AG_UNINITIALIZED);
        _movable[(int)ag::directions::UP].set_y(AG_UNINITIALIZED);
    }

    // DOWN
    bool down_enable = false;
    if (y0 != (AG_FELD_Y_SIZE-1)) {
        for (int y_idx = y0+1; y_idx < AG_FELD_X_SIZE; y_idx++) {
            if (!down_enable) {
                if (_feld_stat[y_idx*AG_FELD_X_SIZE + x0] == 0xFF) {
                    down_enable = true;
                }
                else {
                    // unmovable
                    break;
                }
            }
            else {
                if (_feld_stat[y_idx*AG_FELD_X_SIZE + x0] != 0xFF) {
                    _movable[(int)ag::directions::DOWN].set_x(x0);
                    _movable[(int)ag::directions::DOWN].set_y(y_idx - 1);
                    break;
                }
            }
        }
    }

    if (down_enable) {
        _cursor.set_enable(ag::directions::DOWN, true);
    }
    else {
        _movable[(int)ag::directions::DOWN].set_x(AG_UNINITIALIZED);
        _movable[(int)ag::directions::DOWN].set_y(AG_UNINITIALIZED);
    }

    // RIGHT
    bool right_enable = false;
    if (x0 != (AG_FELD_X_SIZE - 1)) {
        for (int x_idx = x0+1; x_idx < AG_FELD_X_SIZE; x_idx++) {
            if (!right_enable) {
                if (_feld_stat[y0*AG_FELD_X_SIZE + x_idx] == 0xFF) {
                    right_enable = true;
                }
                else {
                    // unmovable
                    break;
                }
            }
            else {
                if (_feld_stat[y0*AG_FELD_X_SIZE + x_idx] != 0xFF) {
                    _movable[(int)ag::directions::RIGHT].set_x(x_idx - 1);
                    _movable[(int)ag::directions::RIGHT].set_y(y0);
                    break;
                }
            }
        }
    }

    if (right_enable) {
        _cursor.set_enable(ag::directions::RIGHT, true);
    }
    else {
        _movable[(int)ag::directions::RIGHT].set_x(AG_UNINITIALIZED);
        _movable[(int)ag::directions::RIGHT].set_y(AG_UNINITIALIZED);
    }

    // LEFT
    bool left_enable = false;
    if (x0 != 0) {
        for (int x_idx = x0-1; x_idx >= 0; x_idx--) {
            if (!left_enable) {
                if (_feld_stat[y0*AG_FELD_X_SIZE + x_idx] == 0xFF) {
                    left_enable = true;
                }
                else {
                    // unmovable
                    break;
                }
            }
            else {
                if (_feld_stat[y0*AG_FELD_X_SIZE + x_idx] != 0xFF) {
                    _movable[(int)ag::directions::LEFT].set_x(x_idx + 1);
                    _movable[(int)ag::directions::LEFT].set_y(y0);
                    break;
                }
            }
        }
    }

    if (left_enable) {
        _cursor.set_enable(ag::directions::LEFT, true);
    }
    else {
        _movable[(int)ag::directions::LEFT].set_x(AG_UNINITIALIZED);
        _movable[(int)ag::directions::LEFT].set_y(AG_UNINITIALIZED);
    }
}

void game::_set_return_top_cursor(bool yes) {
    if (yes) {
        _return_top_cursor.set_x(255-19*8);
    }
    else {
        _return_top_cursor.set_x(255-9*8);
    }
    _return_top_val = yes;
}

void game::_check_mole_completed() {
    // skip to first atom
    int start_m_idx = AG_UNINITIALIZED;
    int row_idx = 0;
    for (int m_idx = 0; m_idx < _mole.size(); m_idx++) {
        int val = _mole[m_idx].id;

        // first available atom
        if (val != 0xFF) {
            start_m_idx = m_idx;
            break;
        }

        if ((m_idx % _mole_width) == (_mole_width-1)) {
            row_idx++;
        }
    }

    BN_ASSERT(start_m_idx >= 0, "Invalid _mole[] data");

    // search atom in _feld_stat[]
    bool check_start = false;
    int start_x_idx = AG_UNINITIALIZED;
    int start_y_idx = AG_UNINITIALIZED;
    int x_idx, y_idx;
    for (y_idx = 0; y_idx < AG_FELD_Y_SIZE; y_idx++) {
        for (x_idx = 0; x_idx < AG_FELD_X_SIZE; x_idx++) {
            int index = _feld_stat[y_idx*AG_FELD_X_SIZE + x_idx];
            if ((0 <= index) && (index < 32)) {
                if (_atom[index]->atom_t() == _mole[start_m_idx]) {
                    check_start = true;
                    start_x_idx = x_idx;
                    start_y_idx = y_idx;
                    break;
                }
            }
            else {
                // continue;
            }
        }
        if (check_start) { break; }
    }

    BN_ASSERT(check_start == true, "Invalid _feld_stat[] data");
    BN_ASSERT((start_x_idx != AG_UNINITIALIZED) && (start_y_idx != AG_UNINITIALIZED), "Invalid start_*_idx");

    // compare _feld_stat[] to _mole[]
    bool not_completed = false;
    //x_idx = start_x_idx;
    //y_idx = start_y_idx;
    row_idx = 0;
    int m_idx = start_m_idx;
    while (m_idx < _mole.size()) {
        int index = _feld_stat[y_idx*AG_FELD_X_SIZE + x_idx];
        // found atom
        if ((0 <= index) && (index < 32)) {
            if (_mole[m_idx].id == 0xFF) {
                not_completed = true;
            }
            else if (_atom[index]->atom_t() == _mole[m_idx]) {
                // continue;
                m_idx++;
                x_idx++;
            }
            else {
                not_completed = true;
            }
        }
        // found empty or wall
        else {
            if (_mole[m_idx].id == 0xFF) {
                // continue;
                m_idx++;
                x_idx++;
            }
            else {
                not_completed = true;
            }
        }

        if (not_completed == true) {
            // loop finish
            break;
        }

        // next line
        if ((m_idx % _mole_width) == 0) {
            row_idx++;
            y_idx = start_y_idx + row_idx;
            x_idx -= _mole_width;
        }
    }

    _mole_completed = not_completed ? false : true;
}

}
