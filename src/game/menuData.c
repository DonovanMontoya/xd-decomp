#include <dolphin/types.h>

struct tagWINDOW_WORK;
typedef void (*MenuCallback)(struct tagWINDOW_WORK*);

/* menu.cpp dispatches cursor/button/control/draw callbacks at 0x0C..0x18. */
typedef struct MenuData {
    u8 flags, cursorFlags, inputFlags, displayMax, cursorID;
    s16 firstItem, x, y;
    MenuCallback cursor, button, control, draw;
} MenuData;
typedef char MenuDataSize[sizeof(MenuData) == 28 ? 1 : -1];

struct DbgFightWindow;
struct DbgMenuPokemonWindow;
struct DbgMenuWindow;
struct DpmWindow;
struct MemoWindow;
struct MenuDBWindow;
struct PdaMailWindow;
struct ShopWindow;
struct tagWINDOW_WORK;

extern void dbgMenuCursor(struct tagWINDOW_WORK *);
extern s32 dbgMenuEsabaDebugCursor(struct DbgMenuWindow*);
extern void dbgMenuFlagCursor(struct DbgMenuWindow*);
extern void dbgMenuFlagInfoCursor(struct DbgMenuWindow*);
extern void dbgMenuFlagInfoDraw(struct DbgMenuWindow*);
extern s32 dbgMenuLogDraw(struct DbgMenuWindow*);
extern s32 dbgMenuMenuWorldMapCursor(struct DbgMenuWindow*);
extern void dbgMenuPokemonEditButton(struct DbgMenuPokemonWindow*);
extern s32 dbgMenuUnderTakerebugCursor(struct DbgMenuWindow*);
extern void dbmMenuFightButtonNormal(struct DbgFightWindow*);
extern void fn_80042BDC(struct tagWINDOW_WORK *);
extern void fn_80085E3C(struct tagWINDOW_WORK*);
extern void fn_800860E8(struct tagWINDOW_WORK*);
extern s32 fn_80091C10(struct tagWINDOW_WORK*);
extern s32 fn_80091CA8(struct tagWINDOW_WORK*);
extern s32 fn_80091D40(struct tagWINDOW_WORK*);
extern s32 fn_80091DD8(struct tagWINDOW_WORK*);
extern s32 fn_8009E664(struct tagWINDOW_WORK*);
extern s32 fn_8009E9FC(struct tagWINDOW_WORK*);
extern s32 fn_8009EA68(struct tagWINDOW_WORK*);
extern s32 fn_800A08C0(struct tagWINDOW_WORK*);
extern s32 menuBattleDiskCtrl(void);
extern s32 menuBdisk_selectL_Btn(struct tagWINDOW_WORK*);
extern s32 menuBingoSheetBtn(struct tagWINDOW_WORK*);
extern s32 menuBingoSheetCtrl(struct tagWINDOW_WORK*);
extern s32 menuBingoSheetCur(struct tagWINDOW_WORK*);
extern s32 menuDbgItemCreateCursor(struct DbgMenuWindow*);
extern s32 menuFieldMainCtrl(struct tagWINDOW_WORK *);
extern void menuFightButtonIwaza1p(void);
extern void menuFightButtonSecretKousan(struct tagWINDOW_WORK *);
extern void menuFightButtonSecretMain(struct tagWINDOW_WORK *);
extern void menuFightButtonSecretPokemonTop(struct tagWINDOW_WORK *);
extern void menuFightButtonSecretWazaTop(struct tagWINDOW_WORK *);
extern void menuFightButtonTargetSecret(struct tagWINDOW_WORK *);
extern s32 menuFightCtrlBall(struct tagWINDOW_WORK *);
extern s32 menuFightCtrlSecretMain(struct tagWINDOW_WORK *);
extern s32 menuFightCtrlSecretPokemonTop(struct tagWINDOW_WORK *);
extern s32 menuFightCtrlSecretWazaTop(struct tagWINDOW_WORK *);
extern void menuFightCtrlTarget(void);
extern s32 menuFightCtrlTimer(struct tagWINDOW_WORK *);
extern void menuFightCurIkousan(void);
extern s32 menuFightMainCtrl(struct tagWINDOW_WORK *);
extern s32 menuFightStatusCtrl(struct tagWINDOW_WORK *);
extern s32 menuFightWazaButton(struct tagWINDOW_WORK *);
extern s32 menuFightWazaCtrl(struct tagWINDOW_WORK *);
extern void menuIntButton(struct tagWINDOW_WORK *);
extern s32 menuIntMainCtrl(struct tagWINDOW_WORK *);
extern s32 menuIntUnderTakerMainCtrl(struct tagWINDOW_WORK *);
extern s32 menuNameEntryBackCtrl(struct tagWINDOW_WORK *);
extern void menuNameEntryButton(void);
extern s32 menuNameEntryCtrl(struct tagWINDOW_WORK *);
extern s32 menuNameEntryCursor(struct tagWINDOW_WORK *);
extern void menuNameEntrySelectButton(struct tagWINDOW_WORK *);
extern s32 menuNameEntrySelectCtrl(struct tagWINDOW_WORK *);
extern void menuNintendoWarningButton(struct tagWINDOW_WORK*);
extern void menuNintendoWarningCtrl(struct tagWINDOW_WORK*);
extern void menuOrreButton(struct tagWINDOW_WORK *);
extern void menuOrreCtrl(struct tagWINDOW_WORK *);
extern s32 menuPanelCtrlLvUp(struct tagWINDOW_WORK *);
extern s32 menuPanelCtrlSelect(struct tagWINDOW_WORK *);
extern s32 menuPanelCtrlSelect2(struct tagWINDOW_WORK *);
extern s32 menuPanelCursorDecimalInput(struct tagWINDOW_WORK*);
extern s32 menuPanelCursorSelect(struct tagWINDOW_WORK *);
extern s32 menuPanelCursorSelect2(struct tagWINDOW_WORK*);
extern s32 menuPanelDrawSelect(struct tagWINDOW_WORK*);
extern s32 menuPanelDrawSelect2(struct tagWINDOW_WORK*);
extern void menuPanelInputNumberCtrl(struct tagWINDOW_WORK *);
extern void menuPanelInputNumberCursor(struct tagWINDOW_WORK *);
extern s32 menuPcBoxCtrl(struct tagWINDOW_WORK *);
extern void menuPcBoxDouguHikidashiButton(void);
extern s32 menuPcBoxDouguHikidashiCtrl(struct tagWINDOW_WORK *);
extern s32 menuPcBoxDouguHikidashiCursor(void);
extern s32 menuPcBoxDouguNumCtrl(struct tagWINDOW_WORK *);
extern s32 menuPcBoxDouguNumCursor(struct tagWINDOW_WORK *);
extern s32 menuPcBoxMarkingCtrl(struct tagWINDOW_WORK *);
extern void menuPdaButton(struct tagWINDOW_WORK *);
extern s32 menuPdaCursorCtrl(struct tagWINDOW_WORK*);
extern void menuPdaDPMButton(struct DpmWindow *);
extern s32 menuPdaDPMCtrl(struct DpmWindow *);
extern s32 menuPdaDPMCursor(struct DpmWindow *);
extern void menuPdaDPMListButton(struct tagWINDOW_WORK *);
extern s32 menuPdaDPMListCtrl(struct tagWINDOW_WORK *);
extern s32 menuPdaDPMListCursor(struct tagWINDOW_WORK *);
extern s32 menuPdaDummyCtrl(void);
extern void menuPdaMailContentsButtonXD(struct tagWINDOW_WORK *);
extern s32 menuPdaMailContentsCursorXD(struct tagWINDOW_WORK *);
extern s32 menuPdaMailCtrlXD(struct tagWINDOW_WORK *);
extern void menuPdaMailListButtonXD(struct PdaMailWindow *);
extern s32 menuPdaMailListCtrlXD(struct PdaMailWindow *);
extern s32 menuPdaMailListCursorXD(struct PdaMailWindow *);
extern void menuPdaMemoListButton(struct MemoWindow *);
extern s32 menuPdaMemoListCtrl(struct MemoWindow *);
extern s32 menuPdaMemoListCursor(struct MemoWindow *);
extern void menuPdaMemoXDButton(struct tagWINDOW_WORK *);
extern s32 menuPdaMemoXDCtrl(struct tagWINDOW_WORK *);
extern s32 menuPdaMemoXDCursor(struct tagWINDOW_WORK *);
extern s32 menuPdaSearcherCtrl(struct tagWINDOW_WORK *);
extern s32 menuPdaTopCtrl(struct tagWINDOW_WORK*);
extern s32 menuPocket2ActionCtrl(struct tagWINDOW_WORK *);
extern s32 menuPocket2ActionCursor(struct tagWINDOW_WORK *);
extern void menuPocket2Button(struct tagWINDOW_WORK *);
extern s32 menuPocket2Ctrl(struct tagWINDOW_WORK *);
extern s32 menuPocket2Cursor(struct tagWINDOW_WORK *);
extern s32 menuPocket2NumCtrl(struct tagWINDOW_WORK *);
extern s32 menuPocket2NumCursor(struct tagWINDOW_WORK *);
extern s32 menuPocketBattleDiskCtrl(struct tagWINDOW_WORK*);
extern s32 menuPocketBattleDiskCursor(void);
extern s32 menuPocketColognCtrl(struct tagWINDOW_WORK *);
extern s32 menuPocketColognCursor(struct tagWINDOW_WORK *);
extern long menuPocketToolCMetaButton(struct tagWINDOW_WORK *);
extern long menuPocketToolCMetaCtrl(struct tagWINDOW_WORK *);
extern long menuPocketToolCMetaDraw(struct tagWINDOW_WORK *);
extern void menuPokemonButton(struct tagWINDOW_WORK *);
extern s32 menuPokemonChangeCtrl(struct tagWINDOW_WORK *);
extern void menuPokemonChangeCursor(struct tagWINDOW_WORK *);
extern void menuPokemonChangeDraw(struct tagWINDOW_WORK *);
extern s32 menuPokemonCtrl(struct tagWINDOW_WORK *);
extern s32 menuPokemonCtrlWaza(void);
extern void menuPokemonCursor(struct tagWINDOW_WORK *);
extern void menuPokemonStatusButton(struct tagWINDOW_WORK*);
extern s32 menuPokemonStatusCtrl(struct tagWINDOW_WORK*);
extern void menuPokemonStatusCtrlRibbon(void);
extern void menuPokemonStatusCursor(struct tagWINDOW_WORK*);
extern void menuSaveLoadCtrl(struct tagWINDOW_WORK *);
extern void menuScriptEeveeCtrl(struct tagWINDOW_WORK *);
extern void menuScriptTutorialCtrl(struct tagWINDOW_WORK *);
extern void menuScriptTutorialCursor(struct tagWINDOW_WORK*);
extern void menuScriptUsohachiCtrl(struct tagWINDOW_WORK *);
extern void menuScriptWazaOshieCtrl(struct tagWINDOW_WORK *);
extern s32 menuScriptWazaOshieCursor(struct tagWINDOW_WORK *);
extern s32 menuShopButton(struct ShopWindow *);
extern s32 menuShopCtrl(struct ShopWindow *);
extern s32 menuShopCursor(struct ShopWindow *);
extern s32 menuShopNumCtrl(struct ShopWindow *);
extern s32 menuShopNumCursor(struct ShopWindow *);
extern void menuTitleButton(struct tagWINDOW_WORK*);
extern void menuTitleFunc(void);
extern void menuTitleOptionButton(struct tagWINDOW_WORK *);
extern void menuTitleOptionCtrl(struct tagWINDOW_WORK *);
extern s32 menuTitleOptionCursorControl(struct tagWINDOW_WORK *);
extern void menuTool_BattleBA01_Button(struct MenuDBWindow *);
extern void menuTool_BattleBA01_Ctrl(struct MenuDBWindow *);
extern void menuTool_BattleBA03_Button(struct MenuDBWindow *);
extern void menuTool_BattleBA03_Ctrl(struct MenuDBWindow *);
extern void menuTool_BattleBA04_Button(struct MenuDBWindow *);
extern void menuTool_BattleBA04_Ctrl(struct MenuDBWindow *);
extern void menuTool_BattleBA05_Button(struct MenuDBWindow *);
extern void menuTool_BattleBA05_Ctrl(struct MenuDBWindow *);
extern void menuTool_BattleBA06_Button(struct MenuDBWindow *);
extern void menuTool_BattleBA06_Ctrl(struct MenuDBWindow *);
extern void menuTool_Cursol_Button(struct MenuDBWindow *);
extern void menuTool_Cursol_Ctrl(struct MenuDBWindow *);
extern void menuTool_FlashCtrl(struct MenuDBWindow *);
extern void menuTool_GBAConnect_Button(struct MenuDBWindow *);
extern void menuTool_GBAConnect_Ctrl(struct MenuDBWindow *);
extern void menuTool_MASK_Ctrl(struct MenuDBWindow *);
extern void menuTool_Rule00_Button(struct MenuDBWindow *);
extern void menuTool_Rule00_Ctrl(struct MenuDBWindow *);
extern void menuTool_Rule01_Button(struct MenuDBWindow *);
extern void menuTool_Rule01_Ctrl(struct MenuDBWindow *);
extern void menuTool_Rule02_Button(struct MenuDBWindow *);
extern void menuTool_Rule02_Ctrl(struct MenuDBWindow *);
extern void menuTool_Rule03_Button(struct MenuDBWindow *);
extern void menuTool_Rule03_Ctrl(struct MenuDBWindow *);
extern void menuTool_Rule04_Button(struct MenuDBWindow *);
extern void menuTool_Rule04_Ctrl(struct MenuDBWindow *);
extern void menuTool_Rule05_Button(struct MenuDBWindow *);
extern void menuTool_Rule05_Ctrl(struct MenuDBWindow *);
extern void menuTool_Rule06_Button(struct MenuDBWindow *);
extern void menuTool_Rule06_Ctrl(struct MenuDBWindow *);
extern void menuTool_error00_Button(struct MenuDBWindow *);
extern void menuTool_error00_Ctrl(struct MenuDBWindow *);
extern void menuTool_error01_Button(struct MenuDBWindow *);
extern void menuTool_error01_Ctrl(struct MenuDBWindow *);
extern void menuTool_imasugu00_Button(struct MenuDBWindow *);
extern void menuTool_imasugu00_Ctrl(struct MenuDBWindow *);
extern void menuTool_imasugu01_Button(struct MenuDBWindow *);
extern void menuTool_imasugu01_Ctrl(struct MenuDBWindow *);
extern void menuTool_imasugu02_Button(struct MenuDBWindow *);
extern void menuTool_imasugu02_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaide00_Button(struct MenuDBWindow *);
extern void menuTool_tunaide00_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaide01_1_Button(struct MenuDBWindow *);
extern void menuTool_tunaide01_1_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaide01_2_Button(struct MenuDBWindow *);
extern void menuTool_tunaide01_2_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaide01_3_Button(struct MenuDBWindow *);
extern void menuTool_tunaide01_3_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaide01_4_Button(struct MenuDBWindow *);
extern void menuTool_tunaide01_4_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaide01_Button(struct MenuDBWindow *);
extern void menuTool_tunaide01_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaide02_Button(struct MenuDBWindow *);
extern void menuTool_tunaide02_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaide03_Button(struct MenuDBWindow *);
extern void menuTool_tunaide03_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry00_Button(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry00_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry01_Button(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry01_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry02_1_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry02_Button(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry02_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry03_1_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry03_Button(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry03_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry04_1_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry04_Button(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry04_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry_Button(struct MenuDBWindow *);
extern void menuTool_tunaideGCEntry_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaidePokemonSelect0_Button(struct MenuDBWindow *);
extern void menuTool_tunaidePokemonSelect0_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaidePokemonSelect1_Button(struct MenuDBWindow *);
extern void menuTool_tunaidePokemonSelect1_Ctrl(struct MenuDBWindow *);
extern void menuTool_tunaide_back_Ctrl(struct MenuDBWindow *);
extern void menuTopBattleSelectCtrl(struct tagWINDOW_WORK *);
extern void menuTopSelectCtrl(struct tagWINDOW_WORK *);
extern void menuWorldMapButton(struct tagWINDOW_WORK *);
extern void menuWorldMapCursor(struct tagWINDOW_WORK *);
extern s32 menuWorldMapMXCtrl(struct tagWINDOW_WORK *);
extern void winMsgButton(struct tagWINDOW_WORK *);
extern s32 winMsgCtrl(struct tagWINDOW_WORK *);
extern s32 winMsgCtrlYesNo(struct tagWINDOW_WORK *);

MenuData _menu_data[] = {
    {0x00, 0x00, 0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0x6E, 0x08, 0x20, 15, 0, 1, 0, 0, (MenuCallback)dbgMenuCursor, 0, 0, 0},
    {0x76, 0x08, 0x20, 0, 0, 3, 50, 60, (MenuCallback)menuPanelCursorDecimalInput, 0, 0, 0},
    {0x63, 0x00, 0x00, 0, 0, 2, 0, 0, 0, 0, 0, 0},
    {0x63, 0x00, 0x00, 0, 0, 4, 0, 0, 0, 0, 0, 0},
    {0x64, 0x00, 0x20, 0, 0, 6, 0, 0, 0, 0, 0, 0},
    {0x63, 0x00, 0x00, 0, 0, 7, 0, 0, 0, 0, 0, 0},
    {0x63, 0x00, 0x00, 0, 0, 8, 0, 0, 0, 0, 0, 0},
    {0x63, 0x00, 0x00, 0, 0, 10, 0, 0, 0, 0, 0, 0},
    {0x62, 0x00, 0x00, 0, 0, 12, 0, 0, 0, 0, 0, 0},
    {0x63, 0x00, 0x00, 0, 0, 9, 0, 0, 0, 0, 0, 0},
    {0x76, 0x08, 0x20, 15, 9, 13, 0, 0, (MenuCallback)dbgMenuFlagCursor, 0, 0, 0},
    {0x63, 0x00, 0x00, 0, 0, 14, 0, 0, 0, 0, 0, 0},
    {0x76, 0x04, 0x80, 0, 0, 21, 40, 50, 0, (MenuCallback)dbgMenuPokemonEditButton, 0, 0},
    {0x76, 0x04, 0x80, 0, 0, 113, 40, 50, 0, (MenuCallback)dbmMenuFightButtonNormal, 0, 0},
    {0x0C, 0x00, 0x80, 0, 0, 0, 0, 0, 0, (MenuCallback)winMsgButton, (MenuCallback)winMsgCtrl, 0},
    {0x0C, 0x00, 0x80, 0, 0, 0, 0, 0, 0, (MenuCallback)winMsgButton, (MenuCallback)winMsgCtrl, 0},
    {0x08, 0x02, 0x80, 0, 0, 7, 0, 0, 0, (MenuCallback)menuTitleButton, (MenuCallback)menuTitleFunc, 0},
    {0x14, 0x12, 0x20, 4, 0, 0, 0, 0, 0, 0, (MenuCallback)menuPokemonCtrlWaza, 0},
    {0xCC, 0x12, 0x20, 3, 0, 51, 0, 0, 0, 0, 0, 0},
    {0x24, 0x00, 0x20, 0, 0, 453, 91, 328, 0, 0, (MenuCallback)menuPanelCtrlLvUp, 0},
    {0x62, 0x00, 0x00, 0, 0, 278, 0, 0, 0, 0, 0, 0},
    {0x00, 0x00, 0x00, 0, 0, 6, 0, 0, 0, 0, 0, 0},
    {0x00, 0x00, 0x00, 0, 0, 5, 0, 0, 0, 0, 0, 0},
    {0x76, 0x04, 0x80, 0, 0, 141, 20, 40, 0, (MenuCallback)dbmMenuFightButtonNormal, 0, 0},
    {0x76, 0x04, 0x80, 0, 0, 221, 20, 40, 0, (MenuCallback)dbmMenuFightButtonNormal, 0, 0},
    {0x76, 0x04, 0x80, 0, 0, 248, 20, 40, 0, (MenuCallback)dbmMenuFightButtonNormal, 0, 0},
    {0x76, 0x04, 0x80, 0, 0, 249, 20, 40, 0, (MenuCallback)dbmMenuFightButtonNormal, 0, 0},
    {0x76, 0x04, 0x80, 0, 0, 178, 20, 40, 0, (MenuCallback)dbmMenuFightButtonNormal, 0, 0},
    {0x76, 0x04, 0x80, 0, 0, 204, 20, 40, 0, (MenuCallback)dbmMenuFightButtonNormal, 0, 0},
    {0x76, 0x04, 0x80, 0, 0, 230, 20, 40, 0, (MenuCallback)dbmMenuFightButtonNormal, 0, 0},
    {0x76, 0x04, 0x80, 0, 0, 250, 20, 40, 0, (MenuCallback)dbmMenuFightButtonNormal, 0, 0},
    {0x76, 0x04, 0x80, 0, 0, 136, 20, 40, 0, (MenuCallback)dbmMenuFightButtonNormal, 0, 0},
    {0x63, 0x00, 0x00, 0, 0, 5, 0, 0, 0, 0, 0, 0},
    {0x63, 0x00, 0x00, 0, 0, 0, 0, 0, 0, 0, 0, (MenuCallback)dbgMenuLogDraw},
    {0x62, 0x00, 0x00, 0, 0, 276, 0, 0, 0, 0, 0, 0},
    {0x6C, 0x18, 0x20, 0, 0, 16, 40, 50, (MenuCallback)menuDbgItemCreateCursor, 0, 0, 0},
    {0x76, 0x04, 0x80, 0, 0, 265, 20, 40, 0, (MenuCallback)dbmMenuFightButtonNormal, 0, 0},
    {0x62, 0x00, 0x00, 0, 0, 277, 0, 0, 0, 0, 0, 0},
    {0x76, 0x08, 0x20, 30, 0, 0, 0, 0, (MenuCallback)dbgMenuFlagInfoCursor, 0, 0, (MenuCallback)dbgMenuFlagInfoDraw},
    {0x63, 0x00, 0x00, 0, 0, 15, 0, 0, 0, 0, 0, 0},
    {0x24, 0x00, 0x20, 0, 0, 453, 91, 328, 0, 0, (MenuCallback)menuPanelCtrlLvUp, 0},
    {0x2B, 0x00, 0x00, 0, 0, 36, 0, 0, 0, (MenuCallback)winMsgButton, (MenuCallback)winMsgCtrl, 0},
    {0x0F, 0x00, 0x80, 0, 0, 275, 0, 0, 0, (MenuCallback)winMsgButton, (MenuCallback)winMsgCtrl, 0},
    {0x2C, 0x08, 0x80, 0, 2, 423, 0, 0, (MenuCallback)menuPocket2Cursor, (MenuCallback)menuPocket2Button, (MenuCallback)menuPocket2Ctrl, 0},
    {0x2C, 0x18, 0x20, 0, 0, 207, 0, 0, (MenuCallback)menuPocket2ActionCursor, 0, (MenuCallback)menuPocket2ActionCtrl, 0},
    {0x2C, 0x18, 0x20, 0, 0, 225, 0, 0, (MenuCallback)menuPocket2NumCursor, 0, (MenuCallback)menuPocket2NumCtrl, 0},
    {0x2C, 0x18, 0x20, 0, 0, 233, 0, 0, (MenuCallback)menuPocket2NumCursor, 0, (MenuCallback)menuPocket2NumCtrl, 0},
    {0x2C, 0x18, 0x20, 0, 0, 244, 0, 0, (MenuCallback)menuPocket2NumCursor, 0, (MenuCallback)menuPocket2NumCtrl, 0},
    {0x2C, 0x18, 0x20, 0, 0, 258, 0, 0, (MenuCallback)menuPocket2NumCursor, 0, (MenuCallback)menuPocket2NumCtrl, 0},
    {0x2C, 0x18, 0x20, 0, 0, 286, 0, 0, (MenuCallback)menuPocketColognCursor, 0, (MenuCallback)menuPocketColognCtrl, 0},
    {0x2C, 0x00, 0x80, 0, 0, 36, 0, 0, 0, (MenuCallback)winMsgButton, (MenuCallback)winMsgCtrl, 0},
    {0x2C, 0x00, 0x80, 0, 0, 46, 0, 0, 0, (MenuCallback)winMsgButton, (MenuCallback)winMsgCtrl, 0},
    {0x2E, 0x24, 0x20, 0, 0, 66, 450, 192, 0, 0, (MenuCallback)winMsgCtrlYesNo, 0},
    {0xA0, 0x12, 0x20, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0xA1, 0x02, 0x20, 0, 0, 208, 24, 46, 0, 0, (MenuCallback)menuFightStatusCtrl, 0},
    {0xA1, 0x02, 0x20, 0, 0, 236, 382, 46, 0, 0, (MenuCallback)menuFightStatusCtrl, 0},
    {0xB4, 0x62, 0x80, 0, 0, 249, 0, 0, 0, (MenuCallback)menuFightWazaButton, (MenuCallback)menuFightWazaCtrl, 0},
    {0xB4, 0x62, 0x20, 0, 0, 287, 0, 0, 0, 0, (MenuCallback)menuFightMainCtrl, 0},
    {0x2C, 0x18, 0x20, 0, 0, 269, 0, 0, (MenuCallback)menuPocketBattleDiskCursor, 0, (MenuCallback)menuPocketBattleDiskCtrl, 0},
    {0x2C, 0x18, 0x80, 0, 0, 84, 0, 0, (MenuCallback)menuShopCursor, (MenuCallback)menuShopButton, (MenuCallback)menuShopCtrl, 0},
    {0x2C, 0x18, 0x20, 0, 0, 136, 0, 0, (MenuCallback)menuShopNumCursor, 0, (MenuCallback)menuShopNumCtrl, 0},
    {0x2C, 0x12, 0x20, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x12, 0x20, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0xA1, 0x02, 0x20, 0, 0, 208, 11, 111, 0, 0, (MenuCallback)menuFightStatusCtrl, 0},
    {0xA1, 0x02, 0x20, 0, 0, 236, 395, 111, 0, 0, (MenuCallback)menuFightStatusCtrl, 0},
    {0xA1, 0x00, 0x00, 0, 0, 177, 0, 0, 0, 0, (MenuCallback)menuFightCtrlBall, 0},
    {0xA1, 0x00, 0x00, 0, 0, 190, 0, 0, 0, 0, (MenuCallback)menuFightCtrlBall, 0},
    {0xA1, 0x00, 0x00, 0, 0, 196, 0, 0, 0, 0, (MenuCallback)menuFightCtrlBall, 0},
    {0xA1, 0x00, 0x00, 0, 0, 202, 0, 0, 0, 0, (MenuCallback)menuFightCtrlBall, 0},
    {0x20, 0x00, 0x00, 0, 0, 732, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 732, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 732, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 732, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 731, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 731, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x18, 0x80, 7, 0, 734, 0, 0, (MenuCallback)menuPokemonCursor, (MenuCallback)menuPokemonButton, (MenuCallback)menuPokemonCtrl, 0},
    {0x20, 0x00, 0x00, 0, 0, 732, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x12, 0x20, 0, 0, 341, 0, 0, 0, 0, 0, 0},
    {0x3C, 0x14, 0x20, 0, 0, 357, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x14, 0x20, 0, 0, 378, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x14, 0x20, 0, 0, 392, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x00, 0x80, 0, 0, 81, 0, 0, 0, (MenuCallback)winMsgButton, (MenuCallback)winMsgCtrl, 0},
    {0x2C, 0x00, 0x80, 0, 0, 83, 0, 0, 0, (MenuCallback)winMsgButton, (MenuCallback)winMsgCtrl, 0},
    {0x2C, 0xA8, 0x80, 0, 0, 327, 0, 0, (MenuCallback)menuWorldMapCursor, (MenuCallback)menuWorldMapButton, (MenuCallback)menuWorldMapMXCtrl, 0},
    {0x2E, 0x22, 0x20, 0, 0, 63, 520, 220, 0, 0, (MenuCallback)winMsgCtrlYesNo, 0},
    {0x2E, 0x24, 0x20, 0, 0, 56, 50, 200, 0, 0, (MenuCallback)winMsgCtrlYesNo, 0},
    {0x2C, 0x14, 0x20, 0, 1, 11, 0, 0, 0, 0, (MenuCallback)menuFieldMainCtrl, 0},
    {0x2C, 0x14, 0x20, 0, 11, 699, 0, 0, 0, 0, (MenuCallback)menuFieldMainCtrl, 0},
    {0x34, 0x18, 0x20, 12, 0, 0, 0, 0, (MenuCallback)menuPanelCursorSelect, 0, (MenuCallback)menuPanelCtrlSelect, (MenuCallback)menuPanelDrawSelect},
    {0x3C, 0x14, 0x20, 0, 0, 410, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x00, 0x20, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0xB8, 0x62, 0x20, 0, 0, 312, 0, 0, 0, 0, (MenuCallback)menuFightCtrlTarget, 0},
    {0x2C, 0x14, 0x20, 0, 0, 434, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x68, 0x80, 0, 0, 2049, 0, 0, (MenuCallback)menuPokemonStatusCursor, (MenuCallback)menuPokemonStatusButton, (MenuCallback)menuPokemonStatusCtrl, 0},
    {0x20, 0x00, 0x00, 0, 0, 522, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 2080, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 518, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 481, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 542, 0, 0, 0, 0, (MenuCallback)menuPokemonStatusCtrlRibbon, 0},
    {0x2C, 0x12, 0x20, 0, 0, 2232, 0, 0, 0, 0, (MenuCallback)menuSaveLoadCtrl, 0},
    {0x2C, 0x44, 0x80, 0, 0, 460, 0, 0, 0, (MenuCallback)menuNameEntrySelectButton, (MenuCallback)menuNameEntrySelectCtrl, 0},
    {0x2C, 0x08, 0x80, 0, 0, 746, 0, 0, (MenuCallback)menuNameEntryCursor, (MenuCallback)menuNameEntryButton, (MenuCallback)menuNameEntryCtrl, 0},
    {0x20, 0x00, 0x00, 0, 0, 697, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x00, 0x00, 0, 0, 2231, 0, 0, 0, 0, (MenuCallback)menuNameEntryBackCtrl, 0},
    {0xA0, 0x00, 0x00, 0, 0, 208, 402, 47, 0, 0, (MenuCallback)menuFightStatusCtrl, 0},
    {0xA0, 0x00, 0x00, 0, 0, 236, 29, 47, 0, 0, (MenuCallback)menuFightStatusCtrl, 0},
    {0x8C, 0x98, 0x20, 0, 0, 1, 0, 0, (MenuCallback)menuPdaCursorCtrl, 0, (MenuCallback)menuPdaTopCtrl, 0},
    {0x8C, 0x50, 0x00, 0, 0, 110, 0, 0, 0, (MenuCallback)menuPdaButton, 0, 0},
    {0x8C, 0x52, 0x80, 0, 0, 372, 0, 0, 0, (MenuCallback)fn_80042BDC, (MenuCallback)menuPdaSearcherCtrl, 0},
    {0x8C, 0x58, 0x80, 5, 10, 112, 0, 0, (MenuCallback)menuPdaMailListCursorXD, (MenuCallback)menuPdaMailListButtonXD, (MenuCallback)menuPdaMailListCtrlXD, 0},
    {0x8C, 0x58, 0x80, 0, 0, 157, 0, 0, (MenuCallback)menuPdaMailContentsCursorXD, (MenuCallback)menuPdaMailContentsButtonXD, (MenuCallback)menuPdaMailCtrlXD, 0},
    {0x2C, 0x14, 0x20, 0, 11, 11, 0, 0, 0, 0, (MenuCallback)menuFieldMainCtrl, 0},
    {0x20, 0x00, 0x00, 0, 0, 691, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 679, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 723, 0, 0, 0, 0, 0, 0},
    {0x8C, 0x58, 0x80, 0, 12, 34, 0, 0, (MenuCallback)menuPdaDPMListCursor, (MenuCallback)menuPdaDPMListButton, (MenuCallback)menuPdaDPMListCtrl, 0},
    {0x8C, 0x58, 0x80, 0, 0, 79, 0, 0, (MenuCallback)menuPdaDPMCursor, (MenuCallback)menuPdaDPMButton, (MenuCallback)menuPdaDPMCtrl, 0},
    {0x20, 0x00, 0x00, 0, 0, 1215, 0, 0, 0, 0, 0, 0},
    {0x8C, 0x02, 0x20, 0, 0, 16, 0, 0, 0, 0, 0, 0},
    {0x8C, 0x58, 0x80, 0, 13, 197, 0, 0, (MenuCallback)menuPdaMemoListCursor, (MenuCallback)menuPdaMemoListButton, (MenuCallback)menuPdaMemoListCtrl, 0},
    {0x20, 0x00, 0x00, 0, 0, 791, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x34, 0x20, 0, 0, 823, 0, 0, 0, 0, (MenuCallback)menuPcBoxCtrl, 0},
    {0x2C, 0x34, 0x20, 0, 0, 859, 0, 0, 0, 0, (MenuCallback)menuPcBoxCtrl, 0},
    {0x8C, 0x58, 0x80, 0, 0, 242, 0, 0, (MenuCallback)menuPdaMemoXDCursor, (MenuCallback)menuPdaMemoXDButton, (MenuCallback)menuPdaMemoXDCtrl, 0},
    {0x8C, 0x58, 0x80, 0, 0, 263, 0, 0, (MenuCallback)menuPdaMemoXDCursor, (MenuCallback)menuPdaMemoXDButton, (MenuCallback)menuPdaMemoXDCtrl, 0},
    {0x8C, 0x58, 0x80, 0, 0, 268, 0, 0, (MenuCallback)menuPdaMemoXDCursor, (MenuCallback)menuPdaMemoXDButton, (MenuCallback)menuPdaMemoXDCtrl, 0},
    {0x8C, 0x52, 0x20, 0, 0, 173, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 942, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 990, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 997, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 1039, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 1077, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x34, 0x20, 0, 0, 1090, 0, 0, 0, 0, (MenuCallback)menuPcBoxMarkingCtrl, 0},
    {0x20, 0x00, 0x00, 0, 0, 1121, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 1131, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 1148, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 1161, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x38, 0x80, 0, 0, 1165, 0, 0, (MenuCallback)menuPcBoxDouguHikidashiCursor, (MenuCallback)menuPcBoxDouguHikidashiButton, (MenuCallback)menuPcBoxDouguHikidashiCtrl, 0},
    {0x2C, 0x38, 0x20, 0, 0, 1192, 0, 0, (MenuCallback)menuPcBoxDouguNumCursor, 0, (MenuCallback)menuPcBoxDouguNumCtrl, 0},
    {0x2C, 0x34, 0x20, 0, 0, 1201, 0, 0, 0, 0, 0, 0},
    {0xB4, 0x60, 0x80, 0, 0, 7, 0, 0, 0, (MenuCallback)menuFightButtonSecretMain, (MenuCallback)menuFightCtrlSecretMain, 0},
    {0xBC, 0x62, 0x80, 0, 0, 37, 0, 0, 0, (MenuCallback)menuFightButtonSecretKousan, 0, 0},
    {0xB4, 0x60, 0x80, 0, 0, 23, 0, 0, 0, (MenuCallback)menuFightButtonSecretWazaTop, (MenuCallback)menuFightCtrlSecretWazaTop, 0},
    {0xB0, 0x60, 0x80, 0, 0, 52, 0, 0, 0, (MenuCallback)menuFightButtonTargetSecret, 0, 0},
    {0xB4, 0x60, 0x80, 0, 0, 23, 0, 0, 0, (MenuCallback)menuFightButtonSecretPokemonTop, (MenuCallback)menuFightCtrlSecretPokemonTop, 0},
    {0xA0, 0x00, 0x00, 0, 0, 105, 0, 0, 0, 0, 0, 0},
    {0xA0, 0x00, 0x00, 0, 0, 77, 0, 0, 0, 0, 0, 0},
    {0xA0, 0x00, 0x00, 0, 0, 131, 0, 0, 0, 0, 0, 0},
    {0xA0, 0x00, 0x00, 0, 0, 676, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x02, 0x80, 0, 0, 1213, 0, 0, 0, (MenuCallback)menuIntButton, (MenuCallback)menuIntMainCtrl, 0},
    {0xA0, 0x00, 0x00, 0, 0, 167, 0, 0, 0, 0, 0, 0},
    {0xA0, 0x00, 0x00, 0, 0, 168, 0, 0, 0, 0, 0, 0},
    {0xA0, 0x00, 0x00, 0, 0, 169, 0, 0, 0, 0, 0, 0},
    {0xA0, 0x00, 0x00, 0, 0, 170, 0, 0, 0, 0, 0, 0},
    {0xA0, 0x00, 0x00, 0, 0, 171, 0, 0, 0, 0, (MenuCallback)menuFightCtrlTimer, 0},
    {0xA0, 0x00, 0x00, 0, 0, 174, 0, 0, 0, 0, (MenuCallback)menuFightCtrlTimer, 0},
    {0xB4, 0x68, 0x80, 0, 0, 316, 9, 172, (MenuCallback)menuFightCurIkousan, (MenuCallback)menuFightButtonIwaza1p, (MenuCallback)menuFightCtrlSecretWazaTop, 0},
    {0xA0, 0x08, 0x00, 0, 0, 422, 9, 217, (MenuCallback)menuFightCurIkousan, 0, 0, 0},
    {0xB4, 0x68, 0x80, 0, 0, 512, 9, 241, (MenuCallback)menuFightCurIkousan, (MenuCallback)menuFightButtonIwaza1p, 0, 0},
    {0xB4, 0x68, 0x80, 0, 0, 369, 318, 172, (MenuCallback)menuFightCurIkousan, (MenuCallback)menuFightButtonIwaza1p, (MenuCallback)menuFightCtrlSecretWazaTop, 0},
    {0xA0, 0x08, 0x00, 0, 0, 467, 318, 217, (MenuCallback)menuFightCurIkousan, 0, 0, 0},
    {0xB4, 0x68, 0x80, 0, 0, 547, 318, 241, (MenuCallback)menuFightCurIkousan, (MenuCallback)menuFightButtonIwaza1p, 0, 0},
    {0x46, 0x00, 0x80, 0, 0, 1611, 0, 0, 0, (MenuCallback)menuTool_imasugu00_Button, (MenuCallback)menuTool_imasugu00_Ctrl, 0},
    {0x4E, 0x14, 0x80, 2, 0, 1262, 0, 0, 0, (MenuCallback)menuTool_imasugu02_Button, (MenuCallback)menuTool_imasugu02_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 1, 0, 0, 0, (MenuCallback)menuTool_error00_Button, (MenuCallback)menuTool_error00_Ctrl, 0},
    {0x4E, 0x14, 0x80, 14, 0, 1237, 0, 0, 0, (MenuCallback)menuTool_error01_Button, (MenuCallback)menuTool_error01_Ctrl, 0},
    {0x8C, 0x50, 0x00, 0, 0, 367, 0, 0, 0, (MenuCallback)menuPdaButton, (MenuCallback)menuPdaDummyCtrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 57, 0, 0, 0, (MenuCallback)menuTool_tunaide00_Button, (MenuCallback)menuTool_tunaide00_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 66, 0, 0, 0, (MenuCallback)menuTool_tunaide01_Button, (MenuCallback)menuTool_tunaide01_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 135, 0, 0, 0, (MenuCallback)menuTool_tunaide02_Button, (MenuCallback)menuTool_tunaide02_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 1525, 0, 0, 0, (MenuCallback)menuTool_tunaide03_Button, (MenuCallback)menuTool_tunaide03_Ctrl, 0},
    {0xA0, 0x00, 0x00, 0, 0, 3, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x18, 0x20, 12, 0, 0, 0, 0, (MenuCallback)menuPanelCursorSelect2, 0, (MenuCallback)menuPanelCtrlSelect2, (MenuCallback)menuPanelDrawSelect2},
    {0x2C, 0x12, 0x20, 0, 0, 1237, 0, 0, 0, 0, (MenuCallback)menuScriptEeveeCtrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 211, 0, 0, 0, (MenuCallback)menuTool_GBAConnect_Button, (MenuCallback)menuTool_GBAConnect_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 1520, 0, 0, 0, (MenuCallback)menuTool_BattleBA01_Button, (MenuCallback)menuTool_BattleBA01_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 686, 0, 0, 0, (MenuCallback)menuTool_BattleBA03_Button, (MenuCallback)menuTool_BattleBA03_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 335, 0, 0, 0, (MenuCallback)menuTool_BattleBA04_Button, (MenuCallback)menuTool_BattleBA04_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 377, 0, 0, 0, (MenuCallback)menuTool_BattleBA05_Button, (MenuCallback)menuTool_BattleBA05_Ctrl, 0},
    {0xA1, 0x00, 0x00, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0x46, 0x00, 0x80, 0, 0, 401, 0, 0, 0, (MenuCallback)winMsgButton, (MenuCallback)winMsgCtrl, 0},
    {0x63, 0x00, 0x00, 0, 0, 279, 400, 40, 0, 0, 0, 0},
    {0x2C, 0x18, 0x20, 0, 0, 1983, 0, 0, (MenuCallback)menuScriptTutorialCursor, 0, (MenuCallback)menuScriptTutorialCtrl, 0},
    {0x2C, 0x18, 0x20, 0, 0, 1280, 0, 0, (MenuCallback)menuPanelInputNumberCursor, 0, (MenuCallback)menuPanelInputNumberCtrl, 0},
    {0x63, 0x00, 0x00, 0, 0, 11, 0, 0, 0, 0, 0, 0},
    {0x46, 0x00, 0x80, 0, 0, 1336, 0, 0, 0, (MenuCallback)menuTool_tunaideGCEntry00_Button, (MenuCallback)menuTool_tunaideGCEntry00_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 1397, 0, 0, 0, (MenuCallback)menuTool_tunaideGCEntry01_Button, (MenuCallback)menuTool_tunaideGCEntry01_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 409, 0, 0, 0, (MenuCallback)menuTool_tunaideGCEntry02_Button, (MenuCallback)menuTool_tunaideGCEntry02_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 439, 0, 0, 0, (MenuCallback)menuTool_tunaideGCEntry03_Button, (MenuCallback)menuTool_tunaideGCEntry03_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 457, 0, 0, 0, (MenuCallback)menuTool_tunaideGCEntry04_Button, (MenuCallback)menuTool_tunaideGCEntry04_Ctrl, 0},
    {0x63, 0x00, 0x00, 0, 0, 283, 400, 240, 0, 0, 0, 0},
    {0x29, 0x02, 0x20, 0, 0, 1298, 100, 0, 0, 0, (MenuCallback)menuIntUnderTakerMainCtrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 545, 0, 0, 0, (MenuCallback)menuTool_tunaideGCEntry_Button, (MenuCallback)menuTool_tunaideGCEntry_Ctrl, 0},
    {0x2C, 0x82, 0x20, 0, 0, 1499, 0, 0, 0, 0, (MenuCallback)fn_80091C10, 0},
    {0x6C, 0x18, 0x20, 0, 0, 284, 160, 200, (MenuCallback)dbgMenuMenuWorldMapCursor, 0, 0, 0},
    {0x46, 0x00, 0x80, 0, 0, 598, 0, 0, 0, (MenuCallback)menuTool_tunaidePokemonSelect0_Button, (MenuCallback)menuTool_tunaidePokemonSelect0_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 1009, 0, 0, 0, (MenuCallback)menuTool_tunaidePokemonSelect1_Button, (MenuCallback)menuTool_tunaidePokemonSelect1_Ctrl, 0},
    {0x2C, 0x82, 0x20, 0, 0, 1333, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x88, 0x80, 0, 0, 1348, 0, 0, (MenuCallback)menuBingoSheetCur, (MenuCallback)menuBingoSheetBtn, (MenuCallback)menuBingoSheetCtrl, 0},
    {0x28, 0x82, 0x20, 0, 0, 1390, 0, 0, 0, 0, 0, 0},
    {0x28, 0x82, 0x20, 0, 0, 2261, 0, 0, 0, 0, 0, 0},
    {0x46, 0x00, 0x80, 0, 0, 959, 0, 0, 0, (MenuCallback)menuTool_tunaide01_1_Button, (MenuCallback)menuTool_tunaide01_1_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 666, 0, 0, 0, (MenuCallback)menuTool_tunaide01_2_Button, (MenuCallback)menuTool_tunaide01_2_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 673, 0, 0, 0, (MenuCallback)menuTool_tunaide01_3_Button, (MenuCallback)menuTool_tunaide01_3_Ctrl, 0},
    {0x46, 0x00, 0x00, 0, 0, 676, 0, 0, 0, 0, (MenuCallback)menuTool_tunaide_back_Ctrl, 0},
    {0x20, 0x00, 0x00, 0, 0, 1479, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 1489, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x82, 0x20, 0, 0, 1506, 0, 0, 0, 0, (MenuCallback)fn_80091D40, 0},
    {0x20, 0x00, 0x00, 0, 0, 1751, 0, 0, 0, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 941, 0, 0, 0, 0, 0, (MenuCallback)menuPokemonChangeDraw},
    {0x20, 0x00, 0x00, 0, 0, 1520, 0, 0, 0, 0, (MenuCallback)menuPokemonChangeCtrl, 0},
    {0x20, 0x00, 0x00, 0, 0, 1564, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x18, 0x20, 0, 0, 1569, 0, 0, (MenuCallback)menuPokemonChangeCursor, 0, (MenuCallback)menuPokemonChangeCtrl, 0},
    {0x6C, 0x18, 0x20, 0, 0, 284, 160, 200, (MenuCallback)dbgMenuMenuWorldMapCursor, 0, 0, 0},
    {0x20, 0x00, 0x00, 0, 0, 1624, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x12, 0x20, 0, 0, 1629, 0, 0, 0, 0, (MenuCallback)menuScriptUsohachiCtrl, 0},
    {0x20, 0x00, 0x80, 0, 0, 941, 0, 0, 0, (MenuCallback)menuPocketToolCMetaButton, (MenuCallback)menuPocketToolCMetaCtrl, (MenuCallback)menuPocketToolCMetaDraw},
    {0x2C, 0x12, 0x20, 0, 0, 1641, 0, 0, 0, 0, (MenuCallback)menuSaveLoadCtrl, 0},
    {0x28, 0x82, 0x20, 0, 0, 1642, 0, 0, 0, 0, 0, 0},
    {0x24, 0x00, 0x00, 0, 0, 1586, 0, 0, 0, 0, (MenuCallback)menuPokemonChangeCtrl, 0},
    {0x24, 0x00, 0x00, 0, 0, 1614, 0, 0, 0, 0, (MenuCallback)menuPokemonChangeCtrl, 0},
    {0x20, 0x00, 0x00, 0, 0, 2036, 0, 0, 0, 0, 0, 0},
    {0xCC, 0x00, 0x00, 0, 0, 120, 0, 0, 0, 0, (MenuCallback)fn_800860E8, 0},
    {0x20, 0x00, 0x00, 0, 0, 1620, 0, 0, 0, 0, 0, 0},
    {0x4E, 0x14, 0x80, 2, 0, 1222, 0, 0, 0, (MenuCallback)menuTool_Cursol_Button, (MenuCallback)menuTool_Cursol_Ctrl, 0},
    {0x20, 0x00, 0x00, 0, 0, 36, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x18, 0x20, 0, 0, 1690, 0, 0, (MenuCallback)menuScriptWazaOshieCursor, 0, (MenuCallback)menuScriptWazaOshieCtrl, 0},
    {0x2C, 0x18, 0x20, 0, 0, 1690, 0, 0, (MenuCallback)menuScriptWazaOshieCursor, 0, (MenuCallback)menuScriptWazaOshieCtrl, 0},
    {0x46, 0x00, 0x00, 0, 0, 738, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x18, 0x20, 0, 0, 1756, 0, 0, (MenuCallback)menuBdisk_selectL_Btn, 0, 0, 0},
    {0x2C, 0x14, 0x20, 0, 0, 1803, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x12, 0x20, 0, 0, 1819, 0, 0, 0, 0, (MenuCallback)fn_800A08C0, 0},
    {0x24, 0x02, 0x20, 0, 0, 2034, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x02, 0x20, 0, 0, 1871, 0, 0, 0, 0, 0, 0},
    {0x20, 0x08, 0x20, 0, 0, 1913, 0, 0, (MenuCallback)menuBattleDiskCtrl, 0, (MenuCallback)fn_8009EA68, 0},
    {0x28, 0x12, 0x20, 0, 0, 1957, 0, 0, 0, 0, 0, 0},
    {0x28, 0x12, 0x20, 0, 0, 1964, 0, 0, 0, 0, 0, 0},
    {0x46, 0x00, 0x80, 0, 0, 739, 0, 0, 0, (MenuCallback)menuTool_Rule01_Button, (MenuCallback)menuTool_Rule01_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 797, 0, 0, 0, (MenuCallback)menuTool_Rule02_Button, (MenuCallback)menuTool_Rule02_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 826, 0, 0, 0, (MenuCallback)menuTool_Rule03_Button, (MenuCallback)menuTool_Rule03_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 853, 0, 0, 0, (MenuCallback)menuTool_Rule04_Button, (MenuCallback)menuTool_Rule04_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 889, 0, 0, 0, (MenuCallback)menuTool_Rule05_Button, (MenuCallback)menuTool_Rule05_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 910, 0, 0, 0, (MenuCallback)menuTool_Rule06_Button, (MenuCallback)menuTool_Rule06_Ctrl, 0},
    {0x46, 0x00, 0x80, 0, 0, 935, 0, 0, 0, (MenuCallback)menuTool_Rule00_Button, (MenuCallback)menuTool_Rule00_Ctrl, 0},
    {0x24, 0x02, 0x20, 0, 0, 2175, 0, 0, 0, 0, (MenuCallback)fn_80091CA8, 0},
    {0x46, 0x00, 0x80, 0, 0, 987, 0, 0, 0, (MenuCallback)menuTool_tunaide01_4_Button, (MenuCallback)menuTool_tunaide01_4_Ctrl, 0},
    {0x20, 0x02, 0x20, 0, 0, 2044, 0, 0, 0, 0, 0, 0},
    {0x20, 0x02, 0x20, 0, 0, 2045, 0, 0, 0, 0, 0, 0},
    {0x20, 0x02, 0x20, 0, 0, 2047, 0, 0, 0, 0, 0, 0},
    {0x20, 0x02, 0x20, 0, 0, 2046, 0, 0, 0, 0, 0, 0},
    {0xCC, 0x12, 0x20, 0, 0, 34, 0, 0, 0, 0, (MenuCallback)menuOrreCtrl, 0},
    {0xCC, 0x14, 0x80, 0, 0, 41, 0, 0, 0, (MenuCallback)menuOrreButton, (MenuCallback)menuOrreCtrl, 0},
    {0xCC, 0x12, 0x20, 0, 0, 28, 0, 0, 0, 0, (MenuCallback)menuOrreCtrl, 0},
    {0xCC, 0x12, 0x20, 0, 0, 40, 0, 0, 0, 0, (MenuCallback)menuOrreCtrl, 0},
    {0x24, 0x02, 0x20, 0, 0, 2048, 0, 0, 0, 0, (MenuCallback)fn_80091DD8, 0},
    {0x2C, 0x12, 0x20, 0, 0, 1629, 0, 0, 0, 0, (MenuCallback)menuScriptUsohachiCtrl, 0},
    {0x20, 0x00, 0x00, 0, 0, 1624, 0, 0, 0, 0, 0, 0},
    {0x46, 0x00, 0x80, 0, 0, 1208, 0, 0, 0, (MenuCallback)menuTool_BattleBA06_Button, (MenuCallback)menuTool_BattleBA06_Ctrl, 0},
    {0x46, 0x00, 0x00, 0, 0, 1220, 0, 0, 0, 0, 0, 0},
    {0x46, 0x00, 0x00, 0, 0, 1221, 0, 0, 0, 0, 0, 0},
    {0x4E, 0x14, 0x80, 5, 0, 1322, 0, 0, 0, (MenuCallback)menuTool_imasugu01_Button, (MenuCallback)menuTool_imasugu01_Ctrl, 0},
    {0x8C, 0x58, 0x80, 0, 0, 1, 0, 0, (MenuCallback)menuPdaCursorCtrl, (MenuCallback)menuPdaButton, (MenuCallback)menuPdaTopCtrl, 0},
    {0x63, 0x00, 0x00, 0, 0, 289, 40, 40, 0, 0, 0, 0},
    {0x2C, 0x18, 0x20, 0, 0, 1871, 0, 0, (MenuCallback)fn_8009E664, 0, (MenuCallback)fn_8009E9FC, 0},
    {0x6C, 0x18, 0x20, 0, 0, 280, 160, 200, (MenuCallback)dbgMenuEsabaDebugCursor, 0, 0, 0},
    {0xA0, 0x00, 0x00, 0, 0, 176, 0, 0, 0, 0, 0, 0},
    {0xCC, 0x12, 0x20, 0, 0, 43, 0, 0, 0, 0, (MenuCallback)menuOrreCtrl, 0},
    {0x46, 0x00, 0x00, 0, 0, 1443, 0, 0, 0, 0, (MenuCallback)menuTool_tunaideGCEntry02_1_Ctrl, 0},
    {0x46, 0x00, 0x00, 0, 0, 1503, 0, 0, 0, 0, (MenuCallback)menuTool_tunaideGCEntry04_1_Ctrl, 0},
    {0x46, 0x00, 0x00, 0, 0, 1425, 0, 0, 0, 0, (MenuCallback)menuTool_tunaideGCEntry03_1_Ctrl, 0},
    {0x46, 0x00, 0x00, 0, 0, 1518, 0, 0, 0, 0, (MenuCallback)menuTool_FlashCtrl, 0},
    {0x6C, 0x18, 0x20, 0, 0, 290, 160, 200, (MenuCallback)dbgMenuUnderTakerebugCursor, 0, 0, 0},
    {0xC4, 0x00, 0x80, 0, 0, 50, 0, 0, 0, (MenuCallback)menuNintendoWarningButton, (MenuCallback)menuNintendoWarningCtrl, 0},
    {0x46, 0x00, 0x00, 0, 0, 1521, 0, 0, 0, 0, (MenuCallback)menuTool_MASK_Ctrl, 0},
    {0xA0, 0x00, 0x00, 0, 0, 582, 13, 202, 0, 0, 0, 0},
    {0xA0, 0x00, 0x00, 0, 0, 604, 160, 329, 0, 0, 0, 0},
    {0xCC, 0x12, 0x20, 0, 0, 55, 0, 0, 0, 0, (MenuCallback)menuTopSelectCtrl, 0},
    {0xCC, 0x18, 0x80, 0, 0, 74, 0, 0, (MenuCallback)menuTitleOptionCursorControl, (MenuCallback)menuTitleOptionButton, (MenuCallback)menuTitleOptionCtrl, 0},
    {0xCC, 0x12, 0x20, 0, 0, 105, 0, 0, 0, 0, (MenuCallback)menuTopBattleSelectCtrl, 0},
    {0xCD, 0x00, 0x00, 0, 0, 117, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x14, 0x20, 0, 0, 2239, 0, 0, 0, 0, 0, 0},
    {0x2C, 0x14, 0x20, 0, 0, 2245, 0, 0, 0, 0, 0, 0},
    {0xAC, 0x68, 0x80, 0, 0, 626, 9, 312, (MenuCallback)menuFightCurIkousan, (MenuCallback)menuFightButtonIwaza1p, 0, 0},
    {0xAC, 0x68, 0x80, 0, 0, 651, 318, 312, (MenuCallback)menuFightCurIkousan, (MenuCallback)menuFightButtonIwaza1p, 0, 0},
    {0xCC, 0x18, 0x80, 0, 0, 121, 0, 0, (MenuCallback)menuTitleOptionCursorControl, (MenuCallback)menuTitleOptionButton, (MenuCallback)menuTitleOptionCtrl, 0},
    {0xCC, 0x12, 0x80, 0, 0, 158, 0, 0, 0, (MenuCallback)fn_80085E3C, 0, 0},
};

u32 _menu_data_number = sizeof(_menu_data) / sizeof(_menu_data[0]);
