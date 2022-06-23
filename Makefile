NAME := containers_ft
SRC_DIR := ./src/
OBJ_DIR := ./obj/
HEADER_DIR := ./inc/
SRCS :=	my_main.cpp
CC := c++
CFLAGS := -g -Wall -Werror -Wextra -std=c++98
OBJS := $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRCS))
HEADERS := $(wildcard $(HEADER_DIR)*.hpp)
INCLUDES := -I $(HEADER_DIR)
DEPS := $(HEADERS) 
MAKE += --no-print-directory
#TEXT FORMAT
RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m
BOLD := \033[1m
UNDERLINED := \033[4m
RESET := \033[0m

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(DEPS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@
	@echo "\n$(GREEN)$(NAME) created$(RESET)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(DEPS) ofilemessage
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo ".\c"

ofilemessage:
	@echo "compiling $(NAME)-object-files: \c"

clean:
	@rm -rf $(OBJS) *.dSYM
	@echo "$(RED)$(NAME)-object-files deleted$(RESET)"
	@echo "$(RED)$(NAME)-dSYM-files deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) deleted$(RESET)"

re: fclean all

peace:
	@echo "\n"
	@echo "     .''.    .',"
	@echo "     |  |   /  /"
	@echo "     |  |  /  /"
	@echo "     |  | /  /"
	@echo "     |  |/  ;-._"
	@echo "     }  \` _/  / ;"
	@echo "     |  /\` ) /  /"
	@echo "     | /  /_/\_/\ "
	@echo "     |/  /      |"
	@echo "     (  ' \ '-  |"
	@echo "      \    \`.  /"
	@echo "       |      |"
	@echo "       |      |\n"

.INTERMEDIATE: ofilemessage

.PHONY: clean fclean all re