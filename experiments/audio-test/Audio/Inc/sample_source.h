/*
 * SampleSource will wrap a StorageDevice, take in raw data from the storage
 * device, and put samples in a destination determined by the user.
 *
 * AudioPlayer:
 *  - Requests SampleSource to fill some amount of sample data into a referenced destination
 *  - Calls SampleSource initialization function.
 *  - Reports explicit errors thrown by SampleSource
 *
 * SampleSource:
 *  - Handles reading information from storage
 *  - Fills a requested number of samples to a destination array, or reports a reason why it could not.
 *  - Exposes necessary error information from StorageDevice to AudioPlayer (such as a read error)
 *  - Hides any block boundaries in the particular storage format that the samples are stored in
 *
 */
#pragma once
#include <cstddef>
#include <cstdint>

class SampleSource {
public:
    virtual ~SampleSource() = default;

    virtual bool init() = 0;
    virtual bool start(size_t clipStartSector) = 0;
    virtual void reset() = 0;
    virtual bool getSamples(int16_t* destination, std::size_t sampleCount) = 0;
    virtual std::size_t getReadPositionSamples() const = 0;
};
