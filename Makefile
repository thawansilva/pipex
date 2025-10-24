NAME := pipex
# Directories
SRCDIR := src
SRCBONUSDIR := src_bonus
OBJDIR := obj
OBJBONUSDIR := obj_bonus
INCDIR := include lib/libft

# Source files and Objects
SRC := main.c pipex.c utils_pipex.c split_literal_args.c
SRC_BONUS := main_bonus.c pipex_bonus.c utils_pipex_bonus.c\
	   split_literal_args_bonus.c\

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
MANDATORY_MARK = .mandatory
BONUS_MARK = .bonus


all: $(NAME) 

# Mandatory
$(NAME): $(MANDATORY_MARK)

$(MANDATORY_MARK): $(OBJS) $(LIBS_TARGET)
	@$(RM) $(BONUS_MARK)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@touch $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(DUP_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

# Bonus
bonus: $(BONUS_MARK)

$(BONUS_MARK): $(OBJS_BONUS) $(LIBS_TARGET)
	@$(RM) $(MANDATORY_MARK)
	$(CC) $(OBJS_BONUS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@touch $@


$(OBJBONUSDIR)/%.o: $(SRCBONUSDIR)/%.c
	$(DUP_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RMDIR) $(OBJDIR) $(OBJBONUSDIR)
	@$(RM) $(BONUS_MARK) $(MANDATORY_MARK)

fclean: clean
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME) $(LIBMLX)

re: fclean all

.PHONY: all clean fclean re bonus
