ASSIGNMENT := 3
NAME := elevator
NAME2 := main
NAME3 := person
NAME4 := utils
CFLAGS := -g -Wall -Wextra

PHONY: clean build
clean:
	@rm -f $(NAME) $<
	@rm -f maples$(ASSIGNMENT).zip $<
	@echo "Build files removed!" $<
build:
	@echo "Compiling..." $<
	@gcc $(NAME).c $(NAME2).c $(NAME3).c $(NAME4).c $(CFLAGS) -o $(NAME) $<

	@echo "Zipping..." $<
	@cd .. && zip -r maples$(ASSIGNMENT).zip maples$(ASSIGNMENT) \
		-x maples$(ASSIGNMENT)/Makefile \
		-x maples$(ASSIGNMENT)/.* \
		-x maples$(ASSIGNMENT)/$(NAME) $<
	@mv ../maples$(ASSIGNMENT).zip . $<
