decode: decode.o
	g++ decode.o -o decode

encode: encode.o
	g++ encode.o -o encode

encode.o: encode.cpp
	g++ -c encode.cpp

decode.o: decode.cpp
	g++ -c decode.cpp

clean: 
	rm *.o encode decode
