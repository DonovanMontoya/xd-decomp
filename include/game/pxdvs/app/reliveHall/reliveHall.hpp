#ifndef PXDVS_APP_RELIVEHALL_HPP
#define PXDVS_APP_RELIVEHALL_HPP

#include <game/pxdvs/app/pokemon/pokemon.hpp>

class CReliveStage {
public:
    Pokemon dancer[4];
    Pokemon visitor;
    s8 pairIndex;

    void init();
    void pickupVisitor(Pokemon &);
    void insertDancer(Pokemon &, long);
    void pickupDancer(Pokemon &, long);
    void exchangeVisitor(Pokemon &);
    void exchangeDancer(Pokemon &, long);
    s32 getDancerQuantity();
    Pokemon *getDancerPointer(long);
    void putVisitor(Pokemon &);
    void putDancer(Pokemon &);
    s32 getEmptyDancerIndex();
    Pokemon *getVisitorPointer();
    s32 getState();
    bool isLugiaReliveReady();
    bool isReliveReady();
    Pokemon *heroWalkReliveCallBack(long, bool);
    bool isPokemonZokuseiAllUnique(bool);
    s32 getTempo();
    s32 getPassionWoBonus();
    bool isBonusGet();
    s32 getPassion();
};

class CReliveHall {
public:
    CReliveStage stages[9];

    void debugPokemonSetup(long);
    static bool isOpen();
    static CReliveHall *getPointer();
    CReliveStage *getStageAt(long);
    bool isReliveReadyDarkLugiaExist();
    s32 getReliveReadyVisitorQuantity();
    bool isReliveReadyPokemonExist();
    Pokemon *heroWalkReliveCallBack(long);
    void init();
    CReliveStage *getStage(long);
    void allocMakeBackup();
    void checkWithBackupSet();
    s32 getReliveGiveStageQuantity();
};

typedef char CReliveStageVisitorOffset[offsetof(CReliveStage, visitor) == 0x310 ? 1 : -1];
typedef char CReliveStagePairOffset[offsetof(CReliveStage, pairIndex) == 0x3D4 ? 1 : -1];
typedef char CReliveStageSize[sizeof(CReliveStage) == 0x3D8 ? 1 : -1];
typedef char CReliveHallSize[sizeof(CReliveHall) == 0x2298 ? 1 : -1];

#endif
