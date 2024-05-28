# This is a minimal set of ANSI/VT100 color codes
END			=	\e[0m
BOLD		=	\e[1m
UNDER		=	\e[4m
REV			=	\e[7m

# Colors

DEF_COLOR 	= 	\033[0;39m
GRAY 		= 	\033[0;90m
GREY_01		=	\033[30m
RED 		= 	\033[0;91m
RED_01		=	\033[31m
GREEN 		= 	\033[0;92m
GREEN_01	=	\033[32m
YELLOW 		= 	\033[0;93m
YELLOW_01	=	\033[33m
BLUE 		= 	\033[0;94m
BLUE_01		=	\033[34m
PURPLE		=	\033[35m
MAGENTA 	= 	\033[0;95m
CYAN 		= 	\033[0;96m
CYAN_01		=	\033[36m
WHITE 		= 	\033[0;97m
WHITE_01	=	\033[37m

# Inverted, i.e. colored backgrounds
IGREY		=	\e[40m
IRED		=	\e[41m
IGREEN		=	\e[42m
IYELLOW		=	\e[43m
IBLUE		=	\e[44m
IPURPLE		=	\e[45m
ICYAN		=	\e[46m
IWHITE		=	\e[47m

# **************************************************************************** #

NAME = philo
INCLUDE = include/
SRC_DIR = src/
OBJ_DIR = obj/
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lpthread
RM = rm -f
AR = ar rcs

# =========================================================================== #

# Sources
SRC_FILES = main utils parser init safe_controls dinner get_set write synchro_utils

#files
SRCS = 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
###
OBJF		=	.cache_exists

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
			@echo "$(GREEN)$(NAME) compilaoh$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "$(YELLOW)Compilando mostro: $(MAGENTA)$< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) -c $< -o $@
$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@echo "$(PURPLE)$(NAME) Objects borraos$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re