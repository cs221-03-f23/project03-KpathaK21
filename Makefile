OBJS = test.o project03.o
PROG = project03

%.o: %.c
	gcc -c -g -o $@ $<

$(PROG): $(OBJS)
	gcc -o $@ $^

clean:
	rm -f $(PROG) $(OBJS)
