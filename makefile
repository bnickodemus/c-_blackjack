OBJS = Board.o Deck.o Player.o Hand.o Card.o Ace.o game.o
EXES = Blackjack
FLAGS = -c
CC = g++

all: $(EXES)

clean:
	rm $(OBJS)

Blackjack: $(OBJS)
	$(CC) $(OBJS) -o Blackjack

Board.o: Board.cpp
	$(CC) $(FLAGS) Board.cpp

Deck.o: Deck.cpp
	$(CC) $(FLAGS) Deck.cpp

Player.o: Player.cpp
	$(CC) $(FLAGS) Player.cpp

Hand.o: Hand.cpp
	$(CC) $(FLAGS) Hand.cpp

Card.o: Card.cpp
	$(CC) $(FLAGS) Card.cpp

Ace.o: Ace.cpp
	$(CC) $(FLAGS) Ace.cpp

game.o: game.cpp
	$(CC) $(FLAGS) game.cpp
