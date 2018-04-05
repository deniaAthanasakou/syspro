CC = gcc -g
FILES = AllTests.c CuTest.c CuTestProcess.c CuTestPathStruct.c ../process.c ../pathStruct.c
OBJECTS = AllTests.o CuTest.o CuTestProcess.o CuTestPathStruct.o process.o pathStruct.o
OUT = test
HEADERS = CuTest.h CuTestProcess.h CuTestPathStruct.h ../process.h ../pathStruct.h

all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) $(FILES)
	make clean

AllTests.o: AllTests.c
	$(CC) -c AllTests.c
	
CuTest.o: CuTest.c
	$(CC) -c CuTest.c	
				
CuTestProcess.o: CuTestProcess.c
	$(CC) -c CuTestProcess.c
	
CuTestPathStruct.o: CuTestPathStruct.c
	$(CC) -c CuTestPathStruct.c	
	
process.o: ../process.c
	$(CC) -c ../process.c	
	
pathStruct.o: ../pathStruct.c
	$(CC) -c ../pathStruct.c		

clean:
	rm -f $(OBJECTS)

