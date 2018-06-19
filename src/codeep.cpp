#include "core.hpp"

#include <iostream>
#include <boost/program_options.hpp>


namespace po = boost::program_options;
using std::cout;
using std::endl;

int help(int argc, char** argv) {
    cout << "Hello world!" << endl;
    return 0;
}

int init(int argc, char **argv) {
    // 'Bonjour' means 'hello' in France.
    cout << "Bonjour, Codeep!!" << endl;
    Codeep::Core::Init();
    return 0;
}

int exit(int argc, char **argv) {
    // 'Au revoir' means 'goodbye' in France.
    cout << "Au revoir, Codeep!!" << endl;
    Codeep::Core::Exit();
    return 0;
}

// A very neat implementation of argument parser.
// You don't need to write many 'if' and 'else if' to check the argument
// parsed by main function.
#define DISPATCHER(COMMAND) \
    do { if (strcmp(argv[1], #COMMAND) == 0) return COMMAND(argc, argv); } while (0)

int main(int argc, char** argv) {
    try {
        if (argc > 1) {
            DISPATCHER(help);
            DISPATCHER(init);
            DISPATCHER(exit);
        }
        help(argc, argv);
    } catch (const std::exception &ec) {
        std::cerr << ec.what() << endl;
    }
}