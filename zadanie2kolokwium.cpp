#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

using namespace std;
using namespace boost;


char globalnaTablica[75];

bool saDane = false;

boost::condition_variable warunekSaDane;
boost::mutex mutexDanych;

class obslugaWatku {
public:
	obslugaWatku(int n) : iloscZnakow(n)
	{

	}
	//kod do wykonania
	void operator()(){
		for (int i = 0; i < iloscZnakow; ++i) {
			unique_lock<mutex> blokadaDanych(mutexDanych);
			if(saDane)
				warunekSaDane.wait(blokadaDanych);
			globalnaTablica[i] = '!' + i;
			saDane = true;
			warunekSaDane.notify_one();
		}
	}

private:
	int iloscZnakow;
};

int main() {
	thread watek(obslugaWatku(10));

	for (int i = 0; i < 10; ++i) {
		boost::unique_lock<boost::mutex> blokadaDanych(mutexDanych);
		if(!saDane)
			warunekSaDane.wait(blokadaDanych);
		cout << i << ": " << globalnaTablica[i] << endl;
		saDane = false;
		warunekSaDane.notify_one();
	}
	watek.join();
	return 0;
}
