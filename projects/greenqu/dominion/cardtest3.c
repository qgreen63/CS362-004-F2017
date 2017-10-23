#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

// Test for council_room card


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


    // We can play any card as if it were a council_room by calling cardEffect
    // and passing in council_room as the card type. Makes testing cards a LOT easier.
    
    for (i = 0; i < MAX_PLAYERS; ++ i) { // Test playing a council_room card for each player
        int t = state.whoseTurn;  
        int cards[numPlayer];
        int j;
        for (j = 0; j < MAX_PLAYERS; ++j)
            cards[j] = state.handCount[j];
        int numBuys = state.numBuys;
        int cardToPlay = state.hand[t][0]; // Remember what type the card at position 0 is.
        cardEffect(council_room, 0, 0, 0, &state, 0, &bonus); // Play it, tricking the game in to thinking its a council_room

        for (j = 0; j < MAX_PLAYERS; ++j)
            if (j == t)
                assertTrue(state.handCount[j] == 3 + cards[j]); // You gain 3 cards net (play 1, draw 4)
            else
                assertTrue(state.handCount[j] == 1 + cards[j]); // Everyone else gains 1 card. 
        // The card played should be added to the end of the played card array
        assertTrue(state.playedCards[state.playedCardCount - 1] == cardToPlay);
        assertTrue(state.numBuys == 1 + numBuys); // Buys goes up 1

        endTurn(&state); // Move on to the next person
    }
}
