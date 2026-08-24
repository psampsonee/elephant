#ifndef UNIT_TEST
#define UNIT_TEST
#endif

#include "audio_sink_fake.h"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>

int main()
{
    AudioSinkFake sink;
    sink.prepare(19200);
    sink.start();
    assert(sink.writeSample(123));
    assert(sink.lastSampleWritten() == 123);
    assert(sink.samplesWritten() == 1);
    assert(!sink.isSilenced());
    assert(!sink.isStopped());

    std::cout << "Tests completed without errors.";
    return 0;
}
