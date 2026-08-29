#!/usr/bin/env python3

import argparse
import struct
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument("pcm_file", help="Input raw s16le PCM file")
parser.add_argument("header_file", help="Output C header file")
args = parser.parse_args()

pcm_path = Path(args.pcm_file)
header_path = Path(args.header_file)

data = pcm_path.read_bytes()

if len(data) % 2 != 0:
    raise ValueError("PCM file size must be a multiple of 2 bytes")

samples = struct.unpack(f"<{len(data) // 2}h", data)

name = header_path.stem

with header_path.open("w") as f:
    f.write("#pragma once\n#include <stdint.h>\n\n")
    f.write(f"static const int16_t {name}[{len(samples)}] = {{\n")

    for i in range(0, len(samples), 12):
        row = ", ".join(str(x) for x in samples[i:i+12])
        f.write(f"    {row},\n")

    f.write("};\n\n")
    f.write(
        f"static const uint32_t {name}_sample_count = {len(samples)};\n"
    )
