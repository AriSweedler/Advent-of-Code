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

    long execute();
    void step();

    void op_add(PARAMETER_MODE, PARAMETER_MODE, PARAMETER_MODE);
    void op_mult(PARAMETER_MODE, PARAMETER_MODE, PARAMETER_MODE);
    void op_read(PARAMETER_MODE);
    void op_print(PARAMETER_MODE);
    void op_jump_if_true(PARAMETER_MODE, PARAMETER_MODE);
    void op_jump_if_false(PARAMETER_MODE, PARAMETER_MODE);
    void op_is_less_than(PARAMETER_MODE, PARAMETER_MODE, PARAMETER_MODE);
    void op_is_equal(PARAMETER_MODE, PARAMETER_MODE, PARAMETER_MODE);
    void op_adjust_relative_base(PARAMETER_MODE);

    struct IntCode {
        IntCode(long input);
        long operation;
        SANTIAC::PARAMETER_MODE mode[3];
        static long decode(const SANTIAC::PARAMETER_MODE);
        friend std::ostream& operator<<(std::ostream& out, const IntCode& c);
    };

    static std::vector<std::string> all_configs(long depth);
    static std::vector<std::string> all_configs_recursive(
            std::vector<std::string>& current, long depth);
private:
    struct m_flags_struct {
        bool debug_fetch = false;
        bool debug_dump = false;
        bool debug = false;
        bool output = true;
    } m_flags;
    struct m_config_struct {
        long value;
        bool unread = false;
    } m_config;
    struct m_io_struct {
        std::queue<long> readMe;
        long prev_output;
    } m_io;
    long m_head = 0;
    long m_base = 0;
    RUN_MODE m_status = RUN_MODE::unstarted;
    std::vector<long> m_data;
    std::queue<long> m_input;

    long fetch_read(PARAMETER_MODE mode, long parameter_number);
    long fetch_write(PARAMETER_MODE mode, long parameter_number);
    long val(PARAMETER_MODE mode) {return static_cast<std::underlying_type<SANTIAC::PARAMETER_MODE>::type>(mode);}
    void dump_data();
};
