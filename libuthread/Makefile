objs := queue.o uthread.o preempt.o sem.o

CFLAGS := -Wall -Wextra -Werror
CFLAGS += -MMD
CC := gcc

# Target library
lib := libuthread.a

all: $(lib)

$(lib): ${objs}
	ar rcs $@ ${objs}

# Include dependencies
deps := $(patsubst %.o,%.d,$(objs))
-include $(deps)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(lib) $(objs) $(deps)