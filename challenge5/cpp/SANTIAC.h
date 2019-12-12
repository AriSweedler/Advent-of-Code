#pragma once

#include <vector>
#include <queue>
#include <iostream>
#include <string>

class SANTIAC {
public:
    enum class PARAMETER_MODE {position, immediate};
    enum class RUN_MODE {running, terminated};

    SANTIAC(std::istream& input_stream);

    void execute(int noun, int verb);
    void step();
    int get(int i) {return m_data[i];}

    void op_add(PARAMETER_MODE, PARAMETER_MODE);
    void op_mult(PARAMETER_MODE, PARAMETER_MODE);
    void op_read();
    void op_print(PARAMETER_MODE);

    struct IntCode {
        IntCode(int input);
        int operation;
        SANTIAC::PARAMETER_MODE mode[3];
        friend std::ostream& operator<<(std::ostream& out, const IntCode& c);
    };
private:
    int m_head;
    RUN_MODE m_status;
    std::vector<int> m_data;
    std::queue<int> m_input;

    int fetch(PARAMETER_MODE mode, int offset);
    void dump_data();
};
