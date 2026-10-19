#ifndef DARK_POKEMON_H
#define DARK_POKEMON_H
#include <global.h>
#include <libc/stddef.h>
// One entry per Shadow Pokemon, 0x80 entries (0x48 bytes each) at savedata+0xE380 (savedataBiosGetDarkpokemonPtr).
// Index with darkPokemonGetDarkPokemon(). Layout verified against getStatus/getPokemonID/getCatchFloorId/... in pokemonStatusPokemon.
enum darkPokemonWhere { place0, place1, place2, place3, place4, place5, place6 };
// status (byte 0 >> 5): 0 unseen, 1 seen, 2 lost to Miror B., 3 snagged, 4 purified
enum darkPokemonStatus { darkStatus0, darkStatus1, darkStatus2, darkStatus3, darkStatus4 };
enum darkPokemonSnatchWho { snatchWho0, snatchWho1, snatchWho2, snatchWho3 };
struct DarkPokemon {
    union {
        struct { u8 status:3; u8 reserved:1; u8 infoLevel:3; u8 whoHigh:1; } statusFlags;
        struct { u16 reserved:7; u16 who:2; u16 remainder:7; } snatchFlags;
        struct { u32 reserved:14; u32 place:3; u32 remainder:15; } placeFlags;
        u8 unk0x0[4];
    };
    union {
        struct { u32 poolExp:20; u32 remainder:12; } experience;
        struct { u8 reserved[2]; u8 upper:4; u8 catchBall:4; u8 information:1; u8 remainder:7; } capture;
    };
    u8 reserved08[3];
    u8 statusRnd[6]; // 0x0b
    u8 placeIndex; // 0x11
    u8 reserved12;
    u8 snatchIndex; // 0x13
    u16 orgTrainer; // 0x14
    u16 catchFloorId; // 0x16
    u16 poolFriendLevel; // 0x18
    u16 pokemonID; // 0x1a, species
    u32 rnd; // 0x1c
    u32 escapeOrSnatchTime; // 0x20
    s32 darkPoint; // 0x24, heart gauge
    u16 trainerName[11]; // 0x28
    u16 darkPokemonID; // 0x3e
    u8 reversPattern; // 0x40
    u8 reserved41[3];
    u32 walkCount; // 0x44
    void setPlace(darkPokemonWhere, u8);
    void getPlace(darkPokemonWhere&, u8&) const;
    void setReversMode(bool);
    bool isReversMode() const;
    void setDarkPoint(f32);
    f32 getDarkPoint() const;
    s32 getInitDarkPointDirect() const;
    s32 getDarkPointDirect() const;
    void setDarkPointDirect(s32);
    void setPoolFriendLevel(u16);
    u16 getPoolFriendLevel() const;
    void setPoolExp(u32);
    u32 getPoolExp() const;
    void setTrainerName(const u16*);
    const u16* getTrainerName() const;
    void setStatusRnd(u8,u8);
    u8 getStatusRnd(u8) const;
    void setInformation(bool);
    bool isInformation() const;
    void setUpdate(bool);
    bool isUpdate() const;
    void setWazaNew(u8,bool);
    bool isWazaNew(u8) const;
    void setEscapeTime(u32);
    u32 getEscapeTime() const;
    void setSnatchTime(u32);
    darkPokemonStatus getStatus() const;
    void setStatus(darkPokemonStatus);
    void addStatus(darkPokemonStatus);
    void setSnatchFromWho(darkPokemonSnatchWho);
    darkPokemonSnatchWho getSnatchFromWho() const;
    void setSnatchInfoLevel(u8);
    bool isSnach() const;
    bool isRelive() const;
    void init();
    void setWalkCount(u32);
    u32 getWalkCount() const;
    void setReversPattern(u8);
    u8 getReversPattern() const;
    void setCatchBallID(u16);
    u16 getCatchBallID() const;
    void setDarkPokemonID(u16);
    u16 getDarkPokemonID() const;
    void setPokemonID(u16);
    u16 getPokemonID() const;
    void setRnd(u32);
    u32 getRnd() const;
    void setCatchFloorId(u16);
    u16 getCatchFloorId() const;
    void setOrgTrainer(u16);
    u16 getOrgTrainer() const;
    void setSnatchIndex(u8);
    u8 getSnatchIndex() const;
    struct ModeFlags { u8 reserved:1; u8 revers:1; u8 update:1; u8 wazaNew:3; u8 remainder:2; };
};
typedef char DarkPokemon_size_check[(sizeof(DarkPokemon) == 0x48) ? 1 : -1];
typedef char DarkPokemon_statusRnd_check[(offsetof(DarkPokemon, statusRnd) == 0x0B) ? 1 : -1];
typedef char DarkPokemon_placeIndex_check[(offsetof(DarkPokemon, placeIndex) == 0x11) ? 1 : -1];
typedef char DarkPokemon_orgTrainer_check[(offsetof(DarkPokemon, orgTrainer) == 0x14) ? 1 : -1];
typedef char DarkPokemon_catchFloor_check[(offsetof(DarkPokemon, catchFloorId) == 0x16) ? 1 : -1];
typedef char DarkPokemon_pokemonID_check[(offsetof(DarkPokemon, pokemonID) == 0x1A) ? 1 : -1];
typedef char DarkPokemon_rnd_check[(offsetof(DarkPokemon, rnd) == 0x1C) ? 1 : -1];
typedef char DarkPokemon_darkPoint_check[(offsetof(DarkPokemon, darkPoint) == 0x24) ? 1 : -1];
typedef char DarkPokemon_trainerName_check[(offsetof(DarkPokemon, trainerName) == 0x28) ? 1 : -1];
typedef char DarkPokemon_darkPokemonID_check[(offsetof(DarkPokemon, darkPokemonID) == 0x3E) ? 1 : -1];
typedef char DarkPokemon_walkCount_check[(offsetof(DarkPokemon, walkCount) == 0x44) ? 1 : -1];
extern "C" DarkPokemon* darkPokemonGetDarkPokemon(u32);
extern "C" u8 darkPokemonBiosGetReliveFlag(u16);
extern "C" u16 darkPokemonBiosGetDarkPoint(u16);
#endif
