objs := queue.o sem.o

CFLAGS := -std=c99 -D_XOPEN_SOURCE=700 -Wall -Wextra -Werror -I. 
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