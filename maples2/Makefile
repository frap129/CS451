ASSIGNMENT := 2
NAME := sched
NAME2 := parser
NAME3 := timer

PHONY: clean build
clean:
	@rm -f $(NAME) $<
	@rm -f maples$(ASSIGNMENT).zip $<
	@echo "Build files removed!" $<
build:
	@echo "Compiling..." $<
	@gcc $(NAME).c $(NAME2).c $(NAME3).c -g -Wall -Wextra -o $(NAME) $<

	@zip -r9 maples$(ASSIGNMENT).zip ../maples$(ASSIGNMENT) \
            -x ../maples$(ASSIGNMENT)/Makefile \
            -x ../maples$(ASSIGNMENT)/.* $<
