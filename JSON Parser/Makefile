all: JSONParser

JSONParser: main.o JSONParser.o ; clang++ main.o JSONParser.o -o JSONParser

main.o : main.cpp ; clang++ -c main.cpp
JSONParser.o : JSONParser.cpp ;  clang++ -c JSONParser.cpp

clean: ; rm main.o JSONParser.o
