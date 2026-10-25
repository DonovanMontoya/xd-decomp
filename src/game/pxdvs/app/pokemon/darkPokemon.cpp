#pragma dollar_identifiers on
#include <game/pxdvs/app/pokemon/darkPokemon.hpp>
#include <game/pxdvs/app/deck/deck_layout.hpp>
class darkpokemonIterateListener {public:virtual u8 exec(unsigned long,DeckDarkPokemon*,DarkPokemon*)=0;};
extern "C" {
DarkPokemon *savedataGetStatus(int,int);void deckInitDarkPokemon(DarkPokemon*);DeckDarkPokemon *deckGetDeckDarkPokemon(u32);u32 deckGetDarkPokemonSize();
DarkPokemon *darkPokemonGetDarkPokemon(u32 index){DarkPokemon *p=savedataGetStatus(0,15);if(index<128)return p+index;return 0;}
}
void DarkPokemon::setDarkPoint(f32 f){s32 point=f;f32 limited;if((f32)point<65535.0f)limited=point;else limited=65535.0f;darkPoint=limited;}
f32 DarkPokemon::getDarkPoint() const{return darkPoint;}
void DarkPokemon::setPlace(darkPokemonWhere p,u8 s){placeFlags.place=p;placeIndex=0;if(p==place1){if(s<=6)placeIndex=s;}else if(p==place2)placeIndex=s;else if(p==place3)placeIndex=s;}
extern "C" void darkpokemonValInit(){deckInitDarkPokemon(savedataGetStatus(0,15));}
u8 darkpokemonScenarioPokemonIterate(darkpokemonIterateListener *listener){if(!listener)return 0;for(u32 i=0;i<deckGetDarkPokemonSize();i++){DeckDarkPokemon *deck=deckGetDeckDarkPokemon(i);DarkPokemon *dark=darkPokemonGetDarkPokemon(i);if(deck && dark && deck->isScenarioPokemon()){if(!listener->exec(i,deck,dark))return 0;}}return 1;}
extern "C" {
// Preserve the listener class names recorded in the retail symbols.
class openDarkPokeInfo$2060darkPokemon_cpp:public darkpokemonIterateListener{public:u32 count;u8 exec(unsigned long,DeckDarkPokemon*,DarkPokemon *dark){if(dark->getStatus()>0)count++;return 1;}};
u32 darkPokemonGetMeetNum(){openDarkPokeInfo$2060darkPokemon_cpp info;info.count=0;darkpokemonScenarioPokemonIterate(&info);return info.count;}
class openDarkPokeInfo$2066darkPokemon_cpp:public darkpokemonIterateListener{public:u32 count;u8 exec(unsigned long,DeckDarkPokemon*,DarkPokemon *dark){if(dark->isSnach())count++;return 1;}};
u32 darkPokemonGetSnatchSuccessNum(){openDarkPokeInfo$2066darkPokemon_cpp info;info.count=0;darkpokemonScenarioPokemonIterate(&info);return info.count;}
class openDarkPokeInfo$2072darkPokemon_cpp:public darkpokemonIterateListener{public:u32 count;u8 exec(unsigned long,DeckDarkPokemon*,DarkPokemon *dark){if(dark->isRelive())count++;return 1;}};
u32 darkPokemonGetReliveNum(){openDarkPokeInfo$2072darkPokemon_cpp info;info.count=0;darkpokemonScenarioPokemonIterate(&info);return info.count;}
class openDarkPokeInfo$2090darkPokemon_cpp:public darkpokemonIterateListener{public:u32 count;u8 exec(unsigned long,DeckDarkPokemon *deck,DarkPokemon *dark){if(dark->getStatus()==darkStatus2&&!dark->isSnach()&&deck->getWorth()&&dark->getCatchFloorId()!=0xb5)count++;return 1;}};
u8 darkpokemonCheckUnderTaker(){openDarkPokeInfo$2090darkPokemon_cpp info;info.count=0;darkpokemonScenarioPokemonIterate(&info);return info.count!=0;}
}
