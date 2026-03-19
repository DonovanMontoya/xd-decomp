# Runtime Verification Status

This file tracks verification status for `src/PowerPC_EABI_Support/Runtime/Src`.

Rules:
- Check this file before touching a runtime unit.
- Update the row when a unit changes source form or verification status.
- Prefer `exact asm` for tiny toolchain/ABI helpers when C/C++ is not matching cleanly.
- Do not reopen a `verified` unit unless there is a concrete mismatch to fix.

Statuses:
- `verified`: source object has been checked against the original object/disassembly closely enough to treat it as done for now.
- `in_progress`: source exists, but verification is still active.
- `provisional`: integrated, but not trusted as a binary-faithful reconstruction.
- `unverified`: source-backed, but not yet checked meaningfully.

| Unit | Source Form | Status | Notes |
| --- | --- | --- | --- |
| `__init_cpp_exceptions.cpp` | C++ | verified | `__init_cpp_exceptions` and `__fini_cpp_exceptions` reached 100%. |
| `__mem.c` | C/asm mix | verified | `memset`, `__fill_mem`, and `memcpy` verified. |
| `__va_arg.s` | exact asm | verified | Converted from C after MWCC produced non-matching control flow. |
| `global_destructor_chain.s` | exact asm | verified | Converted from C to restore trailing `sbss` gap symbol. |
| `CPlusLibPPC.s` | exact asm | verified | Converted from C++ after MWCC unrolled `__copy` into a non-matching loop. |
| `NMWException.s` | exact asm | verified | Converted from C++; functions/extab checked. |
| `runtime.s` | exact asm | verified | Exported helpers and save/restore symbols verified. |
| `Gecko_ExceptionPPC.s` | exact asm | verified | Converted from C++; fixed `bss` symbol layout. |
| `GCN_mem_alloc.s` | exact asm | verified | Converted from C; verified fresh fixed object against original layout. |

Open items:
- `PowerPC_EABI_Support/Runtime/Src` is currently covered by the rows above.
- add new rows before working on runtime files in other folders.
