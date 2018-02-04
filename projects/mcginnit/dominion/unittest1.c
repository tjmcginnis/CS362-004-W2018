#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * Function under test: kingdomCards
 *
 * What it does:
 *  Creates a new integer array of size 10, and sets each
 *   index of the array to one of the passed in values. It
 *   then returns this array. These 10 cards are the cards
 *   used for the current game.
 * 
 * Side effects:
 *  None
 *
 * Test Cases:
 *  The resulting array contains the 10 cards given as
 *   arguments to kingdomCards. Position actually does
 *   not seem to matter.
 */

// Check if an array contains a value
int array_contains (int* haystack, int needle, int haystackSize) {
    int i;
    for (i = 0; i < haystackSize; i++) {
        if (haystack[i] == needle) {
            return 1;
        }
    }

    return 0;
}

int testKingdomCards () {
     // For the purpose of testing kingdomCards, we can
     // simulate the cards with regular 
    int cards[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

     // Call kingdomCards and pass it each "card"
    int* result = kingdomCards(
        cards[0],
        cards[1],
        cards[2],
        cards[3],
        cards[4],
        cards[5],
        cards[6],
        cards[7],
        cards[8],
        cards[9]
    );

    /**
     * Order does not necessarily matter, we primarily
     * want to ensure the result of kingdomCard contains
     * all of the cards that we passed as arguments. So
     * we'll loop through each "card" in our cards array,
     * and check that the result contains that value.
     *
     * We'll also count the number we get correct so
     * that we can make more useful output after the
     * tests have run.
     */
    int i;
    int numCorrect;
    for (i = 0; i < 10; i++) {
        if (array_contains(result, cards[i], 10)) {
            printf("kingdomCards(): PASS result contains test value %i\n", cards[i]);
            numCorrect++;
            continue;
        }
        printf("kingdomCards(): FAIL result missing test value %i\n", cards[i]);
    }

    free(result);

    // If 10 correct, then all tests passed.
    if (numCorrect == 10) {
        printf("kingdomCards(): STATUS: Green... all tests passed\n");
        return 1;
    }

    // Otherwise, 1 or more tests failed.
    printf("kingdomCards(): STATUS: Red... 1 or more tests failed\n");
    return 0;
}

int main (int argc, char** argv) {
    testKingdomCards();
    return 0;
}
