#include "ag_scene_level_menu.h"

// extern variables
extern ag::scene::type next_scene;
extern int g_next_level;

namespace ag {

level_menu::level_menu():
    scene(scene::type::LEVEL_MENU),
    _background(bn::regular_bg_items::level_menu.create_bg(0, 0)),
    _sprite_cursor(bn::sprite_items::digit_numbers.create_sprite(48, 0, 12)),
    _cursor_index(1)
{
    //bn::music_items::music001.play(0.5);

    // set _sprite_digit_number[]
    _digit_num[0] = g_next_level / 10;
    _digit_num[1] = g_next_level % 10;
    _sprite_digit_num[0].reset(new bn::sprite_ptr(
        bn::sprite_items::digit_numbers.create_sprite(32,0,_digit_num[0])));
    _sprite_digit_num[1].reset(new bn::sprite_ptr(
        bn::sprite_items::digit_numbers.create_sprite(48,0,_digit_num[1])));

    set_stat(scene::stat::ACTIVE);
}

void level_menu::update() {
    if (bn::keypad::start_pressed()) {
        //bn::music::stop();
        bn::sound_items::click1.play();
        g_next_level = _digit_num[0]*10 + _digit_num[1];
        next_scene = ag::scene::type::GAME;
        set_stat(scene::stat::DONE);
    }

    // move cursor
    if (bn::keypad::right_pressed() && (_cursor_index == 0)) {
        _cursor_index = 1;
        _sprite_cursor.set_x(48);
    }
    if (bn::keypad::left_pressed() && (_cursor_index == 1)) {
        _cursor_index = 0;
        _sprite_cursor.set_x(32);
    }

    // select number
    bool dirt_upper = false;
    bool dirt_lower = false;
    if (bn::keypad::up_pressed()) {
       // upper number 
       if (_cursor_index == 0) {
            if (_digit_num[0] < 8) { // range(0,8)
                _digit_num[0] += 1;
                dirt_upper = true;
            }

            // correct lower
            if (dirt_upper && (_digit_num[0] == 8)) {
                if (3 < _digit_num[1]) {
                    _digit_num[1] = 3;
                    dirt_lower = true;
                }
            }
        }
        // lower number
        else {
            if (_digit_num[0] == 8) {
                if (_digit_num[1] < 3) { // range(0,3)
                    _digit_num[1] += 1;
                    dirt_lower = true;
                }
            }
            else {
                if (_digit_num[1] < 9) { // range(0,9)
                    _digit_num[1] += 1;
                    dirt_lower = true;
                }
            }
        }
    }
    if (bn::keypad::down_pressed()) {
        // upper number
        if (_cursor_index == 0) {
            if (0 < _digit_num[0]) { // range(0,8)
                _digit_num[0] -= 1;
                dirt_upper = true;
            }

            // correct lower
            if (dirt_upper && (_digit_num[0] == 0)) {
                if (_digit_num[1] < 1) {
                    _digit_num[1] = 1;
                    dirt_lower = true;
                }
            }
        }
        // lower number
        else {
            if (_digit_num[0] == 0) {
                if (1 < _digit_num[1]) { // range(1,9)
                    _digit_num[1] -= 1;
                    dirt_lower = true;
                }
            }
            else {
                if (0 < _digit_num[1]) { // range(0,9)
                    _digit_num[1] -= 1;
                    dirt_lower = true;
                }
            }
        }
    }

    if (dirt_upper) {
        _update_number(0);
    }
    if (dirt_lower) {
        _update_number(1);
    }
    if (dirt_upper || dirt_lower) {
        bn::sound_items::click1.play();
    }

    bn::core::update();
}

void level_menu::_update_number(int index) {
    BN_ASSERT((0 <= index) && (index <= 1),"Invalid index:", index);
    BN_ASSERT((0 <= _digit_num[index]) && (_digit_num[index] <= 9),"Invalid _digit_num[]:", _digit_num[index]);

    _sprite_digit_num[index]->set_tiles(
        bn::sprite_items::digit_numbers.tiles_item().create_tiles(_digit_num[index]));
}

}
