NAME_ASM=asm
NAME_VM=corewar

ASM_SRC_NAME=check_file.c\
			 verify_list.c
COMMON_SRC_NAME = op.c \
				  $(addprefix instr/, $(INSTR_SRC_NAME))
INSTR_SRC_NAME = interpret.c \
				 live.c \
				 ld.c
VM_SRC_NAME	= init_players.c \
				init_vm.c \
				parse_args.c \
				main.c \

ASM_SRC=$(addprefix srcs/asm/, $(ASM_SRC_NAME))
VM_SRC=$(addprefix srcs/vm/, $(VM_SRC_NAME))
COMMON_SRC=$(addprefix srcs/, $(COMMON_SRC_NAME))
ASM_OBJ=$(patsubst srcs/asm/%.c, obj/asm/%.o, $(ASM_SRC))
VM_OBJ=$(patsubst srcs/vm/%.c, obj/vm/%.o, $(VM_SRC))
COMMON_OBJ=$(patsubst srcs/%.c, obj/%.o, $(COMMON_SRC))

CC=gcc
INC=-Iincludes -Ilibft/includes
CFLAGS=-Wall -Wextra -Werror -g $(INC)
LIB=-Llibft -lft


all: $(NAME_ASM) $(NAME_VM)

$(NAME_ASM): $(ASM_OBJ) $(COMMON_OBJ)
	@make -C libft
	@printf "==> compiling %s\n" $@
	@$(CC) $(CFLAGS) -o $@ $(ASM_OBJ) $(COMMON_OBJ) $(LIB)

$(NAME_VM): $(VM_OBJ) $(COMMON_OBJ)
	@make -C libft
	@printf "==> compiling %s\n" $@
	@$(CC) $(CFLAGS) -o $@ $(VM_OBJ) $(COMMON_OBJ) $(LIB)

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
	@rm -f $(NAME_VM)

re: fclean all
