#include <dolphin/types.h>

typedef struct FightEncountWipeData {
    u8 snapshotUse; u16 effectSndId; f32 effectTime; void (*function)(void);
} FightEncountWipeData;

extern void fadeEffectHookFunction_fadeout_in_Init(void);
extern void fadeEffectHookFunction_yoko_Init(void);
extern void fadeEffectHookFunction_tate_Init(void);
extern void fadeEffectHookFunction_ball_Init(void);
extern void fadeEffectHookFunction_boss_Init(void);
extern void fadeEffectHookFunction_carde_Init(void);
extern void fadeEffectHookFunction_yoko_or_tate_Init(void);
extern void fadeEffectHookFunction_yoko_or_tate_or_ball_Init(void);
extern void fadeEffectHookFunction_trainer_Init(void);
extern void fadeEffectHookFunction_fadein_Init(void);
extern void fadeEffectHookFunction_distortion_Init(void);
extern void fadeEffectHookFunction_tear_off_Init(void);
extern void fadeEffectHookFunction_boss_second_Init(void);
extern void fadeEffectHookFunction_bound_ball_Init(void);
extern void fadeEffectHookFunction_ball_second_Init(void);
extern void fadeEffectHookFunction_blur_ball_Init(void);
extern void fadeEffectHookFunction_dist_ball_Init(void);
extern void fadeEffectHookFunction_dist_zoom_in_Init(void);
extern void fadeEffectHookFunction_dist_zoom_out_Init(void);
extern void fadeEffectHookFunction_dist_yoko_Init(void);
extern void fadeEffectHookFunction_distortion_strip_tate_Init(void);
extern void fadeEffectHookFunction_distortion_strip_yoko_Init(void);
extern void fadeEffectHookFunction_four_ball_Init(void);
extern void fadeEffectHookFunction_slide_ball_Init(void);
extern void fadeEffectHookFunction_trainer_second_Init(void);

FightEncountWipeData fight_encount_wipe_data[] = {
    {1, 0, 0.5f, fadeEffectHookFunction_fadeout_in_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_yoko_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_tate_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_ball_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_boss_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_carde_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_yoko_or_tate_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_yoko_or_tate_or_ball_Init},
    {1, 0, 0.5f, fadeEffectHookFunction_fadeout_in_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_trainer_Init},
    {0, 0, 0.1f, fadeEffectHookFunction_fadein_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_distortion_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_tear_off_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_boss_second_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_bound_ball_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_ball_second_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_blur_ball_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_dist_ball_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_dist_zoom_in_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_dist_zoom_out_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_dist_yoko_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_distortion_strip_tate_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_distortion_strip_yoko_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_four_ball_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_slide_ball_Init},
    {1, 34, 2.5f, fadeEffectHookFunction_trainer_second_Init},
};

u32 fight_encount_wipe_data_number = 26;
