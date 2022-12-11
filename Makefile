
CC = gcc

C_FLAGS = -Wall
L_FLAGS = -lm

CFILES = day${day}/day${day}.c \
		 utils/utils.c

OBJDIR = output
OBJ = day${day}

all:
	mkdir -p $(OBJDIR)
	$(CC) -O2 $(C_FLAGS) $(CFILES) -o $(OBJDIR)/$(OBJ) $(L_FLAGS)

debug:
	mkdir -p $(OBJDIR)
	$(CC) -g $(C_FLAGS) $(CFILES) -o $(OBJDIR)/$(OBJ) $(L_FLAGS)

sample:
	./$(OBJDIR)/$(OBJ) day${day}/sample.txt ${part}
	
exec:
	./$(OBJDIR)/$(OBJ) day${day}/input.txt ${part}

.PHONY: clean
clean:
	rm -rf $(OBJDIR)

