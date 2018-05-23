#include <iostream>
#include <boost/thread.hpp>
#include <stdlib.h>
#include <boost/thread/mutex.hpp>

using namespace std;

boost::mutex blokadaKonsoli;

void Watek()
{
	for (int i = 0; i < 15; ++i)
	{
		blokadaKonsoli.lock();
		cout << "i = " << i << " numer: " << boost::this_thread::get_id() << endl;
		blokadaKonsoli.unlock();
		boost::this_thread::yield();
	}
}

int main()
{
	boost::thread watekPierwszy(Watek);
	boost::thread watekDrugi(Watek);

	watekPierwszy.join();
	watekDrugi.join();
	return 0;
}
