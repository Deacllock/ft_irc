CXX = c++
NAME = ft_irc

CPPFLAGS = -Iincludes
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD
DBFLAGS = -DDEBUG -g -D_GLIBCXX_DEBUG

SRCS_PATH = srcs/
OBJS_PATH = objs/
FOLDER_TO_CREATE = server commands commands/connection commands/channel commands/operator commands/message

SRCS = main.cpp utils.cpp\
		$(addprefix server/, Server.cpp serverUtils.cpp User.cpp Channel.cpp) \
		$(addprefix commands/, check.cpp Command.cpp numericReplies.cpp\
		$(addprefix connection/, pass.cpp nick.cpp user.cpp cap.cpp quit.cpp ping.cpp pong.cpp) \
		$(addprefix channel/, join.cpp part.cpp invite.cpp topic.cpp list.cpp names.cpp mode.cpp) \
		$(addprefix operator/, die.cpp kill.cpp oper.cpp kick.cpp userMode.cpp) \
		$(addprefix message/, sendMessage.cpp))

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

opt_debug: CXXFLAGS += $(DBFLAGS)
opt_debug: all

test: opt_debug
	valgrind --leak-check=full ./ft_irc 6667 pwd

debug: opt_debug
	gdb --args ./ft_irc 6667 pwd


clear:
	clear

clean:
	$(RM) $(OBJS_PATH)

fclean:
	$(RM) $(OBJS_PATH) $(NAME)

re: fclean all

.PHONY: all debug clean clear create_objdirs fclean re test
