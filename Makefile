NAME_ASM=asm
NAME_CWAR=corewar

ASM_SRC_NAME=check_file.c\
			 verify_list.c\
COMMON_SRC_NAME = 
CWAR_SRC_NAME = 

ASM_SRC=$(addprefix srcs/asm/, $(ASM_SRC_NAME))
CWAR_SRC=$(addprefix srcs/corewar/, $(CWAR_SRC_NAME))
COMMON_SRC=$(addprefix srcs/, $(COMMON_SRC_NAME))
ASM_OBJ=$(patsubst srcs/asm/%.c, obj/asm/%.o, $(ASM_SRC))
CWAR_OBJ=$(patsubst srcs/corewar/%.c, obj/corewar/%.o, $(CWAR_SRC))
COMMON_OBJ=$(patsubst srcs/%.c, obj/%.o, $(COMMON_SRC))

CC=clang
INC=-Iincludes -Ilibft/includes
CFLAGS=-Wall -Werror -Wextra $(INC)
LIB=-Llibft -lft


all: $(NAME_ASM) $(NAME_CWAR)

$(NAME_ASM): $(ASM_OBJ) $(COMMON_OBJ)
	@make -C libft
	@printf "==> compiling %s\n" $@
	@$(CC) $(CFLAGS) -o $@ $(ASM_OBJ) $(COMMON_OBJ) $(LIB)

$(NAME_CWAR): $(CWAR_OBJ) $(COMMON_OBJ)
	@make -C libft
	@printf "==> compiling %s\n" $@
	@$(CC) $(CFLAGS) -o $@ $(CWAR_OBJ) $(COMMON_OBJ) $(LIB)

obj/%.o: srcs/%.c
	@mkdir -p $(shell dirname $@)
	@printf "==> compiling %s\n" $@
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@make -C libft clean
	@rm -rf obj

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME_ASM)
	@rm -f $(NAME_CWAR)

re: fclean all
