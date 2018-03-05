/*********************************************************************
 ** Author: Romano Garza
 ** Date: 02/22/17
 ** Description: A unit test for adventurerEffect()
 *********************************************************************/

#include "cardtesthelper.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main () {
    struct gameState G = myInitGame();
    int player1 = 0;
    int previousHandCount = G.handCount[player1];
    int previousTresCount = getTreasureyCardCount(player1, G.handCount[player1], G);
    int newTresCount = 0;

    // test with an empty deck
    emptyDeck(player1, &G); // in this function all remaining deck cards are pushed
                            // to the discard pile
    if(!cardEffect(7, -1, -1, -1, &G, -1, 0))
    {
        printf("adventurerEffect(): PASS general test with empty deck\n");
    }
    else
    {
        printf("adventurerEffect(): FAIL general test with empty deck\n");
    }

    // after this first test the following should be the case:
    // hand should be increased by two cards, those two cards should be
    // treasure cards
    //
    if(previousHandCount == G.handCount[player1] - 2)
    {
        printf("adventurerEffect(): PASS hand count is increased by 2\n");
    }
    else
    {
        printf("adventurerEffect(): FAIL hand count is increased by 2\n");
    }

    newTresCount = getTreasureyCardCount(player1, G.handCount[player1], G);
    if(previousTresCount == newTresCount - 2)
    {
        printf("adventurerEffect(): PASS treasurey card increased by 2\n");
    }
    else
    {
        printf("adventurerEffect(): FAIL treasurey card increased by 2\n");
    }

    if(G.deckCount[player1] == 3)
    {
        printf("adventurerEffect(): PASS deck was successfully transfered from discard\n\n");
    }
    else
    {
        printf("adventurerEffect(): FAIL deck was successfully transfered from discard\n\n");
    }


    // reinit gamestate
    G = myInitGame();
    // test adventurer when deck is not empty
    if(!cardEffect(7, -1, -1, -1, &G, -1, 0))
    {
        printf("adventurerEffect(): PASS general test with non empty deck\n");
    }
    else
    {
        printf("adventurerEffect(): FAIL general test with non empty deck\n");
    }

    // after this first test the following should be the case:
    // hand should be increased by two cards, those two cards should be
    // treasure cards
    //
    if(previousHandCount == G.handCount[player1] - 2)
    {
        printf("adventurerEffect(): PASS hand count is increased by 2\n");
    }
    else
    {
        printf("adventurerEffect(): FAIL hand count is increased by 2\n");
    }

    newTresCount = getTreasureyCardCount(player1, G.handCount[player1], G);
    if(previousTresCount == newTresCount - 2)
    {
        printf("adventurerEffect(): PASS treasurey card increased by 2\n\n");
    }
    else
    {
        printf("adventurerEffect(): FAIL treasurey card increased by 2\n\n");
    }

    // reinit gamestate
    G = myInitGame();
    advC3(player1, &G);
    // test adventurer when deck has no treasure cards, but discard does
    if(cardEffect(7, -1, -1, -1, &G, -1, 0) == 0)
    {
        printf("adventurerEffect(): PASS general test - deck (no treasure cards) discard (has treasure cards)\n");
    }
    else
    {
        printf("adventurerEffect(): FAIL general test - deck (no treasure cards) discard (has treasure cards)\n");
    }

    // after this first test the following should be the case:
    // hand should be increased by two cards, those two cards should be
    // treasure cards
    //
    if(previousHandCount == G.handCount[player1] - 2)
    {
        printf("adventurerEffect(): PASS hand count is increased by 2\n");
    }
    else
    {
        printf("adventurerEffect(): FAIL hand count is increased by 2\n");
    }

    newTresCount = getTreasureyCardCount(player1, G.handCount[player1], G);
    if(previousTresCount == newTresCount - 2)
    {
        printf("adventurerEffect(): PASS treasurey card increased by 2\n\n");
    }
    else
    {
        printf("adventurerEffect(): FAIL treasurey card increased by 2\n\n");
    }


    // reinit gamestate
    G = myInitGame();
    advC4(player1, &G);
    // test adventurer when deck has no treasure cards, but discard does
    if(cardEffect(7, -1, -1, -1, &G, -1, 0) == 0)
    {
        printf("adventurerEffect(): PASS general test - deck (no treasure cards) discard (no treasure cards)\n");
    }
    else
    {
        printf("adventurerEffect(): FAIL general test - deck (no treasure cards) discard (no treasure cards)\n");
    }

    // after this first test the following should be the case:
    // hand should be increased by two cards, those two cards should be
    // treasure cards
    //
    if(previousHandCount == G.handCount[player1] - 2)
    {
        printf("adventurerEffect(): PASS hand count is increased by 2\n");
    }
    else
    {
        printf("adventurerEffect(): FAIL hand count is increased by 2\n");
    }

    newTresCount = getTreasureyCardCount(player1, G.handCount[player1], G);
    if(previousTresCount == newTresCount - 2)
    {
        printf("adventurerEffect(): PASS treasurey card increased by 2\n\n");
    }
    else
    {
        printf("adventurerEffect(): FAIL treasurey card increased by 2\n\n");
    }


    return 0;
}
