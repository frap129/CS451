ASSIGNMENT := 2
NAME := sched
NAME2 := parser
NAME3 := timer
NAME4 := child
PHONY: clean build
clean:
	@rm -f $(NAME) $<
	@rm -f maples$(ASSIGNMENT).zip $<
	@echo "Build files removed!" $<
build:
	@echo "Compiling..." $<
	@gcc $(NAME).c $(NAME2).c $(NAME3).c -g -Wall -Wextra -o $(NAME) $<
	@gcc $(NAME4).c -g -lm -Wall -Wextra -o $(NAME4) $<


	@echo "Zipping..." $<
	@cd .. && zip -r maples$(ASSIGNMENT).zip maples$(ASSIGNMENT) \
		-x maples$(ASSIGNMENT)/Makefile \
		-x maples$(ASSIGNMENT)/.* \
		-x maples$(ASSIGNMENT)/$(NAME) \
		-x maples$(ASSIGNMENT)/$(NAME4) $<
	@mv ../maples$(ASSIGNMENT).zip . $<
