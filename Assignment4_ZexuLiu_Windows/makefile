all : solveLinear.exe
solveLinear.exe: solveLinear.o
	g++ -o $@ $<
solveLinear.o:solveLinear.cpp
	g++ -c $<
clean:
	rm solveLinear.o