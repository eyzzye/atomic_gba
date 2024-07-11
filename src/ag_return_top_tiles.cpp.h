#ifndef AG_RETURN_TOP_TILES_H
#define AG_RETURN_TOP_TILES_H

#include "ag_bg_tiles.h"
#include "ag_bg_map_manager.h"
#include "ag_array_t.h"

namespace ag {

struct return_top_static_data {
    // message
    struct ag::bg_map_manager::init_data_t return_top_msg_init_data[88] = {
        { (41 + 0    ), (1    ), MSG_TILE0_1},
        { (41 + 0 + 1), (1    ), MSG_TILE0_2},
        { (41 + 0    ), (1 + 1), MSG_TILE0_3},
        { (41 + 0 + 1), (1 + 1), MSG_TILE0_4},
        { (41 + 0    ), (1 + 2), MSG_TILE0_5},
        { (41 + 0 + 1), (1 + 2), MSG_TILE0_6},
        { (41 + 0    ), (1 + 3), MSG_TILE0_7},
        { (41 + 0 + 1), (1 + 3), MSG_TILE0_8},
        { (41 + 2    ), (1    ), MSG_TILE1_1},
        { (41 + 2 + 1), (1    ), MSG_TILE1_2},
        { (41 + 2    ), (1 + 1), MSG_TILE1_3},
        { (41 + 2 + 1), (1 + 1), MSG_TILE1_4},
        { (41 + 2    ), (1 + 2), MSG_TILE1_5},
        { (41 + 2 + 1), (1 + 2), MSG_TILE1_6},
        { (41 + 2    ), (1 + 3), MSG_TILE1_7},
        { (41 + 2 + 1), (1 + 3), MSG_TILE1_8},
        { (41 + 4    ), (1    ), MSG_TILE2_1},
        { (41 + 4 + 1), (1    ), MSG_TILE2_2},
        { (41 + 4    ), (1 + 1), MSG_TILE2_3},
        { (41 + 4 + 1), (1 + 1), MSG_TILE2_4},
        { (41 + 4    ), (1 + 2), MSG_TILE2_5},
        { (41 + 4 + 1), (1 + 2), MSG_TILE2_6},
        { (41 + 4    ), (1 + 3), MSG_TILE2_7},
        { (41 + 4 + 1), (1 + 3), MSG_TILE2_8},
        { (41 + 6    ), (1    ), MSG_TILE3_1},
        { (41 + 6 + 1), (1    ), MSG_TILE3_2},
        { (41 + 6    ), (1 + 1), MSG_TILE3_3},
        { (41 + 6 + 1), (1 + 1), MSG_TILE3_4},
        { (41 + 6    ), (1 + 2), MSG_TILE3_5},
        { (41 + 6 + 1), (1 + 2), MSG_TILE3_6},
        { (41 + 6    ), (1 + 3), MSG_TILE3_7},
        { (41 + 6 + 1), (1 + 3), MSG_TILE3_8},
        { (41 + 8    ), (1    ), MSG_TILE4_1},
        { (41 + 8 + 1), (1    ), MSG_TILE4_2},
        { (41 + 8    ), (1 + 1), MSG_TILE4_3},
        { (41 + 8 + 1), (1 + 1), MSG_TILE4_4},
        { (41 + 8    ), (1 + 2), MSG_TILE4_5},
        { (41 + 8 + 1), (1 + 2), MSG_TILE4_6},
        { (41 + 8    ), (1 + 3), MSG_TILE4_7},
        { (41 + 8 + 1), (1 + 3), MSG_TILE4_8},
        { (41 + 10    ), (1    ), MSG_TILE5_1},
        { (41 + 10 + 1), (1    ), MSG_TILE5_2},
        { (41 + 10    ), (1 + 1), MSG_TILE5_3},
        { (41 + 10 + 1), (1 + 1), MSG_TILE5_4},
        { (41 + 10    ), (1 + 2), MSG_TILE5_5},
        { (41 + 10 + 1), (1 + 2), MSG_TILE5_6},
        { (41 + 10    ), (1 + 3), MSG_TILE5_7},
        { (41 + 10 + 1), (1 + 3), MSG_TILE5_8},
        { (41 + 12    ), (1    ), MSG_TILE6_1},
        { (41 + 12 + 1), (1    ), MSG_TILE6_2},
        { (41 + 12    ), (1 + 1), MSG_TILE6_3},
        { (41 + 12 + 1), (1 + 1), MSG_TILE6_4},
        { (41 + 12    ), (1 + 2), MSG_TILE6_5},
        { (41 + 12 + 1), (1 + 2), MSG_TILE6_6},
        { (41 + 12    ), (1 + 3), MSG_TILE6_7},
        { (41 + 12 + 1), (1 + 3), MSG_TILE6_8},
        { (41 + 14    ), (1    ), MSG_TILE7_1},
        { (41 + 14 + 1), (1    ), MSG_TILE7_2},
        { (41 + 14    ), (1 + 1), MSG_TILE7_3},
        { (41 + 14 + 1), (1 + 1), MSG_TILE7_4},
        { (41 + 14    ), (1 + 2), MSG_TILE7_5},
        { (41 + 14 + 1), (1 + 2), MSG_TILE7_6},
        { (41 + 14    ), (1 + 3), MSG_TILE7_7},
        { (41 + 14 + 1), (1 + 3), MSG_TILE7_8},
        { (41 + 16    ), (1    ), MSG_TILE8_1},
        { (41 + 16 + 1), (1    ), MSG_TILE8_2},
        { (41 + 16    ), (1 + 1), MSG_TILE8_3},
        { (41 + 16 + 1), (1 + 1), MSG_TILE8_4},
        { (41 + 16    ), (1 + 2), MSG_TILE8_5},
        { (41 + 16 + 1), (1 + 2), MSG_TILE8_6},
        { (41 + 16    ), (1 + 3), MSG_TILE8_7},
        { (41 + 16 + 1), (1 + 3), MSG_TILE8_8},
        { (41 + 18    ), (1    ), MSG_TILE9_1},
        { (41 + 18 + 1), (1    ), MSG_TILE9_2},
        { (41 + 18    ), (1 + 1), MSG_TILE9_3},
        { (41 + 18 + 1), (1 + 1), MSG_TILE9_4},
        { (41 + 18    ), (1 + 2), MSG_TILE9_5},
        { (41 + 18 + 1), (1 + 2), MSG_TILE9_6},
        { (41 + 18    ), (1 + 3), MSG_TILE9_7},
        { (41 + 18 + 1), (1 + 3), MSG_TILE9_8},
        { (41 + 20    ), (1    ), MSG_TILE10_1},
        { (41 + 20 + 1), (1    ), MSG_TILE10_2},
        { (41 + 20    ), (1 + 1), MSG_TILE10_3},
        { (41 + 20 + 1), (1 + 1), MSG_TILE10_4},
        { (41 + 20    ), (1 + 2), MSG_TILE10_5},
        { (41 + 20 + 1), (1 + 2), MSG_TILE10_6},
        { (41 + 20    ), (1 + 3), MSG_TILE10_7},
        { (41 + 20 + 1), (1 + 3), MSG_TILE10_8},
    };
    ag::array_t<struct ag::bg_map_manager::init_data_t> return_top_msg_init_list = {
        sizeof(return_top_msg_init_data) / sizeof(return_top_msg_init_data[0]),
        return_top_msg_init_data
    };

