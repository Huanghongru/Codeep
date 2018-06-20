#ifndef _SRC_UTILS_HPP_
#define _SRC_UTILS_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

/*
 * Some applications must run in root
 */
void rootCheck();

int openKeyboardDeviceFile(const char*);

char *getKeyboardDeviceFileName();

#endif