#ifndef AG_COMMON_H
#define AG_COMMON_H

#define AG_FELD_X_SIZE (15)
#define AG_FELD_Y_SIZE (15)

#define AG_UNINITIALIZED (-1)
#define AG_Z_ORDER_CURSOR (-128)

namespace ag {

enum class directions {
    DOWN=0,
    UP=1,
    RIGHT=2,
    LEFT=3,
};

}

#endif
