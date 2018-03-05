/*********************************************************************
 ** Author: Romano Garza
 ** Date: 02/22/17
 ** Description: A unit test for smithyEffect()
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
    int prevHandCount = 0;
    int prevDeckCount = 0;
    // add smithy to index 5
    G.hand[player1][5] = 13; // smithy is at index 5
    G.handCount[player1]++;// increment hand count
    // store the previous hand count
    prevHandCount = G.handCount[player1];
    prevDeckCount = G.deckCount[player1];
    //printf("handCount: %d\n", prevHandCount);
    //printf("deckCount: %d\n", G.deckCount[player1]);

    if(!cardEffect(13, -1, -1, -1, &G, 5, 0)){
        printf("smithyEffect(): PASS case 1: general call with correct parameters\n");
    }
    else
    {
        printf("smithyEffect(): FAIL case 1: general call with correct parameters\n");
    }

    // hand count should increase by 2 (+3 - 1)
    //printf("handCount: %d\n", G.handCount[player1]);
    //printf("deckCount: %d\n", G.deckCount[player1]);
    if(G.handCount[player1] == prevHandCount + 2)
    {
        printf("smithyEffect(): PASS case 1 + handcount check increase by 2\n");
    }
    else
    {
        printf("smithyEffect(): FAIL case 1 + handcount check increase by 2\n");
    }

    // hand should not contain smithy
    if(inDeck(player1, G, 13)){
        printf("smithyEffect(): FAIL case 1 + smithy discarded\n");
    }
    else
    {
        printf("smithyEffect(): PASS case 1 + smithy discarded\n");
    }

    // deck count should decrease by 3
    // hand should not contain smithy
    if(G.deckCount[player1] == prevDeckCount - 3){
        printf("smithyEffect(): PASS case 1 + deckcount decreased by 3\n");
    }
    else
    {
        printf("smithyEffect(): FAIL case 1 + deckcount decreased by 3\n");
    }


    // reinit gameState for second use case
    G = myInitGame();
    // add smithy to index 5
    G.hand[player1][5] = 13; // smithy is at index 5
    G.handCount[player1]++;// increment hand count
    // store the previous hand count
    prevHandCount = G.handCount[player1];
    prevDeckCount = G.deckCount[player1];
    if(!cardEffect(13, -1, -1, -1, &G, 4, 0)){
        printf("smithyEffect(): FAIL case 2: detect call with incorrect parameter (handpos)\n");
    }
    else
    {
        printf("smithyEffect(): PASS case 2: call with incorrect parameter (handPos)\n");
    }

    // hand count should increase by 2 (+3 - 1)
    //printf("handCount: %d\n", G.handCount[player1]);
    //printf("deckCount: %d\n", G.deckCount[player1]);

    if(G.handCount[player1] == prevHandCount + 2)
    {
        printf("smithyEffect(): PASS case 2 + handcount check increase by 2\n");
    }
    else
    {
        printf("smithyEffect(): FAIL case 2 + handcount check increase by 2\n");
    }

    // hand should not contain smithy
    if(inDeck(player1, G, 13)){
        printf("smithyEffect(): FAIL case 2 + smithy discarded\n");
    }
    else
    {
        printf("smithyEffect(): PASS case 2 + smithy discarded\n");
    }

    // deck count should decrease by 3
    // hand should not contain smithy
    if(G.deckCount[player1] == prevDeckCount - 3){
        printf("smithyEffect(): PASS case 2 + deckcount decreased by 3\n");
    }
    else
    {
        printf("smithyEffect(): FAIL case 2 + deckcount decreased by 3\n");
    }

}
