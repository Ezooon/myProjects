CFLAGS = -Wall -g -O2
OBJS = main.o denoise.o read.o write.o time.o
denoise: $(OBJS)	
	$(CC) $(CFLAGS) -o $@ $?
clean:
	rm -rf $(OBJS) denoise *~ 