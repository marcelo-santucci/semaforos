CC=gcc
CFLAGS=-pthread -g -Wall
OBJS=memoria_compartida.o
EXE=escribememcomp.elf leememcomp.elf eliminamemcomp.elf

all: $(EXE)

%.elf: %.o $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.dSYM *.o $(EXE)