CC		:= cc

CFLAGS	:= -Wall -Wextra -pthread -g3

SRCS	:= philo.c

OBJS	:= $(SRCS:.c=.o)

NAME	:= philo

all			:	 $(NAME)

%.o			:	%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	:	$(OBJS)
	@$(CC) $(CFLAGS) $(LIBFT) $^ -o $@


clean		:
	@rm -f $(OBJS)

fclean		:	clean
	@rm -f $(NAME)

re			:	fclean all

tsan: CFLAGS += -fsanitize=thread,undefined,float-divide-by-zero,signed-integer-overflow -g3 -O3 -fno-omit-frame-pointer
tsan: re

asan: CFLAGS += -fsanitize=address,undefined,float-divide-by-zero,signed-integer-overflow -g3 -O3 -fno-omit-frame-pointer 
asan: re

# print_art	:
# 	@/bin/echo"                                                      "
# 	@/bin/echo "       ███████████                 ██████████        "
# 	@/bin/echo "    ████          ███            ███         ███     "
# 	@/bin/echo "   ██               ██         ██              ██    "
# 	@/bin/echo "  ██    █████████    ██       ██    ████████    ██   "
# 	@/bin/echo "  ██   ██       ██    ██     ██   ███       ██   ██  "
# 	@/bin/echo " ██   ██          █    ████████   █          █    ██ "
# 	@/bin/echo " ██   ██        ███               ███        █    ██ "
# 	@/bin/echo "  █    ██    ████████                ██     ██    █  "
# 	@/bin/echo "  ██    ████████████████     ████████████████    ██  "
# 	@/bin/echo "   ██     ████   ████  ██  ███   ███   ███      ██   "
# 	@/bin/echo "     ███  ██     ███     ███    ████    ███   ██     "
# 	@/bin/echo "        ████     ███     ███    ████     ████        "
# 	@/bin/echo "        ████    █████    ███    █████    ███         "
# 	@/bin/echo "        ██ ██   █████   ████    █████   ██ █         "
# 	@/bin/echo "        █   ██  ████   ██   ██  ████  ███  ██        "
# 	@/bin/echo "        ██    █████████       █████████    ██        "
# 	@/bin/echo "        ████████████████████████████████████         "
# 	@/bin/echo "         ██  ██ █    ███     ██     █ █   ██         "
# 	@/bin/echo "          ████  █   █  █     ███   █   ██ █          "
# 	@/bin/echo "           ██   ██ ██  ██   █  ██ ██    ██           "
# 	@/bin/echo "            ███  █ █    ██ ██   ████   ██            "
# 	@/bin/echo "              ██ ██      █ █    ███  ██              "
# 	@/bin/echo "                ████     ███     ████                "
# 	@/bin/echo "                    █████████████                    "
# 	@/bin/echo "                                                     "


PHONY: all clean fclean re print_art tsan
