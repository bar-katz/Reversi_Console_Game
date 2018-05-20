# Eden Yefet 204778294
# Bar Katz 208561357

a.out: compileAll
	g++ -o ../../exe/server.out *.o -lpthread
	rm -f *.o

compileAll: include/*.h src/*.cpp
	g++ -Iinclude/ -c src/*.cpp -g
run:
	./a.out


	
