objs := uthread.o queue.o sem.o

CFLAGS := -std=c99 -D_XOPEN_SOURCE=700 -Wall -Wextra -Werror -I.
CC := gcc

# Target library
lib := libuthread.a

all: $(lib)

## TODO: Phase 1
all: $(lib)

$(lib): $(objs) ar rcs $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(lib) $(objs)