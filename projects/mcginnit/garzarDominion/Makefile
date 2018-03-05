CFLAGS = -Wall -fpic -coverage -lm -std=c99



rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

cardtesthelper.o: cardtesthelper.h cardtesthelper.c dominion.o rngs.o
	gcc -c cardtesthelper.c -g $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
unittest4: unittest4.c dominion.o rngs.o 
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
cardtest1: cardtest1.c dominion.o rngs.o cardtesthelper.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o cardtesthelper.o $(CFLAGS)
cardtest2: cardtest2.c dominion.o rngs.o cardtesthelper.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o cardtesthelper.o $(CFLAGS)
cardtest3: cardtest3.c dominion.o rngs.o cardtesthelper.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o cardtesthelper.o $(CFLAGS)
cardtest4: cardtest4.c dominion.o rngs.o cardtesthelper.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o cardtesthelper.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o cardtesthelper.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o cardtesthelper.o $(CFLAGS)
randomtestcard1: randomtestcard1.c dominion.o rngs.o cardtesthelper.o 
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o cardtesthelper.o $(CFLAGS)
randomtestcard2: randomtestcard2.c dominion.o rngs.o cardtesthelper.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o cardtesthelper.o $(CFLAGS)


runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 
echo "unittest1.c:" >> unittestresults.out
	./unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "unittest2.c:" >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "unittest3.c:" >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "unittest4.c:" >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "cardtest1.c:" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "cardtest2.c:" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "cardtest3.c:" >> unittestresults.out
	./cardtest3 >> unittestresults.out 
	gcov dominion.c >> unittestresults.out
	echo "cardtest4.c:" >>  unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

testHelpers_mcginnit.o: testHelpers_mcginnit.h testHelpers_mcginnit.c
	gcc -c testHelpers_mcginnit.c -g $(CLAGS)

unittest1_mcginnit: unittest1_mcginnit.c dominion.o \
  rngs.o testHelpers_mcginnit.o
	gcc -o unittest1_mcginnit -g unittest1_mcginnit.c dominion.o \
	  rngs.o testHelpers_mcginnit.o $(CFLAGS)

unittest2_mcginnit: unittest2_mcginnit.c dominion.o \
  rngs.o testHelpers_mcginnit.o
	gcc -o unittest2_mcginnit -g unittest2_mcginnit.c dominion.o \
	  rngs.o testHelpers_mcginnit.o $(CFLAGS)

unittest3_mcginnit: unittest3_mcginnit.c dominion.o \
  rngs.o testHelpers_mcginnit.o
	gcc -o unittest3_mcginnit -g unittest3_mcginnit.c dominion.o \
	  rngs.o testHelpers_mcginnit.o $(CFLAGS)

unittest4_mcginnit: unittest4_mcginnit.c dominion.o \
  rngs.o testHelpers_mcginnit.o
	gcc -o unittest4_mcginnit -g unittest4_mcginnit.c dominion.o \
	  rngs.o testHelpers_mcginnit.o $(CFLAGS)

cardtest1_mcginnit: cardtest1_mcginnit.c dominion.o \
  rngs.o testHelpers_mcginnit.o
	gcc -o cardtest1_mcginnit -g cardtest1_mcginnit.c dominion.o \
	  rngs.o testHelpers_mcginnit.o $(CFLAGS)

cardtest2_mcginnit: cardtest2_mcginnit.c dominion.o \
  rngs.o testHelpers_mcginnit.o
	gcc -o cardtest2_mcginnit -g cardtest2_mcginnit.c dominion.o \
	  rngs.o testHelpers_mcginnit.o $(CFLAGS)

cardtest3_mcginnit: cardtest3_mcginnit.c dominion.o \
  rngs.o testHelpers_mcginnit.o
	gcc -o cardtest3_mcginnit -g cardtest3_mcginnit.c dominion.o \
	  rngs.o testHelpers_mcginnit.o $(CFLAGS)

cardtest4_mcginnit: cardtest4_mcginnit.c dominion.o \
  rngs.o testHelpers_mcginnit.o
	gcc -o cardtest4_mcginnit -g cardtest4_mcginnit.c dominion.o \
	  rngs.o testHelpers_mcginnit.o $(CFLAGS)

