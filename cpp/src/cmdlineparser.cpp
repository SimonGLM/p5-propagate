#include "cmdlineparser.h"
#include "raywalkconfig.h"
#include <string>
#include <iostream>
#include <unistd.h>

void cmd_line_parser::print_help()
{
    std::cout << std::endl;
    std::cout << PROJECT_NAME << " v" << project_VERSION_MAJOR << "." << project_VERSION_MINOR << std::endl;
    std::cout << "<description>" << std::endl;
    std::cout << "Usage:    " << PROJECT_NAME << " [-abvh?] [positional arguments]" << std::endl;
    std::cout << "  Options:" << std::endl;
    std::cout << "  -h?                     : shows this help page." << std::endl;
    std::cout << "  -v                      : shows program release version." << std::endl;
    std::cout << "  -a                      : sets flag A to true." << std::endl;
    std::cout << "  -b                      : sets flag B to true." << std::endl;
    std::cout << "  -V <unsigned>           : sets verbosity level." << std::endl;
    std::cout << std::endl;
    std::cout << "written by <marvin.peter@physik.uni-giessen.de>" << std::endl;
    std::cout << "---status (compiled) " << __DATE__ << " " << __TIME__ << std::endl << std::endl;

} // end of print_help()

auto cmd_line_parser::parse(int argc, char **argv) -> options
{

    options my_options;
    // Shut GetOpt error messages down (return '?'):
    opterr = 0;

    // Retrieve the options:
    int opt{};
    while ((opt = getopt(argc, argv, "ab?vV:")) != -1)
    { // for each option...
        switch (opt)
        {
        case 'a':
            my_options.flagA = true;
            break;
        case 'b':
            my_options.flagB = true;
            break;
        case 'v':
            std::cout << PROJECT_NAME << " v" << project_VERSION_MAJOR << "." << project_VERSION_MINOR << std::endl;
            exit(0);
            break;
        case 'V':
            my_options.verbosity = std::stoul(optarg);
            break;
        case '?': // unknown option...
            print_help();
            exit(0);
            break;
        default:
            std::cerr << "Unknown option: '" << char(optopt) << "'!" << std::endl;
            print_help();
            exit(-1);
            break;
        }
    }
    for (auto i = optind; i < argc; i++)
    {
        std::cout << "Non-option argument " << std::string(argv[i]) << "\n";
    }
    std::cout << std::flush;
    return my_options;
}
