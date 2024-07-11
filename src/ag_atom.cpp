#include "ag_atom.h"

namespace ag
{

atom::atom(int id, int conn_flg):
    object(ag::object::type::ATOM, id),
    _graphics_index(0),
    _x_idx(0),
    _y_idx(0),
    _x_offset(0),
    _y_offset(0)
{
    _atom.id = id;
    _atom.conn_flg = conn_flg;

    _set_sprite(id);
    _set_sprite_conn(conn_flg);
}

void atom::set_index(int x, int y) {
    // pos_x = (x - (AG_FELD_X_SIZE/2)) * TileSize(2*8) + (TileSize/2) + offset
    bn::fixed_point pos((x-7)*2*8 +8 +_x_offset, (y-7)*2*8 +8 +_y_offset);
    _sprite_ptr->set_position(pos);
    for (int i = 0; i < 4; i++) {
        if (_sprite_conn_ptr[i].get() != nullptr) {
            // tweak diagonal
            if (i == 0) { // b
                bn::fixed_point b_pos(pos.x()+1,pos.y()-1);
                _sprite_conn_ptr[i]->set_position(b_pos);
            }
            else if (i == 1) { // d
                bn::fixed_point d_pos(pos.x()+1,pos.y()+1);
                _sprite_conn_ptr[i]->set_position(d_pos);
            }
            else if (i == 2) { // f
                bn::fixed_point f_pos(pos.x()-1,pos.y()+1);
                _sprite_conn_ptr[i]->set_position(f_pos);
            }
            else if (i == 3) { // h
                bn::fixed_point h_pos(pos.x()-1,pos.y()-1);
                _sprite_conn_ptr[i]->set_position(h_pos);
            }
        }
    }
    _x_idx = x;
    _y_idx = y;
}

void atom::set_enable(bool on) {
    if (on) {
        _sprite_ptr->set_visible(true);

        for (int i = 0; i < 4; i++) {
            if (_sprite_conn_ptr[i].get() != nullptr) {
                _sprite_conn_ptr[i]->set_visible(true);
            }
        }
    }
    else {
        _sprite_ptr->set_visible(false);

        for (int i = 0; i < 4; i++) {
            if (_sprite_conn_ptr[i].get() != nullptr) {
                _sprite_conn_ptr[i]->set_visible(false);
            }
        }
    }
}

void atom::set_palette(const bn::sprite_palette_item& palette_item) {
    _sprite_ptr->set_palette(palette_item);

    for (int i = 0; i < 4; i++) {
        if (_sprite_conn_ptr[i].get() != nullptr) {
            _sprite_conn_ptr[i]->set_palette(palette_item);
        }
    }
}

void atom::_set_sprite(int id) {
    switch (id) {
    case (int)ag::object::atom_id::H:
        _graphics_index = 0;
        break;
    case (int)ag::object::atom_id::C:
        _graphics_index = 1;
        break;
    case (int)ag::object::atom_id::O:
        _graphics_index = 2;
        break;
    case (int)ag::object::atom_id::N:
        _graphics_index = 3;
        break;
    case (int)ag::object::atom_id::S:
        _graphics_index = 4;
        break;
    case (int)ag::object::atom_id::F:
        _graphics_index = 5;
        break;
    case (int)ag::object::atom_id::Cl:
        _graphics_index = 6;
        break;
    case (int)ag::object::atom_id::Br:
        _graphics_index = 7;
        break;
    case (int)ag::object::atom_id::P:
        _graphics_index = 8;
        break;
    case (int)ag::object::atom_id::J:
        _graphics_index = 9;
        break;
    case (int)ag::object::atom_id::Crystal:
        _graphics_index = 10;
        break;
    case (int)ag::object::atom_id::HorizontalConn:
        _graphics_index = 28;
        break;
    case (int)ag::object::atom_id::SlashConn:
        _graphics_index = 29;
        break;
    case (int)ag::object::atom_id::VerticalConn:
        _graphics_index = 27;
        break;
    case (int)ag::object::atom_id::BackSlashConn:
        _graphics_index = 30;
        break;
    default:
        BN_ERROR("Invalid atom_id:", id);
        break;
    }

    _sprite_ptr.reset(new bn::sprite_ptr(bn::sprite_items::atomic.create_sprite(0,0,_graphics_index)));
}

void atom::_set_sprite_conn(int conn_flg) {
    for (int i = 0; i < 4; i++) {
        _sprite_conn_ptr[i].reset(nullptr);
    }

    // single
    if (conn_flg & (0x0001 << 0)) { // a
        _marge_sprite(11);
    }
    if (conn_flg & (0x0001 << 1)) { // b
        _sprite_conn_ptr[0].reset(new bn::sprite_ptr(bn::sprite_items::atomic.create_sprite(0,0,15)));
    }
    if (conn_flg & (0x0001 << 2)) { // c
        _marge_sprite(13);
    }
    if (conn_flg & (0x0001 << 3)) { // d
        _sprite_conn_ptr[1].reset(new bn::sprite_ptr(bn::sprite_items::atomic.create_sprite(0,0,16)));
    }
    if (conn_flg & (0x0001 << 4)) { // e
        _marge_sprite(12);
    }
    if (conn_flg & (0x0001 << 5)) { // f
        _sprite_conn_ptr[2].reset(new bn::sprite_ptr(bn::sprite_items::atomic.create_sprite(0,0,17)));
    }
    if (conn_flg & (0x0001 << 6)) { // g
        _marge_sprite(14);
    }
    if (conn_flg & (0x0001 << 7)) { // h
        _sprite_conn_ptr[3].reset(new bn::sprite_ptr(bn::sprite_items::atomic.create_sprite(0,0,18)));
    }

    // double
    if (conn_flg & (0x0100 << 0)) { // A
        _marge_sprite(19);
    }
    if (conn_flg & (0x0100 << 1)) { // B
        _marge_sprite(21);
    }
    if (conn_flg & (0x0100 << 2)) { // C
        _marge_sprite(20);
    }
    if (conn_flg & (0x0100 << 3)) { // D
        _marge_sprite(22);
    }

    // triple
    if (conn_flg & (0x0100 << 4)) { // E
        _marge_sprite(23);
    }
    if (conn_flg & (0x0100 << 5)) { // F
        _marge_sprite(25);
    }
    if (conn_flg & (0x0100 << 6)) { // G
        _marge_sprite(24);
    }
    if (conn_flg & (0x0100 << 7)) { // H
        _marge_sprite(26);
    }
}

void atom::_marge_sprite(int graphics_index) {
    // src sprite
    _sprite_tmp_ptr.reset(new bn::sprite_ptr(
        bn::sprite_items::atomic.create_sprite(0,0,graphics_index)));
    const bn::sprite_tiles_ptr src_core_ptr = _sprite_tmp_ptr->tiles();
    bn::optional<bn::span<const bn::tile>> src_tiles = src_core_ptr.tiles_ref();

    // dst sprite
    bn::bpp_mode bpp = bn::sprite_items::atomic.tiles_item().bpp();
    const bn::sprite_tiles_ptr dst_core_ptr = _sprite_ptr->tiles();
    bn::optional<bn::span<const bn::tile>> dst_tiles = dst_core_ptr.tiles_ref();

    // marge _sprite_tmp_ptr to _sprite_ptr
    bn::span<const bn::tile> *src = src_tiles.get();
    bn::span<const bn::tile> *dst = dst_tiles.get();
    int new_tile_index = _tile_list.size();
    for (int i = 0; i < 4; i++) {
        bn::tile tmp_tile;
        for (int tile_h = 0; tile_h < 8; tile_h++) {
            tmp_tile.data[tile_h] = (*dst)[i].data[tile_h] | (*src)[i].data[tile_h];
        }
        _tile_list.push_back(tmp_tile);
    }

    // set new_tiles
    bn::span<bn::tile> new_span_tiles(&_tile_list[new_tile_index],4);
    bn::sprite_tiles_item new_tiles(new_span_tiles,bpp); 
    _sprite_ptr->set_tiles(new_tiles);
    _sprite_tmp_ptr.reset();
}

}

