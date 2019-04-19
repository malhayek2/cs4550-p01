# This Makefile turns off exec protection
CXXFLAGS=-fno-stack-protector -D_FORTIFY_SOURCE=0
CXXFLAGS += -std=c++11 

toy: main.o
	$(CXX) -o $@ $^ 
	execstack -s $@

instructions.o: instructions_starter.cpp instructions.h
# symbol.o: symbol.cpp symbol.h debug.h
# token.o: token.cpp token.h debug.h
# scanner.o: scanner.cpp scanner.h debug.h token.h StateMachine.h
# node.o: node.cpp node.h debug.h symbol.h instructions.h
# parser.o: parser.cpp parser.h debug.h token.h scanner.h symbol.h node.h
main.o: main.cpp instructions.h
# main.o: main.cpp scanner.h symbol.h parser.h node.h token.h instructions.h debug.h
# StateMachine.o: StateMachine.cpp StateMachine.h token.h debug.h

clean:
	@echo "doing a clean:"
	rm -f *.o toy
