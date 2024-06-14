BINARY_PATH = ./test

run: compile
	@$(BINARY_PATH)
	
compile:
	@gcc \
	-std=c99 \
	-o $(BINARY_PATH) \
	hangman.c \
	-lwinmm