    // yes
    struct ag::bg_map_manager::init_data_t return_top_yes_init_data[32] = {
        { (45 + 0    ), (7    ), YES_TILE0_1},
        { (45 + 0 + 1), (7    ), YES_TILE0_2},
        { (45 + 0    ), (7 + 1), YES_TILE0_3},
        { (45 + 0 + 1), (7 + 1), YES_TILE0_4},
        { (45 + 0    ), (7 + 2), YES_TILE0_5},
        { (45 + 0 + 1), (7 + 2), YES_TILE0_6},
        { (45 + 0    ), (7 + 3), YES_TILE0_7},
        { (45 + 0 + 1), (7 + 3), YES_TILE0_8},
        { (45 + 2    ), (7    ), YES_TILE1_1},
        { (45 + 2 + 1), (7    ), YES_TILE1_2},
        { (45 + 2    ), (7 + 1), YES_TILE1_3},
        { (45 + 2 + 1), (7 + 1), YES_TILE1_4},
        { (45 + 2    ), (7 + 2), YES_TILE1_5},
        { (45 + 2 + 1), (7 + 2), YES_TILE1_6},
        { (45 + 2    ), (7 + 3), YES_TILE1_7},
        { (45 + 2 + 1), (7 + 3), YES_TILE1_8},
        { (45 + 4    ), (7    ), YES_TILE2_1},
        { (45 + 4 + 1), (7    ), YES_TILE2_2},
        { (45 + 4    ), (7 + 1), YES_TILE2_3},
        { (45 + 4 + 1), (7 + 1), YES_TILE2_4},
        { (45 + 4    ), (7 + 2), YES_TILE2_5},
        { (45 + 4 + 1), (7 + 2), YES_TILE2_6},
        { (45 + 4    ), (7 + 3), YES_TILE2_7},
        { (45 + 4 + 1), (7 + 3), YES_TILE2_8},
    };
    ag::array_t<struct ag::bg_map_manager::init_data_t> return_top_yes_init_list = {
        sizeof(return_top_yes_init_data) / sizeof(return_top_yes_init_data[0]),
        return_top_yes_init_data
    };

    // no
    struct ag::bg_map_manager::init_data_t return_top_no_init_data[32] = {
        { (55 + 0    ), (7    ), NO_TILE0_1},
        { (55 + 0 + 1), (7    ), NO_TILE0_2},
        { (55 + 0    ), (7 + 1), NO_TILE0_3},
        { (55 + 0 + 1), (7 + 1), NO_TILE0_4},
        { (55 + 0    ), (7 + 2), NO_TILE0_5},
        { (55 + 0 + 1), (7 + 2), NO_TILE0_6},
        { (55 + 0    ), (7 + 3), NO_TILE0_7},
        { (55 + 0 + 1), (7 + 3), NO_TILE0_8},
        { (55 + 2    ), (7    ), NO_TILE1_1},
        { (55 + 2 + 1), (7    ), NO_TILE1_2},
        { (55 + 2    ), (7 + 1), NO_TILE1_3},
        { (55 + 2 + 1), (7 + 1), NO_TILE1_4},
        { (55 + 2    ), (7 + 2), NO_TILE1_5},
        { (55 + 2 + 1), (7 + 2), NO_TILE1_6},
        { (55 + 2    ), (7 + 3), NO_TILE1_7},
        { (55 + 2 + 1), (7 + 3), NO_TILE1_8},
    };
    ag::array_t<struct ag::bg_map_manager::init_data_t> return_top_no_init_list = {
        sizeof(return_top_no_init_data) / sizeof(return_top_no_init_data[0]),
        return_top_no_init_data
    };

};

BN_DATA_EWRAM return_top_static_data return_top_data;

}
#endif

