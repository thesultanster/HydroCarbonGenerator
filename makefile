GCC=g++ -g

default: main

main: 
	$(GCC) main.cpp -o organ

clean:
	rm -rf *.o organ
