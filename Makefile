CXX = g++
CXXFLAGS = -Wall

proj1: driver2.o Llama.o LlamaNode.o
	$(CXX) $(CXXFLAGS) driver2.o Llama.o LlamaNode.o -o proj1

Llama.o: Llama.h Llama.cpp
	$(CXX) $(CXXFLAGS) -c Llama.cpp

LlamaNode.o: LlamaNode.h LlamaNode.cpp
	$(CXX) $(CXXFLAGS) -c LlamaNode.cpp

driver1.o: driver1.cpp
	$(CXX) $(CXXFLAGS) -c driver1.cpp

driver2.o: driver2.cpp
	$(CXX) $(CXXFLAGS) -c driver2.cpp

driver3.o: driver3.cpp
	$(CXX) $(CXXFLAGS) -c driver3.cpp

clean:
	rm *.o proj1
	rm *~

