#include <dolphin/types.h>

__declspec(section ".init") void __fill_mem(void* dst, int ch, size_t size);

__declspec(section ".init") void* memset(void* dst, int ch, size_t size) {
    void* out = dst;

    __fill_mem(dst, ch, size);
    return out;
}

__declspec(section ".init") asm void __fill_mem(void* dst, int ch, size_t size)
{ // clang-format off
    nofralloc
    cmplwi r5, 0x20
    clrlwi r4, r4, 24
    subi r6, r3, 0x1
    mr r7, r4
    blt tail_bytes
    nor r0, r6, r6
    clrlwi. r3, r0, 30
    beq fill_word
    subf r5, r3, r5
align_bytes:
    subic. r3, r3, 0x1
    stbu r7, 0x1(r6)
    bne align_bytes
fill_word:
    cmplwi r7, 0x0
    beq block_loop_prep
    slwi r3, r7, 24
    slwi r0, r7, 16
    slwi r4, r7, 8
    or r0, r3, r0
    or r0, r4, r0
    or r7, r7, r0
block_loop_prep:
    srwi. r3, r5, 5
    subi r4, r6, 0x3
    beq word_loop_prep
block_loop:
    stw r7, 0x4(r4)
    subic. r3, r3, 0x1
    stw r7, 0x8(r4)
    stw r7, 0xc(r4)
    stw r7, 0x10(r4)
    stw r7, 0x14(r4)
    stw r7, 0x18(r4)
    stw r7, 0x1c(r4)
    stwu r7, 0x20(r4)
    bne block_loop
word_loop_prep:
    extrwi. r3, r5, 3, 27
    beq tail_prep
word_loop:
    subic. r3, r3, 0x1
    stwu r7, 0x4(r4)
    bne word_loop
tail_prep:
    addi r6, r4, 0x3
    clrlwi r5, r5, 30
tail_bytes:
    cmplwi r5, 0x0
    beqlr
tail_loop:
    subic. r5, r5, 0x1
    stbu r7, 0x1(r6)
    bne tail_loop
    blr
}

__declspec(section ".init") void* memcpy(void* dst, const void* src, size_t size) {
    if ((const unsigned char*)src >= (unsigned char*)dst) {
        const unsigned char* in = (const unsigned char*)src - 1;
        unsigned char* out = (unsigned char*)dst - 1;
        size_t count = size + 1;

        while (--count != 0) {
            *++out = *++in;
        }
    } else {
        const unsigned char* in = (const unsigned char*)src + size;
        unsigned char* out = (unsigned char*)dst + size;
        size_t count = size + 1;

        while (--count != 0) {
            *--out = *--in;
        }
    }

    return dst;
}
