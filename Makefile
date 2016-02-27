
CXX=g++          # define compiler to use for C++ programs
CXXFLAGS= -Wall  # define flags to use
#CXXFLAGS=-g -DDEBUG -Wall  # define alternate flags to use

# Define some variables to reduce duplication and possible errors.
OBJS=main.o floor.o cell.o character.o player.o mob.o map.o dragon.o item.o potion.o gold.o
EXEC=cc3k
CURS=-lncurses

# Define first/default rule
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC) $(CURS)

# Define rule to clean up.
clean:
	rm *.o $(EXEC)
