#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

// Test for village card

// This is fairly minimal as most of the functionality of the village card 
// is handled by the drawCard and discardCard functions (which of course should
// have their own unit tests rather than piggy backing on this one).

int main () {
    int i;

    int bonus = 0;
    int seed = 10;
    int numPlayer = MAX_PLAYERS;

    int k[10] = { village,
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


    // We can play any card as if it were a village by calling cardEffect
    // and passing in village as the card type. Makes testing cards a LOT easier.
    
    for (i = 0; i < MAX_PLAYERS; ++ i) { // Test playing a village card for each player
        int t = state.whoseTurn;
        int numActions = state.numActions;
        int handCount = state.handCount[t]; // Remember how many cards in hand
        int cardToPlay = state.hand[t][0]; // Remember what type the card at position 0 is.

        cardEffect(village, 0, 0, 0, &state, 0, &bonus); // Play it, tricking the game in to thinking its a village
        assertTrue(state.handCount[t] == handCount); // Hand count should stay the same (play one card, draw another)
        // The card played should be added to the end of the played card array
        assertTrue(state.playedCards[state.playedCardCount - 1] == cardToPlay); 
        assertTrue(state.numActions == 2 + numActions);

        endTurn(&state); // Move on to the next person
    }
}
