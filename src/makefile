CC = gcc
CFLAGS = -std=c99 -g
OBJ = CPUArithLogOps.o CPUJumpCtrl.o CPUMemRegTrans.o CPURotShift.o a2600.o
HEAD = CPUArithLogOps.h CPUJumpCtrl.h CPUMemRegTrans.h CPURotShift.h a2600.h


.PHONY: clean default

default: debug

debug: debug.o $(OBJ)
	$(CC) $(CFLAGS) -o debug debug.o $(OBJ)

debug.o: debug.c $(HEAD)
	$(CC) $(CFLAGS) -c debug.c

CPUArithLogOps.o: CPUArithLogOps.c $(HEAD)
	$(CC) $(CFLAGS) -c CPUArithLogOps.c

CPUJumpCtrl.o: CPUJumpCtrl.c $(HEAD)
	$(CC) $(CFLAGS) -c CPUJumpCtrl.c

CPUMemRegTrans.o: CPUMemRegTrans.c $(HEAD)
	$(CC) $(CFLAGS) -c CPUMemRegTrans.c

CPURotShift.o: CPURotShift.c $(HEAD)
	$(CC) $(CFLAGS) -c CPURotShift.c

a2600.o: a2600.c $(HEAD)
	$(CC) $(CFLAGS) -c a2600.c

clean:
	rm -f *.o debug
