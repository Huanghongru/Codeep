#include "core.hpp"
#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <assert.h>

namespace Codeep {
namespace Core {

typedef struct input_event input_event;
char* LOGFILE = "./codeep.log";
const int timestamp = 10;

void KeystrokesRecord() {
    char* kbd_file = Codeep::Utils::getKeyboardDeviceFileName();
    int kbd_fd = Codeep::Utils::openKeyboardDeviceFile(kbd_file);
    assert(kbd_fd > 0);
    input_event event; 

    std::ofstream logfile;
    logfile.open(LOGFILE, std::ios::out | std::ios::app);

    int cnt = 0;
    time_t timer = time(NULL);
    time_t start_point = timer;
    int time_counter = 0;
    sleep(1);   // For initialziation.
    while (true) {
        time_t _timer = time(NULL);
        if ((_timer-timer) > 10) {
            logfile << (_timer-start_point) << "\t" << cnt << std::endl;
            cnt = 0;
            timer = _timer;
        }

        if (read(kbd_fd, &event, sizeof(input_event)) > 0){
            if (event.type == EV_KEY) {
                cnt++;
            }
        }
    }
    close(kbd_fd);
    logfile.close();
}

void Init() {
    std::cout << "Codeep has been successfully launched !!! \n"
              << "Enjoy coding !!!" << std::endl;

    if (daemon(1, 0) == -1) {
        std::cout << "Something wrong ... :(" << std::endl;
        exit(-1);
    }
    /*
     * You must get process id after setting daemon.
     */
    pid_t daemon_pid = getpid();
    std::ofstream tmpfile;
    tmpfile.open("tmppid.txt");
    tmpfile << daemon_pid;
    tmpfile.close();
    
    KeystrokesRecord();
}

void Exit() {
    std::ifstream tmpfile;
    tmpfile.open("tmppid.txt");
    pid_t pid;
    tmpfile >> pid;
    tmpfile.close();
    remove("tmppid.txt");
    std::cout << geteuid() << std::endl;

    if (kill(pid, 9) == -1) {
        std::cout << strerror(errno) << std::endl;
    }

    std::cout << "Coding finished !!!" << std::endl;

    // std::string show_graph = "python draw_keystrokes.py";
    // system(show_graph.c_str());
}

}
}