# Reused matching source

The matching implementations listed below were adapted from these public source
checkpoints. Existing exact functions are retained where compatible with the
recovered types and inline helpers. Each adaptation was compiled with this
project’s configured compiler and checked against the retail object.

- [Pokémon XD Decomp](https://github.com/imyourhuckleberryponcho/Pokemon-XD-Decomp),
  commit `7a84160273832d34c35258b06c113533e767221a` (CC0).
- [Pokémon Colosseum decompilation](https://github.com/dougchansan/pkmn-colosseum),
  commit `e354ba3f0475ac50af3b7d9dccc1f2855be8369c` (MIT).

The XD source also incorporates code from the Colosseum project. The MIT notice
below is retained for those portions and for the two adapted particle renderer
functions. It does not change the license of the rest of this repository.

| Local source (under `src/`) | Newly matched functions |
| --- | --- |
| `game/pxdvs/GSAPI/GSmaterial/GSmaterial.cpp` | `_matGSmatEnableEnvMapExt` |
| `game/pxdvs/GSAPI/GSmodel/blend.cpp` | `modelIntpJObjRotate__FP9_HSD_JObjP9_HSD_JObjP9_HSD_JObjfP5GSvecUl`, `_modelIntpJObjAll__FP8_GSmodelP9_HSD_JObjP9_HSD_JObjP9_HSD_JObjff` |
| `game/pxdvs/GSAPI/GScolsys/GScolsys2Walk.cpp` | `getCpPolyVec__FP5GSvecP5GSvecP5GSvecP5GSvec`, `GScolsys2WalkGetHeight` |
| `game/pxdvs/GSAPI/GScolsys/GScolsys2Hit.cpp` | `checkHitFixedMdl__FP5GSvecfP15CCD_HITMDL_HEADP5GSvec`, `checkHitMdl__FP5GSvecfP15CCD_HITMDL_HEADP5GSmtxP5GSmtxP5GSvec`, `checkHitCollision__FP5GSvecP5GSvecfP5GSvecb` |
| `game/pxdvs/GSAPI/GScolsys/GScolsys2Util.cpp` | `GScolsy2UtilChkInTri` |
| `game/pxdvs/GSAPI/GSparticle/peContainer.cpp` | `__dt__17peRenderContainerFv` |
| `game/maximum/GSAPI/particle/pslist.cpp` | `particleSort` |
| `game/maximum/GSAPI/particle/particle.cpp` | `psInitDataBankLocate`, `psInitDataBank`, `psRemoveParticle` |
| `game/dbgMenuPokemon.cpp` | `dbgMenuPokemonEditButton` |
| `game/menuPda.cpp` | `menuPdaBackDrawTitleText`, `_SelectCursorCalcPositon__FP6GSvec2`, `_SelectCursorCalcAngle__FSc` |
| `game/menuCB_PokemonEntry.cpp` | `_menuCBPokemonEntryWorkInit__Fv` |
| `game/menuToolBattle.cpp` | `_menuCB_FlashStart_WINLOSE__Fv`, `menuToolBattleMain` |
| `game/menuHologram.cpp` | `modelVisitorSetYPosition__Q226@unnamed@menuHologram_cpp@13CMenuHologramFl` |
| `game/pxdvs/app/menu/menu.cpp` | `menuCursorNormal` |
| `game/pxdvs/app/pokemon/pokemonEvolution.cpp` | `getEvoPokemonLevelUp__FP7PokemonPUsP22POKEMON_EVOLUTION_INFO` |
| `game/pxdvs/app/msgctrl/msgctrl.cpp` | `_msgctrlMakeDigit__FPUslUll` |
| `game/pxdvs/app/kouka/kouka.cpp` | `_koukaOneExec__FUlPvPvPl` |
| `game/pxdvs/app/item/itemUse2Pokemon.cpp` | `itemUse2Pokemon` |
| `game/pxdvs/app/fade/fade_fluid.cpp` | `fadeFluidInit` |
| `game/pxdvs/app/wazaSequence/billboard.cpp` | `_update__15billboardEffectFf` |
| `game/pxdvs/app/fight/fightTrainer.cpp` | `fightTrainerSortFightTrainerDataIdToHeroTemotiPokemon`, `_fightTrainerCreateRndCheckRare__FP4Herob`, `_fightTrainer_GetUnderTakerDarkPoke__FPUcUcUcP4HeroUcUs` |
| `game/pxdvs/app/fight/fightPokemonBios.cpp` | `__as__15FightOutPokemonFRC15FightOutPokemon` |
| `game/pxdvs/app/fight/fightSeq/fightSeqWSWaza.cpp` | `CriticalCheckHikaePokemon`, `EscapeNGCheck` |
| `game/pxdvs/app/fight/fightGSfloor.cpp` | `fightGSfloorPopData` |
| `game/pxdvs/app/people/peopleSave.cpp` | `_peopleRestoreAnywaySaveData__FP15GSBinReadStream` |
| `game/pxdvs/app/fight/fightTrainerAiWazaValue.cpp` | `fightTrainerAiWazaValueMamoru`, `fightTrainerAiWazaValueIryokuHonoo` |
| `game/maximum/GSAPI/particle/psdisp.cpp` | `psDispSubAppSRT`, `psDispSub` |
| `game/pxdvs/GSAPI/GSsnd/sndStream.cpp` | `_sndStreamPrepareGetDataCallback` |
| `game/pxdvs/GSAPI/GSinput/GSinput.cpp` | `GSinputMotorStart` |
| `game/pxdvs/app/floor/floorFieldCameraEditor.cpp` | `floorInitFieldCameraEditor` |
| `game/pxdvs/GSAPI/GSbound/GSbound.cpp` | `GSboundIsInViewFast` |
| `game/pxdvs/GSAPI/GSmodel/shadow.cpp` | `modelShadowPrepare__FP8_GSmodelb` |
| `game/pxdvs/GSAPI/GSmovie/GSmovie.cpp` | `_movieStreamTHPPlayerPrepareGetDataCallback__FlPvl` |
| `game/pxdvs/GSAPI/GSmovie/movieStream.cpp` | `_VideoDecode__FP18__GSmovieStreamingP13THPReadBufferP13THPTextureSet` |
| `game/pxdvs/GSAPI/GSshape/shapeObject.cpp` | `DrawShapeGfx__13GsShapeObjectFP10GSgfxLayersUc` |
| `game/pxdvs/GSAPI/GSmodel/GSmodel.cpp` | `_modelRenderModelSub__FP10GSgfxLayer14GSgfxLayerPassP8_GSmodel` |
| `game/pxdvs/GSAPI/GSfsys/GSfsys2.cpp` | `GSfsysFree`, `_fsysBackgroundTaskNormalType`, `_fsysCheckExpandComplete` |
| `game/gbaCommand.cpp` | `gbaCommandRequestAction`, `gbaCommandEntryResult` |
| `game/menuWorldMapMX.cpp` | `ControlPad__8WorldMapFP14tagWINDOW_WORK`, `CheckIconAnime__8WorldMapFl` |
| `game/pxdvs/GSAPI/GSpart/GSpart.cpp` | `GSpartRegisterAnimMix` |
| `game/menuPdaMemoWaveXD.cpp` | `DispFuncSub__14pdaMemoNakigoeFP15NakigoeDispWork12GSgfxLayerID`, `_drawLine__F12GSgfxLayerIDP5GSvecP5GSvecf` |
| `game/pxdvs/app/fight/fightPokemon.cpp` | `fightOutPokemonCopyHensinStatus`, `fightOutPokemonCreateFightPokemonEnemyAryEnemySideAll`, `fightOutPokemonIsFightActionAttackWazaOut`, `fightOutPokemonSetMeetEnemyFightPokemonEnemySideAll` |
| `game/pxdvs/GSAPI/GSgfxM/gamecube.cpp` | `GSgfx_GCWriteTevIndTile` |
| `game/pxdvs/GSAPI/GSScript/tiga.cpp` | `runParamsPC__Q28GSscript4TigaFP7TPCCodePQ28GSscript11tigaVariantib`, `tigaErrMessage__8GSscriptFPCc` |
| `game/dbgMenuFlag.cpp` | `dbgMenuFlagInfoDraw` |
| `game/menuFight.cpp` | `menuFightDrawIwaitStatus`, `menuFightOpenTarget` |
| `game/menuPocketTool.cpp` | `draw__11CInfoWindowFv` |
| `game/menuPocket.cpp` | `_swapItemSlot__24@unnamed@menuPocket_cpp@Fiii`, `_selectItem__24@unnamed@menuPocket_cpp@FRiPl`, `menuPocket2PrintNumMenu`, `menuPocket2PrintItemKind`, `menuPocket2DrawExchangeCursor` |
| `game/menuNameEntry.cpp` | `menuNameEntryDraw50Text`, `menuNameEntryOpen` |
| `game/menuPdaSearcher.cpp` | `_animMojiCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORKUs` |
| `game/menuPdaDPMonitor.cpp` | `DispPokemonModel__10menuPdaDPMFP14tagWINDOW_WORKP14tagSPRITE_WORKP12DPM_CONTENTS` |
| `game/menuScript.cpp` | `menuScriptTutorialCursor` |
| `game/menuSub.cpp` | `menuSubOpenYesNo` |
| `game/dbgMenuSub.cpp` | `dbgMenuGetRootMenu` |
| `game/menuPcBoxDouguNew.cpp` | `menuPcBoxDouguNumDrawNum` |
| `game/menuLogoDemo.cpp` | `menuNintendoWarningCtrl`, `_setTextureWindow__FP14tagWINDOW_WORKP14tagSPRITE_WORKP9GStexture` |
| `game/menuBattleDisk.cpp` | `BattleDiskContentsDraw` |
| `game/pxdvs/GSAPI/GScamera/GScamera.cpp` | `_cameraLoadClipping__FP9_GScameraP10GSgfxLayer` |
| `game/pxdvs/GSAPI/GSlight/GSlight.cpp` | `GSlightSetColor` |
| `game/pxdvs/GSAPI/GSmodel/bound.cpp` | `_modelBoundPObj__FP9_HSD_PObjP5GSmtxP5GSmtxP5GSmtxPv` |
| `game/pxdvs/app/menu/winSprite.cpp` | `winSpriteDrawTexture` |
| `game/pxdvs/app/floor/floorCharacterBios.cpp` | `floorCharacterBiosInitGlobalCharacter` |
| `game/pxdvs/GSAPI/GSflag/GSflag.cpp` | `_flagSet` |
| `game/pxdvs/app/script/appScript.cpp` | `cmpFight__9AppScriptFiPQ28GSscript11tigaVariantPQ28GSscript11tigaVariant` |
| `game/pxdvs/app/script/script.cpp` | `scriptSoundOpenPlayME` |
| `game/pxdvs/app/memcard/memcard.cpp` | `_memcardJobMain__FUlUl` |
| `game/pxdvs/app/wazaSequence/wazaSequenceSys.cpp` | `wazaSequenceSysFreeWazaResource__FP12WazaSequence` |
| `game/pxdvs/app/fight/fightFloor.cpp` | `fightFloorSetTimeOutAllFightResult` |
| `game/pxdvs/app/fight/fightSeq/fightWazaWzx.cpp` | `fightWazaWzxTypeFuncHuuin` |
| `game/pxdvs/app/fight/fightTrainerAi2.cpp` | `_fightTrainerAiCheckHorobinoutaSub` |
| `game/maximum/GSAPI/baselib/displayfunc.cpp` | `HSD_JObjDisp` |
| `game/maximum/GSAPI/baselib/texpdag.cpp` | `assign_reg` |
| `game/menuPcBoxPokemon.cpp` | `loop__Q230@unnamed@menuPcBoxPokemon_cpp@17CMenuPokemonLeaveFv` |
| `game/pxdvs/app/hero/heroMove.cpp` | `getStep__FP8FOOTSTEPP8_GSmodelPiP8FOOTWORK`, `heroMoveMain` |
| `game/pxdvs/app/fade/fade_effect.cpp` | `fadeEffectHookFunction_distortion_zoom__F12GSgfxLayerIDbffffPvb`, `fadeEffectHookFunction_distortion__F12GSgfxLayerIDbffffPv`, `_disp_slide_ball__FP10GSgfxLayerffffi` |

Additional adaptations use XD commit
`50a8d7284ec86bb82c2a387e335a2099cb1a905c` (CC0, with the same inherited MIT notice):

| Local source (under `src/`) | Newly matched functions |
| --- | --- |
| `game/menuCB_PokemonEntry.cpp` | `_menuCBPokemonEntryEntCheck__F13GSinputDevicel` |
| `game/menuCB_Battle.cpp` | `menuCB_InitBattle` |
| `game/menuGBAC.cpp` | `_mainFlow__F15_MENU_GBAC_TYPEUlPP4Hero` |
| `game/menuBingo.cpp` | `menuBattleDeBingoGetEpoint`, `menuBingoSheetBtn`, `setStepMessage__6cBingoFv`, `SetupSheet__6cBingoFUl` |
| `game/pxdvs/GSAPI/GSmsg/GSmsg.cpp` | `GSmsgFontClose`, `_msgDispRuby__FP13MSG_TASK_WORK`, `_msgGetCodeInfo__FP13MSG_TASK_WORKUsPP12tagFONT_INFO` |
| `game/pxdvs/app/menu/menu.cpp` | `menuDaemon` |
| `game/pxdvs/app/menu/menuModel.cpp` | `_menuModelAdjustCamera__FP10MENU_MODELb` |
| `game/pxdvs/app/floor/floorFieldCameraEditor.cpp` | `floorUpdateFieldCameraEditor` |
| `game/pxdvs/app/battleGrid/battleCamera.cpp` | `_battleCameraStartRandom__FP13ModelSequence`, `_battleCameraUpdateWaza__Fv` |
| `game/pxdvs/app/fade/fade_effect.cpp` | `fadeEffectHookFunction_distortion_strip_yoko__F12GSgfxLayerIDbffffPv`, `fadeEffectHookFunction_distortion_strip_tate__F12GSgfxLayerIDbffffPv` |
| `game/pxdvs/app/flashmenu/flashcalc.cpp` | `flcalcMultiTransformColor` |
| `game/pxdvs/GSAPI/GSshape/GSshape.cpp` | `shapePrimitiveEditorRender` |
| `game/pxdvs/GSAPI/GSgfxM/layerState.cpp` | `renderState_NL_VC_T__10GSgfxLayerFUc`, `renderState_NL_NVC_T__10GSgfxLayerFUc` |
| `game/pxdvs/GSAPI/GSmsg/GSmsg.cpp` | `GSmsgGetGSchar` |
| `game/pxdvs/app/wazaSequence/wazaSequenceSys.cpp` | `wazaSequenceSysFreeSequenceResource__FP13ModelSequence` |
| `game/pxdvs/app/wazaSequence/wazaSequenceEntry.cpp` | `Start__10SoundEntryFv` |
| `game/pxdvs/app/fight/fightTrainerAi.cpp` | `fightAi_SelectDefPoke`, `fightAi_AttackResult` |

Two unused math helpers were also restored from the Colosseum checkpoint above:
`HSD_MtxGetScaleMelee` in `src/hsd/mtx.c`, adapted in
`src/game/maximum/GSAPI/baselib/mtx_base.cpp`, and `HSD_QuatLib_8037ECE0` in
`src/hsd/quatlib.c`, adapted as `QuatFromAxisAngle` in
`src/game/maximum/GSAPI/baselib/quatlib.cpp`. Their shared literals restore the
retail data layout; the linker strips the unused helper code. Both linked units
were verified against the retail DOL hash.

## Camera reset helper

`cameraResetOffsets` in `game/pxdvs/app/camera/camera.cpp` was adapted from
[Decomp-Robot/pokemon-xd](https://github.com/Decomp-Robot/pokemon-xd/blob/f5cb7af499cba4ab5af02b03abc7f537b89a9ef4/src/game/app/camera/camera.cpp),
commit `f5cb7af499cba4ab5af02b03abc7f537b89a9ef4` (CC0). The existing calls from
`cameraPlayOffsetAnime` and `cameraInit` share its offset, scale, and optional
field-of-view reset. Both calls inline; the linker removes the unused out-of-line
copy while retaining the shared literal pool. The linked retail DOL hash was
verified after restoring the unit's function and template emission order.

## Battle sequence processing

The following bodies were adapted from
[Decomp-Robot/pokemon-xd](https://github.com/Decomp-Robot/pokemon-xd/tree/f5cb7af499cba4ab5af02b03abc7f537b89a9ef4),
commit `f5cb7af499cba4ab5af02b03abc7f537b89a9ef4` (CC0):

- `WS_WKC_ACT`: `src/game/app/fight/fightSeq/fightSeqBasis.cpp`.
- `fightSeqSoubiItemCheckTurn` and `fightSeqFightOutPokemonTokuseiCheckWazaHitAfter`:
  `src/game/app/fight/fightSeq/fightSeq.cpp`.
- `fightSeqCallExec`: `src/game/app/fight/fightSeq/fightSeqWSWaza.cpp`.

Local adaptations retain the existing types and symbols, with narrow call views
where the retail parameter or return widths differ. Referenced sequence symbols,
relocation offsets, and initializer bytes were checked against the retail object;
all previously exact functions remain exact.

## Additional menu and particle routines

Focused bodies were adapted from
[Decomp-Robot/pokemon-xd](https://github.com/Decomp-Robot/pokemon-xd/tree/b74b73e67debf8b4c7a7277f424650918bb94834),
commit `b74b73e67debf8b4c7a7277f424650918bb94834` (CC0):

- `dbgMenuFight`, `menuPocketBattleDisk`, `menuPcBoxDouguNew`, `menuNameEntry`,
  `menuPocket`, `menuPokemon`, `menuPokemonStatus`, `menuBattleDisk`, and
  `menuPocketTool`: matching draw, cursor, action, and list routines in the
  corresponding menu sources.
- `menuWorldMapMX`: `WorldMap::CalcModel2D`.
- `menuColosseumBattleConnection`: connection main control.
- `GScolsys2Thru`: `GScolsys2ThruPassEventID`.
- `GScolsys2Draw`: hit-model drawing, fixed-object display lists, and the draw entry.
- `menuCB_BattleResult`: `_menuCB_BattleResultTaisen`, named `menuCBResultMain`
  in the donor.
- `GSparticle`: `GSparticlePreUpdate` and `GSparticleLoad`.
- `GSspline`: `GSsplineCreate`.
- `peParticle`: particle depth sorting, container and node rendering, and start.
- `peBank`: `peBankFreeFile`.
- `GSinput`: `_inputUpdateMotors`, including the volatile motor state types.
- `fightTimer`: the used zero and frame-rate constant arrays and exported timer
  API signatures from `src/game/app/fight/fightTimer/fightTimer.cpp`.

Adaptations preserve the existing unit layouts and symbols. Narrow prototype,
member padding, and constant-table corrections follow the retail object. Every
previously exact function remains exact; complete linked units additionally pass
the retail DOL hash check.

The existing `HSD_MObjAlloc` and `HSD_MaterialAlloc` helper emission was restored
using `src/hsd/mobj.c` from
[dougchansan/pkmn-colosseum](https://github.com/dougchansan/pkmn-colosseum/blob/e354ba3f0475ac50af3b7d9dccc1f2855be8369c/src/hsd/mobj.c),
commit `e354ba3f0475ac50af3b7d9dccc1f2855be8369c` (MIT). The linker removes the
unused helpers while retaining their shared literal pool. The linked unit passes
the retail DOL hash check; the license notice below applies.

The natural recursive bodies for `HSD_JObjReqAnimAllByFlags` and
`HSD_JObjDispAll` were restored from XD commit
`50a8d7284ec86bb82c2a387e335a2099cb1a905c`. A scoped inline-size recipe also
matches `HSD_JObjSetMtxDirtySub`, retaining all earlier exact functions. The unit
remains nonmatching pending its complete linked layout.

`GSparticle` retains the genuine unused `GSparticleSetGeneratorZDraw` diagnostic
API. Immediate emission of this unforced function before the deferred functions
preserves the retail diagnostic string order; the linker removes its unused
code. The module initializer remains an ordinary local aggregate. The complete
linked unit passes the retail DOL hash check.

## Particle interpreter and retained runtime helpers

`modifyDirGenBase`, `modifyDir`, and `setVelToJObj` in
`game/maximum/GSAPI/particle/psinterpret.cpp` were adapted from
`src/game/psinterpret.c` at Colosseum commit
`e354ba3f0475ac50af3b7d9dccc1f2855be8369c` (MIT). The native vector fields and
actual double-precision trigonometric calls replace temporary register-shaped
expressions. The retained weak SDK `sqrtf` body is identical to the existing
runtime implementation; normal duplicate removal restores the exact literal
pool and linked retail DOL.

`timeGetVsyncRate` was restored from `src/game/time.cpp` at XD commit
`7a84160273832d34c35258b06c113533e767221a`. Its paused frame-rate conversion
retains the zero and integer-conversion literals shared by the two surviving
time functions. The unused function is stripped, and the linked unit passes the
retail DOL hash check.

The `tobj` layout retains the existing real `HSD_TObjTevAlloc`, `HSD_TlutAlloc`,
and `HSD_Index2TexMap` copies while emitting the original assertion literals.
Normal dead stripping removes their unused code and jump table. The complete
linked unit passes the retail DOL hash check.

## Colosseum license notice

```text
MIT License

Copyright (c) 2026 pkmn-colosseum contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
