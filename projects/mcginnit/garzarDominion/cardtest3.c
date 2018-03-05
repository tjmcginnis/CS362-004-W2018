/*********************************************************************
 ** Author: Romano Garza
 ** Date: 02/22/17
 ** Description: A unit test for villageEffect()
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
    int prevHand = G.handCount[player1];
    int prevNumAct = G.numActions;
    emptyDeck(player1, &G);
    G.hand[player1][0] = 14;
    if(cardEffect(14, -1, -1, -1, &G, 0, 0)== 0 )
    {
        printf("villageEffect(): PASS general test village in hand with empty deck\n");
    }
    else
    {
        printf("villageEffect(): FAIL general test village in hand with empty deck\n");
    }

    if(prevHand == G.handCount[player1])
    {
        printf("villageEffect(): PASS hand increased by 0\n");
    }
    else
    {
        printf("villageEffect(): FAIL hand increased by 0\n");
    }

    if(prevNumAct == G.numActions - 2)
    {
        printf("villageEffect(): PASS actions increased by 2\n");
    }
    else
    {
        printf("villageEffect(): FAIL actions increased by 2\n");
    }

    if(!inDeck(player1, G, 14))
    {
        printf("villageEffect(): PASS village properly discarded\n\n");
    }
    else
    {
        printf("villageEffect(): FAIL village properly discarded\n\n");
    }


    G = myInitGame();
    if(cardEffect(14, -1, -1, -1, &G, 0, 0)== 0 )
    {
        printf("villageEffect(): FAIL general test village not in hand \n");
    }
    else
    {
        printf("villageEffect(): FAIL general test village not in hand \n");
    }

    if(prevHand == G.handCount[player1])
    {
        printf("villageEffect(): PASS hand increased by 0\n");
    }
    else
    {
        printf("villageEffect(): FAIL hand increased by 0\n");
    }

    if(prevNumAct == G.numActions - 2)
    {
        printf("villageEffect(): PASS actions increased by 2\n");
    }
    else
    {
        printf("villageEffect(): FAIL actions increased by 2\n");
    }

    if(!inDeck(player1, G, 14))
    {
        printf("villageEffect(): PASS village properly discarded\n\n");
    }
    else
    {
        printf("villageEffect(): FAIL village properly discarded\n\n");
    }
    return 0;


}
