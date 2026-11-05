#include <dolphin/types.h>

/* pokemonFriendFilterDataBiosGetValue sign-extends one of three adjustments. */
typedef struct PokemonFriendFilterDataRecord { s8 value[3]; } PokemonFriendFilterDataRecord;
PokemonFriendFilterDataRecord pokemon_friend_filter_data[] = {
    { { 5, 3, 2 } },
    { { 5, 3, 2 } },
    { { 1, 1, 0 } },
    { { 3, 2, 1 } },
    { { 1, 1, 0 } },
    { { 1, 1, 1 } },
    { { -1, -1, -1 } },
    { { -5, -5, -10 } },
    { { -5, -5, -10 } },
};

u32 pokemon_friend_filter_data_number = sizeof(pokemon_friend_filter_data) / sizeof(pokemon_friend_filter_data[0]);
