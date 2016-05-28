#pragma once

#include <iostream>

#ifndef LOG_ALL
#define LOG_ALL 0
#endif

#define LOG if (LOG_ALL != 1) {} \
            else std::cerr

