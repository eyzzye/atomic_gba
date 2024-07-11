#ifndef AG_SCENE_LEVEL_MENU_H
#define AG_SCENE_LEVEL_MENU_H

#include "bn_core.h"
#include "bn_fixed.h"
#include "bn_vector.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_music_actions.h"
#include "bn_keypad.h"
#include "bn_memory.h"

#include "bn_regular_bg_items_level_menu.h"
#include "bn_sprite_items_digit_numbers.h"
//#include "bn_music_items.h"
#include "bn_sound_items.h"

#include "ag_common.h"
#include "ag_scene.h"

namespace ag {

class level_menu : public scene {
public:
    level_menu();
    ~level_menu() = default;
    void update();

private:
    bn::regular_bg_ptr _background;
    bn::unique_ptr<bn::sprite_ptr> _sprite_digit_num[2];
    bn::sprite_ptr _sprite_cursor;

    int _digit_num[2];
    int _cursor_index;

    void _update_number(int index); // 0: upper, 1: lower
};

}

#endif
