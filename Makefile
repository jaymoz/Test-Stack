NAME		= SearchReplace
SRCS		= main.cpp SearchReplace.cpp
OBJS		= $(SRCS:.cpp=.o)
CC			= g++
CFLAGS		= -g -std=c++17
RM			= rm -rf

%.o:		%.cpp
			$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re