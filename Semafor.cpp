/*
 * Semafor.cpp
 *
 *  Created on: 04-11-2014
 *      Author: dawid
 */

#include "Semafor.h"

Semafor::Semafor(int _count) : licznikZasobow(_count){}

int Semafor::wartosc() const
{
	return licznikZasobow;
}

void Semafor::sygnalizuj()
{
	//licznik na wyłączność
	unique_lock<mutex> blokadaLicznika(mutexLicznika);
	//zwiekszamy licznik
	++licznikZasobow;
	//powiadamiamy jeden oczekujacy watek że licznik został zwiększony
	warunekLicznikRoznyOdZera.notify_one();
}

void Semafor::czekaj()
{
	//licznik na wyłączność
	unique_lock<mutex> blokadaLicznika(mutexLicznika);
	//jeżeli licznik jest równy 0 to nie możemy go
	//zmniejszyć, czekamy aż zostanie zwiększony przez
	//inny wątek
	while(licznikZasobow == 0)
		warunekLicznikRoznyOdZera.wait(blokadaLicznika);
	//zmniejszamy licznik
	--licznikZasobow;
}

bool Semafor::probuj_czekac()
{
	//licznik na wylacznosc
	unique_lock<mutex> blokadaLicznika(mutexLicznika);
	//jezeli licznik jest wiekszy od 0 to go zmniejszamy
	if (licznikZasobow != 0) {
		--licznikZasobow;
		return true;
	} else {
		//w przeciwnym razie informujemy ze nie udalo sie
		return false;
	}
}
