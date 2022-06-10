NAME := test
SRC_DIR := ./src/
OBJ_DIR := ./obj/
HEADER_DIR := ./inc/
SRCS :=	my_main.cpp
CC := c++
CFLAGS := -Wall -Werror -Wextra -std=c++98
OBJS := $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRCS))
HEADERS := $(wildcard $(HEADER_DIR)*.hpp)
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
NC := \033[0m
INCLUDES := -I $(HEADER_DIR)
DEPS := $(HEADERS) 
MAKE += --no-print-directory

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(DEPS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@
	@echo "\n$(GREEN)$(NAME) created$(NC)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(DEPS) ofilemessage
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo ".\c"

ofilemessage:
	@echo "compiling $(NAME)-object-files: \c"

clean:
	@rm -rf $(OBJS) *.dSYM
	@echo "$(RED)$(NAME)-object-files deleted$(NC)"
	@echo "$(RED)$(NAME)-dSYM-files deleted$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) deleted$(NC)"

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