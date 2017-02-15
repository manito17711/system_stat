
CC = g++
CFLAGS  = -g -Wall -std=c++11
TARGET = system_stat
OBJ_FILES = main.o dispatcher.o server.o client.o reporter.o network.o node.o
ENUMS = connection_types.hpp

default: $(TARGET)

$(TARGET):  $(OBJ_FILES)  
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES) $(ENUMS)



main.o:  main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

dispatcher.o:  dispatcher.cpp dispatcher.hpp 
	$(CC) $(CFLAGS) -c dispatcher.cpp

server.o:  server.cpp server.hpp 
	$(CC) $(CFLAGS) -c server.cpp

client.o:  client.cpp client.hpp 
	$(CC) $(CFLAGS) -c client.cpp

reporter.o:  reporter.cpp reporter.hpp 
	$(CC) $(CFLAGS) -c reporter.cpp

network.o:  network.cpp network.hpp 
	$(CC) $(CFLAGS) -c network.cpp

node.o:  node.cpp node.hpp 
	$(CC) $(CFLAGS) -c node.cpp



clean: 
	$(RM) $(TARGET) *.o *~
