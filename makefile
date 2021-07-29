CC=g++

CFLAGS=-c -Wall

INCLUDES = -I ./export -I ./component/RestServer/export/ -I ./component/DBHandler/export/ -I ./component/TwikiContext/export/ -I /usr/include/mysql-cppconn/jdbc/
INC = $(INCLUDES)
LIBS = -lpthread -lssl -lcrypto -lcpprest -lboost_system -lmysqlcppconn
COMPILE=-g
OUTPUT=./bin/
DBHANDLE=./component/DBHandler/
REST=./component/RestServer/
TWIKKI=./component/TwikiContext/
TARGET=shounproject
all: run 

run: $(DBHANDLE)*.o $(REST)*.o $(TWIKKI)*.o main.o
	$(CC) $(COMPILE) $(DBHANDLE)*.o $(REST)*.o $(TWIKKI)*.o main.o -o $(OUTPUT)$(TARGET) $(LIBS)

$(DBHANDLE)*.o: $(DBHANDLE)*.cpp
	$(CC) $(COMPILE) $(INC) $(CFLAGS) $(DBHANDLE)*.cpp 
	mv *.o $(DBHANDLE)

$(REST)*.o: $(REST)*.cpp
	$(CC) $(COMPILE) $(INC) $(CFLAGS) $(REST)*.cpp 
	mv *.o $(REST)

$(TWIKKI)*.o: $(TWIKKI)*.cpp
	$(CC) $(COMPILE) $(INC) $(CFLAGS) $(TWIKKI)*.cpp 
	mv *.o $(TWIKKI)

main.o: main.cpp
	$(CC) $(COMPILE) $(INC) $(CFLAGS) main.cpp 

clean:
	rm -rf *.o $(OUTPUT)$(TARGET)
	rm -rf $(REST)*.o 
	rm -rf $(TWIKKI)*.o 
	rm -rf *.o 
	rm -rf $(DBHANDLE)*.o
Run:
	$(OUTPUT)$(TARGET)
