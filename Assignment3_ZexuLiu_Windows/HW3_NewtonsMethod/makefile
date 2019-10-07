all : NewtonsMethod.exe
NewtonsMethod.exe: NewtonsMethod.o
	g++ -o $@ $<
NewtonsMethod.o:NewtonsMethod.cpp
	g++ -c $<
clean:
	rm NewtonsMethod.o