#
# this makefile will compile and and all source
# found in the ~/develop/dataReader directory.
#
#==============================================

# FINAL BINARY Target
./bin/dataReader : ./obj/dataReader.o
	cc ./obj/dataReader.o -o ./bin/dataReader
#
# =======================================================
#                     Dependencies
# =======================================================

./obj/dataReader.o : ./src/dataReader.c ./inc/dataReader.h
	cc -c ./src/dataReader.c -o ./obj/dataReader.o

#
# =======================================================
# Other targets
# =======================================================
all : ./bin/dataReader

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
