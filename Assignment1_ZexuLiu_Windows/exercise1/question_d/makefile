all : question_d.exe
question_d.exe: main.o
	g++ -o $@ $<
main.o:main.cpp
	g++ -c $<
clean:
	rm main.o