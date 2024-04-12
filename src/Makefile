CPP=g++
CFLAGS:=-Wall -Werror -Wextra -g -c
FOLDER=../build/
OBJS=$(addprefix $(FOLDER),main.o sort.o search.o)

all:

build: main.o sort.o search.o
	$(CPP) $(OBJS) -o $(FOLDER)search
	$(MAKE) clean_objs

rebuild: clean build

main.o: main.cpp main.h sort.h search.h
	$(CPP) $(CFLAGS) $< -o $(FOLDER)$@

sort.o: sort.cpp sort.h
	$(CPP) $(CFLAGS) $< -o $(FOLDER)$@

search.o: search.cpp search.h
	$(CPP) $(CFLAGS) $< -o $(FOLDER)$@

clean_objs:
	rm -rf $(OBJS)

clean: clean_objs
	rm -rf $(FOLDER)*