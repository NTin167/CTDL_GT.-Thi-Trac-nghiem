#ifndef _DIEM_H
#define _DIEM_H
#include<fstream>
#include"SinhVien.h"
//#include"Monhoc.h"

//KIEM TRA SL THI
bool CheckSLThi (dsdiemThi dsd, string mamon)
{
	for(nodediemThi *k = dsd.First; k != NULL; k = k->pNext)
	{
		if(k->info.MAMH.compare(mamon) == 0)
		{
			return true;
		}
	}
	return false;
}

//IN BANG DIEM THI TN 1 MH CUA SV 
void InBangDiemSV (nodeSV *sv, int page, NODECH dsch)
{
	int maxpage;
	int slt = DemLanThi(sv->info.diem);
	if(slt <= 10)
	{
		maxpage = 0;
	}
	else if(slt > 10 && slt % 10 == 0)
	{
		maxpage = (slt/10) - 1;
	}
	else maxpage = slt/10;
	nodediemThi *p;
	if (page == 0)
	{
		p = sv->info.diem.First;
	}
	else
	{
		p = sv->info.diem.First;
		for (int i=0; i < page*10; i++)
		{
			if (p->pNext != NULL)
			{
				p = p->pNext;
			}
		}	
	}
	int dem = 1;
	int k = 0;
	for(int i = 0; i < 10; i++)
	{
		if(p->pNext != NULL)
		{
			gotoxy(20,6+k);
			cout << dem;
			gotoxy(50,6+k);
			cout << p->info.ctdt.sct;
			gotoxy(80,6+k);
			int socaudung = TinhDiem(p->info.ctdt,dsch)*10;
			int sct = p->info.ctdt.sct;
			int sDiem = (socaudung/sct);
			string diem = IntToString(sDiem);
			cout << diem;
			dem ++;
			k += 3;
			p = p->pNext;
		}
		else
		{
			gotoxy(20,6+k);
			cout << dem;
			gotoxy(50,6+k);
			cout << p->info.ctdt.sct;
			gotoxy(80,6+k);
			int socaudung = TinhDiem(p->info.ctdt,dsch)*10;
			int sct = p->info.ctdt.sct;
			int sDiem = (socaudung/sct);
			string diem = IntToString(sDiem);
			cout << diem;
			dem ++;
			k += 3;
			break;
		}
	}
	gotoxy(62,37);
	cout << "Trang" << page + 1 << "/" << maxpage + 1;
}
//XEM BANG DIEM THI TN 1 MH CUA SV
void XemBangDiemSV(nodeSV *k, NODECH dsch)
{
	system("cls");
	gotoxy(126,2);
	veKhung(11,40);
	gotoxy(128,4);
	cout << "MSSV: ";
	gotoxy(134,4);
	cout << k->info.MASV;
	gotoxy(128,7);
	cout << "HO VA TEN: ";
	gotoxy(139,7);
	cout << k->info.HO << " " << k->info.TEN;
	gotoxy(128,10);
	cout << "GIOI TINH: ";
	gotoxy(139,10);
	cout << k->info.PHAI;
	gotoxy(5,2);
	vekhungDS(34, 90, 3);
	gotoxy(17,3);
	cout << "LAN THI";
	gotoxy(46,3);
	cout << "SO CAU THI";
	gotoxy(76,3);
	cout << "DIEM";
	int state = 0;
	int maxpage;
	int page = 0;
	InBangDiemSV(k,page,dsch);
	int slt = DemLanThi(k->info.diem);
	char s;
	bool sCheck;
	gotoxy(7,6);
	cout << muiten;
	batPhim(s,sCheck);
	while(s != ESC)
	{
		if(slt <= 10)
		{
			maxpage = 0;
		}
		else if(slt % 10 == 0) 
		{
			maxpage = slt/10 -1;
		}
		else maxpage = slt/10;
		if(s == UP && sCheck == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if((state > 0) )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                             ";
						gotoxy(36,6+i);
						cout << "                             ";
						gotoxy(66,6+i);
						cout << "                             ";
						gotoxy(96,6+i);
						cout << "                            ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InBangDiemSV(k,page,dsch);
					gotoxy(7,33);
					cout << muiten;
					state = 9;
					
				}
			}
		}
		if(s == DOWN && sCheck == false)
		{
			if(state == 9)
			{
				nodediemThi *p = k->info.diem.First;
				for(int i=0; i< state + page*10; i++)
				{
					if (p->pNext != NULL)
					{
						p = p->pNext;
					}
				}
				if(p->pNext != NULL)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					if(page < maxpage)
					{
						for(int i = 0; i < 28;i++)
						{
							gotoxy(6,6+i);
							cout << "                             ";
							gotoxy(36,6+i);
							cout << "                             ";
							gotoxy(66,6+i);
							cout << "                             ";
							gotoxy(96,6+i);
							cout << "                            ";
						}
					}
					page++;
					InBangDiemSV(k,page,dsch);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				nodediemThi *p = k->info.diem.First;
				for(int i=0; i< state + page*10; i++)
				{
					if (p->pNext != NULL)
					{
						p = p->pNext;
					}
				}
				if(p->pNext != NULL)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				if(p->pNext == NULL) 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && sCheck == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                             ";
					gotoxy(36,6+i);
					cout << "                             ";
					gotoxy(66,6+i);
					cout << "                             ";
					gotoxy(96,6+i);
					cout << "                            ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				int hd = wherex();
				int td = wherey();
				InBangDiemSV(k,page,dsch);
				gotoxy(hd,td);
			}
		}
		if(s == PAGEUP && sCheck == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                             ";
					gotoxy(36,6+i);
					cout << "                             ";
					gotoxy(66,6+i);
					cout << "                             ";
					gotoxy(96,6+i);
					cout << "                            ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				int hd = wherex();
				int td = wherey();
				InBangDiemSV(k,page,dsch);
				gotoxy(hd,td);
			}
		}
		batPhim(s,sCheck);
	}
}
//IN DANH SACH DIEM THEO MH
void InDSDiemMH (lop *l,int page, monHoc *m,NODECH dsch)
{
	if (l->danhsach.First == NULL)
	{
		return;
	}
	int k = 2;
	int sl = DemSV(l->danhsach);
	int maxpage;
	if(sl <= 10)
	{
		maxpage = 0;
	}
	else if (sl % 10 == 0)
	{
		maxpage = sl/10 - 1;
	}
	else maxpage = sl/10;
	nodeSV *j = new nodeSV;
	if (page == 0)
	{
		j = l->danhsach.First;
	}
	else
	{
		j = l->danhsach.First;
		for (int i=0; i<page*10; i++)
		{
			if (j->pNext != NULL)
			{
				j = j->pNext;
			}
		}	
	}
	nodediemThi *p;
	for(int i = 0; i < 10; i++)
	{
		p = j->info.diem.First;
		int slt = 0;
		if (j->pNext != NULL) //j khong cuoi 
		{
			gotoxy(12,4+k);
			cout << j->info.MASV;
			gotoxy(32,4+k);
			cout << j->info.HO << " " << j->info.TEN;
			if(p == NULL) //j chua thi
			{	
				gotoxy(109,4+k);
				cout << "CHUA THI";
			}
			else //j co thi
			{
				while(p != NULL) //tim slt cua mon
				{
					if(p->info.MAMH.compare(m->MAMH) == 0)
					{
						slt++;
					}
					p = p->pNext;
				}
				if(slt == 0) //neu chi thi mon
				{
					gotoxy(109,4+k);
					cout << "CHUA THI";
				}
				else //neu co thi mon
				{
					gotoxy(113,4+k);
					cout << slt;
				}
			}
			k += 3;
			j = j->pNext;
		}
		else //j la cuoi
		{
			gotoxy(12,4+k);
			cout << j->info.MASV;
			gotoxy(32,4+k);
			cout << j->info.HO << " " << j->info.TEN;
			if(p == NULL)
			{	
				gotoxy(109,4+k);
				cout << "CHUA THI";
			}
			else //j co thi
			{
				while(p != NULL) //tim slt cua mon
				{
					if(p->info.MAMH.compare(m->MAMH) == 0)
					{
						slt++;
					}
					p = p->pNext;
				}
				if(slt == 0) //neu chi thi mon
				{
					gotoxy(109,4+k);
					cout << "CHUA THI";
				}
				else //neu co thi mon
				{
					gotoxy(113,4+k);
					cout << slt;
				}
			}
			k += 3;
			break;
		}
	}
	gotoxy(125/2,36);
	cout << "Trang " << page + 1 << "/" << maxpage + 1;
}
//XEM DIEM
void XemDiem1Lop(lop *l, monHoc *m, NODECH dsch)
{
	AnConTro();
	system("cls");
	
	gotoxy(10,1);
	
	cout << "Diem mon : " << m->TENMH;
	gotoxy(105,1);
	cout << "Lop : " << l->MALOP;
	gotoxy(5,2);
	VeKhungDSLop1(34,120,10);;
	int page = 0;
	gotoxy(15,3);
	cout << "MA SV";
	gotoxy(60,3);
	cout << "HO VA TEN";
	gotoxy(108,3);
	cout << "SO LAN THI";
	InDSDiemMH(l,page,m, dsch);
	int maxpage;
	int state = 0;
	char s;
	bool sCheck;
	gotoxy(7,6);
	cout << muiten;
	batPhim(s,sCheck);
	while(s != ESC)
	{
		if(DemSV(l->danhsach) % 10 == 0) 
		{
			maxpage = DemSV(l->danhsach)/10;
		}
		else maxpage = DemSV(l->danhsach)/10 + 1;
		if(s == UP && sCheck == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if((state > 0) )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                      ";
						gotoxy(31,6+i);
						cout << "                                             ";
						gotoxy(79,6+i);
						cout << "                     ";
						gotoxy(103,6+i);
						cout << "                     ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSDiemMH(l,page,m, dsch);
					gotoxy(7,33);
					cout << muiten;
					state = 9;
				}
			}
		}
		if(s == DOWN && sCheck == false)
		{
			if(state == 9)
			{
				nodeSV *k= l->danhsach.First;
				for(int i=0; i< state + page*10; i++)
				{
					if (k->pNext != NULL)
					{
						k = k->pNext;
					}
				}
				if(k->pNext != NULL)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					if(page < maxpage)
					{
					
						for(int i = 0; i < 28;i++)
						{
							gotoxy(6,6+i);
							cout << "                      ";
							gotoxy(31,6+i);
							cout << "                                             ";
							gotoxy(79,6+i);
							cout << "                     ";
							gotoxy(103,6+i);
							cout << "                     ";
						}
					}
					page++;
					InDSDiemMH(l,page,m, dsch);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				nodeSV *k= l->danhsach.First;
				for(int i=0; i< state + page*10; i++)
				{
					if (k->pNext != NULL)
					{
						k = k->pNext;
					}
				}
				if(k->pNext != NULL)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				if(k->pNext == NULL) 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && sCheck == false)
		{
			AnConTro();
			if(page < maxpage -1)
			{
				for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                      ";
						gotoxy(31,6+i);
						cout << "                                             ";
						gotoxy(79,6+i);
						cout << "                     ";
						gotoxy(103,6+i);
						cout << "                     ";
					}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				int hd = wherex();
				int td = wherey();
				InDSDiemMH(l,page,m, dsch);
				gotoxy(hd,td);
			}
		}
		if(s == PAGEUP && sCheck == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                      ";
						gotoxy(31,6+i);
						cout << "                                             ";
						gotoxy(79,6+i);
						cout << "                     ";
						gotoxy(103,6+i);
						cout << "                     ";
					}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				int hd = wherex();
				int td = wherey();
				InDSDiemMH(l,page,m, dsch);
				gotoxy(hd,td);
			}
		}
		if(s == ENTER)
		{
			//XEM BANG DIEM SINH VIEN
			nodeSV *k = l->danhsach.First;
			for (int i = 0; i < state + page*10; i++)
			{
				if (k->pNext != NULL)
				{
					k = k->pNext;
				}
			}
			if(k->info.diem.First == NULL)
			{
				gotoxy(wherex()-1,wherey());
				cout << " ";
				Message(130, 30, "Sinh vien chua thi ");
				AnConTro();
				Sleep(750);
				DeleteMessage(130, 30);
				gotoxy(7,6);
				cout << muiten;
				state = 0;
			}
			else
			{
				if(CheckSLThi(k->info.diem,m->MAMH) == false)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					Message(130, 30, "Sinh vien chua thi lan nao");
					AnConTro();
					Sleep(750);
					DeleteMessage(130, 30);
					gotoxy(7,6);
					cout << muiten;
					state = 0;
				}
				else
				{
					XemBangDiemSV(k,dsch);
					system("cls");
					gotoxy(10,1);
					cout << "Diem mon : " << m->TENMH;
					gotoxy(105,1);
					cout << "Lop : " << l->MALOP;
					gotoxy(5,2);
					VeKhungDSLop1(34,120,10);
					int page = 0;
					gotoxy(15,3);
					cout << "MA SV";
					gotoxy(60,3);
					cout << "HO VA TEN";
					gotoxy(108,3);
					cout << "SO LAN THI";
					InDSDiemMH(l,page,m, dsch);
					gotoxy(7,6);
					cout << muiten;
					state = 0;
				}
			}
		}
	batPhim(s,sCheck);
	}
}
// NHAP MON XEM DIEM 
void NhapMonXemDiem(lop *l, DSMH dsm, NODECH dsch)
{
	if(dsm.somon == 0)
	{
		Message(5, 40,"Danh sach mon hien tai dang trong");
		AnConTro();
		Sleep(850);
		DeleteMessage(5, 40);
		return;
	}
	gotoxy(5,2);
	vekhungDS(34,120,2);
	gotoxy(30,3);
	cout << "MA MON HOC";
	gotoxy(90,3);
	cout << "TEN MON HOC";
	int page = 0;
	int maxpage;
	InDSMon(dsm,page, 30, 4);
	char s;
	int state = 0;
	bool sCheck;
	Message(5, 40,"Vui long chon 1 mon hoc de xem diem");
	Sleep(750);
	DeleteMessage(5, 40);
	AnConTro();
	gotoxy(7,6);
	cout << muiten;
	batPhim(s,sCheck);
	while (s != ESC)
	{
		if(dsm.somon <= 10)
		{
			maxpage = 0;
		}
		else if(dsm.somon % 10 == 0) 
		{
			maxpage = dsm.somon/10 -1;
		}
		else maxpage = dsm.somon/10;
		if(s == UP && sCheck == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if((state > 0) )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                                          ";
						gotoxy(66,6+i);
						cout << "                                                          ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSMon(dsm,page,30,4);
					gotoxy(7,33);
					cout << muiten;
					state = 9;
				}
			}
		}
		if(s == DOWN && sCheck == false)
		{
			if(state == 9)
			{
				if(dsm.m[state + page*10 + 1] != NULL)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					if(page < maxpage)
					{
						for(int i = 0; i < 28;i++)
						{
							gotoxy(6,6+i);
							cout << "                                                          ";
							gotoxy(66,6+i);
							cout << "                                                          ";
						}
					}
					page++;
					InDSMon(dsm,page, 30, 4);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				if(dsm.m[state + page*10 + 1] != NULL)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				if(dsm.m[state + page*10 + 1] == NULL) 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && sCheck == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                                          ";
					gotoxy(66,6+i);
					cout << "                                                          ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				int hd = wherex();
				int td = wherey();
				InDSMon(dsm,page, 30, 4);
				gotoxy(hd,td);
			}
		}
		if(s == PAGEUP && sCheck == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                                          ";
					gotoxy(66,6+i);
					cout << "                                                          ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				int hd = wherex();
				int td = wherey();
				InDSMon(dsm,page, 30, 4);
				gotoxy(hd,td);
			}
		}
		if (s == ENTER)
		{
			XemDiem1Lop(l, dsm.m[state + page*10], dsch);
			system("cls");
			gotoxy(5,2);
			vekhungDS(34,120,2);
			gotoxy(30,3);
			cout << "MA MON HOC";
			gotoxy(90,3);
			cout << "TEN MON HOC";
			InDSMon(dsm,page,30,4);
			state = 0;
			
			Message(5, 40, "Vui long chon 1 mon hoc de xem diem");
			Sleep(750);
			DeleteMessage(5, 40);
			gotoxy(7,6);
			cout << muiten;
		}
	batPhim(s,sCheck);
	}
	for(int i = 0; i < 10; i++)
	{
		gotoxy(7,6+i*3);
		cout << " ";
	}
}
// ==================== NHAP LOP  ==========================
void NhapLopXemDiem(dslop dsl , DSMH dsm, NODECH dsch)
{
	system("cls");
	
	gotoxy(5,2);
	vekhungDS(34,100,2);
	gotoxy(26, 3);
	cout<<"MA LOP";
	gotoxy(70, 3);
	cout<<"TEN LOP";
	int page = 0;
	int maxpage;
	InDSLop(dsl,page,6,4);
	char s;
	int state = 0;
	bool sCheck;
	gotoxy(7,6);
	cout << muiten;
	batPhim(s,sCheck);
	while (s != ESC)
	{
		if(dsl.solop <= 10)
		{
			maxpage = 0;
		}
		else if(dsl.solop % 10 == 0) 
		{
			maxpage = dsl.solop/10 -1;
		}
		else maxpage = dsl.solop/10;
		if(s == UP && sCheck == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if((state > 0) )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 29;i++)
					{
						gotoxy(6,6+i);
						cout << "                                 ";
						gotoxy(58,6+i);
						cout << "                                           ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSLop(dsl,page,6,4);
					gotoxy(7,33);
					cout << muiten;
					state = 9;
					
				}
			}
		}
		if(s == DOWN && sCheck == false)
		{
			if(state == 9)
			{
				if(dsl.l[state + page*10 + 1] != NULL)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					if(page < dsl.solop/10)
					{
					
						for(int i = 0; i < 29;i++)
						{
							gotoxy(6,6+i);
							cout << "                                  ";   
							gotoxy(58,6+i); 
							cout << "                                            ";
						}
					}
					page++;
					InDSLop(dsl,page, 6, 4);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				if(dsl.l[state + page*10 + 1] != NULL)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				if(dsl.l[state + page*10 + 1] == NULL) 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && sCheck == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                 ";
					gotoxy(58,6+i);
					cout << "                                           ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				int hd = wherex();
				int td = wherey();
				InDSLop(dsl,page,6,4);
				gotoxy(hd,td);
			}
		}
		if(s == PAGEUP && sCheck == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                            ";
					gotoxy(58,6+i);
					cout << "                                      ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				int hd = wherex();
				int td = wherey();
				InDSLop(dsl,page,6,4);
				gotoxy(hd,td);
			}
		}
		if (s == ENTER)
		{
			if(dsl.l[state + page*10]->danhsach.First == NULL)
			{
				Message(5,40,"Lop khong co sinh vien khong the xem diem !");
				AnConTro();
				Sleep(850);
				DeleteMessage(5, 40);
				gotoxy(7,6 + state*3);
				cout << " ";
				state = 0;
				gotoxy(7,6);
				cout << muiten;
			}
			else
			{
				NhapMonXemDiem(dsl.l[state + page*10], dsm, dsch);
				system("cls");
				gotoxy(5, 2);
				vekhungDS(34,100,2);
				gotoxy(26, 3);
				cout<<"MA LOP";
				gotoxy(70, 3);
				cout<<"TEN LOP";
				InDSLop(dsl,page,6,4);
				state = 0;
				gotoxy(7,6);
				cout << muiten;
			}
			
		}
	batPhim(s,sCheck);
	}
}
//FUNCTION DIEM
void QUANLYDIEM(dslop dsl, dssv ds,DSMH dsm, NODECH dsch)
{
	int page = 0;
	if(dsl.solop == 0)
	{
		Message(5, 40, "Danh sach lop hien tai dang trong");
		AnConTro();
		Sleep(750);
		DeleteMessage(5, 40);
	}
	else
	{
		NhapLopXemDiem(dsl,dsm,dsch);
	}
}
#endif
