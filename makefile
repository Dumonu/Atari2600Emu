all: debug

SUBDIRS = src

include makefile.inc

debug: $(SUBDIRS)
	@$(GCC) $(CFLAGS) $(OBJ_DIR)/*.o -o debug

clean:
	rm -f $(OBJ_DIR)/*
	rm -f debug
