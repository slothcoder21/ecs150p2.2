objs := queue.o

CFLAGS := -Wall -Wextra -Werror
CC := gcc

# Target library
lib := libuthread.a

all: $(lib)

## TODO: Phase 1
$(lib): ${objs}
	ar rcs $@ ${objs}

# Dep tracking *must* be below the 'all' rule
deps := $(patsubst %.o,%.d,$(objs))
-include $(deps)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
