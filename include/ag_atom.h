#ifndef AG_ATOM_H
#define AG_ATOM_H

#include "bn_vector.h"
#include "bn_optional.h"
#include "bn_span.h"
#include "bn_tile.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_camera_ptr.h"
#include "bn_memory.h"

#include "bn_sprite_items_atomic.h"

#include "ag_common.h"
#include "ag_object.h"
#include "ag_atom_t.h"

namespace ag {

class atom : public object {
public:
    atom(int id, int conn_flg);

    atom(ag::atom_t& atom_data):
        atom(atom_data.id, atom_data.conn_flg)
    {
    }

    void set_camera(bn::camera_ptr& camera) {
        _sprite_ptr->set_camera(camera);

        for (int i = 0; i < 4; i++) {
            if (_sprite_conn_ptr[i].get() != nullptr) {
                _sprite_conn_ptr[i]->set_camera(camera);
            }
        }
    }

    ag::atom_t& atom_t(){ return _atom; }
    bn::point index() { bn::point p(_x_idx,_y_idx); return p; }
    void set_index(int x, int y);
    void set_offset(int x, int y) { _x_offset = x; _y_offset = y; }
    void set_enable(bool on);
    void set_palette(const bn::sprite_palette_item& palette_item);

private:
    bn::unique_ptr<bn::sprite_ptr> _sprite_ptr;
    bn::unique_ptr<bn::sprite_ptr> _sprite_conn_ptr[4];
    bn::unique_ptr<bn::sprite_ptr> _sprite_tmp_ptr;
    bn::vector<bn::tile,4*4> _tile_list;

    ag::atom_t _atom;
    int _graphics_index;
    int _x_idx;
    int _y_idx;
    int _x_offset;
    int _y_offset;

    void _set_sprite(int id);
    void _set_sprite_conn(int conn_flg);
    void _marge_sprite(int graphics_index);
};

}
#endif
