#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

// Test for council_room card


int randomTestGen(int iterations) {
    int i;
    int j;
    int t;
    int cardIndex;
    int bonus = 0;

    int numPlayer = MAX_PLAYERS;

    int cardToPlay;

    int handCount[numPlayer];
    int deckCount[numPlayer];
    int numBuys;



    struct gameState state;

    for (j = 0; j < iterations; ++j) {
        printf("Run %d\n", j + 1);


        // Make random decks/hands for everyone
        for (t = 0; t < numPlayer; ++t) {
            // Pick a random deck
            deckCount[t] = rand() % (MAX_DECK + 1);
            for (i = 0; i < deckCount[t]; ++i)
                state.deck[t][i] = rand() % (treasure_map + 1);

            // Randomly create a hand
            handCount[t] = rand() % (MAX_HAND - 1); // Leave room for treasure cards
            for (i = 0; i < handCount[t]; ++ i)
                state.hand[t][i] = rand() % (treasure_map + 1);
        }

        // Randomize played card count
        state.playedCardCount = rand () % MAX_DECK;

        // Pick a random player
        t = rand() % numPlayer;
        
        state.whoseTurn = t;

        // Give them a random number of buys
        numBuys = rand();
        

        // Choose which card to play (doesn't have to be a council_room)
        cardIndex = rand() % (handCount[t] + 1);

        // Update state variables
        state.numPlayers = numPlayer;
        for (i = 0; i < numPlayer; ++i)
            state.handCount[i] = handCount[i];
        for (i = 0; i < numPlayer; ++i)
            state.deckCount[i] = deckCount[i];
        for (i = 0; i < numPlayer; ++i)        
            state.discardCount[i] = 0; // Discard has nothing to do with this card
        state.numBuys = numBuys;
        cardToPlay = cardIndex;   
    
        // Play the selected card as if it was a council_room
        cardEffect(council_room, 0, 0, 0, &state, cardIndex, &bonus);

        // Verify results
        
        // Verify proper card gains
        for (i = 0; i < numPlayer; ++i)
            if (i == t) {
                assertTrue(state.handCount[i] == 3 + handCount[i]); // Current player gains 3 cards net (play 1, draw 4)
            }
            else
                assertTrue(state.handCount[i] == 1 + handCount[i]); // Everyone else gains 1 card. 

        // The card played should be added to the end of the played card array
        assertTrue(state.playedCards[state.playedCardCount - 1] == cardToPlay);

        //Buys should go up 1
        assertTrue(state.numBuys == 1 + numBuys);
    }
}

int main () {
    srand(10);
    randomTestGen(100);
    return 0;
}
