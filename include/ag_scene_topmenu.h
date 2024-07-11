#ifndef AG_SCENE_TOPMENU_H
#define AG_SCENE_TOPMENU_H

#include "bn_core.h"
#include "bn_fixed.h"
#include "bn_vector.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_music_actions.h"
#include "bn_keypad.h"

#include "bn_regular_bg_items_title240x160.h"
#include "common_variable_8x16_sprite_font.h"
#include "bn_sprite_items_font_palette.h"
//#include "bn_music_items.h"
#include "bn_sound_items.h"

#include "ag_common.h"
#include "ag_scene.h"

namespace ag {

class topmenu : public scene {
public:
    topmenu();
    ~topmenu() = default;
    void update();

private:
    bn::regular_bg_ptr _background;
    bn::sprite_text_generator _text_generator;
    bn::vector<bn::sprite_ptr, 16> _text_sprites;
};

}

#endif
