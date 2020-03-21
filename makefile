#
# this makefile will compile and and all source
# found in the ~/develop/dataReader directory.
#
#==============================================

# FINAL BINARY Target
./bin/dataReader : ./obj/dataReader.o  ./obj/linkedList.o ./obj/logger.o
	cc -g ./obj/dataReader.o ./obj/linkedList.o ./obj/logger.o -o  ./bin/dataReader
#
# =======================================================
#                     Dependencies
# =======================================================

./obj/dataReader.o : ./src/dataReader.c ./inc/dataReader.h
	cc -g -c ./src/dataReader.c -o  ./obj/dataReader.o

./obj/logger.o : ./src/logger.c ./inc/logger.h
		cc -g -c ./src/logger.c -o  ./obj/logger.o

./obj/linkedList.o : ./src/linkedList.c ./inc/dataReader.h
	cc -g -c ./src/linkedList.c -o ./obj/linkedList.o

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
