
UNAME := $(shell uname)
$(info UNAME: $(UNAME))

ifeq ($(UNAME), Linux)
  CC=gcc
else
  CC=clang
endif

.PHONY: clean

$(info CC: $(CC))

list_test: list.c list_test.c
	$(CC) -g list.c list_test.c -o list_test


clean:
	rm list_test
