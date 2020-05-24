NAME = simple_socket.a

CC = gcc

COPTIONS = -c

CFLAGS = -Wall -Wextra

LIBCC = ar

LIBCOPTIONS = rc

SRCS =	accept_connection.c 	\
		connect_to_server.c		\
		create_ipv4_server.c	\
		create_ipv6_server.c	\
		recvall.c				\
		sendall.c				\
		print_bytearray.c		\
		encoding.c				\

OBJS =	accept_connection.o		\
		connect_to_server.o		\
		create_ipv4_server.o	\
		create_ipv6_server.o	\
		recvall.o				\
		sendall.o				\
		print_bytearray.o		\
		encoding.o				\

all:$(NAME)

$(NAME): $(addprefix src/, $(SRCS))
	$(CC) $(COPTIONS) $(CFLAGS) $(addprefix src/, $(SRCS))
	mv $(OBJS) obj/
	$(LIBCC) $(LIBCOPTIONS) $(NAME) $(addprefix obj/, $(OBJS))

clean:
	/bin/rm -f $(addprefix obj/, $(OBJS))

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
