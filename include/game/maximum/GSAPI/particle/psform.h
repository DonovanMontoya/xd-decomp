#ifndef GS_PSFORM_H
#define GS_PSFORM_H

#include <dolphin/types.h>

typedef struct PSFormVertex {
    f32 u;
    f32 v;
} PSFormVertex;

typedef struct PSFormPrimitive {
    u8 type;
    u8 vertexCount;
    u8 reserved[2];
    PSFormVertex vertices[1];
} PSFormPrimitive;

/* Variable-length primitives immediately follow the count. */
typedef struct PSForm {
    u32 primitiveCount;
} PSForm;

typedef struct PSFormGroup {
    u32 num;
    PSForm* formTable[1];
} PSFormGroup;

#endif
