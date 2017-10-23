#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

// Test for updateCoins

int main () {
    int i;
    int maxBonus = 10;

    // Not using initialize game because most of what it does
    // is unnecessary for this test and the initialized values 
    // just need to be changed almost immediately anyway
    struct gameState state;
    state.numPlayers = MAX_PLAYERS;
    for (i = 0; i < MAX_PLAYERS; ++i)
        state.handCount[i] = 5;

    printf("\nTesting updateCoins:\n");

    // Start by testing to make sure all players' hands and handcounts can be accessed
    // without errors or crashing. If each player's hand array can be accessed, 
    // the remainder of the testing can be completed for only a single player

    for (i = 0; i < MAX_PLAYERS; ++i)
        assertTrue(updateCoins(i, &state, 0) == 0);

    // Test updateCoins if a player has no cards and no bonus
    state.handCount[0] = 0;
    updateCoins(0, &state, 0);
    assertTrue(state.coins == 0);

    // No cards, max bonus
    updateCoins(0, &state, maxBonus);
    assertTrue(state.coins == maxBonus);

    // Mixed hand, no bonus
    state.handCount[0] = 3;
    state.hand[0][0] = copper;
    state.hand[0][1] = silver;
    state.hand[0][2] = gold;
    updateCoins(0, &state, 0);
    assertTrue(state.coins == 6);

    // Mixed hand, max bonus
    updateCoins(0, &state, maxBonus);
    assertTrue(state.coins == 6 + maxBonus);

    // Full hand of coppers, no bonus
    state.handCount[0] = MAX_HAND;
    for (i = 0; i < MAX_HAND; ++i)
        state.hand[0][i] = copper;
    updateCoins(0, &state, 0);
    assertTrue(state.coins == MAX_HAND);

    // Full hand of coppers max bonus
    updateCoins(0, &state, maxBonus);
    assertTrue(state.coins == MAX_HAND + maxBonus);

    // Full hand of silvers, no bonus
    for (i = 0; i < MAX_HAND; ++i)
        state.hand[0][i] = silver;
    updateCoins(0, &state, 0);
    assertTrue(state.coins == 2 * MAX_HAND);

    // Full hand of silvers max bonus
    updateCoins(0, &state, maxBonus);
    assertTrue(state.coins == 2 * MAX_HAND + maxBonus);

    // Full hand of golds, no bonus
    for (i = 0; i < MAX_HAND; ++i)
        state.hand[0][i] = gold;
    updateCoins(0, &state, 0);
    assertTrue(state.coins == 3 * MAX_HAND);

    // Full hand of golds max bonus
    updateCoins(0, &state, maxBonus);
    assertTrue(state.coins == 3 * MAX_HAND + maxBonus);
}
