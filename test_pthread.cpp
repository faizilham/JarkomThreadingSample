/**
	Deskripsi permasalahan:
		Permasalahan producer-consumer.
		Producer: menghasilkan sebuah 10 bilangan random 0-999 setiap 0 - 999 milisekon
		Consumer: mengambil bilangan dari queue lalu menampilkannya ke layar setiap 500 milisekon
		
		Buffer queue maksimal 5 integer
*/

// bisa juga dibuat versi C nya

// untuk thread
#include <pthread.h>

// queue
#include <queue>

// untuk printf
#include <cstdio>

// untuk random, usleep, dan time
#include <cstdlib>
#include <unistd.h>
#include <time.h>  


using std::queue;

queue<int> message;
bool all;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* producer(void* param){
	all = false;
	for (int i = 0; i < 10; ++i){
	
		pthread_mutex_lock(&lock); // ambil lock
		
		// jika buffer masih cukup, tambahkan bilangan random
		if (message.size() < 5)
			message.push(rand() % 1000);
		pthread_mutex_unlock(&lock); // lepas lock
		
		// sleep selama 0 - 999 milisekon (0 - 999000 nanosekon)
		usleep((rand() % 1000) * 1000);
	}
	all = true;
}

void* consumer(void* param){
	int id = (int) param; // konversi param menjadi int, yaitu id thread consumer
	while(!all){
		pthread_mutex_lock(&lock); // ambil lock
		
		// jika ada bilangan dalam buffer, ambil lalu print
		if (message.size() > 0){
			int m = message.front(); message.pop();
			printf("thread %d: %d\n", id, m);
		}
		
		pthread_mutex_unlock(&lock); // lepas lock
		
		// sleep selama 500 milisekon (500000 nanosekon)
		usleep(500 * 1000);
	}
}

int main(){
	srand(time(NULL));
	pthread_t p, c[3];
	
	// buat thread yang menjalankan producer(NULL)
	if (pthread_create(&p, NULL, producer, NULL)){
		exit(1);
	}
	
	// buat 3 thread, masing2 menjalankan consumer((void*) i)
	for (int i = 0; i < 3; i++){
		if (pthread_create(&c[i], NULL, consumer, (void*) i))
			exit(1);
	}
	
	pthread_join(p, NULL); // tunggu thread producer selesai
	
	// tunggu thread consumer selesai	
	for (int i = 0; i < 3; i++){
		pthread_join(c[i], NULL);
	}
}