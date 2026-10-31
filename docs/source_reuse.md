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
