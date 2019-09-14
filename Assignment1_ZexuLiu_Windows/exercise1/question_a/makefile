all : question_a.exe
question_a.exe: main.o
	g++ -o $@ $<
main.o:main.cpp
	g++ -c $<
clean:
	rm main.o