/*********************************************************************
 ** Author: Romano Garza
 ** Date: 02/22/17
 ** Description: A unit test for remodelEffect()
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


    // put remodel in the deck
    G.hand[player1][5] = 12;
    G.handCount[player1]++;
    // put village in the deck
    G.hand[player1][6] = 14;
    G.handCount[player1]++;
    // the card that's being traded up for (minion) is 2 higher
    // than the card being discarded (village)
    if(cardEffect(12, 14, 17, -1, &G, 5, 0) == 0 )
    {
        printf("remodelEffect(): PASS general test trading 3 cost for 5 cost\n");
    }
    else
    {
        printf("remodelEffect(): FAIL general test trading 3 cost for 5 cost\n");
    }
    if(inDeck(player1, G, 14) == 0 )
    {
        printf("remodelEffect(): PASS  traded card discarded\n");
    }
    else
    {
        printf("remodelEffect(): FAIL traded card discarded\n");
    }

    if(inDeck(player1, G, 17))
    {
        printf("remodelEffect(): PASS  traded up card in deck\n");
    }
    else
    {
        printf("remodelEffect(): FAIL traded up card in deck\n");
    }

    if(inDeck(player1, G, 12)==0)
    {
        printf("remodelEffect(): PASS remodel discarded\n\n");
    }
    else
    {
        printf("remodelEffect(): FAIL remodel discarded\n\n");
    }


    // gained card does not need to costexactly  more, it can cost much less
    G = myInitGame();
    // put remodel in the deck
    G.hand[player1][5] = 12;
    G.handCount[player1]++;
    // put minion in the deck
    G.hand[player1][6] = 17;
    G.handCount[player1]++;
    // the card that's being traded down (minion) is 2 higher
    // than the card being traded for (village)
    if(cardEffect(12, 17, 14, -1, &G, 5, 0) == 0 )
    {
        printf("remodelEffect(): PASS general test trading 5 cost for 3 cost\n");
    }
    else
    {
        printf("remodelEffect(): FAIL general test trading 5 cost for 3 cost\n");
    }
    if(inDeck(player1, G, 17) == 0 )
    {
        printf("remodelEffect(): PASS  traded card discarded\n");
    }
    else
    {
        printf("remodelEffect(): FAIL traded card discarded\n");
    }

    if(inDeck(player1, G, 14))
    {
        printf("remodelEffect(): PASS  traded up card in deck\n");
    }
    else
    {
        printf("remodelEffect(): FAIL traded up card in deck\n");
    }

    if(inDeck(player1, G, 12)==0)
    {
        printf("remodelEffect(): PASS remodel discarded\n\n");
    }
    else
    {
        printf("remodelEffect(): FAIL remodel discarded\n\n");
    }

    // gained card does not need to costexactly  more, it can cost much less
    G = myInitGame();
    // put remodel in the deck
    G.hand[player1][5] = 12;
    G.handCount[player1]++;
    // put village in the deck
    G.hand[player1][6] = 14;
    G.handCount[player1]++;
    // the card that's being traded up for (adventurer) is 3 higher
    // than the card being discarded (village)
    if(cardEffect(12, 14, 7, -1, &G, 5, 0) == 0 )
    {
        printf("remodelEffect(): PASS general test trading 3 cost for 6 cost\n");
    }
    else
    {
        printf("remodelEffect(): FAIL general test trading 3 cost for 6 cost\n");
    }
    if(inDeck(player1, G, 14) == 0 )
    {
        printf("remodelEffect(): PASS  traded card discarded\n");
    }
    else
    {
        printf("remodelEffect(): FAIL traded card discarded\n");
    }

    if(inDeck(player1, G, 7))
    {
        printf("remodelEffect(): PASS  traded up card in deck\n");
    }
    else
    {
        printf("remodelEffect(): FAIL traded up card in deck\n");
    }

    if(inDeck(player1, G, 12)==0)
    {
        printf("remodelEffect(): PASS remodel discarded\n\n");
    }
    else
    {
        printf("remodelEffect(): FAIL remodel discarded\n\n");
    }

    return 0;
}
