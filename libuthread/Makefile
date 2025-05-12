objs := queue.o uthread.o preempt.o

CFLAGS := -Wall -Wextra -Werror
CFLAGS += -MMD
CC := gcc

# Target library
lib := libuthread.a

all: $(lib)

## TODO: Phase 1
$(lib): ${objs}
	ar rcs $@ ${objs}

# Include dependencies
deps := $(patsubst %.o,%.d,$(objs))
-include $(deps)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(lib) $(objs) $(deps)