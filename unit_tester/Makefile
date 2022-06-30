NAME := ../unit_test
SRC_DIR := ./
OBJ_DIR := ./obj/
SRCS :=	main.cpp \
		TesterClass.cpp
CC := c++
CFLAGS := -Wall -Werror -Wextra -std=c++11
OBJS := $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRCS))
#TEXT FORMAT
RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m
BOLD := \033[1m
UNDERLINED := \033[4m
RESET := \033[0m
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@
	@echo "$(GREEN)unit_test created$(RESET)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) deleted$(RESET)"

re: fclean all