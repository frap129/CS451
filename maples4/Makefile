ASSIGNMENT := 4
NAME := allocator
CFLAGS := -g -Wall -Wextra -Iinclude
SRC := src/main.c \
       src/list.c
 
PHONY: clean build
clean:
	@rm -f $(NAME) $<
	@rm -f maples$(ASSIGNMENT).zip $<
	@echo "Build files removed!" $<
build:
	@echo "Compiling..." $<
	@gcc $(SRC) $(CFLAGS) -o $(NAME) $<

	@echo "Zipping..." $<
	@cd .. && zip -r maples$(ASSIGNMENT).zip maples$(ASSIGNMENT) \
		-x maples$(ASSIGNMENT)/.* \
		-x maples$(ASSIGNMENT)/$(NAME) $<
	@mv ../maples$(ASSIGNMENT).zip . $<
