#include "SANTIAC.h"

SANTIAC::SANTIAC(std::istream& input_stream) {
    for (std::string int_str; std::getline(input_stream, int_str, ',');) {
        int num = stoi(int_str);
        m_data.push_back(num);
    }
}

void SANTIAC::execute(int noun, int verb) {
    m_status = RUN_MODE::running;
    m_head = 0;

    //m_data[1] = noun;
    //m_data[2] = verb;

    while (m_status == RUN_MODE::running) {
        step();
    }
}

void SANTIAC::dump_data() {
    for (int i = 0; i < m_data.size(); i++) {
        std::cout << m_data[i] << ",";
    }
    std::cout << std::endl;
}

void SANTIAC::step() {
    IntCode c(m_data[m_head]);

    switch (c.operation) {
        case 1: op_add(c.mode[0], c.mode[1]); break;
        case 2: op_mult(c.mode[0], c.mode[1]); break;
        case 3: op_read(); break;
        case 4: op_print(c.mode[0]); break;
        case 5: op_jump_if_true(c.mode[0], c.mode[1]); break;
        case 6: op_jump_if_false(c.mode[0], c.mode[1]); break;
        case 7: op_is_less_than(c.mode[0], c.mode[1]); break;
        case 8: op_is_equal(c.mode[0], c.mode[1]); break;
        case 99:
                //std::cout << "Program terminated." << std::endl;
                //std::cout << "m_data[0] = " << m_data[0] << std::endl;
                m_status = RUN_MODE::terminated;
                break;
        default:
                std::cout << "There's been an error - illegal intcode: " <<
                    c.operation << std::endl;
                exit(1);
                break;
    }

}

int SANTIAC::fetch(PARAMETER_MODE mode, int offset) {
    int addr;
    int parameter = m_data[m_head + offset];
    if (mode == PARAMETER_MODE::immediate) {
        return parameter;
    } else {
        return m_data[parameter];
    }
}

void SANTIAC::op_add(PARAMETER_MODE m1, PARAMETER_MODE m2) {
    // Fetch
    int arg1 = fetch(m1, 1);
    int arg2 = fetch(m2, 2);
    int arg3_addr = fetch(PARAMETER_MODE::immediate, 3);

    // Execute and write back
    //std::cout << "Adding " << arg1 << " to " << arg2 << " and storing it in addr " << arg3_addr << std::endl;
    m_data[arg3_addr] = arg1 + arg2;

    // Update instruction pointer
    m_head += 4;
}

void SANTIAC::op_mult(PARAMETER_MODE m1, PARAMETER_MODE m2) {
    // Fetch
    int arg1 = fetch(m1, 1);
    int arg2 = fetch(m2, 2);
    int arg3_addr = fetch(PARAMETER_MODE::immediate, 3);

    // Execute and write back
    //std::cout << "Multiplying " << arg1 << " to " << arg2 << " and storing it in addr " << arg3_addr << std::endl;
    m_data[arg3_addr] = arg1 * arg2;

    // Update instruction pointer
    m_head += 4;
}

void SANTIAC::op_read() {
    // Fetch
    int arg1 = fetch(PARAMETER_MODE::immediate, 1);

    // Execute and write back
    int readMe = 5;
    //std::cout << "Reading in a " << readMe << " and writing it to addr " << arg1 << std::endl;
    m_data[arg1] = readMe;

    // Update instruction pointer
    m_head += 2;
}

void SANTIAC::op_print(PARAMETER_MODE m1) {
    // Fetch
    int arg1 = fetch(m1, 1);

    // Execute and write back
    int writeMe = arg1;
    //std::cout << "From addr " << arg1 << " we issue Print" << std::endl;
    std::cout << "System printed " << writeMe << std::endl;

    // Update instruction pointer
    m_head += 2;
}


// Opcode 5 is jump-if-true: if the first parameter is non-zero, it sets the
// instruction pointer to the value from the second parameter. Otherwise, it
// does nothing.
void SANTIAC::op_jump_if_true(PARAMETER_MODE m1, PARAMETER_MODE m2) {
    // Fetch
    int arg1 = fetch(m1, 1);
    int arg2 = fetch(m2, 2);

    // Execute and write back
    if (arg1 != 0) {
        m_head = arg2;
    } else {
        // Update instruction pointer
        m_head += 3;
    }
}

// Opcode 6 is jump-if-false: if the first parameter is zero, it sets the
// instruction pointer to the value from the second parameter. Otherwise, it
// does nothing.
void SANTIAC::op_jump_if_false(PARAMETER_MODE m1, PARAMETER_MODE m2) {
    // Fetch
    int arg1 = fetch(m1, 1);
    int arg2 = fetch(m2, 2);

    // Execute and write back
    if (arg1 == 0) {
        m_head = arg2;
    } else {
        // Update instruction pointer
        m_head += 3;
    }
}

// Opcode 7 is less than: if the first parameter is less than the second
// parameter, it stores 1 in the position given by the third parameter.
// Otherwise, it stores 0.
void SANTIAC::op_is_less_than(PARAMETER_MODE m1, PARAMETER_MODE m2) {
    // Fetch
    int arg1 = fetch(m1, 1);
    int arg2 = fetch(m2, 2);
    int arg3_addr = fetch(PARAMETER_MODE::immediate, 3);

    // Execute and write back
    int storeMe = (arg1 < arg2) ? 1 : 0;
    m_data[arg3_addr] = storeMe;

    // Update instruction pointer
    m_head += 4;
}


// Opcode 8 is equals: if the first parameter is equal to the second parameter, it stores 1 in the position given by the third parameter. Otherwise, it stores 0.
void SANTIAC::op_is_equal(PARAMETER_MODE m1, PARAMETER_MODE m2) {
    // Fetch
    int arg1 = fetch(m1, 1);
    int arg2 = fetch(m2, 2);
    int arg3_addr = fetch(PARAMETER_MODE::immediate, 3);

    // Execute and write back
    int storeMe = (arg1 == arg2) ? 1 : 0;
    m_data[arg3_addr] = storeMe;

    // Update instruction pointer
    m_head += 4;
}


int main(int argc, char** argv) {
    SANTIAC myProgram(std::cin);

    SANTIAC tester = myProgram;
    tester.execute(0, 0);

    return 0;
}
