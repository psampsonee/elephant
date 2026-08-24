#ifndef UNIT_TEST
#define UNIT_TEST
#endif

#include "ADPCM_codec.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    using namespace std;

    if (argc != 3) {
        cout << "Invalid number of arguments." << endl;
        return 1;
    }

    char* adpcmFilePath = argv[1];
    char* pcmFilePath = argv[2];
    streampos size;
    uint8_t* memBlock;
    int16_t* output;

    ifstream adpcmFile(adpcmFilePath,ios::in|ios::binary|ios::ate);
    if(adpcmFile.is_open())
    {
        // The below code reads the adpcm file:

        size_t bytesCount = 0;

        size = adpcmFile.tellg();
        memBlock = new uint8_t [size];
        output = new int16_t [size*2];
        adpcmFile.seekg (0, ios::beg);
        adpcmFile.read(reinterpret_cast<char*>(memBlock), size);

        auto adpcmFilePos = adpcmFile.gcount();

        if (adpcmFile.bad()) {
            cout << "Error reading file." << endl;
            return 1;
        }

        if (adpcmFilePos >= 0) {
            bytesCount = static_cast<size_t>(adpcmFilePos);
        }

        else {
            cout << "Error reading file." << endl;
            return 1;
        }

        adpcmFile.close();


        // ADPCM decoding implementation code below

        size_t blocksCount = bytesCount / BLOCK_SIZE;

        IMA_ADPCM_BLOCKHEADER blockHeader;
        uint8_t currentCode = 0;

        size_t outputPos = 0;
        SampleState state;

        for (size_t block = 0; block < blocksCount; block++ ) {
            uint8_t* blockPos = memBlock+(block*BLOCK_SIZE);

            blockHeader = getBlockHeader(blockPos);
            output[outputPos++] = blockHeader.iSample;

            state.predictor = blockHeader.iSample;
            state.stepIndex = blockHeader.iIndex;

            blockPos += 4; // Leave the block header.

            for(size_t compByteCnt = 0; compByteCnt < BLOCK_SIZE - BLOCK_HEADER_SIZE; compByteCnt++) {
                for(uint8_t nibbleState = 0; nibbleState < 2; nibbleState++) {
                    currentCode = code(
                        *blockPos,
                        nibbleState == 1
                    );
                    output[outputPos++] = sample(currentCode, state);
                }
                blockPos++;
            }
        }

        delete[] memBlock;

        // Writes the output array to a pcm file:

        ofstream pcmFile(pcmFilePath, ios::binary);

        if(!pcmFile) {
            cout << "Failure to write decoded file." << endl;
            return 1;
        }

        pcmFile.write(
            reinterpret_cast<const char*>(output),
            outputPos * sizeof(int16_t)
        );

        // Cleanup

        delete[] output;
        cout << "File decoded." << endl;

    }

    else {
        cout << "Error reading file." << endl;
        return 1;
    }

    return 0;
}
