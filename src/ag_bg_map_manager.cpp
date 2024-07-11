#include "ag_bg_map_manager.h"

namespace ag::bg_map_manager
{

class static_data {
public:
    bn::unique_ptr<bg_map> bg_map_ptr;
};

BN_DATA_EWRAM static_data data;

bg_map::bg_map(const bn::regular_bg_tiles_item& tiles_item_ref, const bn::bg_palette_item& palette_item):
    _bg_map_items(),
    _bg_ptr(nullptr),
    _bg_map_ptr(nullptr),
    _map_dirt(false)
{
    bn::regular_bg_item bg_item(tiles_item_ref, palette_item, _bg_map_items.map_item);
    _bg_ptr.reset(new bn::regular_bg_ptr(bg_item.create_bg(0, 0)));
    _bg_map_ptr.reset(new bn::regular_bg_map_ptr(_bg_ptr->map()));
}

void bg_map::init(struct array_t<struct init_data_t>* init_list) {
    for (int i = 0; i < (int)init_list->size; i++) {
        set_tile(init_list->data[i].x,
                 init_list->data[i].y,
                 init_list->data[i].tile_index);
    }

    // if (list_size == 0)
    _map_dirt = true;
}

void bg_map::set_tile(int x_idx, int y_idx, int tile_idx) {
    int index = _bg_map_items.map_item.cell_index(x_idx,y_idx);
    _bg_map_items.cells[index] = tile_idx;
    _map_dirt = true;
}

void bg_map::update() {
    if (_map_dirt) {
        _bg_map_ptr->reload_cells_ref();
        _map_dirt = false;
    }
}

//
// extern functions
//
void create_bg_map(const bn::regular_bg_tiles_item& tiles_item, const bn::bg_palette_item& palette_item)
{
    data.bg_map_ptr.reset(new bg_map(tiles_item, palette_item));
}

void set_camera(bn::camera_ptr& camera) {
    data.bg_map_ptr->set_camera(camera);
}

void init_bg_map(struct array_t<struct init_data_t>* init_list) {
    data.bg_map_ptr->init(init_list);
}

void set_tile(int x_idx, int y_idx, int tile_idx) {
    data.bg_map_ptr->set_tile(x_idx, y_idx, tile_idx);
}

void update() {
    data.bg_map_ptr->update();
}

void destroy_bg_map() {
    data.bg_map_ptr.reset();
}

}

