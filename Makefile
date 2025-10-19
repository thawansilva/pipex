NAME := pipex
# Directories
SRCDIR := src
OBJDIR := obj
INCDIR := include lib/libft

# Source files and Objects
SRC := main.c pipex.c utils_pipex.c ft_split_literal.c\

SRC := $(SRC:%=$(SRCDIR)/%)
OBJS := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

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

$(LIBS_TARGET):
	@$(MAKE) -C $(@D)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(DUP_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "✅ $(COLOR_GREEN)$@ CREATED $(END_COLOR)"

clean:
	@$(RMDIR) $(OBJDIR)
	@echo "✅ $(COLOR_GREEN)Fdf Object Files DELETED $(END_COLOR)"

fclean: clean
	@for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	@$(RM) $(NAME) $(LIBMLX)
	@echo "✅ $(COLOR_GREEN)$(NAME) and libmlx42.a DELETED $(END_COLOR)"

re: fclean all

.PHONY: all clean fclean re
