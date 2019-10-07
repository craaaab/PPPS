all : BisectionMethod.exe
BisectionMethod.exe: BisectionMethod.o
	g++ -o $@ $<
BisectionMethod.o:BisectionMethod.cpp
	g++ -c $<
clean:
	rm BisectionMethod.o