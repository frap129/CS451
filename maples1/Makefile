ASSIGNMENT := 1
NAME := 5ps
NAME2 := utils

PHONY: clean build
clean:
	@rm -f $(NAME) $<
	@rm -f maples$(ASSIGNMENT).zip $<
	@echo "Build files removed!" $<
build:
	@echo "Compiling..." $<
	@gcc $(NAME).c $(NAME2).c -g -Wall -Wextra -o $(NAME) $<

	@zip -r9 maples$(ASSIGNMENT).zip ../maples$(ASSIGNMENT) \
            -x ../maples$(ASSIGNMENT)/Makefile \
            -x ../maples$(ASSIGNMENT)/.* $<
