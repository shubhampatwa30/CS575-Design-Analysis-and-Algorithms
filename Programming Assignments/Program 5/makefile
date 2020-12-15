CC=gcc
CFLAGS=-g
.PHONY: all checkmem clean

all:createkn01.c bruteforce.c dynpro.c backtrack.c
	$(CC) $(CFLAGS) createkn01.c -o createkn01
	$(CC) $(CFLAGS) bruteforce.c -o bruteforce
	$(CC) $(CFLAGS) dynpro.c -o dynpro
	$(CC) $(CFLAGS) backtrack.c -o backtrack	

run: 	createkn01 bruteforce dynpro backtrack
	./createkn01 -k knapsack01.txt
	./bruteforce -k knapsack01.txt
	./dynpro -k knapsack01.txt
	./backtrack -k knapsack01.txt

clean:
	rm createkn01	
	rm bruteforce
	rm dynpro
	rm backtrack
	rm knapsack01.txt
	rm output1.txt
	rm output2.txt
	rm entries2.txt
	rm entries3.txt
	rm output3.txt
	



        


