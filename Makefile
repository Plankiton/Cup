all: obj
	${CC} *.o -o cup ${CFLAGS} ${LDFLAGS}

obj:
	${CC} -c *.c ${CFLAGS} ${LDFLAGS}

clean:
	rm *.o *.a *.bin cup
