NAME := ../unit_test
SRC_DIR := ./
OBJ_DIR := ./obj/
HEADER_DIR := ./
SRCS :=	main.cpp \
		TesterClass.cpp
CC := c++
CFLAGS := -Wall -Werror -Wextra -std=c++11
OBJS := $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRCS))
HEADERS := $(wildcard $(HEADER_DIR)*.hpp)
DEPS := $(HEADERS)
#TEXT FORMAT
RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m
BOLD := \033[1m
UNDERLINED := \033[4m
RESET := \033[0m

all: $(MAKE) re

$(NAME): $(OBJ_DIR) $(OBJS) $(DEPS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@
	@echo "$(GREEN)unit_test created$(RESET)"
	@echo "$(HEADERS)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) deleted$(RESET)"

re: fclean $(NAME)