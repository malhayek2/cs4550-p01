all:
	g++ -Wall -o main main.cpp scanner.h scanner.cpp token.h token.cpp statemachine.h statemachine.cpp Symbol.h Symbol.cpp  -lglut -lGLU -lGL
clean:
	rm main *.o