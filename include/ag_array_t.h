#ifndef AG_ARRAY_T_H
#define AG_ARRAY_T_H

namespace ag
{

template <typename T> 
struct array_t {
    size_t size;
    T *data;
};

}
#endif

