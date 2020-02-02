twist: twist.c
	gcc -o twist twist.c

xor: xor.c
	gcc -o xor xor.c

tx: tx.c
	gcc -o tx tx.c

all: 
	gcc -o twist twist.c
	gcc -o xor xor.c
	gcc -o tx tx.c

clean:
	rm twist
