#include "bn_core.h"
#include "bn_memory.h"

#include "ag_common.h"
#include "ag_scene.h"
#include "ag_scene_topmenu.h"
#include "ag_scene_level_menu.h"
#include "ag_scene_game.h"

//
// global variables
//
ag::scene::type next_scene = ag::scene::type::NONE;
bn::fixed g_sound_effect_wait = 0;
int g_next_level = AG_UNINITIALIZED;

int main()
{
    bn::unique_ptr<ag::scene> current_scene;
    const bn::fixed change_scene_wait = 0.5f;
    bn::fixed g_wait_time = 0.0f;

    // init butano engine
    bn::core::init();
    
    current_scene.reset(new ag::topmenu());

    while(true)
    {
        if (current_scene->get_stat() == ag::scene::stat::ACTIVE) {
            current_scene->update();
        }

        if (next_scene != ag::scene::type::NONE) {
            bool result = false;

            // finish current_scene
            current_scene.reset();

            // wait a little time
            while (g_wait_time < change_scene_wait) {
                bn::core::update();
                g_wait_time += 0.016f;
            }
            g_wait_time = 0.0f; // clear

            switch (next_scene) {
            case ag::scene::type::TOPMENU:
                current_scene.reset(new ag::topmenu());
                result = true;
                break;
            case ag::scene::type::LEVEL_MENU:
                current_scene.reset(new ag::level_menu());
                result = true;
                break;
            case ag::scene::type::GAME:
                current_scene.reset(new ag::game());
                result = true;
                break;
            default:
                BN_ERROR("main(): Invalid next_scene ", (int)next_scene);
                break;
            }

            if (result && (current_scene->get_stat() == ag::scene::stat::ACTIVE)) {
                next_scene = ag::scene::type::NONE;
            }
            else {
                BN_ERROR("main(): Invalid next_scene");
                next_scene = ag::scene::type::NONE;
            }
        }
    }
}
