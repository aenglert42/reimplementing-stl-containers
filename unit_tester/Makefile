TITLE := unit_test
NAME := ../$(TITLE)
SRC_DIR := ./
OBJ_DIR := ./obj/
HEADER_DIR := ./
SRCS :=	main.cpp \
		TesterClass.cpp
CC := c++
CFLAGS := -g -std=c++11 -Wall -Wextra -Werror -Wno-deprecated-copy
OBJS := $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRCS))
HEADERS := $(wildcard $(HEADER_DIR)*.hpp)
DEPS := $(HEADERS) Makefile
#TEXT FORMAT
RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m
BOLD := \033[1m
UNDERLINED := \033[4m
RESET := \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@
	@echo "$(GREEN)$(TITLE) created$(RESET)"
#	@echo "$(HEADERS)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(DEPS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(TITLE) deleted$(RESET)"

re: fclean $(NAME)