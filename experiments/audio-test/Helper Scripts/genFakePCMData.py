#!/usr/bin/env python3

import argparse


def main():
    parser = argparse.ArgumentParser(
        description="Generate raw PCM/test data matching StorageDeviceFake::setStorageData()."
    )
    parser.add_argument(
        "sector_count",
        type=int,
        help="Number of sectors to generate",
    )
    parser.add_argument(
        "-s",
        "--sector-size",
        type=int,
        default=512,
        help="Sector size in bytes (default: 512)",
    )
    parser.add_argument(
        "-o",
        "--output",
        default="fake_pcm_data.pcm",
        help="Output file (default: fake_pcm_data.pcm)",
    )
    args = parser.parse_args()

    with open(args.output, "wb") as f:
        for sector in range(args.sector_count):
            for byte in range(args.sector_size):
                value = (sector * 17 + byte) & 0xFF
                f.write(bytes([value]))


if __name__ == "__main__":
    main()
