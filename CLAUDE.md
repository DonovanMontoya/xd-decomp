# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is the **TeamOrre decompilation project** for **Pokémon XD: Gale of Darkness** (GameCube). The goal is to reconstruct the game's C/C++ source code such that it compiles to a byte-for-byte matching binary. Target versions:
- `GXXE01` – USA Rev 0 (primary)
- `NXXJ01` – JP Demo Disc Rev 0

The compiler is **Metrowerks CodeWarrior** (PowerPC/Gekko). All code must match that compiler's output, not a modern GCC/Clang.

## Build Commands

```sh
# Initial setup (run once, requires game disc image in orig/GXXE01/)
python configure.py

# For the JP demo version
python configure.py --version NXXJ01

# Build
ninja

# Other configure flags
python configure.py --map              # Generate map files
python configure.py --non-matching    # Include non-matching objects
python configure.py --debug           # Non-matching debug build
python configure.py --warn error      # Treat warnings as errors
```

After a successful build, `objdiff.json` is generated in the project root. Use [objdiff](https://github.com/encounter/objdiff) to interactively diff compiled objects against the original. objdiff watches for file changes and rebuilds automatically.

## Verification Workflow

When doing actual matching work, use this process:

- Stay inside one object file for a while instead of translating many files at once.
- Rebuild the exact object directly with the Metrowerks command emitted in `build.ninja`; do not rely on a full `ninja` run as the primary feedback loop.
- Confirm the rebuilt object in `build/<GAMEID>/src/...` actually changed before trusting any diff result.
- Use `build/tools/objdiff-cli.exe diff -1 <original object> -2 <rebuilt object> <symbol>` to verify one symbol at a time.
- Only move on after the current symbol or small symbol tranche is at `100%`.
- Treat "source-backed" objects and successful configure/build graph updates as integration progress only, not binary verification.
- If CodeWarrior refuses to emit the correct shape from a faithful C reconstruction, prefer direct Metrowerks-style PPC `asm` for that symbol rather than speculative high-level logic.
- For `src/PowerPC_EABI_Support/Runtime/Src`, check `docs/runtime-verification-status.md` before editing and update it when a unit changes state.
- Do not redo a runtime unit already marked `verified` in `docs/runtime-verification-status.md` unless a concrete object mismatch is found.

## Repository Structure

- `src/` – Decompiled C/C++ source files
  - `src/dolphin/` – Dolphin SDK (GameCube OS/hardware layer), written in C
  - `src/game/pxdvs/` – Game-specific code (Pokémon XD logic), written in C++
- `include/` – Reconstructed header files
- `config/GXXE01/` – Build config for the USA version
  - `config.yml` – Project metadata (symbols file, splits file, linker script)
  - `symbols.txt` – Function and variable symbol addresses/attributes
  - `splits.txt` – DOL/REL segment boundaries (maps address ranges to source files)
  - `module/ldscript.lcf` – Metrowerks linker script
- `tools/` – Build system and utilities
  - `project.py` – Core build logic (Object, ProjectConfig, Ninja generation)
  - `configure.py` (root) – Entry point; generates `build.ninja` and `objdiff.json`
  - `decompctx.py` – Generates context files for decomp.me
  - `apply_objdiff_mappings.py` – Applies objdiff symbol mappings back to symbols.txt
- `extern/musyx/` – MusyX audio library (git submodule)
- `orig/` – User-provided game disc images (not included in repo)
- `build/` – Generated build output (gitignored)

## Compiler Flags

The Metrowerks compiler flags matter for matching. Key flags (from `configure.py`):
- Base: `-nodefaults -proc gekko -O4,p -inline auto -enum int -fp hardware -Cpp_exceptions off -RTTI off`
- Dolphin SDK adds: `-char unsigned -sym on -D__GEKKO__`
- REL modules add: `-sdata 0 -sdata2 0`

On non-Windows platforms, `wibo` (a 32-bit Windows binary wrapper) is auto-downloaded to run the Metrowerks compiler.

## Object Matching Status

Objects in `configure.py` are tagged with their matching status:
- `Matching` – compiles to a byte-for-byte identical object
- `NonMatching` – functionally correct but not yet matching
- `Equivalent` – deliberately non-matching (improved/modified version)

The build system only includes `NonMatching` objects when `--non-matching` is passed to configure.

## Symbols and Splits

**Symbols** (`config/GXXE01/symbols.txt`) define function/variable addresses. Format documented at [dtk-template/docs/symbols.md](https://github.com/encounter/dtk-template/blob/main/docs/symbols.md).

**Splits** (`config/GXXE01/splits.txt`) define which source file each address range belongs to. Format documented at [dtk-template/docs/splits.md](https://github.com/encounter/dtk-template/blob/main/docs/splits.md).

When adding symbols, prefer names from the JP demo symbol map (`NXXJ01/symbols.txt`) for shared symbols.

## Contribution Rules

- No direct commits to `main` — all changes go through pull requests.
- PRs should be small and single-purpose (e.g., "Add 12 new retail XD symbols").
- Verify splits work by building locally before submitting.
- Ask before adding new C/C++ source files or changing project structure.
- Use names from symbol maps when available; avoid speculative names without evidence.

## Shared Ghidra Project

The team maintains a shared Ghidra reverse engineering project at `ghidra.decomp.dev:13100`. Access requires a Discord account linked at `https://ghidra.decomp.dev`. Uses the Rootcubed Ghidra 11.2 DEV build with OpenJDK 21.
