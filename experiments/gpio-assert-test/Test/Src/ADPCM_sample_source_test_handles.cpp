#include "ADPCM_sample_source_test_handles.h"

void ADPCMSampleSourceTestHandles::setStorageData(const uint8_t* data, size_t size) {
    auto& storageData = storage.getStorageData();
    std::memcpy(storageData.data, data, size);
}
