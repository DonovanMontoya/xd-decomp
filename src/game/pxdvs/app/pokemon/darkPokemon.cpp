#include <game/pxdvs/app/pokemon/darkPokemon.hpp>
#include <game/pxdvs/app/deck/deck_layout.hpp>
class darkpokemonIterateListener {public:virtual u8 exec(unsigned long,DeckDarkPokemon*,DarkPokemon*)=0;};
extern "C" {
DarkPokemon *savedataGetStatus(int,int);void deckInitDarkPokemon(DarkPokemon*);DeckDarkPokemon *deckGetDeckDarkPokemon(u32);u32 deckGetDarkPokemonSize();
DarkPokemon *darkPokemonGetDarkPokemon(u32 index){DarkPokemon *p=savedataGetStatus(0,15);if(index<128)return p+index;return 0;}
void darkpokemonValInit(){deckInitDarkPokemon(savedataGetStatus(0,15));}
}
u8 darkpokemonScenarioPokemonIterate(darkpokemonIterateListener *listener){if(!listener)return 0;for(u32 i=0;i<deckGetDarkPokemonSize();i++){DeckDarkPokemon *deck=deckGetDeckDarkPokemon(i);DarkPokemon *dark=darkPokemonGetDarkPokemon(i);if(deck && dark && deck->isScenarioPokemon()){if(!listener->exec(i,deck,dark))return 0;}}return 1;}
void DarkPokemon::setPlace(darkPokemonWhere p,u8 s){placeFlags.place=p;placeIndex=0;if(p==place1){if(s<=6)placeIndex=s;}else if(p==place2)placeIndex=s;else if(p==place3)placeIndex=s;}
f32 DarkPokemon::getDarkPoint() const{return darkPoint;}
void DarkPokemon::setDarkPoint(f32 f){s32 point=f;f32 limited;if((f32)point<65535.0f)limited=point;else limited=65535.0f;darkPoint=limited;}
extern "C" {
u32 darkPokemonGetMeetNum(){class openDarkPokeInfo:public darkpokemonIterateListener{public:u32 count;u8 exec(unsigned long,DeckDarkPokemon*,DarkPokemon *dark){if(dark->getStatus()>0)count++;return 1;}}info;info.count=0;darkpokemonScenarioPokemonIterate(&info);return info.count;}
u32 darkPokemonGetSnatchSuccessNum(){class openDarkPokeInfo:public darkpokemonIterateListener{public:u32 count;u8 exec(unsigned long,DeckDarkPokemon*,DarkPokemon *dark){if(dark->isSnach())count++;return 1;}}info;info.count=0;darkpokemonScenarioPokemonIterate(&info);return info.count;}
u32 darkPokemonGetReliveNum(){class openDarkPokeInfo:public darkpokemonIterateListener{public:u32 count;u8 exec(unsigned long,DeckDarkPokemon*,DarkPokemon *dark){if(dark->isRelive())count++;return 1;}}info;info.count=0;darkpokemonScenarioPokemonIterate(&info);return info.count;}
u8 darkpokemonCheckUnderTaker(){class openDarkPokeInfo:public darkpokemonIterateListener{public:u32 count;u8 exec(unsigned long,DeckDarkPokemon *deck,DarkPokemon *dark){if(dark->getStatus()==darkStatus2&&!dark->isSnach()&&deck->getWorth()&&dark->getCatchFloorId()!=0xb5)count++;return 1;}}info;info.count=0;darkpokemonScenarioPokemonIterate(&info);return info.count!=0;}
}
