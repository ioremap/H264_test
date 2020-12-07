CC			=g++
CFLAGS		=-Wall
SOURCES     =$(wildcard ./src/*.cpp)
INCLUDES  	+=-I./include
INCLUDES  	+=-I./lib/libx264/include
LIB_NAMES 	=-lx264 -lpthread -ldl
LIB_PATH 	=-L./lib/libx264/lib/
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