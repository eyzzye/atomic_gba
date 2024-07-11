#ifndef AG_SCENE_GAME_H
#define AG_SCENE_GAME_H

#include "bn_core.h"
#include "bn_fixed.h"
#include "bn_vector.h"
#include "bn_string.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_text_generator.h"
#include "bn_music_actions.h"
#include "bn_camera_actions.h"
#include "bn_keypad.h"
#include "bn_memory.h"

#include "bn_regular_bg_items_bg_tiles.h"
#include "bn_sprite_items_atomic.h"
#include "bn_sprite_items_atomic_palette1.h"
#include "common_variable_8x16_sprite_font.h"
#include "bn_sprite_items_font_palette.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"

#include "ag_common.h"
#include "ag_scene.h"
#include "ag_bg_map_manager.h"
#include "ag_atom_t.h"
#include "ag_atom.h"
#include "ag_cursor.h"

namespace ag {

class game : public scene {
public:
    enum class ctrl_mode {
        CURSOR_MOVE,
        ATOM_MOVE,
        RETURN_TOP,
        DISABLE
    };

    game();
    ~game();
    void update();

private:
    // control status
    ctrl_mode _ctrl_mode;
    ctrl_mode _prev_ctrl_mode;
    int _key_wait_time;

    // game status
    int _current_level_id;
    int _current_atom;
    int _feld_stat[AG_FELD_X_SIZE * AG_FELD_Y_SIZE];
    bn::point _movable[4];

    // atom data
    bn::vector<ag::atom_t,32> _atom_list;
    bn::vector<ag::atom_t,15*15> _mole;
    int _mole_width;

    // game complete
    bool _mole_completed;
    int _mole_blink_time;
    bool _mole_blink_on;

    // background/text generator/camera
    bn::unique_ptr<bn::regular_bg_ptr> _bg_ptr;
    bn::sprite_text_generator _text_generator;
    bn::vector<bn::sprite_ptr, 36> _text_sprites;
    bn::camera_ptr _camera;

    // game objects
    ag::cursor _cursor;
    bn::unique_ptr<ag::atom> _mole_atom[32];
    bn::unique_ptr<ag::atom> _atom[32];
    int _atom_count;

    // return top menu
    bn::sprite_ptr _return_top_cursor;
    bool _return_top_val;

    void _init();
    void _update();

    void _init_bg_map();
    void _init_atom();
    void _init_mole();
    void _init_title();
    void _init_return_top();

    void _ctrl_cursor_move();
    void _ctrl_atom_move();
    void _ctrl_return_top();

    void _set_camera(int x, int y);
    void _set_movable(int x, int y);
    void _set_return_top_cursor(bool yes);
    void _check_mole_completed();
};

}

#endif
