#include "SANTIAC.h"

std::ostream& operator<<(std::ostream& out, const SANTIAC::IntCode& c) {
    out <<
        "'" << ((c.mode[2] == SANTIAC::PARAMETER_MODE::position) ? 0 : 1)
        << ((c.mode[1] == SANTIAC::PARAMETER_MODE::position) ? 0 : 1)
        << ((c.mode[0] == SANTIAC::PARAMETER_MODE::position) ? 0 : 1)
        << "_" << c.operation << "'";
    return out;
}

SANTIAC::IntCode::IntCode(int input) {
    if (input >= 10000) {
        input -= 10000;
        mode[2] = SANTIAC::PARAMETER_MODE::immediate;
    } else {
        mode[2] = SANTIAC::PARAMETER_MODE::position;
    }

    if (input >= 1000) {
        input -= 1000;
        mode[1] = SANTIAC::PARAMETER_MODE::immediate;
    } else {
        mode[1] = SANTIAC::PARAMETER_MODE::position;
    }

    if (input >= 100) {
        input -= 100;
        mode[0] = SANTIAC::PARAMETER_MODE::immediate;
    } else {
        mode[0] = SANTIAC::PARAMETER_MODE::position;
    }

    operation = input;
}
