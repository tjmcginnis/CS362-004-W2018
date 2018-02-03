CFLAGS = -Wall -fpic -lm

all: testme

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

# Set up a .PHONY rule to make and run testme
.PHONY: run
run:
	# Run testme as (./testme || true) so we 
	# don't get error message about the 
	# Makefile failing
	make && (./testme || true) 

clean:
	rm -f *.o testme *.gcno *.gcda
	