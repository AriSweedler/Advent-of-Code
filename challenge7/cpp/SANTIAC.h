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

    int amplify(std::string config);
    int execute();
    void step();

    void op_add(PARAMETER_MODE, PARAMETER_MODE);
    void op_mult(PARAMETER_MODE, PARAMETER_MODE);
    void op_read();
    void op_print(PARAMETER_MODE);
    void op_jump_if_true(PARAMETER_MODE, PARAMETER_MODE);
    void op_jump_if_false(PARAMETER_MODE, PARAMETER_MODE);
    void op_is_less_than(PARAMETER_MODE, PARAMETER_MODE);
    void op_is_equal(PARAMETER_MODE, PARAMETER_MODE);

    struct IntCode {
        IntCode(int input);
        int operation;
        SANTIAC::PARAMETER_MODE mode[3];
        friend std::ostream& operator<<(std::ostream& out, const IntCode& c);
    };

    static std::vector<std::string> all_configs(int depth);
    static std::vector<std::string> all_configs_recursive(
            std::vector<std::string>& current, int depth);
private:
    struct m_flags_struct {
        bool debug = false;
        bool output = false;
    } m_flags;

    int m_head;
    RUN_MODE m_status;
    std::vector<int> m_data;
    std::queue<int> m_input;
    struct m_io_struct {
        std::queue<int> readMe;
        int prev_output;
    } m_io;

    int fetch(PARAMETER_MODE mode, int offset);
    void dump_data();
};
