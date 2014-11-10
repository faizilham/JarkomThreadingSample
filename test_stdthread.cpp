/**
	Deskripsi permasalahan:
		Permasalahan producer-consumer.
		Producer: menghasilkan sebuah 10 bilangan random 0-999 setiap 0 - 999 milisekon
		Consumer: mengambil bilangan dari queue lalu menampilkannya ke layar setiap 500 milisekon
		
		Buffer queue maksimal 5 integer
*/
// thread & mutex
#include <thread>
#include <mutex>

// queue & vector
#include <queue>
#include <vector>

// untuk printf
#include <cstdio>

// untuk random, usleep, dan time
#include <cstdlib>
#include <unistd.h>
#include <time.h>

using std::queue;
using std::thread;
using std::mutex;
using std::vector;

queue<int> message;
bool all;
mutex lock;

void producer(){
	all = false;
	for (int i = 0; i < 10; ++i){
	
		lock.lock(); // ambil lock
		
		// jika buffer masih cukup, tambahkan bilangan random
		if (message.size() < 5)
			message.push(rand() % 1000);
			
		lock.unlock(); // lepas lock
		
		// sleep selama 0 - 999 milisekon (0 - 999000 nanosekon)
		usleep((rand() % 1000) * 1000);
	}
	all = true;
}

void consumer(int id){
	
	while(!all){
		lock.lock(); // ambil lock
		
		// jika ada bilangan dalam buffer, ambil lalu print
		if (message.size() > 0){
			int m = message.front(); message.pop();
			printf("thread %d: %d\n", id, m);
		}
		
		lock.unlock(); // lepas lock
		
		// sleep selama 500 milisekon (500000 nanosekon)
		usleep(500 * 1000);
	}
}

int main(){
	srand(time(NULL));
	vector<thread> c;
	
	// buat thread yang menjalankan producer()
	thread p(producer);
	
	// buat 3 thread, masing2 menjalankan consumer(i)
	for (int i = 0; i < 3; i++){
		c.push_back(thread(consumer, i));
	}
	
	p.join();
	
	// tunggu thread consumer selesai	
	for (int i = 0; i < 3; i++){
		c[i].join();
	}
}