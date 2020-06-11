CXX = g++
CXXFLAGS = -Wall

proj1: Driver.o driver1.o driver2.o driver3.o Llama.o LlamaNode.o OvCoInt.o
	$(CXX) $(CXXFLAGS) Driver.o driver1.o driver2.o driver3.o Llama.o LlamaNode.o OvCoInt.o -o proj1

Llama.o: Llama.h Llama.cpp
	$(CXX) $(CXXFLAGS) -c Llama.cpp

LlamaNode.o: LlamaNode.h LlamaNode.cpp
	$(CXX) $(CXXFLAGS) -c LlamaNode.cpp

OvCoInt.o: OvCoInt.h OvCoInt.cpp
	$(CXX) $(CXXFLAGS) -c OvCoInt.cpp

Driver.o: Driver.cpp
	$(CXX) $(CXXFLAGS) -c Driver.cpp

driver1.o: driver1.cpp
	$(CXX) $(CXXFLAGS) -c driver1.cpp

driver2.o: driver2.cpp
	$(CXX) $(CXXFLAGS) -c driver2.cpp

driver3.o: driver3.cpp
	$(CXX) $(CXXFLAGS) -c driver3.cpp

clean:
	rm *.o proj1 *~


