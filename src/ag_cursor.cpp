#include "ag_cursor.h"

namespace ag
{

void cursor::set_index(int x, int y) {
    // pos_x = (x - (AG_FELD_X_SIZE/2)) * TileSize(2*8) + (TileSize/2)
    bn::fixed_point pos((x-7)*2*8 + 8, (y-7)*2*8 + 8);
    _sprite.set_position(pos);

    _sprite_arrow[(int)ag::directions::UP]->set_x(pos.x());
    _sprite_arrow[(int)ag::directions::UP]->set_y(pos.y()-16);

    _sprite_arrow[(int)ag::directions::DOWN]->set_x(pos.x());
    _sprite_arrow[(int)ag::directions::DOWN]->set_y(pos.y()+16);

    _sprite_arrow[(int)ag::directions::RIGHT]->set_x(pos.x()+16);
    _sprite_arrow[(int)ag::directions::RIGHT]->set_y(pos.y());

    _sprite_arrow[(int)ag::directions::LEFT]->set_x(pos.x()-16);
    _sprite_arrow[(int)ag::directions::LEFT]->set_y(pos.y());

    _x_idx = x;
    _y_idx = y;
}

void cursor::set_enable(bool on) {
    if (on) {
        _sprite.set_visible(true);
        for (int i = 0; i < 4; i++) {
            if (_arrow_enable[i] == true) {
                _sprite_arrow[i]->set_visible(true);
            }
        }
    }
    else {
        _sprite.set_visible(false);
        for (int i = 0; i < 4; i++) {
            _sprite_arrow[i]->set_visible(false);
        }
    }
}

void cursor::set_enable(ag::directions direct, bool on) {
    _arrow_enable[(int)direct] = on;
    _sprite_arrow[(int)direct]->set_visible(on);
}

void cursor::set_enable_arrows(bool on) {
    for (int i = 0; i < 4; i++) {
        _arrow_enable[i] = on;
        _sprite_arrow[i]->set_visible(on);
    }
}

}

