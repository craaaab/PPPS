all : main.exe
main.exe: main.o solve.o
	g++ -o $@ $< solve.o
main.o: main.cpp solve.h
	g++ -c $<
solve.o: solve.cpp solve.h
	g++ -c solve.cpp
clean:
	rm main.o