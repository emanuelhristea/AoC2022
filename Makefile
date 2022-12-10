
CC = gcc

C_FLAGS = -O2 \
		  -Wall 

C_DEBUG_FLAGS = -g \
 				-Wall


CFILES = day${day}/day${day}.c \
		 utils/utils.c

OBJDIR = output
OBJ = day${day}

all:
	mkdir -p $(OBJDIR)
	$(CC) $(C_FLAGS) $(CFILES) -o $(OBJDIR)/$(OBJ)

debug:
	mkdir -p $(OBJDIR)
	$(CC) $(C_DEBUG_FLAGS) $(CFILES) -o $(OBJDIR)/$(OBJ)

sample:
	./$(OBJDIR)/$(OBJ) day${day}/sample.txt ${part}
	
exec:
	./$(OBJDIR)/$(OBJ) day${day}/input.txt ${part}

.PHONY: clean
clean:
	rm -rf $(OBJDIR)

