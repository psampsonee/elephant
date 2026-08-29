import struct

data = open("fake_pcm_data.adpcm", "rb").read()
nBytes = struct.unpack(f"<{len(data)}B", data)

with open("fake_adpcm_data.h", "w") as f:
    f.write("#pragma once\n#include <stdint.h>\n#include <stddef.h>\n\n")
    f.write(f"static const uint8_t fake_adpcm_data[{len(nBytes)}] = {{\n")

    for i in range(0, len(nBytes), 12):
        row = ", ".join(str(x) for x in nBytes[i:i+12])
        f.write(f"    {row},\n")

    f.write("};\n\n")
    f.write(
        f"static const size_t fake_adpcm_byte_count = {len(nBytes)};\n"
    )
