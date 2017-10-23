#include "asserttrue.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

// Test for fullDeckCount

int main () {
    int i;

    struct gameState state;
    state.numPlayers = MAX_PLAYERS;
    
    printf("\nTesting fullDeckCount:\n");

    // Test that all players' hands can be properly accessed
    for (i = 0; i < MAX_PLAYERS; ++i) {
        state.handCount[i] = 1;
        state.hand[i][0] = tribute;

        state.deckCount[i] = 1;
        state.deck[i][0] = tribute;

        state.discardCount[i] = 1;
        state.discard[i][0] = tribute;

        assertTrue(fullDeckCount(i, tribute, &state) == 3);
    }
    
    // Test card boundaries for deck, hand, and discard
    //   curse (card index 0)
    state.handCount[0] = 1;
    state.hand[0][0] = curse;
    assertTrue(fullDeckCount(0, curse, &state) == 1);

    state.deckCount[0] = 1;
    state.deck[0][0] = curse;
    assertTrue(fullDeckCount(0, curse, &state) == 2);

    state.discardCount[0] = 1;
    state.discard[0][0] = curse;
    assertTrue(fullDeckCount(0, curse, &state) == 3);

    //   Then treasure_map (highest card index)
    state.handCount[0] = 1;
    state.hand[0][0] = treasure_map;
    assertTrue(fullDeckCount(0, treasure_map, &state) == 1);

    state.deckCount[0] = 1;
    state.deck[0][0] = treasure_map;
    assertTrue(fullDeckCount(0, treasure_map, &state) == 2);

    state.discardCount[0] = 1;
    state.discard[0][0] = treasure_map;
    assertTrue(fullDeckCount(0, treasure_map, &state) == 3);

    // Test that it is counting matching cards not just all cards for
    // Deck, Hand, and Discard
    state.hand[0][0] = duchy;
    assertTrue(fullDeckCount(0, duchy, &state) == 1);

    state.deck[0][0] = copper;
    assertTrue(fullDeckCount(0, copper, &state) == 1);

    state.discard[0][0] = mine;
    assertTrue(fullDeckCount(0, mine, &state) == 1);

    // Test empty deck, hand, and discard
    state.handCount[0] = 0;
    state.deckCount[0] = 0;
    state.discardCount[0] = 0;
    assertTrue(fullDeckCount(0, 0, &state) == 0);

    // Test deck, hand, and discard full of card
    state.handCount[0] = MAX_HAND;
    for (i = 0; i < MAX_HAND; i++)
        state.hand[0][i] = gold;
    assertTrue(fullDeckCount(0, gold, &state) == MAX_HAND);

    state.handCount[0] = 0;
    state.deckCount[0] = MAX_DECK;
    for (i = 0; i < MAX_DECK; i++)
        state.deck[0][i] = gold;
    assertTrue(fullDeckCount(0, gold, &state) == MAX_DECK);

    state.deckCount[0] = 0;
    state.discardCount[0] = MAX_HAND;
    for (i = 0; i < MAX_HAND; i++)
        state.discard[0][i] = gold;
    assertTrue(fullDeckCount(0, gold, &state) == MAX_HAND);

    //   All 3 maxed out
    state.deckCount[0] = MAX_DECK;
    state.handCount[0] = MAX_HAND;
    assertTrue(fullDeckCount(0, gold, &state) == 2 * MAX_DECK + MAX_HAND);



}
