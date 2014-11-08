#include <pthread.h>
#include <cstdlib>
#include <queue>
#include <unistd.h>
#include <time.h>   
#include <cstdio>

using std::queue;

queue<int> message;
bool all;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// bisa juga dibuat versi C nya

void* producer(void* param){
	all = false;
	for (int i = 0; i < 10; ++i){
		pthread_mutex_lock(&lock);
		if (message.size() < 10)
			message.push(rand() % 1000);
		pthread_mutex_unlock(&lock);
		usleep((rand() % 1000) * 1000);
	}
	all = true;
}

void* consumer(void* param){
	int id = (int) param;
	while(!all){
		pthread_mutex_lock(&lock);
		if (message.size() > 0){
			int m = message.front(); message.pop();
			printf("thread %d: %d\n", id, m);
		}
		pthread_mutex_unlock(&lock);
		usleep(500 * 1000);
	}
}

int main(){
	srand(time(NULL));
	pthread_t p, c[3];
	
	if (pthread_create(&p, NULL, producer, NULL)){
		exit(1);
	}
	
	for (int i = 0; i < 3; i++){
		if (pthread_create(&c[i], NULL, consumer, (void*) i))
			exit(1);
	}
	
	pthread_join(p, NULL);
	
	for (int i = 0; i < 3; i++){
		pthread_join(c[i], NULL);
	}
}