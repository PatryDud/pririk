#include <iostream>
#include <boost/thread.hpp>
#include <stdlib.h>
#include <boost/thread/mutex.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random.hpp>

#include "Semafor.h"

using namespace std;

boost::mutex blokadaKonsoli;
boost::random::minstd_rand generator;
boost::random::uniform_int_distribution<int> zakres(100,500);

Semafor sem(3);
Semafor sem2(1);

void Watek()
{
	sem.czekaj();
	for (int i = 0; i < 15; ++i)
	{
		sem2.czekaj();
		cout << "i = " << i << " numer: " << boost::this_thread::get_id() << endl;
		sem2.sygnalizuj();
		this_thread::sleep_for(chrono::milliseconds(zakres(generator)));
	}
	sem.sygnalizuj();
}

int main()
{

	boost::thread_group grupaWatkow;

	for (int i = 0; i < 7; ++i) {
		grupaWatkow.create_thread(Watek);

	}

	grupaWatkow.join_all();
	return 0;
}
