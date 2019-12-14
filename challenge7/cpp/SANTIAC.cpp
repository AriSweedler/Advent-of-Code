#include "SANTIAC.h"

SANTIAC::SANTIAC(std::istream& input_stream) {
    for (std::string int_str; std::getline(input_stream, int_str, ',');) {
        int num = stoi(int_str);
        m_data.push_back(num);
    }
}

int SANTIAC::amplify(std::string config) {
    int next_setting = 0;
    int out = 0;
    SANTIAC amp[5] = {*this, *this, *this, *this, *this};
    for (int i = 0; i < config.size(); i++) {
        amp[i].m_config.value = config.at(i) - '0';
    }

    // push '0' to the read queue of amp A to get things started
    amp[0].m_io.readMe.push(0);

    // Execute
    amp[0].execute();
    out = amp[0].m_io.prev_output;
    return out;
}

int SANTIAC::execute() {
    m_status = RUN_MODE::running;
    m_head = 0;

    while (m_status == RUN_MODE::running) {
        step();
    }

    return m_io.prev_output;
}

void SANTIAC::dump_data() {
    for (int i = 0; i < m_data.size(); i++) {
        if (m_head == i) std::cout << "!>";
        std::cout << m_data[i] << ",";
    }
    std::cout << std::endl;
    if (m_flags.debug) std::cout << std::endl;
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
    m_data[arg3_addr] = arg1 + arg2;
    if (m_flags.debug) {
        std::cout << "Adding " << arg1 << " to " << arg2 << " and storing it in addr " << arg3_addr << std::endl;
        dump_data();
    }

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
    if (m_flags.debug) {
        std::cout << "Multiplying " << arg1 << " to " << arg2 << " and storing it in addr " << arg3_addr << std::endl;
        dump_data();
    }

    // Update instruction pointer
    m_head += 4;
}

// Start the copy of the amplifier controller software that will run on
// amplifier A. At its first input instruction, provide it the amplifier's phase
// setting, 3. At its second input instruction, provide it the input signal, 0.
// After some calculations, it will use an output instruction to indicate the
// amplifier's output signal.
void SANTIAC::op_read() {
    // Fetch
    int arg1 = fetch(PARAMETER_MODE::immediate, 1);

    // Execute and write back
    int readMe = 0;
    if (m_config.unread) {
        if (m_flags.debug) {
            std::cout << "Reading in config: " << m_config.value << std::endl;
        }
        readMe = m_config.value;
        m_config.unread = false;
    } else if (!m_io.readMe.empty()) {
        readMe = m_io.readMe.front();
        m_io.readMe.pop();
    } else {
        std::cout << "Waiting on a read..." << std::endl;
    }

    m_data[arg1] = readMe;
    if (m_flags.debug) {
        std::cout << "Reading in a " << readMe << " and writing it to addr " << arg1 << std::endl;
        dump_data();
    }

    // Update instruction pointer
    m_head += 2;
}

void SANTIAC::op_print(PARAMETER_MODE m1) {
    // Fetch
    int arg1 = fetch(m1, 1);

    // Execute and write back
    int writeMe = arg1;
    if (m_flags.output) std::cout << "System printed " << writeMe << std::endl;
    m_io.prev_output = writeMe;
    if (m_flags.debug) {
        std::cout << "From addr " << arg1 << " we issue Print" << std::endl;
        dump_data();
    }

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
    if (m_flags.debug) {
        std::cout << "Arg1 is " << arg1 << " so we " << ((arg1 != 0)?("do"):("don't")) << " jump to arg2: " << arg2 << std::endl;
        dump_data();
    }
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
    if (m_flags.debug) {
        std::cout << "Arg1 is " << arg1 << " so we " << ((arg1 == 0)?("do"):("don't")) << " jump to arg2: " << arg2 << std::endl;
        dump_data();
    }
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
    if (m_flags.debug) {
        std::cout << "(<) Arg1 is " << arg1 << ", Arg2 is " << arg2 << " so we write " << storeMe << " to addr " << arg3_addr << std::endl;
        dump_data();
    }
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
    if (m_flags.debug) {
        std::cout << "(==) Arg1 is " << arg1 << ", Arg2 is " << arg2 << " so we write " << storeMe << " to addr " << arg3_addr << std::endl;
        dump_data();
    }
    m_data[arg3_addr] = storeMe;

    // Update instruction pointer
    m_head += 4;
}

std::vector<std::string> SANTIAC::all_configs(int depth) {
    std::vector<std::string> answer;
    answer.push_back("");
    return all_configs_recursive(answer, depth - 1);
}

std::vector<std::string> SANTIAC::all_configs_recursive(
        std::vector<std::string>& current, int depth) {
    if (depth < 0) return current;
    std::vector<std::string> answer;
    std::string depth_str = std::to_string(depth);

    // "kern" is the space between letters in a font. If we have "01" and we
    // wish to insert "2", then we have 3 places to place the "2":
    // * "012"
    // * "021"
    // * "201"
    // ==> kern == 3
    int kern = current[0].size() + 1;
    for (int i = 0; i < kern; i++) {
        // For each kern column that we place our digit in, we must duplicate
        // the whole current vector
        for (auto str : current) {
            answer.push_back(str.insert(i, depth_str));
        }
    }

    return all_configs_recursive(answer, depth-1);
}

int main(int argc, char** argv) {
    SANTIAC myProgram(std::cin);

    int max = -1;
    std::string answer;
    std::vector<std::string> configs = SANTIAC::all_configs(5);
    for (auto config : configs) {
        std::cout << "config = " << config << std::endl;
        SANTIAC tester = myProgram;
        int result = tester.amplify(config);
        std::cout << "config = " << config << " done, exiting" << std::endl;
        exit(1);
        std::cout << "result = " << result << std::endl;
        if (result > max) {
            max = result;
            answer = config;
        }
    }

    std::cout << "max = " << max << std::endl;
    std::cout << "answer = " << answer << std::endl;

    return 0;
}
