CXX = c++
NAME = ft_irc

CPPFLAGS = -Iincludes
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD
DBFLAGS = -g

SRCS_PATH = srcs/
OBJS_PATH = objs/
FOLDER_TO_CREATE = server commands commands/connection

SRCS = main.cpp User.cpp Channel.cpp\
		$(addprefix server/, Server.cpp serverUtils.cpp) \
		$(addprefix commands/, check.cpp Command.cpp numericReplies.cpp \
		$(addprefix connection/, pass.cpp nick.cpp))
OBJS = $(addprefix $(OBJS_PATH), $(SRCS:.cpp=.o))
DEPS = $(OBJS:.o=.d)

RM = rm -rf

all: clear create_objdirs $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

create_objdirs:
	mkdir -p $(OBJS_PATH)
	mkdir -p $(addprefix $(OBJS_PATH), $(FOLDER_TO_CREATE))

$(NAME): $(OBJS)
	$(CXX) $^ -o $@

-include $(DEPS)

debug: CXXFLAGS += $(DBFLAGS)
debug: fclean all

test: debug
	valgrind ./ft_irc "6667" "plop"

clear:
	clear

clean:
	$(RM) $(OBJS_PATH)

fclean:
	$(RM) $(OBJS_PATH) $(NAME)

re: fclean all

.PHONY: all debug clean clear create_objdirs fclean re test
