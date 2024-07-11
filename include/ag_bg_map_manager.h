#ifndef AG_BG_MAP_MANAGER_H
#define AG_BG_MAP_MANAGER_H

#include "bn_vector.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_regular_bg_map_cell.h"
#include "bn_regular_bg_map_cell_info.h"
#include "bn_regular_bg_map_item.h"
#include "bn_bg_palette_item.h"
#include "bn_memory.h"
#include "bn_camera_ptr.h"

#include "ag_common.h"
#include "ag_array_t.h"

namespace ag::bg_map_manager {

struct init_data_t {
    int x;
    int y;
    int tile_index;
};

struct bg_map_items_t {
    #define BG_MAP_MANAGER_CELL_COLS (64)
    #define BG_MAP_MANAGER_CELL_ROWS (64)
    bn::regular_bg_map_cell cells[BG_MAP_MANAGER_CELL_COLS * BG_MAP_MANAGER_CELL_ROWS];
    bn::regular_bg_map_item map_item;

    bg_map_items_t():
        map_item(cells[0], bn::size(BG_MAP_MANAGER_CELL_COLS, BG_MAP_MANAGER_CELL_ROWS))
    {
        bn::memory::clear(BG_MAP_MANAGER_CELL_COLS * BG_MAP_MANAGER_CELL_ROWS, cells[0]);
    }
};

class bg_map {
public:
    bg_map(const bn::regular_bg_tiles_item& tiles_item, const bn::bg_palette_item& palette_item);

    void init(struct array_t<struct init_data_t>* init_list);
    void set_camera(bn::camera_ptr& camera) { _bg_ptr->set_camera(camera); }
    void set_tile(int x_idx, int y_idx, int tile_idx);
    void update();

private:
    struct bg_map_items_t _bg_map_items;
    bn::unique_ptr<bn::regular_bg_ptr> _bg_ptr;
    bn::unique_ptr<bn::regular_bg_map_ptr> _bg_map_ptr;
    bool _map_dirt;
};

// extern functions
void create_bg_map(const bn::regular_bg_tiles_item& tiles_item, const bn::bg_palette_item& palette_item);
void set_camera(bn::camera_ptr& camera);
void init_bg_map(struct array_t<struct init_data_t>* init_list);
void set_tile(int x_idx, int y_idx, int tile_idx);
void update();
void destroy_bg_map();

}
#endif
