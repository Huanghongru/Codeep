#include "core.hpp"
#include <iostream>

namespace Codeep {
namespace Core {

pid_t daemon_pid;
int a;

void Init() {
    if (daemon(1, 1) == -1)
        exit(-1);
    std::cout << "hello again" << std::endl;
    daemon_pid = getpid();
    std::cout << daemon_pid << std::endl;

    a = 10;

    while (true) {}
}

void Exit() {
    std::cout << a << std::endl;
}

}
}