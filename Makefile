all:
	g++ -o test_pthread test_pthread.cpp -lpthread
	
run_pthread:
	./test_pthread