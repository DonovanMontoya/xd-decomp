#include <dolphin/types.h>

typedef struct FightJoukenLinkData { u8 joint; u16 joukenDataId; u16 nextLinkDataId; } FightJoukenLinkData;

FightJoukenLinkData fight_jouken_link_data[] = {{0, 0, 0}};

u32 fight_jouken_link_data_number = 1;
