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

    m_data[1] = noun;
    m_data[2] = verb;

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
    int opcode = m_data[m_head];

    // Process opcode and decide what insn to execute
    PARAMETER_MODE m1 = PARAMETER_MODE::position;
    PARAMETER_MODE m2 = PARAMETER_MODE::position;
    switch (opcode) {
        case 1: op_add(m1, m2); break;
        case 2: op_mult(m1, m2); break;
        case 99:
                //std::cout << "Program terminated." << std::endl;
                //std::cout << "m_data[0] = " << m_data[0] << std::endl;
                m_status = RUN_MODE::terminated;
                break;
        default:
                std::cout << "There's been an error - illegal opcode: " <<
                    opcode << std::endl;
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
    m_data[arg3_addr] = arg1 * arg2;

    // Update instruction pointer
    m_head += 4;
}

int main(int argc, char** argv) {
    SANTIAC myProgram(std::cin);

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            SANTIAC tester = myProgram;
            tester.execute(i, j);
            if (tester.get(0) == 19690720) {
                std::cout << "Noun: " << i << std::endl;
                std::cout << "Verb: " << j << std::endl;
            }
        }
    }

    return 0;
}
