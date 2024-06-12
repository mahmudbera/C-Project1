compile:program run
program: pMain.o pLib.o
	gcc pMain.o pLib.o -o program
pMain.o: pMain.c
	gcc -c pMain.c
pLib.o: pLib.c pLib.h
	gcc -c pLib.c
clean:
	del *.o program.exe
run:
	program.exe 400	
