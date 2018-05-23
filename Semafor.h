#ifndef SEMAFOR_H_
#define SEMAFOR_H_

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

using namespace boost;

class Semafor {
public:
	Semafor(int _count);

	//zwalnia zasob
	void sygnalizuj();

	//zajmuje zasob (jezeli nie ma wolnych to czeka na zwolnienie zasobu
	void czekaj();

	//probuje zajac zasob, zwraca true jezeli sie udalo, false jezeli wszystkie zasoby sa zajete
	bool probuj_czekac();

	//zwraca biezaca wartosc licznika
	int wartosc() const;

private:
	//licznik dostepnych zasobow
	int licznikZasobow;

	//synchronizacja watkow
	mutex mutexLicznika;
	condition_variable warunekLicznikRoznyOdZera;
};




#endif /* SEMAFOR_H_ */
