#ifndef _TIME_H
#define _TIME_H
#include"struct.h"
bool stop = 1;
// CAP NHAP MANG TGIAN DE IN
void insertarray(char *h, TG *j) 
{
	int temp = 0;
	temp = j->giay;
	h[7] = doichar(temp % 10);
	h[6] = doichar(temp /= 10);

	temp = j->phut;
	h[4] = doichar(temp % 10);
	h[3] = doichar(temp /= 10);

	temp = j->gio;
	h[1] = doichar(temp % 10);
	h[0] = doichar(temp /= 10);

}

// CAP NHAP THOI GIAN THI
bool changetime(TG *h)
{
	if (h->giay > 0) --h->giay;
	else if (h->phut > 0)
	{
		h->giay = 59;
		--h->phut;
	}
	else if (h->gio > 0)
	{
		--h->gio;
		h->phut = 59;
		h->giay = 59;
	}
	else return false;
	return true;
}
//IN DONG HO
void printClock(int tg)
{
	TG h;
	if(tg < 60)
	{
		h = { 0,tg,0};
	}
	else if (tg == 60)
	{
		h = { 1,0,0};
	}
	else
	{
		int gio = tg/60;
		int phut = tg%60;
		h = { gio,phut,0};
	}
	char a[8] = { '0','0',':','0','0',':','0','0'};
	while (stop)
	{
		if (changetime(&h) == false) stop = 0;
		insertarray(a, &h);
		WriteBlockChar(a, 115, 1,0x007|0x000);
		Sleep(1000);
	}
	return;
}
#endif
