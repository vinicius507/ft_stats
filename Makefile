NAME = ft_stats
CC = clang
CFLAGS = -Wall -Wextra -Werror -g -DMG_ENABLE_MBEDTLS=1

MBEDTLS_DIR = /usr/lib/x86_64-linux-gnu/lib
MBEDTLS_LIBS = -L$(MBEDTLS_DIR) -lmbedtls -lmbedcrypto -lmbedx509
LIBMONGO = -lbson-1.0 -lmongoc-1.0
LIBS = $(MBEDTLS_LIBS) $(LIBMONGO)

SRC_DIR = ./src
BUILD_DIR = ./build
INCLUDES_DIR = ./include ./mongoose ./mjson

SRCS = ft_stats.c routes.c api.c handle_request.c redirect.c \
	   auth_intra.c send_request.c get_user_data.c request_token_intra.c \
	   tls.c get_user_data_intra.c handle_response.c request.c parse_user_data.c
OBJS := $(addprefix $(BUILD_DIR)/,$(SRCS:.c=.o))
SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
INCLUDES := $(addprefix -I,$(INCLUDES_DIR))

MONGOOSE = ./mongoose/mongoose.c
MJSON = ./mjson/mjson.c

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(MONGOOSE) $(MJSON)
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(LIBS) -o $@

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

install: all
	cp $(NAME) /usr/local/sbin/$(NAME)
	cp ./ft_stats.service /etc/systemd/system/ft_stats.service
	systemctl enable --now ft_stats.service

.PHONY: all clean fclean re
