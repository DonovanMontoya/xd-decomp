#!/usr/bin/env python3
"""Generate private USA pokecolo C initializers; never commit generated files."""

import argparse
import hashlib
from pathlib import Path
import struct

DOL_SHA1 = "ff9e752ead9914af0b363ae6c831a34ccce189d2"
# name, runtime address, byte length; config/GXXE01/symbols.txt.
ASSETS = (
    ("resident_fnt", 0x8032EE80, 0x48A10),
    ("common_fnt", 0x80377890, 0x730),
    ("common_tbl", 0x80377FC0, 0x178BC),
    ("system_error_tbl", 0x8038F87C, 0x364),
    ("lbl_8038FBE0", 0x8038FBE0, 0x21EB4),
    ("debug_menu_fnt", 0x803B1A94, 0x10984),
    ("system_error_fnt", 0x804E7F9C, 8),
)


def extract(dol, address, size):
    offsets = struct.unpack_from(">18I", dol, 0)
    addresses = struct.unpack_from(">18I", dol, 0x48)
    sizes = struct.unpack_from(">18I", dol, 0x90)
    for offset, start, length in zip(offsets, addresses, sizes):
        if length and start <= address and address + size <= start + length:
            position = offset + address - start
            if position + size > len(dol):
                raise ValueError("truncated DOL section")
            return dol[position : position + size]
    raise ValueError(f"DOL has no file-backed range {address:#x}+{size:#x}")


def generate(dol_path, output_dir):
    dol = dol_path.read_bytes()
    digest = hashlib.sha1(dol).hexdigest()
    if digest != DOL_SHA1:
        raise ValueError(f"expected USA main.dol SHA1 {DOL_SHA1}, got {digest}")
    # Validate every range before writing any output.
    payloads = [(name, extract(dol, address, size)) for name, address, size in ASSETS]
    output_dir.mkdir(parents=True, exist_ok=True)
    for name, data in payloads:
        text = "/* Private build asset. Do not commit. */\n" + "".join(
            ",".join(f"0x{byte:02x}" for byte in data[i : i + 16]) + ",\n"
            for i in range(0, len(data), 16)
        )
        output = output_dir / (name + ".inc")
        encoded = text.encode("ascii")
        if not output.exists() or output.read_bytes() != encoded:
            temporary = output.with_suffix(".inc.tmp")
            temporary.write_bytes(encoded)
            temporary.replace(output)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dol", required=True, type=Path)
    parser.add_argument("--output-dir", required=True, type=Path)
    args = parser.parse_args()
    try:
        generate(args.dol, args.output_dir)
    except (OSError, ValueError) as error:
        parser.exit(1, f"{error}\n")


if __name__ == "__main__":
    main()
