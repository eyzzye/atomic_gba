#include "ag_scene_topmenu.h"

// extern variables
extern ag::scene::type next_scene;
extern int g_next_level;

namespace ag {

topmenu::topmenu():
    scene(scene::type::TOPMENU),
    _background(bn::regular_bg_items::title240x160.create_bg(0, 0)),
    _text_generator(common::variable_8x16_sprite_font,
                    bn::sprite_items::font_palette.palette_item())
{
    //bn::music_items::music001.play(0.5);

    _text_generator.set_center_alignment();
    _text_generator.generate(0, 32, "PUSH START", _text_sprites);

    set_stat(scene::stat::ACTIVE);
}

void topmenu::update() {
    if (bn::keypad::start_pressed()) {
        //bn::music::stop();
        g_next_level = 1;
        bn::sound_items::click1.play();
        next_scene = ag::scene::type::LEVEL_MENU;
        set_stat(scene::stat::DONE);
    }

    bn::core::update();
}

}
