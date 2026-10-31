#pragma force_active on
#include <global.h>

extern "C" {
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
s32 menuSubOpenYesNoField();
s32 GSfloorChange(s32);
}

static s32 _coutineSave() {
    s8 result;
    s32 state = 0;
    s32 done = 0;
    while (done == 0) {
        switch (state) {
        case 2:
            break;
        case 0: {
            winMsgOpen(2, 1, 1, 1);
            result = (s8)menuSubOpenYesNoField();
            winMsgClose(1);
            if (result != 0) done = 1;
            else state = 2;
            break;
        }
        case 3:
            GSfloorChange(0x395);
            state = 4;
            break;
        case 4:
            done = 1;
            break;
        }
    }
    return 0;
}

extern "C" s32 scriptBattleMountainEnd(s32) {
    GSfloorChange(0x395);
    return 0;
}

extern "C" s32 scriptContinueSave() {
    return _coutineSave();
}
#pragma force_active reset
