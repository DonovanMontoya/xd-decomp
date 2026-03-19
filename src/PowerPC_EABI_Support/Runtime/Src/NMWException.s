.include "macros.inc"
.file "NMWException.cp"

.section extab, "a"
.balign 4

.obj "@etb_80005600", local
    .4byte 0x30080000
    .4byte 0x00000000
.endobj "@etb_80005600"

.obj "@etb_80005608", local
    .4byte 0x20080000
    .4byte 0x00000060
    .4byte 0x00000010
    .4byte 0x00000000
    .4byte 0x82000008
    .4byte __dt__26__partial_array_destructorFv
.endobj "@etb_80005608"

.obj "@etb_80005620", local
    .4byte 0x18080000
    .4byte 0x00000000
.endobj "@etb_80005620"

.obj "@etb_80005628", local
    .4byte 0x28080000
    .4byte 0x00000070
    .4byte 0x00000010
    .4byte 0x00000000
    .4byte 0x82000008
    .4byte __dt__26__partial_array_destructorFv
.endobj "@etb_80005628"

.section extabindex, "a"
.balign 4

.obj "@eti_80005640", local
    .4byte __destroy_new_array
    .4byte 0x0000007C
    .4byte "@etb_80005600"
.endobj "@eti_80005640"

.obj "@eti_8000564C", local
    .4byte __construct_array
    .4byte 0x000000FC
    .4byte "@etb_80005608"
.endobj "@eti_8000564C"

.obj "@eti_80005658", local
    .4byte __dt__26__partial_array_destructorFv
    .4byte 0x000000B8
    .4byte "@etb_80005620"
.endobj "@eti_80005658"

.obj "@eti_80005664", local
    .4byte __construct_new_array
    .4byte 0x00000104
    .4byte "@etb_80005628"
.endobj "@eti_80005664"

.text
.balign 4

.fn __destroy_new_array, global
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r26, 0x8(r1)
    mr. r26, r3
    mr r27, r4
    beq .L_800D9D90
    cmplwi r27, 0x0
    beq .L_800D9D88
    lwz r29, -0x10(r26)
    li r31, 0x0
    lwz r30, -0xc(r26)
    mullw r0, r29, r30
    add r28, r26, r0
    b .L_800D9D80
.L_800D9D64:
    subf r28, r29, r28
    mr r12, r27
    mr r3, r28
    li r4, -0x1
    mtctr r12
    bctrl
    addi r31, r31, 0x1
.L_800D9D80:
    cmplw r31, r30
    blt .L_800D9D64
.L_800D9D88:
    subi r3, r26, 0x10
    bl __dla__FPv
