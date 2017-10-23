#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

// Test for adventurer card

int isTreasure(int card) {
    if (card == copper || card == silver || card == gold)
        return 1;
    return 0;
}

int main () {
    int i;

    int bonus = 0;
    int seed = 10;
    int numPlayer = MAX_PLAYERS;

    int k[10] = { smithy,
                  adventurer,
                  council_room,
                  remodel,
                  baron,
                  steward,
                  ambassador,
                  sea_hag,
                  treasure_map,
                  minion,
                };

    struct gameState state;
    initializeGame(numPlayer, k, seed, &state);


    // We can play any card as if it were a advneturer by calling cardEffect
    // and passing in advneturer as the card type. Makes testing cards a LOT easier.
    
    for (i = 0; i < MAX_PLAYERS; ++ i) { // Test playing a adventurer card for each player
        int t = state.whoseTurn;

        int handCount = state.handCount[t];
        int cardToPlay = state.hand[t][0];      

        cardEffect(adventurer, 0, 0, 0, &state, 0, &bonus);
        int handIndex = state.handCount[t] - 1;
        // Both of the most recently drawn cards in hand should be treasure
        assertTrue(isTreasure(state.hand[t][handIndex]) && isTreasure(state.hand[t][handIndex-1]));
        assertTrue(handCount + 1 == state.handCount[t]); //Cards in hand go up one (gain 2, but lose the adventurer card)
        assertTrue(state.playedCards[state.playedCardCount - 1] == cardToPlay); // Last played card matches the card we played 

        endTurn(&state); // Move on to the next person
    }
}

