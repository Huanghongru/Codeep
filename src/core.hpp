#ifndef _SRC_CORE_HPP_
#define _SRC_CORE_HPP_

#include <unistd.h>
#include <errno.h>
#include <linux/input.h>
#include <iostream>

namespace Codeep {
namespace Core {

//typedef struct input_event input_event;
/*
 * Initialize a daemon process to record frequency of keystrokes
 */
void Init();

/* 
 * Kill the daemon process
 */
void Exit();

}
}
#endif