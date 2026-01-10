CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -O1 -Iinc
EXEC    = ft_nmap

SRCDIR  = src
OBJDIR  = obj

SRCS    = $(addprefix $(SRCDIR)/, main.c arg.c addr.c)
OBJS    = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re
