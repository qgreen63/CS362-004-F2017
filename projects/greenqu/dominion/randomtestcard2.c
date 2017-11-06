#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

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
    int coins;
    int cardToPlay;

    int choice;
    int card1;
    int card2;

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
        handCount = rand() % (MAX_HAND - 1); // Leave room for cards
        for (i = 0; i < handCount; ++ i)
            state.hand[t][i] = rand() % (treasure_map + 1);

        // Randomize played card count
        state.playedCardCount = rand () % MAX_DECK;

        // Random number of coins
        coins = rand();

        // Randomly choose one of the 3 actions for the card
        choice  = rand() % 3;

        // Randomly choose 2 cards from hand
        do {
            card1 = rand() % (handCount + 1);
            card2 = rand() % (handCount + 1);
        } while (card1 != card2);


        // Choose which card to play (doesn't have to be a steward)
        cardIndex = rand() % (handCount + 1);

        // Update state variables
        state.numPlayers = numPlayer;
        state.handCount[t] = handCount;
        state.deckCount[t] = deckCount;
        state.discardCount[t] = discardCount;
        state.coins = coins;
        cardToPlay = cardIndex;      
        
        // Play the selected card as if it were a steward
        cardEffect(steward, choice, card1, card2, &state, cardIndex, &bonus);

        // Verify that everything worked right
        if (choice == 0) { // Trash 2 cards
            printf("Trash\n");

            // Hand has 3 less cards (2 trashed, 1 played)
            assertTrue(state.handCount[t] == handCount - 3);

            // Trashed cards are actually trashed, not discarded
            assertTrue(state.discardCount[t] == discardCount);
        }
        else if (choice == 1) { // Draw 2 cards
            printf("Draw\n");

            // Hand has 1 more card (2 drawn, 1 played)
            assertTrue(state.handCount[t] == handCount + 1);

            // Deck has 2 less cards
            assertTrue(state.deckCount[t] == deckCount - 2);
        }
        else { // + 2 coins
            printf("Coins\n");

            // Hand has 1 less card (the one that was played)
            assertTrue(state.handCount[t] == handCount - 1);

            // Coins has gone up 2
            assertTrue(state.coins == coins + 2);
        } 

        // Last played card matches the card we played
        assertTrue(state.playedCards[state.playedCardCount - 1] == cardToPlay);
    }
    return 0;
}

int main () {
    srand(10);
    randomTestGen(100);
    return 0;
}
