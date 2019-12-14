#pragma once

#include <vector>
#include <queue>
#include <iostream>
#include <string>

class SANTIAC {
public:
    enum class PARAMETER_MODE {
        position = 0,
        immediate = 1,
        relative = 2
    };
    enum class RUN_MODE {unstarted, running, paused, terminated};

    SANTIAC(std::istream& input_stream);

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
    void op_adjust_relative_base(PARAMETER_MODE);

    struct IntCode {
        IntCode(int input);
        int operation;
        SANTIAC::PARAMETER_MODE mode[3];
        static int decode(const SANTIAC::PARAMETER_MODE);
        friend std::ostream& operator<<(std::ostream& out, const IntCode& c);
    };

    static std::vector<std::string> all_configs(int depth);
    static std::vector<std::string> all_configs_recursive(
            std::vector<std::string>& current, int depth);
private:
    struct m_flags_struct {
        bool debug = false;
        bool output = true;
    } m_flags;
    struct m_config_struct {
        int value;
        bool unread = true;
    } m_config;
    struct m_io_struct {
        std::queue<int> readMe;
        int prev_output;
    } m_io;
    int m_head = 0;
    int m_base = 0;
    RUN_MODE m_status = RUN_MODE::unstarted;
    std::vector<int> m_data;
    std::queue<int> m_input;

    int fetch(PARAMETER_MODE mode, int parameter_number);
    void dump_data();
};
