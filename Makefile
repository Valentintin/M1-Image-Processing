OBJ_DIR = obj
EXEC_DIR = bin

EXEC_NAME = main.out
OBJS = 
CC = g++
CFLAGS = -Wall -g -I/usr/local/include/opencv4
LDFLAGS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs

default: make_dir clean $(EXEC_DIR)/$(EXEC_NAME) 

make_dir:
	test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	test -d $(EXEC_DIR) || mkdir $(EXEC_DIR)

$(EXEC_DIR)/$(EXEC_NAME):	$(OBJS)
	$(CC) $(CFLAGS) main.cpp $(OBJS) -o $(EXEC_DIR)/$(EXEC_NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(EXEC_DIR)/*
	!(test -f callgrind.out.*) || rm callgrind.out.*
	!(test -f optimisation) || rm optimisation

#pour regarder les fuites de mêmoire : 
#	valgrind --tool=memcheck --leak-check=full bin/main.out 
#pour regarder l'optimisation : 
#	valgrind --tool=callgrind bin/main.out && callgrind_annotate callgrind.out.* >>optimisation
#	et penser à rm callgrind.out* à la fin