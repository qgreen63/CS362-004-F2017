#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

// Test for supplyCount

int main () {
    int i;
    // This should be the most a supply pile can have in game 
    // (coppers starting supply with 2 players)
    int maxSupply = 46; 

    struct gameState state;
    for (i = 0; i < treasure_map; ++i)
        state.supplyCount[i] = 0;

    printf("\nTesting supplyCount:\n");


    // Make sure that the counts for all of the supply piles can be accessed
    int sum = 0; 
    for (i = 0; i < treasure_map; ++i)
       sum += supplyCount(i, &state);
    assertTrue(!sum);

    // Boundary test possible supply count values.
    // Min has already been completed in last test
    
    state.supplyCount[0] = maxSupply;
    assertTrue(supplyCount(0, &state) == maxSupply);
}
    
