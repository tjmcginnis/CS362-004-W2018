/*********************************************************************
 ** Author: Romano Garza
 ** Date: 02/22/17
 ** Description: A unit test for fullDeckCount()
 *********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


void initScores(struct gameState *G, int player1){
    
    G->discardCount[player1] = 0;
    G->deckCount[player1]= 0;
    G->handCount[player1] = 0;
    
    for(int i = 0; i < 3; i++) // deck, hand, and discard has 3 of every card
    {
        G->deck[player1][i] = curse;
        G->discard[player1][i] = curse;
        G->hand[player1][i] = curse;
        G->discardCount[player1] += 1;
        G->deckCount[player1]+= 1;
        G->handCount[player1]+= 1;
        
    }
    for(int i = 3; i < 6; i++)
    {
        G->deck[player1][i] = estate;
        G->discard[player1][i] = estate;
        G->hand[player1][i] = estate;
        G->discardCount[player1] += 1;
        G->deckCount[player1]+= 1;
        G->handCount[player1]+= 1;
    }
    for(int i = 6; i < 9; i++)
    {
        G->deck[player1][i] = duchy;
        G->discard[player1][i] = duchy;
        G->hand[player1][i] = duchy;
        G->discardCount[player1] += 1;
        G->deckCount[player1]+= 1;
        G->handCount[player1]+= 1;
    }
    for(int i = 9; i < 12; i++)
    {
        G->deck[player1][i] = province;
        G->discard[player1][i] = province;
        G->hand[player1][i] = province;
        G->discardCount[player1] += 1;
        G->deckCount[player1]+= 1;
        G->handCount[player1]+= 1;
    }
    for(int i = 12; i < 15; i++)
    {
        G->deck[player1][i] = great_hall;
        G->discard[player1][i] = great_hall;
        G->hand[player1][i] = great_hall;
        G->discardCount[player1] += 1;
        G->deckCount[player1]+= 1;
        G->handCount[player1]+= 1;
    }
    /*for(int i = 15; i < 18; i++)
     {
     G->deck[player1][i] = gardens;
     G->discard[player1][i] = gardens;
     G->hand[player1][i] = gardens;
     G->discardCount[player1] += 1;
     G->deckCount[player1]+= 1;
     G->handCount[player1]+= 1;
     }*/
}

int main () {
    struct gameState G;
    int player1 = 0;

    /*THIS AREA CHECKS THAT FOR LOOPS ARE SCORING PROPERLY WHEN ALL COUNTS ARE 0*/
    if(scoreFor(player1, &G) == 0)
    {
        printf("scoreFor(): PASS when all counts are 0\n");
    }
    else
    {
        printf("scoreFor(): FAIL when all counts are 0\n");
    }
    
    /*THIS AREA BROADLY CHECKS THE FOR LOOPS ARE SCORING PROPERLY*/
    initScores(&G, player1);
    if(scoreFor(player1, &G) == 90)
    {
        printf("scoreFor(): PASS when 3 cards per score category for all decks\n");
    }
    else
    {
        printf("scoreFor(): FAIL when 3 cards per score category for all decks\n");
    }
    
    
    /*THIS AREA CHECKS THE FOR LOOPS ARE INDEXING PROPERLY*/
    initScores(&G, player1);
    G.deckCount[player1]= 0;
    if(scoreFor(player1, &G) == 60)
    {
        printf("scoreFor(): PASS when 3 cards per score category for all decks but deckCount = 0\n");
    }
    else
    {
        printf("scoreFor(): FAIL when 3 cards per score category for all decks but deckCount = 0\n");
    }
    initScores(&G, player1);
    G.handCount[player1]= 0;
    if(scoreFor(player1, &G) == 60)
    {
        printf("scoreFor(): PASS when 3 cards per score category for all decks but handCount = 0 \n");
    }
    else
    {
        printf("scoreFor(): FAIL when 3 cards per score category for all decks but handCount = 0 \n");
    }
    initScores(&G, player1);
    G.discardCount[player1]= 0;
    if(scoreFor(player1, &G) == 60)
    {
        printf("scoreFor(): PASS when 3 cards per score category for all decks but discardCount = 0 \n");
    }
    else
    {
        printf("scoreFor(): FAIL when 3 cards per score category for all decks but discardCount = 0 \n");
    }
    return 0;
}
