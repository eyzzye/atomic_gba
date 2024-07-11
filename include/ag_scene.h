#ifndef AG_SCENE_H
#define AG_SCENE_H

#include "ag_common.h"

namespace ag {

class scene {
public:
    enum class type {
        NONE,
        TOPMENU,
        LEVEL_MENU,
        GAME,
    };

    enum class stat {
        INIT,
        ACTIVE,
        DONE
    };

    scene(ag::scene::type type_val):
        _type(type_val),
        _stat(stat::INIT)
    {}

    virtual ~scene() = default;
    virtual void update() = 0;

    ag::scene::type get_type() { return _type; }
    ag::scene::stat get_stat() { return _stat; }
    void set_stat(ag::scene::stat stat_val) { _stat = stat_val; }
    
private:
    ag::scene::type _type;
    ag::scene::stat _stat;
};

}

#endif
