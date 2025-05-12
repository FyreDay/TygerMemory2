#pragma once

#include <string>
#include <fstream>
#include "framework.h"

class Logging {
public:
    static void del();
    static void log(const std::string& message);
};