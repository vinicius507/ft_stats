NAME = ft_stats
CC = clang
# CFLAGS = -Wall -Wextra -Werror -pg

SRC_DIR = ./src
BUILD_DIR = ./build
INCLUDES_DIR = ./include ./mongoose

INCLUDES := $(addprefix -I,$(INCLUDES_DIR))
SRCS = ft_stats.c callback.c
OBJS := $(addprefix $(BUILD_DIR)/,$(SRCS:.c=.o))
SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))

MONGOOSE = ./mongoose/mongoose.c

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(MONGOOSE) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $< -c -o $@

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	./$(NAME)

.PHONY: all clean fclean re