unittestresults_mcginnit.out: unittest1_mcginnit unittest2_mcginnit \
  unittest3_mcginnit unittest4_mcginnit \
  cardtest1_mcginnit cardtest2_mcginnit \
  cardtest3_mcginnit cardtest4_mcginnit
	./unittest1_mcginnit > unittestresults_mcginnit.out 2>&1
	./unittest2_mcginnit >> unittestresults_mcginnit.out 2>&1
	./unittest3_mcginnit >> unittestresults_mcginnit.out 2>&1
	./unittest4_mcginnit >> unittestresults_mcginnit.out 2>&1
	./cardtest1_mcginnit >> unittestresults_mcginnit.out 2>&1
	./cardtest2_mcginnit >> unittestresults_mcginnit.out 2>&1
	./cardtest3_mcginnit >> unittestresults_mcginnit.out 2>&1
	./cardtest4_mcginnit >> unittestresults_mcginnit.out 2>&1
	gcov dominion.c >> unittestresults_mcginnit.out
	cat dominion.c.gcov >> unittestresults_mcginnit.out

randomtestadventurer_mcginnit: randomtestadventurer_mcginnit.c dominion.o rngs.o
	gcc -o randomtestadventurer_mcginnit -g randomtestadventurer_mcginnit.c \
	  dominion.o rngs.o $(CFLAGS)

randomtestcard1_mcginnit: randomtestcard1_mcginnit.c dominion.o rngs.o
	gcc -o randomtestcard1_mcginnit -g randomtestcard1_mcginnit.c \
	  dominion.o rngs.o $(CFLAGS)

randomtestcard2_mcginnit: randomtestcard2_mcginnit.c dominion.o rngs.o
	gcc -o randomtestcard2_mcginnit -g randomtestcard2_mcginnit.c \
	  dominion.o rngs.o $(CFLAGS)

randomtestadventurer_mcginnit.out: randomtestadventurer_mcginnit
	./randomtestadventurer_mcginnit > randomtestadventurer_mcginnit.out 2>&1
	gcov dominion.c >> randomtestadventurer_mcginnit.out
	cat dominion.c.gcov >> randomtestadventurer_mcginnit.out

randomtestcard1_mcginnit.out: randomtestcard1_mcginnit
	./randomtestcard1_mcginnit > randomtestcard1_mcginnit.out 2>&1
	gcov dominion.c >> randomtestcard1_mcginnit.out
	cat dominion.c.gcov >> randomtestcard1_mcginnit.out

randomtestcard2_mcginnit.out: randomtestcard2_mcginnit
	./randomtestcard2_mcginnit > randomtestcard2_mcginnit.out 2>&1
	gcov dominion.c >> randomtestcard2_mcginnit.out
	cat dominion.c.gcov >> randomtestcard2_mcginnit.out

randomtestcard1.out: randomtestcard1
	echo "randomtestcard1:" >> randomtestcard1.out
	./randomtestcard1 >> randomtestcard1.out
	gcov -b -abcfu dominion.c >> randomtestcard1.out
randomtestcard2.out: randomtestcard2
	echo "randomtestcard2:" >> randomtestcard2.out
	./randomtestcard2 >> randomtestcard2.out 
	gcov -b -abcfu dominion.c >> randomtestcard2.out 
randomtestadventurer.out : randomtestadventurer
	echo "randomtestadventurer:" >> randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b -abcfu dominion.c >> randomtestadventurer.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard unittestresults.out randomtestcard1.out randomtestcard2.out randomtestadventurer.out

randtest: randomtestcard1.out randomtestcard2.out randomtestadventurer.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda \
	  *.gcno *.so *.out *.dSYM testDrawCard badTestDrawCard \
	  testDrawCard.exe unittest1 unittest2 unittest3 unittest4 \
	  cardtest1 cardtest2 cardtest3 cardtest4 \
	  unittest1_mcginnit unittest2_mcginnit unittest3_mcginnit \
	  unittest4_mcginnit \
	  cardtest1_mcginnit cardtest2_mcginnit cardtest3_mcginnit \
	  cardtest4_mcginnit \
	  randomtestadventurer_mcginnit randomtestcard1_mcginnit \
	  randomtestcard2_mcginnit
