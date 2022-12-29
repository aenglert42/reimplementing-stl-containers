NAME := containers_ft
SRC_DIR := src/
OBJ_DIR := obj/
HEADER_DIR := inc/
SRCS :=	my_main.cpp
CC := c++
ifeq ($(DEBUG),1)
CFLAGS := -g -Wall -Werror -Wextra
else ifeq ($(DEBUG),2)
CFLAGS := -g
else
CFLAGS := -g -Wall -Werror -Wextra -std=c++98 -DNDEBUG
endif
OBJS := $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRCS))
HEADERS := $(wildcard $(HEADER_DIR)*.hpp)
INCLUDES := -I $(HEADER_DIR)
DEPS := $(HEADERS) Makefile
MAKE += --no-print-directory
UNIT_TESTER_DIR := unit_tester/
#TEXT FORMAT
RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m
BOLD := \033[1m
UNDERLINED := \033[4m
RESET := \033[0m

all: $(NAME)

run: all
	./$(NAME)

unit:
	@make -C $(UNIT_TESTER_DIR)

unitre:
	@make re -C $(UNIT_TESTER_DIR)

test: all unit
	./unit_test

terminator:
	@cd ft_containers-terminator; \
	./test_containers.sh map; \
	cd ../../ft_containers;

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
	@$(MAKE) clean -C ./unit_tester/
	@echo "$(RED)$(NAME)-object-files deleted$(RESET)"
	@echo "$(RED)$(NAME)-dSYM-files deleted$(RESET)"
	@make clean -C $(UNIT_TESTER_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C ./unit_tester/
	@echo "$(RED)$(NAME) deleted$(RESET)"
	@make fclean -C $(UNIT_TESTER_DIR)

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