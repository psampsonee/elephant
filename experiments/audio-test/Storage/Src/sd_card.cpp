#include "sd_card.h"

void SdCard::csLow()
{
    SpiStorageBase::csLow();
}

void SdCard::csHigh()
{
    SpiStorageBase::csHigh();
    txrx(0xFF); // extra clocks after release
}

void SdCard::dummyClocks()
{
    csHigh();

    for (int i = 0; i < 10; i++) {
        txrx(0xFF); // 80 clocks
    }
}

uint8_t SdCard::waitR1()
{
    for (int i = 0; i < 8; i++) {
        uint8_t r = txrx(0xFF);

        if ((r & 0x80) == 0) {
            return r;
        }
    }

    return 0xFF;
}

uint8_t SdCard::command(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    csLow();

    txrx(0x40 | cmd);
    txrx((arg >> 24) & 0xFF);
    txrx((arg >> 16) & 0xFF);
    txrx((arg >> 8) & 0xFF);
    txrx(arg & 0xFF);
    txrx(crc);

    return waitR1();
}

uint8_t SdCard::appCommand(uint8_t cmd, uint32_t arg)
{
    uint8_t r = command(55, 0, 0xFF);
    csHigh();

    if (r > 1) {
        return r;
    }

    return command(cmd, arg, 0xFF);
}

bool SdCard::init()
{
    highCapacity_ = false;

    HAL_Delay(10);
    dummyClocks();

    uint8_t r = 0xFF;

    // CMD0: reset card
    for (int i = 0; i < 10; i++) {
        r = command(0, 0, 0x95);
        csHigh();

        if (r == 0x01) {
            break;
        }

        HAL_Delay(10);
    }

    if (r != 0x01) {
        return false;
    }

    // CMD8: check SD v2
    r = command(8, 0x000001AA, 0x87);

    uint8_t r7[4];
    for (uint8_t& b : r7) {
        b = txrx(0xFF);
    }

    csHigh();

    if (r != 0x01) {
        return false;
    }

    if (r7[2] != 0x01 || r7[3] != 0xAA) {
        return false;
    }

    // ACMD41: initialize card, request HCS
    for (int i = 0; i < 1000; i++) {
        r = appCommand(41, 0x40000000);
        csHigh();

        if (r == 0x00) {
            break;
        }

        HAL_Delay(1);
    }

    if (r != 0x00) {
        return false;
    }

    // CMD58: read OCR, check CCS bit
    r = command(58, 0, 0xFF);

    uint8_t ocr[4];
    for (uint8_t& b : ocr) {
        b = txrx(0xFF);
    }

    csHigh();

    if (r != 0x00) {
        return false;
    }

    highCapacity_ = (ocr[0] & 0x40) != 0;

    return true;
}

SdCard::ReadResult SdCard::read(std::size_t sector, uint8_t* buffer)
{
    if (buffer == nullptr) {
        return ReadResult::Error;
    }

    uint32_t addr = highCapacity_ ? sector : sector * 512;

    uint8_t r = command(17, addr, 0xFF);

    if (r != 0x00) {
        csHigh();
        return ReadResult::Error;
    }

    uint8_t token = 0xFF;

    for (uint32_t i = 0; i < 100000; i++) {
        token = txrx(0xFF);

        if (token == 0xFE) {
            break;
        }
    }

    if (token != 0xFE) {
        csHigh();
        return ReadResult::Error;
    }

    for (int i = 0; i < 512; i++) {
        buffer[i] = txrx(0xFF);
    }

    // Discard CRC
    txrx(0xFF);
    txrx(0xFF);

    csHigh();

    return ReadResult::Success;
}
