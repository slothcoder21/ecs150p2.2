objs := queue.o

CFLAGS := -Wall -Wextra -Werror
CC := gcc

# Target library
lib := libuthread.a

all: $(lib)

## TODO: Phase 1
$(lib): ${objs}
	ar rcs $@ ${objs}

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(lib) $(objs)