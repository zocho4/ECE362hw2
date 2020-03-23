twist: twist.c
	gcc -o twist twist.c -std=99

xor: xor.c
	gcc -o xor xor.c -std=99

tx: tx.c xor.c twist.c
	gcc -o tx tx.c -std=99

pipe: tx.c firstProg.c secondProg.c
        gcc -o tx tx.c -std=c99

progA: firstProg.c
        gcc -o firstProg firstProg.c -std=c99

progB: secondProg.c
        gcc -o secondProg secondProg.c -std=c99

all: 
	gcc -o twist twist.c -std=99
	gcc -o xor xor.c -std=99
	gcc -o tx tx.c -std=99
        gcc -o firstProg firstProg.c -std=c99
        gcc -o secondProg secondProg.c -std=c99

clean:
	rm twist xor tx firstProg secondProg
