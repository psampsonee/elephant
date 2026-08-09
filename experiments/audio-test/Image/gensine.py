import struct

data = open("sine.pcm", "rb").read()
samples = struct.unpack(f"<{len(data) // 2}h", data)

with open("sine_pcm.h", "w") as f:
    f.write("#pragma once\n#include <stdint.h>\n\n")
    f.write(f"static const int16_t sine_pcm[{len(samples)}] = {{\n")

    for i in range(0, len(samples), 12):
        row = ", ".join(str(x) for x in samples[i:i+12])
        f.write(f"    {row},\n")

    f.write("};\n\n")
    f.write(
        f"static const uint32_t sine_pcm_sample_count = {len(samples)};\n"
    )
