NAME := pipex
# Directories
SRCDIR := src
SRCBONUSDIR := src_bonus
OBJDIR := obj
OBJBONUSDIR := obj_bonus
INCDIR := include lib/libft

# Source files and Objects
SRC := main.c pipex.c utils_pipex.c ft_split_literal.c
SRC_BONUS := main_bonus.c handle_multiple_pipes_bonus.c utils_pipex_bonus.c\

SRC := $(SRC:%=$(SRCDIR)/%)
SRC_BONUS := $(SRC_BONUS:%=$(SRCBONUSDIR)/%)
OBJS := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJS_BONUS := $(SRC_BONUS:$(SRCBONUSDIR)/%.c=$(OBJBONUSDIR)/%.o)

# Libs
LIBS := ft
LIBS_TARGET := lib/libft/libft.a

# Flags
CC := clang
CFLAGS := -Wall -Wextra -Werror -g2
CPPFLAGS := $(addprefix -I, $(INCDIR))
LDFLAGS := $(addprefix -L, $(dir $(LIBS_TARGET)))
LDLIBS := $(addprefix -l, $(LIBS))

# Useful variables
RM := rm -f
RMDIR := rm -fr
DUP_DIR = mkdir -p $(@D)
COLOR_GREEN := \033[0;32m
END_COLOR := \033[0m

all: $(NAME) 

$(NAME): $(OBJS) $(LIBS_TARGET)
	@$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "✅ $(COLOR_GREEN)$(NAME) CREATED $(END_COLOR)"

bonus: $(OBJS_BONUS) $(LIBS_TARGET)
	@$(CC) $(OBJS_BONUS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "✅ $(COLOR_GREEN)$(NAME) CREATED $(END_COLOR)"

$(LIBS_TARGET):
	@$(MAKE) -C $(@D)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(DUP_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "✅ $(COLOR_GREEN)$@ CREATED $(END_COLOR)"

$(OBJBONUSDIR)/%.o: $(SRCBONUSDIR)/%.c
	@$(DUP_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "✅ $(COLOR_GREEN)$@ CREATED $(END_COLOR)"

clean:
	@$(RMDIR) $(OBJDIR) $(OBJBONUSDIR)
	@echo "✅ $(COLOR_GREEN) Pipex Object Files DELETED $(END_COLOR)"

fclean: clean
	@for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	@$(RM) $(NAME) $(LIBMLX)
	@echo "✅ $(COLOR_GREEN)$(NAME) and libft.a DELETED $(END_COLOR)"

re: fclean all

.PHONY: all clean fclean re bonus