.L_800D9D90:
    lmw r26, 0x8(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
.endfn __destroy_new_array

.fn __construct_array, global
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    li r0, 0x0
    stw r31, 0x2c(r1)
    mr r31, r3
    stw r30, 0x28(r1)
    mr r30, r7
    stw r29, 0x24(r1)
    mr r29, r6
    stw r30, 0x18(r1)
    stw r28, 0x20(r1)
    mr r28, r4
    stw r3, 0x8(r1)
    stw r29, 0xc(r1)
    stw r30, 0x10(r1)
    stw r5, 0x14(r1)
    stw r0, 0x18(r1)
    b .L_800D9E14
.L_800D9DF0:
    mr r12, r28
    mr r3, r31
    li r4, 0x1
    mtctr r12
    bctrl
    lwz r3, 0x18(r1)
    add r31, r31, r29
    addi r0, r3, 0x1
    stw r0, 0x18(r1)
.L_800D9E14:
    lwz r4, 0x18(r1)
    cmplw r4, r30
    blt .L_800D9DF0
    lwz r0, 0x10(r1)
    cmplw r4, r0
    bge .L_800D9E80
    lwz r0, 0x14(r1)
    cmplwi r0, 0x0
    beq .L_800D9E80
    lwz r0, 0xc(r1)
    lwz r3, 0x8(r1)
    mullw r0, r0, r4
    add r31, r3, r0
    b .L_800D9E74
.L_800D9E4C:
    lwz r0, 0xc(r1)
    li r4, -0x1
    lwz r12, 0x14(r1)
    subf r31, r0, r31
    mr r3, r31
    mtctr r12
    bctrl
    lwz r3, 0x18(r1)
    subi r0, r3, 0x1
    stw r0, 0x18(r1)
.L_800D9E74:
    lwz r0, 0x18(r1)
    cmplwi r0, 0x0
    bne .L_800D9E4C
.L_800D9E80:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r28, 0x20(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
.endfn __construct_array

.fn __dt__26__partial_array_destructorFv, weak
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    mr. r29, r3
    beq .L_800D9F38
    lwz r4, 0x10(r29)
    lwz r0, 0x8(r29)
    cmplw r4, r0
    bge .L_800D9F28
    lwz r0, 0xc(r29)
    cmplwi r0, 0x0
    beq .L_800D9F28
    lwz r0, 0x4(r29)
    lwz r3, 0x0(r29)
    mullw r0, r0, r4
    add r31, r3, r0
    b .L_800D9F1C
.L_800D9EF4:
    lwz r0, 0x4(r29)
    li r4, -0x1
    lwz r12, 0xc(r29)
    subf r31, r0, r31
    mr r3, r31
    mtctr r12
    bctrl
    lwz r3, 0x10(r29)
    subi r0, r3, 0x1
    stw r0, 0x10(r29)
.L_800D9F1C:
    lwz r0, 0x10(r29)
    cmplwi r0, 0x0
    bne .L_800D9EF4
.L_800D9F28:
    extsh. r0, r30
    ble .L_800D9F38
    mr r3, r29
    bl __dl__FPv
.L_800D9F38:
    lwz r0, 0x24(r1)
    mr r3, r29
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
.endfn __dt__26__partial_array_destructorFv

.fn __construct_new_array, global
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stmw r27, 0x2c(r1)
    mr. r30, r3
    mr r27, r4
    mr r28, r6
    mr r29, r7
    beq .L_800DA044
    stw r28, 0x0(r30)
    cmplwi r27, 0x0
    stw r29, 0x4(r30)
    addi r30, r30, 0x10
    beq .L_800DA044
    stw r29, 0x18(r1)
    li r0, 0x0
    mr r31, r30
    stw r30, 0x8(r1)
    stw r28, 0xc(r1)
    stw r29, 0x10(r1)
    stw r5, 0x14(r1)
    stw r0, 0x18(r1)
    b .L_800D9FD8
.L_800D9FB4:
    mr r12, r27
    mr r3, r31
    li r4, 0x1
    mtctr r12
    bctrl
    lwz r3, 0x18(r1)
    add r31, r31, r28
    addi r0, r3, 0x1
    stw r0, 0x18(r1)
.L_800D9FD8:
    lwz r4, 0x18(r1)
    cmplw r4, r29
    blt .L_800D9FB4
    lwz r0, 0x10(r1)
    cmplw r4, r0
    bge .L_800DA044
    lwz r0, 0x14(r1)
    cmplwi r0, 0x0
    beq .L_800DA044
    lwz r0, 0xc(r1)
    lwz r3, 0x8(r1)
    mullw r0, r0, r4
    add r31, r3, r0
    b .L_800DA038
.L_800DA010:
    lwz r0, 0xc(r1)
    li r4, -0x1
    lwz r12, 0x14(r1)
    subf r31, r0, r31
    mr r3, r31
    mtctr r12
    bctrl
    lwz r3, 0x18(r1)
    subi r0, r3, 0x1
    stw r0, 0x18(r1)
.L_800DA038:
    lwz r0, 0x18(r1)
    cmplwi r0, 0x0
    bne .L_800DA010
.L_800DA044:
    mr r3, r30
    lmw r27, 0x2c(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
.endfn __construct_new_array
