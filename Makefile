# Project compilation files and directories

NAME                    =   ft_irc

SRCS                    =   main.cpp    VectorTests.cpp		MapTests.cpp		

SRCSFD					=	srcs/
OBJSFD					=	objs/
HDR_INC					=	-I./includes

OBJS					=	$(addprefix $(OBJSFD), $(SRCS:.cpp=.o))
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Compilation
CFLAGS					=	-Wall -Wextra -Werror -std=c++98
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# Colors
RED						=	\033[0;31m
GREEN					=	\033[0;32m
NONE					=	\033[0m
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # 

all: project $(NAME)
	@echo "... project ready"

project:
	@echo "Checking project ..."

$(OBJSFD):
	@mkdir $@
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ directory"

$(NAME): $(OBJSFD) $(OBJS)
	@clang++ $(CFLAGS) $(OBJS) -o $@
	@echo "\t[ $(GREEN)✔$(NONE) ] $(NAME) executable"

$(OBJSFD)%.o: $(SRCSFD)%.cpp
	@clang++ $(CFLAGS) $(HDR_INC) -c $< -o $@
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ object"

clean:
	@echo "Cleaning project ..."
	@/bin/rm -rf $(OBJSFD)
	@echo "\t[ $(RED)✗$(NONE) ] Objects directory"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable deleted"

re: fclean all

.PHONY: project all clean fclean re