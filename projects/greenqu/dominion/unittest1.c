#include "asserttrue.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


// Tests isGameOver

int main () {
    int seed = 10;
    int numPlayer = 3;

    // choose kingdom cards from throughout the enumerator,
    // ensuring that those at the boundaries of the enumeration
    // are represented
    int k[10] = { adventurer,
                  council_room,
                  remodel,
                  baron,
                  steward,
                  ambassador,
                  sea_hag,
                  treasure_map,
                  minion,
                  salvager
                };

    struct gameState cleanState;
    // While not strictly necessary, invoking initialize game does set
    // the supply counts to the proper values saving a lot of work here.
    initializeGame(numPlayer, k, seed, &cleanState);

    struct gameState state = cleanState;

    printf("\nTesting isGameOver:\n");

    // New game shouldn't be over before anything happens
    assertTrue(!isGameOver(&cleanState));

    // Make sure that the game ends when province card supply is depleted
    state.supplyCount[province] = 0;
    assertTrue(isGameOver(&state));

    state = cleanState; // Reset Game

    // Make sure game ends when 3 supply piles are empty
    //   First check boundaries.
    //     First 3 supply piles empty
    state.supplyCount[curse] = 0;
    state.supplyCount[estate] = 0;
    state.supplyCount[duchy] = 0;
    assertTrue(isGameOver(&state));
        
    state = cleanState; // Reset Game

    //     Last 3 supply piles empty
    state.supplyCount[salvager] = 0;
    state.supplyCount[sea_hag] = 0;
    state.supplyCount[treasure_map] = 0;
    assertTrue(isGameOver(&state));

    state = cleanState; // Reset Game

    //   Now check middle of array
    state.supplyCount[copper] = 0;
    state.supplyCount[baron] = 0;
    state.supplyCount[minion] = 0;
    assertTrue(isGameOver(&state));

    state = cleanState; // Reset Game

    // Ensure that the game doesn't end if 2 piles are gone
    state.supplyCount[curse] = 0;
    state.supplyCount[estate] = 0;
    assertTrue(!isGameOver(&state));

    // Ensure that the game ends properly if 3 piles are gone 
    // and one of those piles is the province supply
    state.supplyCount[province] = 0;
    assertTrue(isGameOver(&state));

    state = cleanState; // Reset Game

    // Make sure the game still ends if >3 supply piles are empty
    state.supplyCount[copper] = 0;
    state.supplyCount[silver] = 0;
    state.supplyCount[gold] = 0;
    state.supplyCount[curse] = 0;

    assertTrue(isGameOver(&state));
}
