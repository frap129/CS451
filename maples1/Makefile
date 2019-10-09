ASSIGNMENT := 1
NAME := 5ps

PHONY: clean build
clean:
	@rm -f $(NAME1).out $(NAME2).out $(NAME3).out $<
	@rm -f maples$(ASSIGNMENT).zip $<
	@echo "Build files removed!" $<
build:
	@echo "Compiling..." $<
	@gcc $(NAME1).c -g -Wall -Wextra -o $(NAME).out $<
	@zip -r9 maples$(ASSIGNMENT).zip ../maples$(ASSIGNMENT) \
            -x ../maples$(ASSIGNMENT)/Makefile \
            -x ../maples$(ASSIGNMENT)/.* $<
