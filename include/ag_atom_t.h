#ifndef AG_ATOM_T_H
#define AG_ATOM_T_H

namespace ag
{

struct atom_t {
    int id;
    int conn_flg;

    bool operator==(atom_t const & rhs) const {
        return ((this->id == rhs.id) && (this->conn_flg == rhs.conn_flg));
    }
};

}
#endif

