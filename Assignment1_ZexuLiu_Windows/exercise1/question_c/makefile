all : question_c.exe
question_c.exe: main.o
	g++ -o $@ $<
main.o:main.cpp
	g++ -c $<
clean:
	rm main.o