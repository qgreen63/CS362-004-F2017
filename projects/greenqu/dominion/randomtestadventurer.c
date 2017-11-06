#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

// Random Test Generator for adventure card

int isTreasure(int card) {
    if (card == copper || card == silver || card == gold)
        return 1;
    return 0;
}

int randomTestGen(int iterations) {
    int i;
    int j;
    int t;
    int cardIndex;
    int bonus = 0;

    int numPlayer = MAX_PLAYERS;

    int handCount;
    int deckCount;
    int discardCount;
    int cardToPlay;
    int numDeckTreasure;
    int numDiscardTreasure;

    int treasureToTake;


    struct gameState state;

    for (j = 0; j < iterations; ++j) {
        printf("Run %d\n", j + 1);

        // Pick a random player
        t = rand() % numPlayer;
        
        state.whoseTurn = t;


        // Pick them a random deck
        deckCount = rand() % (MAX_DECK + 1);
        for (i = 0; i < deckCount; ++i)
            state.deck[t][i] = rand() % (treasure_map + 1);

        // Discard a random number of cards from deck
        discardCount = rand() % (deckCount + 1);
        for (i = 0; i < discardCount; ++i)
            state.discard[t][i] = state.deck[t][deckCount - 1 - i];
        deckCount -= discardCount;

        // Randomly create a hand
        handCount = rand() % (MAX_HAND - 1); // Leave room for treasure cards
        for (i = 0; i < handCount; ++ i)
            state.hand[t][i] = rand() % (treasure_map + 1);

        // Choose which card to play (doesn't have to be an adventurer)
        cardIndex = rand() % (handCount + 1);

        // Update state variables
        state.numPlayers = numPlayer;
        state.handCount[t] = handCount;
        state.deckCount[t] = deckCount;
        state.discardCount[t] = discardCount;
        cardToPlay = cardIndex;      
        numDeckTreasure = 0;
        numDiscardTreasure = 0;

        treasureToTake = 2;

        for (i = 0; i < deckCount; ++i)
            if (isTreasure(state.deck[t][i]))
                ++numDeckTreasure;

        for (i = 0; i < discardCount; ++i)
            if (isTreasure(state.discard[t][i]))
                ++numDiscardTreasure;
        
        // Play the selected card as if it were an adventurer
        cardEffect(adventurer, 0, 0, 0, &state, cardIndex, &bonus);

        // Verify that everything worked right
        if (numDeckTreasure + numDiscardTreasure < 2) { // Not enough treasure. Take whats there and discard everything else
                treasureToTake = numDeckTreasure + numDiscardTreasure;

                // Discard and deck piles changed appropriately
                assertTrue(state.discardCount[t] == (deckCount + discardCount - 1));
                assertTrue(state.deckCount[t] == 0);

                // None of the cards discarded by adventurer are treasure
                for (i = 0; i < state.discardCount[t]; ++i)
                assertTrue(!isTreasure(state.discard[t][i]));
        }
        else if (numDeckTreasure >= 2) { // No need for discard pile shuffle

            // Discard and deck counts have changed properly reflecting an adventure card w/out shuffle
            assertTrue((deckCount - state.deckCount[t] - 2) == (state.discardCount[t] - discardCount));

            // None of the cards discarded by adventurer are treasure
            for (i = discardCount; i < state.discardCount[t]; ++i)
                assertTrue(!isTreasure(state.discard[t][i]));  
        } 
        else { // Discard pile was shuffled

            // Discard and deck counts have changed properly reflecting an adventure card w/ shuffle
            assertTrue(state.discardCount[t] == (deckCount + (discardCount - state.deckCount[t]) - 2));

            // None of the cards discarded by adventurer are treasure
            for (i = 0; i < state.discardCount[t]; ++i)
                assertTrue(!isTreasure(state.discard[t][i]));  
        }

        // Newly drawn cards should be treasure
        for (i = 1; i <= treasureToTake; ++i)
            assertTrue(isTreasure(state.hand[t][state.handCount[t] - i]));

        //Cards in hand go up 1 less than the amount of treasure taken (adventurer card leaves hand).
        assertTrue(handCount + treasureToTake - 1 == state.handCount[t]);

        // Last played card matches the card we played
        assertTrue(state.playedCards[state.playedCardCount - 1] == cardToPlay);
    }
}

int main () {
    srand(10);
    randomTestGen(1000);
    return 0;
}
