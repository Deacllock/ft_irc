CXX = c++
NAME = ft_irc

CPPFLAGS = -Iincludes
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD
DBFLAGS = -g

SRCS_PATH = srcs/
OBJS_PATH = objs/

SRCS = main.cpp
OBJS = $(addprefix $(OBJS_PATH), $(SRCS:.cpp=.o))
DEPS = $(OBJS:.o=.d)

RM = rm -rf

all: $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
	mkdir -p $(OBJS_PATH)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $^ -o $@

-include $(DEPS)

debug: CXXFLAGS += $(DBFLAGS)
debug: fclean all

test: debug
	clear && valgrind ./ft_irc

clean:
	$(RM) $(OBJS_PATH)

fclean:
	$(RM) $(OBJS_PATH) $(NAME)

re: fclean all

.PHONY: all debug test clean fclean re
