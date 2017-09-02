GCC = gcc
WORKDIR = `git rev-parse --show-toplevel`
CFLAGS = -std=c99 -g -fopenmp `sdl2-config --cflags --libs`
OBJ_DIR = $(WORKDIR)/build

%.o: %.c
	@ $(GCC) $(CFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(SUBDIRS):
	@ $(MAKE) -C $@ all

.PHONY: $(SUBDIRS) all

all: $(OBS) $(SUBDIRS)
