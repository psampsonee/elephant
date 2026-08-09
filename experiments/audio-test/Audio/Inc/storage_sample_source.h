#pragma once
#include "sample_source.h"
#include "storage_device.h"

class StorageSampleSource : public SampleSource {
public:

    explicit StorageSampleSource(StorageDevice& storage)
        : storage_(storage) {}

protected:
    StorageDevice& storage_;

    size_t nextSectorToRead_;
};
