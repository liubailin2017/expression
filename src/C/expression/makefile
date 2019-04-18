tar = queue.o exp.o
exp.exe:$(tar)
	gcc -o exp.exe $(tar)
queue.o:queue.c queue.h
	gcc -c queue.c
exp.o:exp.c
	gcc -c exp.c
clean:
	del *.o
	del *.exe
test:
	exp
