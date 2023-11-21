# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rhorbach <rhorbach@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/14 12:49:02 by rhorbach      #+#    #+#                  #
#    Updated: 2023/09/19 17:01:25 by rhorbach      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADERFILES = \
	./libft.h						\
	./src/chr/chr.h					\
	./src/gnl/get_next_line_int.h	\
	./src/gnl/get_next_line.h		\
	./src/io/io.h					\
	./src/lst/lst.h					\
	./src/mem/mem.h					\
	./src/num/num.h					\
	./src/str/str.h

NORMFLAGS = -Wall -Wextra -Werror $(if $(DEBUG),-g)
# -fsanitize=address)
OBJDIR = obj
CFILES =							\
	./src/chr/ft_isalnum.c			\
	./src/chr/ft_isalpha.c			\
	./src/chr/ft_isascii.c			\
	./src/chr/ft_isdigit.c			\
	./src/chr/ft_isprint.c			\
	./src/chr/ft_isspace.c			\
	./src/chr/ft_tolower.c			\
	./src/chr/ft_toupper.c			\
									\
	./src/gnl/get_next_line.c		\
	./src/gnl/utils.c				\
									\
	./src/io/ft_putchar_fd.c		\
	./src/io/ft_putendl_fd.c		\
	./src/io/ft_puthexnbr_fd.c		\
	./src/io/ft_putnbr_fd.c			\
	./src/io/ft_putstr_fd.c			\
	./src/io/ft_putunbr_fd.c		\
									\
	./src/lst/ft_lst_dispose_one.c	\
	./src/lst/ft_lst_to_array_rev.c	\
	./src/lst/ft_lst_to_array.c		\
	./src/lst/ft_lstadd_back.c		\
	./src/lst/ft_lstadd_front.c		\
	./src/lst/ft_lstclear.c			\
	./src/lst/ft_lstdelone.c		\
	./src/lst/ft_lstiter.c			\
	./src/lst/ft_lstlast.c			\
	./src/lst/ft_lstmap.c			\
	./src/lst/ft_lstnew_front.c		\
	./src/lst/ft_lstnew_back.c		\
	./src/lst/ft_lstnew.c			\
	./src/lst/ft_lstsize.c			\
									\
	./src/mem/ft_bzero.c			\
	./src/mem/ft_calloc.c			\
	./src/mem/ft_free_ptr_array.c	\
	./src/mem/ft_memchr.c			\
	./src/mem/ft_memcmp.c			\
	./src/mem/ft_memcpy.c			\
	./src/mem/ft_memmove.c			\
	./src/mem/ft_memset.c			\
	./src/mem/ft_ptr_array_length.c	\
									\
	./src/num/ft_atoi.c				\
	./src/num/ft_itoa.c				\
	./src/num/ft_itob.c				\
	./src/num/ft_itoh.c				\
	./src/num/ft_satoi.c			\
									\
	./src/str/ft_split.c			\
	./src/str/ft_strchr.c			\
	./src/str/ft_strcmp.c			\
	./src/str/ft_strdup.c			\
	./src/str/ft_striteri.c			\
	./src/str/ft_strjoin.c			\
	./src/str/ft_strlcat.c			\
	./src/str/ft_strlcpy.c			\
	./src/str/ft_strlen.c			\
	./src/str/ft_strmapi.c			\
	./src/str/ft_strncmp.c			\
	./src/str/ft_strnstr.c			\
	./src/str/ft_strrchr.c			\
	./src/str/ft_strtrim.c			\
	./src/str/ft_substr.c

INCLUDES = $(addprefix -I, $(sort $(dir $(HEADERFILES))))
OBJFILES = $(addprefix $(OBJDIR)/,$(CFILES:c=o))

clear_line = \e[K
move_up = \e[A
define prettycomp
printf "$(1)$(clear_line)\n"
$(1)
printf "$(move_up)"
endef

all: $(NAME)

$(NAME): $(OBJFILES)
	ar -rcs libft.a $(OBJFILES)

obj/%.o: %.c $(HEADERFILES)
	@mkdir -p $(dir $@)
	@$(call prettycomp,$(CC) -c $(NORMFLAGS) $(INCLUDES) -o $@ $<)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

ifdef DEBUG
test: $(NAME)
	gcc $(NORMFLAGS) main.c -L. -lft -o test_libft
else
test:
	$(MAKE) test DEBUG=1
endif

.PHONY: all clean fcleam re test bonus
