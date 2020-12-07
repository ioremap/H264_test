CC			=g++
CFLAGS		+=-Wall
CFLAGS		+=-std=c++11
CFLAGS		+=-g

SOURCES     =$(wildcard ./*.cpp)

INCLUDES  	+=-I../../include
INCLUDES  	+=-I../../lib/amqp_cpp/include
#INCLUDES  	+=-I../../lib/amqp_cpp/include/amqpcpp

INCLUDES  	+=-I../../lib/libevent/include
INCLUDES  	+=-I../../lib/libevent/include/event2

LIB_NAMES 	=-lamqpcpp -lpthread -ldl -levent -lrt

LIB_PATH 	+=-L../../lib/amqp_cpp/lib/
LIB_PATH 	+=-L../../lib/libevent/lib/

OBJ			=$(patsubst %.cpp, %.o, $(SOURCES))
TARGET		=app

#links
$(TARGET):$(OBJ)
	$(CC) $(OBJ) $(LIB_PATH) $(LIB_NAMES) -o $(TARGET)
	@rm -rf $(OBJ)
	
#compile
%.o: %.cpp
	$(CC) $(INCLUDES) $(DEBUG) -c $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	@echo "Remove linked and compiled files......"
	rm -rf $(OBJ) $(TARGET) output 