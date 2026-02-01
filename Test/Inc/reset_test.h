#pragma once
#include "sys_const.h"
#include "rtcObject.h"
#include "gpioObject.h"
#include <array>

namespace reset_test {
    void runTest(rtcObject& rtcObj, gpioObject& gpioObj);
}