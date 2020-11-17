NAME  = RT
CFLAGS = -Wall -Werror -Wextra
CC = gcc
LFLAGS = -lmlx -framework OpenGL -framework AppKit -lm
SRCS  = main.c\
		hook.c\
		mlx.c\
		stor_stl.c\
		find_the_box.c\
		creat_camera.c\
		color.c\
		ray_genaration.c\
		vec_scaling.c\
		vectors_ops.c\
		traingle_intersection.c\


LIBFT = libft/libft.a


OBJS = $(SRCS:.c=.o)

all: lib $(NAME)

lib:
	@make -C libft > /dev/null

$(NAME): $(OBJS)
	@gcc $(OBJS) -o $(NAME) $(LFLAGS) $(LIBFT)
	@echo "\033[92mDone\033[0m"

$(OBJS): %.o : %.c
	#@gcc $(CFLAGS) -c -o $@ $<
	gcc  -c -o $@ $<
clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
