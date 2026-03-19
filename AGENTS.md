# Repository Guidelines

## Project Structure & Module Organization
- `src/` contains decompiled game and Dolphin SDK C/C++ translation units.
- `include/` holds reconstructed headers shared by `src/`.
- `config/<GAMEID>/` stores per-version build metadata (`config.yml`, `symbols.txt`, `splits.txt`, linker script, `build.sha1`).
- `tools/` contains Python utilities used by configure/build/diff workflows.
- `orig/<GAMEID>/` is local input data location; keep proprietary assets out of commits.

## Build, Test, and Development Commands
- `git clone --recurse-submodules <repo>`: clone with required submodules.
- `python configure.py --version GXXE01`: generate Ninja files for a target version (default is `GXXE01`).
- `ninja`: run the standard local build.
- `ninja all_source progress build/GXXE01/report.json`: CI-style verification plus progress report.
- `python configure.py --map --version NXXJ01`: generate map-enabled build files for analysis/diffing.

## Coding Style & Naming Conventions
- C/C++: follow existing style in touched files (include order, brace layout, and local naming patterns).
- Python tools: follow PEP 8 style with repository `flake8` settings (`E203` and `E501` ignored).
- Symbol naming: prefer confirmed map names; otherwise use descriptive technical names, not speculative lore names.
- Keep tools focused and single-purpose; place new scripts in `tools/` unless they belong in external tooling repos.

## Testing Guidelines
- There is no separate unit-test suite; correctness is validated by successful matching builds.
- Before opening a PR, run `python configure.py --version <GAMEID>` and `ninja` for each affected version.
- For symbol/split changes, ensure updated `config/<GAMEID>/symbols.txt` or `splits.txt` still builds cleanly.

## Decomp Verification Workflow
- Prefer verification-first work over breadth-first translation when touching existing decomp units.
- Work in small symbol groups inside one object file until those symbols are match-verified before moving to new files.
- Treat `python configure.py` and `ninja` as integration checks, not as proof of a matching decomp.
- For active matching work, rebuild the exact object directly with the generated Metrowerks command from `build.ninja` and confirm the object timestamp changed.
- Verify one symbol at a time with `build/tools/objdiff-cli.exe diff -1 <orig.o> -2 <src.o> <symbol>`.
- If a symbol still fights CodeWarrior codegen after a faithful C reconstruction, prefer direct Metrowerks-style PPC `asm` over speculative high-level rewrites.
- Do not count a translation as "done" just because the source exists or the object is source-backed; it is done when the relevant symbols are actually diff-verified.
- For `src/PowerPC_EABI_Support/Runtime/Src`, check `docs/runtime-verification-status.md` before editing and update it when a unit changes state.
- Do not redo a runtime unit already marked `verified` in `docs/runtime-verification-status.md` unless a concrete object mismatch is found.

## Commit & Pull Request Guidelines
- Do not commit directly to `main`; use feature branches and pull requests.
- Keep commits and PRs single-purpose and reviewable (for example: "add text splits up to <module>", "port symbols for <area>").
- PRs should include: scope summary, affected game version(s), build status, and any diff/progress impact.
- If changing structure or adding source files, discuss first with maintainers.
