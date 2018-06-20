#include "utils.hpp"

#include <unistd.h>
#include <sys/types.h>

void rootCheck() {
    if (geteuid() != 0) {
        std::cout << "Must run as root" << std::endl;
        exit(-1);
    }
}

int openKeyboardDeviceFile(const char* deviceFile) {
    int kbd_fd = open(deviceFile, O_RDONLY);
    if (kbd_fd == -1) {
        std::cout << "Something wrong ... :(" << std::endl;
        exit(-1);
    }
    return kbd_fd;
}

/**
 * Detects and returns the name of the keyboard device file. This function uses
 * the fact that all device information is shown in /proc/bus/input/devices and
 * the keyboard device file should always have an EV of 120013
 *
 * This function call a terminal command from C/C++ program through popen().
 * @return the name of the keyboard device file
 */
char *getKeyboardDeviceFileName() {
    static const char *command = 
      "grep -E 'Handlers|EV' /proc/bus/input/devices |"
      "grep -B1 120013 |"
      "grep -Eo event[0-9]+ |"
      "tr '\\n' '\\0'";

    FILE *pipe = popen(command, "r");
    if (pipe == NULL) {
        std::cout << "Could not determine keyboard device file" << std::endl;
        exit(-1);
    }
    char result[20] = "/dev/input/";
    char temp[9];
    fgets(temp, 9, pipe);

    pclose(pipe);
    return strdup(strcat(result, temp));
}

