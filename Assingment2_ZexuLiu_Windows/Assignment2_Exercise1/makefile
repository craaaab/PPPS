all : main.exe
main.exe: main.o
	g++ -o $@ $<
main.o:main.cpp
	g++ -c $<
clean:
	rm main.o