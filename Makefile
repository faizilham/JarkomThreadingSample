all:
	g++ -o run_pthread test_pthread.cpp -pthread
	g++ -std=c++11 -o run_stdthread test_stdthread.cpp -pthread -Wl,--no-as-needed
	
pthread:
	./run_pthread
	
stdthread:
	./run_stdthread