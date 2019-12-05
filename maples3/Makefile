ASSIGNMENT := 3
NAME := elevator
CFLAGS := -g -Wall -Wextra -Iinclude -lpthread
ifneq ($(strip $(EXTRA_CREDIT)),)
    CFLAGS += -DEXTRA_CREDIT
endif
SRC := src/elevator.c \
       src/main.c \
       src/person.c \
       src/utils.c \
       src/queue/queue.c \
       src/queue/node.c
 
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
