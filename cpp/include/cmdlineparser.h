#ifndef CMD_LINE_PARSER
#define CMD_LINE_PARSER

class cmd_line_parser
{
public:
    struct options
    {
        bool flagA{false};
        bool flagB{false};
        unsigned long verbosity{0};
    };

    static auto parse(int argc, char **argv) -> options;
    static void print_help();

private:
    cmd_line_parser() = default; // this class should only be static
    ~cmd_line_parser() = default;
};

#endif // CMD_LINE_PARSER