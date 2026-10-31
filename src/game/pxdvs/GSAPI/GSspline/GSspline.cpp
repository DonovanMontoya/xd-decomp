#include <global.h>
struct SplineVector { f32 x,y,z; };
struct GSspline {
    s32 mode, dataType;
    u8 capacity, count, reserved, valueCount;
    void* controlPoints;
    void* workspace;
    f32* values;
    f32 startValue, endValue;
    void* selfAllocation;
    void* dataAllocation;
};
typedef char SplineNativeSize[(sizeof(GSspline) == 0x28) ? 1 : -1];
extern "C" {
void GSmemFree(void*);
void* GSmemAlloc(unsigned long);
void GSlogWrite(const char*, ...);
// Diagnostics retained from the complete spline API, including stripped operations.
struct SplineDiagnostics {
 char text0[60];
 char text60[44];
 char text104[60];
 char text164[40];
 char text204[68];
 char text272[60];
 char text332[48];
 char text380[68];
 char text448[56];
 char text504[48];
 char text552[56];
 char text608[56];
 char text664[80];
 char text744[84];
 char text828[76];
};
static const SplineDiagnostics diagnostics = {
 "GSsplineGetVectorValue: spline parameters not initialised!",
 "GSsplineGetVectorValue: wrong data type!",
 "GSsplineGetFloatValue: spline parameters not initialised!",
 "GSsplineGetFloatValue: wrong data type!",
 "GSsplineAddControlVectorValue: Warning! We are going back in Time!",
 "GSsplineAddControlVectorValue: cannot add control point!",
 "GSsplineAddControlVectorValue: wrong data type!",
 "GSsplineAddControlFloatValue: Warning! We are going back in Time!",
 "GSsplineAddControlFloatValue: cannot add control point!",
 "GSsplineAddControlFloatValue: wrong data type!",
 "GSsplineInitialise: invalid number of control points!",
 "GSsplineCreate: too few control points; minimum is 2!",
 "GSsplineCreate: invalid number of control points. Forcing Linear interpolation!",
 "GSsplineCreate: invalid number of control points. Forcing Lagrance interpolation!",
 "GSsplineCreate: spline has 2 control points; forcing Linear interpolation!",
};
void GSsplineFree(GSspline *spline) {
    if (spline != 0) {
        GSmemFree(spline->dataAllocation);
        GSmemFree(spline->selfAllocation);
    }
}

void GSsplineAddControlVectorValue(GSspline *spline, SplineVector *vector, f32 value) {
    const char *errors;
    s32 mode;
    s32 valueOffset;
    u8 valueIndex;
    u8 controlIndex;
    u8 hasValue;
    u8 *control;

    errors = (const char*)&diagnostics;
    if (spline != 0) {
        if ((s32) spline->dataType == 1) {
            controlIndex = spline->count;
            if (controlIndex < (u8) spline->capacity) {
                mode = spline->mode;
                hasValue = 1;
                if (((mode == 1) || (mode == 2)) && ((spline->count % 3) != 0)) {
                    hasValue = 0;
                }
                control = (u8*)spline->controlPoints + (controlIndex * 0xC);
                ((SplineVector*)control)->x = (f32) vector->x;
                ((SplineVector*)control)->y = (f32) vector->y;
                ((SplineVector*)control)->z = (f32) vector->z;
                spline->values[spline->count] = value;
                spline->count = (u8) (spline->count + 1);
                if (hasValue != 0) {
                    valueIndex = spline->valueCount;
                    valueOffset = (valueIndex * 4) & 0x3FC;
                    *(f32*)(valueOffset + (u8*)spline->values) = value;
                    if (valueIndex == 0) {
                        spline->startValue = value;
                    } else if (value < (spline->values + valueIndex)[-1]) {
                        GSlogWrite(errors + 0xCC);
                    }
                    if ((u8) spline->count == (u8) spline->capacity) {
                        spline->endValue = value;
                    }
                    spline->valueCount = (u8) (spline->valueCount + 1);
                }
            } else {
                GSlogWrite(errors + 0x110);
            }
        } else {
            GSlogWrite(errors + 0x14C);
        }
    }
}

GSspline * GSsplineCreate(s32 interpolation, s32 dataType, u8 count)
{
    GSspline *spline = 0;
    void *data;
    const char* errors = (const char*)&diagnostics;

    if (count < 2) {
        GSlogWrite(errors + 608);
        return 0;
    }

    if ((interpolation == 1 || interpolation == 2) && (count - 1) % 3 != 0) {
        if (count == 2) {
            GSlogWrite(errors + 664);
            interpolation = 0;
        } else {
            GSlogWrite(errors + 744);
            interpolation = 3;
        }
    } else if (count == 2 && interpolation != 0) {
        interpolation = 0;
        GSlogWrite(errors + 828);
    }

    data = GSmemAlloc(sizeof(GSspline));
    if (data) {
        spline = (GSspline*)data;
        spline->selfAllocation = data;
        spline->mode = interpolation;
        spline->dataType = dataType;
        spline->count = 0;
        spline->valueCount = 0;

        switch (interpolation) {
        case 0:
            if (dataType == 1) {
                data = GSmemAlloc(count * (sizeof(SplineVector) + sizeof(f32)));
                if (data) {
                    spline->dataAllocation = data;
                    spline->controlPoints = data;
                    data = (SplineVector *)data + count;
                    spline->workspace = 0;
                    spline->values = (f32 *)data;
                    spline->capacity = count;
                    spline->dataType = 1;
                } else {
                    GSmemFree(spline->selfAllocation);
                    spline = 0;
                }
            } else {
                data = GSmemAlloc(count * 2 * sizeof(f32));
                if (data) {
                    spline->dataAllocation = data;
                    spline->controlPoints = data;
                    data = (f32 *)data + count;
                    spline->workspace = 0;
                    spline->values = (f32 *)data;
                    spline->capacity = count;
                    spline->dataType = 0;
                } else {
                    GSmemFree(spline->selfAllocation);
                    spline = 0;
                }
            }
            break;
        case 1:
        case 2:
            if (dataType == 1) {
                data = GSmemAlloc(count * sizeof(SplineVector) + ((count + 2) / 3) * sizeof(f32));
                if (data) {
                    spline->dataAllocation = data;
                    spline->controlPoints = data;
                    data = (SplineVector *)data + count;
                    spline->workspace = 0;
                    spline->values = (f32 *)data;
                    spline->capacity = count;
                    spline->dataType = 1;
                } else {
                    GSmemFree(spline->selfAllocation);
                    spline = 0;
                }
            } else {
                data = GSmemAlloc((count + (count + 2) / 3) * sizeof(f32));
                if (data) {
                    spline->dataAllocation = data;
                    spline->controlPoints = data;
                    data = (f32 *)data + count;
                    spline->workspace = 0;
                    spline->values = (f32 *)data;
                    spline->capacity = count;
                    spline->dataType = 0;
                } else {
                    GSmemFree(spline->selfAllocation);
                    spline = 0;
                }
            }
            break;
        default:
            if (dataType == 1) {
                data = GSmemAlloc(count * (sizeof(SplineVector) + 2 * sizeof(f32)));
                if (data) {
                    spline->dataAllocation = data;
                    spline->controlPoints = data;
                    spline->workspace = (f32 *)((SplineVector *)data + count);
                    spline->values = (f32 *)((SplineVector *)data + count) + count;
                    spline->capacity = count;
                    spline->dataType = 1;
                } else {
                    GSmemFree(spline->selfAllocation);
                    spline = 0;
                }
            } else {
                data = GSmemAlloc(count * 3 * sizeof(f32));
                if (data) {
                    u8 *cursor;
                    u32 offset;

                    spline->dataAllocation = data;
                    spline->controlPoints = data;
                    offset = (u32)count * sizeof(f32);
                    cursor = (u8 *)data + offset;
                    spline->workspace = (f32 *)cursor;
                    cursor += offset;
                    spline->values = (f32 *)cursor;
                    spline->capacity = count;
                    spline->dataType = 0;
                } else {
                    GSmemFree(spline->selfAllocation);
                    spline = 0;
                }
            }
            break;
        }
    }
    return spline;
}
}
