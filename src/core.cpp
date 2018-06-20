#include "core.hpp"
#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <assert.h>

namespace Codeep {
namespace Core {

typedef struct input_event input_event;
char* LOGFILE = "./codeep.log";

void Init() {
   // daemon_pid = fork();
    pid_t daemon_pid = getpid();
    std::ofstream tmpfile;
    tmpfile.open("tmppid.txt");
    tmpfile << daemon_pid;
    tmpfile.close();

    std::cout << "Codeep has been successfully launched !!! \n"
              << "Enjoy coding !!!" << std::endl;

    char* kbd_file = getKeyboardDeviceFileName();
    std::cout << "Keyboard File: " << kbd_file << std::endl;
    int kbd_fd = openKeyboardDeviceFile(kbd_file);
    assert(kbd_fd > 0);

    if (daemon(1, 0) == -1) {
        std::cout << "Something wrong ... :(" << std::endl;
        exit(-1);
    }
    
    input_event event; 
    FILE *logfile = fopen(LOGFILE, "a");
    setbuf(logfile, NULL);
    int cnt = 0;
    while (read(kbd_fd, &event, sizeof(input_event)) > 0) {
        if (event.type == EV_KEY) {
            cnt++;
            std::string _cnt = std::to_string(cnt);
            char* _c_cnt = new char[_cnt.length()+1];
            strcpy(_c_cnt, _cnt.c_str());
            fputs(_c_cnt, logfile);
            delete [] _c_cnt;
        }
    }
    close(kbd_fd);
    fclose(logfile);
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