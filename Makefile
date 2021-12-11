CC := gcc
SOURCEDIR := src
BUILDDIR := build
INCLUDEDIR := src
SOURCE := $(wildcard $(SOURCEDIR)/*.c)
OBJ := $(patsubst %c,%o,$(SOURCE))
LINKOBJ := $(wildcard $(BUILDDIR)/*.o)
CFLAGS := -g -std=gnu11 -I$(INCLUDEDIR)

all: clean prebuild build main 

prebuild:
	mkdir $(BUILDDIR)

build: $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)
	mv $@ $(BUILDDIR)

main: $(LINKOBJ)
	$(CC) $? -o $@ $(CFLAGS)

clean:
	rm -rf $(BUILDDIR) main

