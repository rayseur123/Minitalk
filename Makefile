NAME := client server

SRCS_client := client.c
SRCS_server := server.c

UTILS := utils

OBJS_client := $(addprefix $(UTILS)/,$(SRCS_client:.c=.o))
OBJS_server := $(addprefix $(UTILS)/,$(SRCS_server:.c=.o))

DEPS_client := $(addprefix $(UTILS)/,$(SRCS_client:.c=.d))
DEPS_server := $(addprefix $(UTILS)/,$(SRCS_server:.c=.d))

LIBS := -Llibft/ -lft
PATH_LIBS := libft/libft.a
INCLUDE_DIRS := -Ilibft/include

CC = cc
CPPFLAGS += -MMD -MP -g3 $(INCLUDE_DIRS)
CFLAGS += -Wall -Wextra -Werror

all: $(NAME)

client: $(OBJS_client) $(PATH_LIBS)
	$(CC) $^ -o $@

server: $(OBJS_server) $(PATH_LIBS)
	$(CC) $^ -o $@

$(UTILS)/%.o: %.c | $(UTILS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(UTILS):
	@mkdir -p $(UTILS)

$(PATH_LIBS):
	$(MAKE) -C $(dir $(PATH_LIBS))

-include $(DEPS_client) $(DEPS_server)

clean:
	$(MAKE) clean -C libft/
	rm -f $(OBJS_client) $(OBJS_server) $(DEPS_client) $(DEPS_server)

fclean: clean
	$(MAKE) fclean -C libft/
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
