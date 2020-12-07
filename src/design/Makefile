CC			=g++
CFLAGS		+=-Wall
CFLAGS		+=-std=c++11

SOURCES     =$(wildcard ./*.cpp)

INCLUDES  	+=-I../../include

LIB_NAMES 	=-lpthread

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