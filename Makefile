CC=gcc
AR=ar
CFLAGS=-Wall -Werror -O0 -g -m64
LFLAGS=-lmedian -lvector -L. -L./vector
APP=median
LIBS=libmedian.a vector
OBJS=test.o

ifeq ($(DEBUG),y)
	CFLAGS += -g -O0
else
	CFLAGS += -O3
endif

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $<

lib%.a: %.o
	$(AR) -r $@ $<

.PHONY: all clean cleanall vector

all: $(APP)

vector:
	$(MAKE) -C vector $(patsubst %,lib%.a,$@)

$(APP): $(LIBS) $(OBJS)
	$(CC) -o $@ $(OBJS) $(LFLAGS)

clean:
	@echo "removing executables"
	@rm -f $(APP)
	@echo "removing object files"
	@rm -f *.o *.a
	@$(MAKE) -C vector clean

cleanall: clean
	@echo "removing pre compilation files"
	@rm -f *_pre.c
	@echo "removing tag file"
	@rm -f tags
	@echo "removing vector library"
	@$(MAKE) -C vector cleanall

