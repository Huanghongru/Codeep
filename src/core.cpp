#include "core.hpp"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <signal.h>
#include <sys/types.h>

namespace Codeep {
namespace Core {

void Init() {
    if (daemon(1, 1) == -1) {
        std::cout << "Something wrong ... :(" << std::endl;
        exit(-1);
    }
    // daemon_pid = fork();
    pid_t daemon_pid = getpid();
    std::ofstream tmpfile;
    tmpfile.open("tmppid.txt");
    tmpfile << daemon_pid;
    tmpfile.close();

    std::cout << "Codeep has been successfully launched !!! \n"
              << "Enjoy coding !!!" << std::endl;

    while (true) {}
}

void Exit() {
    std::ifstream tmpfile;
    tmpfile.open("tmppid.txt");
    pid_t pid;
    tmpfile >> pid;
    tmpfile.close();
    remove("tmppid.txt");

    kill(pid, 9);

    std::cout << "Coding finished !!!" << std::endl;
}

}
}