NAME_ASM=asm
NAME_VM=corewar

ASM_SRC_NAME=check_file.c \
			 verify_list.c \
			 check_fcts.c \
			 get_data.c \
			 compiler.c \
			 error.c \
			 get_label_pos.c \
			 write.c \
			 main.c
COMMON_SRC_NAME = op.c \
				  bits.c \
				  arena.c \
				  $(addprefix instr/, $(INSTR_SRC_NAME))
INSTR_SRC_NAME = interpret.c \
				 cast.c \
				 live.c \
				 ld.c \
				 st.c \
				 add.c \
				 sub.c \
				 and.c \
				 or.c \
				 xor.c \
				 zjmp.c \
				 ldi.c \
				 sti.c \
				 fork.c \
				 lld.c \
				 lldi.c \
				 lfork.c \
				 aff.c \
				 registers.c
VISU_SRC_NAME=	arena.c \
				header.c \
				init_and_free.c \
				stats.c \
				visu_ncurses.c \
				windows.c
VM_SRC_NAME	= init_players.c \
				init_vm.c \
				parse_args.c \
				run_vm.c \
				main.c

ASM_SRC=$(addprefix srcs/asm/, $(ASM_SRC_NAME))
VISU_SRC=$(addprefix srcs/visu/, $(VISU_SRC_NAME))
VM_SRC=$(addprefix srcs/vm/, $(VM_SRC_NAME))
COMMON_SRC=$(addprefix srcs/, $(COMMON_SRC_NAME))
ASM_OBJ=$(patsubst srcs/asm/%.c, obj/asm/%.o, $(ASM_SRC))
VISU_OBJ=$(patsubst srcs/visu/%.c, obj/visu/%.o, $(VISU_SRC))
VM_OBJ=$(patsubst srcs/vm/%.c, obj/vm/%.o, $(VM_SRC))
COMMON_OBJ=$(patsubst srcs/%.c, obj/%.o, $(COMMON_SRC))

CC=gcc
INC=-Iincludes -Ilibft/includes
CFLAGS=-Wall -Wextra -Werror -g $(INC)
LIB=-Llibft -lft -lncurses


all: $(NAME_ASM) $(NAME_VM)

$(NAME_ASM): $(ASM_OBJ) $(COMMON_OBJ)
	@make -C libft
	@printf "==> compiling %s\n" $@
	@$(CC) $(CFLAGS) -o $@ $(ASM_OBJ) $(COMMON_OBJ) $(LIB)

$(NAME_VM): $(VM_OBJ) $(COMMON_OBJ) $(VISU_OBJ)
	@make -C libft
	@printf "==> compiling %s\n" $@
	@$(CC) $(CFLAGS) -o $@ $(VM_OBJ) $(COMMON_OBJ) $(VISU_OBJ) $(LIB)

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
