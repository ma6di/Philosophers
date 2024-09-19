CC = gcc
CFLAGS = -Wall -Werror -Wextra
SANITIZE = -fsanitize=thread

# Target executable
NAME = philo

# Source files
SRCS = philosophers.c utils.c data_init.c dinner.c write_status.c ft_syncro.c time.c monitor.c

# Object files
OBJS = $(SRCS:.c=.o)

# Build the target
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Compile with Thread Sanitizer
tsan: CFLAGS += $(SANITIZE) -g
tsan: clean $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME)_tsan $(OBJS)

# Compile the .c files to .o files
%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(NAME) $(NAME)_tsan $(OBJS)

# Remove all files, including executables
fclean: clean
	rm -f $(NAME)_tsan

# Rebuild the project
re: fclean $(NAME)
