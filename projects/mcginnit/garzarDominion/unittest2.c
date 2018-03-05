/*********************************************************************
 ** Author: Romano Garza
 ** Date: 02/22/17
 ** Description: A unit test for shuffle
 *********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/*********************************************************************
** Description: checkCards checks the the cards for a player are not 
** out of the limits that are allowed, max 3 ones and 7 fours.
*********************************************************************/
int checkCards(int player, struct gameState state)
{
    int j = 0;
    int oneCount = 0;
    int fourCount = 0;
    for (j = 0; j < state.deckCount[player]; j++)
    {
        if( state.deck[player][j] == 1 )
        {
            oneCount++;
            if(oneCount > 3){
                return 0;
            }
        }
        else if( state.deck[player][j] == 4)
        {
            fourCount++;
            if(fourCount > 7)
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
        
    }
    
    return 1;
    
}

int main () {
    struct gameState G;
    int player1 = 0;
    int j;
    
    //assume game has just started
    G.deckCount[player1] = 10;
    for (j = 0; j < 3; j++)
    {
        G.deck[player1][j] = estate;
    }
    for (j = 3; j < 10; j++)
    {
        G.deck[player1][j] = copper;
    }
    
    if(!shuffle(player1, &G))
    {
        printf("shuffle(): PASS when deck count is 10\n\n");
    }
    else
    {
        printf("shuffle(): FAIL when deck count is 10\n\n");
    }
    
    // check that the deck count altered is correct
    if(G.deckCount[player1] == 10)
    {
        printf("shuffle(): PASS checking that altered deckcount is 10\n\n");
    }
    else
    {
        printf("shuffle(): Fail checking that altered deckcount is 10n\n");
    }
    
    // check that the cards are not out of bounds
    if(checkCards(player1, G))
    {
        printf("shuffle(): PASS checking that shuffled card values are in range\n\n");
    }
    else
    {
        printf("shuffle(): Fail checking that shuffled card values are in rangen\n");
    }
    

    //assume player has 0 cards
    G.deckCount[player1] = 0;
    
    if(shuffle(player1, &G)==-1)
    {
        printf("shuffle(): PASS when deck count is 0\n\n");
    }
    else
    {
        printf("shuffle(): FAIL when deck count is 0\n\n");
    }
    
    //assume player has negative cards
    G.deckCount[player1] = -50;
    
    if(shuffle(player1, &G)==-1)
    {
        printf("shuffle(): PASS when deck count is negative\n\n");
    }
    else
    {
        printf("shuffle(): FAIL when deck count is negative\n\n");
    }
    
    
    return 0;
}
