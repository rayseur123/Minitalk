NAME := client server

SRCS_client := client.c
SRCS_server := server.c

UTILS := utils

OBJS_client := $(addprefix $(UTILS)/,$(SRCS_client:.c=.o))
OBJS_server := $(addprefix $(UTILS)/,$(SRCS_server:.c=.o))

DEPS_client := $(addprefix $(UTILS)/,$(SRCS_client:.c=.d))
DEPS_server := $(addprefix $(UTILS)/,$(SRCS_server:.c=.d))

LIBS := -Llibft/ -lft
PATH_LIBS := libft/
INCLUDE_DIRS := -I libft/include

CC = cc
CPPFLAGS := -MMD -MP -g3 $(INCLUDE_DIRS)
CFLAGS := -Wall -Wextra -Werror

all: $(NAME)

client: $(OBJS_client) $(LIBS)
	$(CC) $^ -o $@

server: $(OBJS_server) $(LIBS)
	$(CC) $^ -o $@

$(UTILS)/%.o: %.c | $(UTILS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(UTILS):
	@mkdir -p $(UTILS)

$(LIBS):
	$(MAKE) -C $(PATH_LIBS)

-include $(DEPS_client) $(DEPS_server)

bonus: $(OBJS_B) $(LIBS)
	$(CC) $^ -o checker

clean:
	$(MAKE) clean -C lib/libft/
	rm -f $(OBJS_client) $(OBJS_server) $(DEPS_client) $(DEPS_server)

fclean: clean
	$(MAKE) fclean -C lib/libft/
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
