#include "SANTIAC.h"

std::ostream& operator<<(std::ostream& out, const SANTIAC::IntCode& c) {
    out <<
        "'" << SANTIAC::IntCode::decode(c.mode[2])
        << SANTIAC::IntCode::decode(c.mode[1])
        << SANTIAC::IntCode::decode(c.mode[0])
        << "_" << c.operation << "'";
    return out;
}

long SANTIAC::IntCode::decode(const SANTIAC::PARAMETER_MODE mode) {
    switch(mode) {
        case SANTIAC::PARAMETER_MODE::position : return 0;
        case SANTIAC::PARAMETER_MODE::immediate: return 1;
        case SANTIAC::PARAMETER_MODE::relative : return 2;
        default: return -1;
    }
}

SANTIAC::IntCode::IntCode(long input) {
    long gate = 10000;
    for (long i = 2; i >= 0; i--) {
        if (input >= 2*gate) {
            input -= 2*gate;
            mode[i] = SANTIAC::PARAMETER_MODE::relative;
        } else if (input >= gate) {
            input -= gate;
            mode[i] = SANTIAC::PARAMETER_MODE::immediate;
        } else {
            mode[i] = SANTIAC::PARAMETER_MODE::position;
        }

        gate /= 10;
    }

    operation = input;
}
