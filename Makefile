PREFIXE						= pipex
EXEC						= $(PREFIXE)
DEBUG						= yes

SRCS_DIR					= src
SRCS						= $(SRCS_DIR)/pipex.c 			\
								$(SRCS_DIR)/parsing.c 		\
								$(SRCS_DIR)/utils.c 		\
								$(SRCS_DIR)/children.c	

OBJ							= $(SRCS:.c=.o)
DEP							= $(SRCS:.c=.d)

%.o				: %.c
							$(CC) -c $(CFLAGS) $*.c -o $*.o
							$(CC) -MM $(CFLAGS) $*.c -o $*.d

CC							= cc

$(EXEC)						: libft/libft.a $(OBJ)
							$(CC) $(CFLAGS) $(OBJ) -L libft -lft -o $(EXEC)

CFLAGS						= -Wall -Werror -Wextra -g

all							: $(EXEC)

libft/libft.a				:
							make -C libft

clean						: 
							rm -f $(OBJ) $(DEP)
							rm -rf obj
							make clean -C libft
					
fclean						: clean
							rm -f $(EXEC)
							make fclean -C libft

re							: fclean
							@make all

.PHONY						= all clean fclean re