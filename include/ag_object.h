#ifndef AG_OBJECT_H
#define AG_OBJECT_H

#include "ag_common.h"

namespace ag {

class object {
public:
    enum class type {
        ATOM,
        WALL,
        CURSOR
    };

    enum class atom_id {
        J = 0,
        H,
        C,
        O,
        N,
        S,
        F,
        Cl,
        Br,
        P,
        Crystal        = 24,
        HorizontalConn = 0x010A,
        SlashConn      = 0x010B,
        VerticalConn   = 0x010C,
        BackSlashConn  = 0x010D,
    };

    object(ag::object::type type_val):
        _type(type_val),
        _id(AG_UNINITIALIZED)
    {}

    object(ag::object::type type_val, int id):
        _type(type_val),
        _id(id)
    {}

    virtual ~object() = default;

    ag::object::type get_type() { return _type; }
    int get_id() { return _id; }

private:
    ag::object::type _type;
    int _id;
};

}

#endif
