#pragma once
#ifdef TYGERMEM2_EXPORTS
#define TYGERMEM2 __declspec(dllexport)
#else
#define TYGERMEM2 __declspec(dllimport)
#endif
#include <string>
#include <fstream>
#include "framework.h"

class Logging {
public:
    static void del();
    static void log(const std::string& message);
};