#ifndef AG_CURSOR_H
#define AG_CURSOR_H

#include "bn_sprite_ptr.h"
#include "bn_camera_ptr.h"
#include "bn_memory.h"

#include "bn_sprite_items_atomic.h"

#include "ag_common.h"
#include "ag_object.h"

namespace ag {

class cursor : public object {
public:
    cursor():
        object(ag::object::type::CURSOR),
        _sprite(bn::sprite_items::atomic.create_sprite(0,0,35)),
        _x_idx(0),
        _y_idx(0)
    {
        // set _sprite_arrow
        _sprite_arrow[(int)ag::directions::UP].reset(new bn::sprite_ptr(
            bn::sprite_items::atomic.create_sprite(0,-16,31)));
        _sprite_arrow[(int)ag::directions::DOWN].reset(new bn::sprite_ptr(
            bn::sprite_items::atomic.create_sprite(0,16,32)));
        _sprite_arrow[(int)ag::directions::RIGHT].reset(new bn::sprite_ptr(
            bn::sprite_items::atomic.create_sprite(16,0,33)));
        _sprite_arrow[(int)ag::directions::LEFT].reset(new bn::sprite_ptr(
            bn::sprite_items::atomic.create_sprite(-16,0,34)));

        // set z order
        _sprite.set_z_order(AG_Z_ORDER_CURSOR);
        for (int i = 0; i < 4; i++) {
            _sprite_arrow[i]->set_z_order(AG_Z_ORDER_CURSOR);
        }

        // set _arrow_enable
        set_enable_arrows(false);
    }

    void set_camera(bn::camera_ptr& camera) {
        _sprite.set_camera(camera);
        for (int i = 0; i < 4; i++) {
            _sprite_arrow[i]->set_camera(camera);
        }
    }

    bn::point index() { bn::point p(_x_idx,_y_idx); return p; }
    void set_index(int x, int y);
    void set_enable(bool on);
    void set_enable(ag::directions direct, bool on);
    void set_enable_arrows(bool on);

private:
    bn::sprite_ptr _sprite;
    bn::unique_ptr<bn::sprite_ptr> _sprite_arrow[4];
    int _x_idx;
    int _y_idx;
    bool _arrow_enable[4];
};

}
#endif
