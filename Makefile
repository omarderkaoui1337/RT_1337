#@gcc $(OBJS) -o $(NAME) $(LFLAGS) $(LIBFT) 
#@gcc $(CFLAGS) -c -o $@ $<

#@gcc $(OBJS) -o $(NAME) $(PFLAGS) $(LIBFT)

PTHFLAG = -pthread
PFLAGS= -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11 -lm
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
	@make -C libft

$(NAME): $(OBJS)
	@gcc $(OBJS) -o $(NAME) $(PFLAGS) $(LIBFT) $(PTHFLAG)
	@echo "\033[92mDone\033[0m"

$(OBJS): %.o : %.c
	@gcc -g -c -o $@ $<
clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
