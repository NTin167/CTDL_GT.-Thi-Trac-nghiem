#ifndef _MONHOC_H
#define _MONHOC_H
#include<iostream>
#include<fstream>
#include<string.h>
#include"struct.h"
//#include"CauHoiThi.h"
#define MAXMH 100


//SO SANH MA MH
int SoSanhMaMH(string mA, string mB)
{
	int x = mA.length();
	int y = mB.length();
	int z;
	if(x < y)
	{
		z = x;
	}
	else z = y;
	for(int i = 0; i < z; i++)
	{
		if(mA[i] < mB[i])
		{
			return 1;
		}
		else if(mA[i] >  mB[i])
		{
			return -1;
		}
		//else continue;
	}
	return 0;
}

// THEM MON THEO THU TU
void InsertMon(DSMH &dsm, monHoc mh)
{
	if(dsm.m[0] == NULL)
	{
		dsm.m[dsm.somon] = new monHoc;
		*dsm.m[dsm.somon] = mh;
		dsm.somon++;
	}
	else
	{
		int j;
		for(j = dsm.somon-1; j >=0 ; j--)
		{
			if(SoSanhMaMH(mh.MAMH,dsm.m[j]->MAMH) == -1)
			{
				break;
			}
		}
		dsm.m[dsm.somon] = new monHoc;
		dsm.somon ++;
		if(j == dsm.somon - 2)
		{
			*dsm.m[j+1] = mh;
		}
		else
		{
			
			for(int i = dsm.somon-1; i > j+1; i--)
			{
				*dsm.m[i] = *dsm.m[i-1];
			}
			*dsm.m[j+1] = mh;
		}
	}
}
// TIM KIEM MON HOC
monHoc* Search_Mon(DSMH dsm, string maMH)
{
	for(int i = 0; i < dsm.somon ; i++)
	{
		if(dsm.m[i]->MAMH.compare(maMH) == 0)
		{
			return dsm.m[i];
		}
	}
}

//DOC DANH SACH MON HOC TU FILE
void DocFileDSMH (DSMH &dsm)
{
	ifstream fileIn;
	fileIn.open("InputMonHoc.txt", ios_base :: in );
	if(fileIn.fail()) 
		cout << "Failed to open this file!";
	monHoc mh;
	while(!fileIn.eof())
	{
		getline(fileIn, mh.MAMH, '\n');
		getline(fileIn,mh.TENMH,'\n');
		InsertMon(dsm,mh);
	}
	fileIn.close();
}
//IN DS MON HOC
void InDSMon(DSMH dsm, int &page, int x, int y)
{
	if (dsm.somon == 0)
	{
		return;
	}
	int k = 2;
	int maxpage;
	if (dsm.somon % 10 == 0)
	{
		maxpage = dsm.somon/10;
	}
	else maxpage = dsm.somon/10 +1;
	for(int i = page*10; i < (page+1)*10; i++)
	{
		if(dsm.m[i] == NULL)
		{
			break;
		}
		gotoxy(x,y+k);
		cout << dsm.m[i]->MAMH;
		gotoxy(x+ 35 +((60 - dsm.m[i]->TENMH.length()) / 2),y+k);
		cout << dsm.m[i]->TENMH;
		k += 3;
	}
	
}
bool CheckMonNhapNew(DSMH dsm, string mamon, string tenmon, int &vitri)
{
	for(int i = 0; i < dsm.somon; i++)
	{
		if(mamon.compare(dsm.m[i]->MAMH) == 0 && tenmon.compare(dsm.m[i]->TENMH) == 0)
		{
			vitri = i;
			return false;
		}
	}
	return true;
}
//KIEM TRA MA MON & TEN MON TRONG DS
bool CheckMonNhap (DSMH dsm, string mamon, string tenmon)
{
	for(int i = 0; i < dsm.somon; i++)
	{
		if(mamon.compare(dsm.m[i]->MAMH) == 0 || tenmon.compare(dsm.m[i]->TENMH) == 0)
		{
			return false;
		}
	}
	return true;
}
//NHAP MON HOC THEM
void NhapMonHoc(DSMH &dsm, int page)
{	
	veNutMenu(1, 25, 75, 13, "THEM MON", 176);// nut Subject
	gotoxy(75, 15);
	veKhung(15, 60);
	gotoxy(85, 17);
	veKhung(3, 40);	
	gotoxy(85, 20);
	veKhung(3, 40);
	veNutMenu(1, 5, 79, 18, "MA MON", 176);
	veNutMenu(1, 5, 79, 21, "TEN MON", 176);
	veNutMenu(3, 20, 93, 24, "LUU", 176);
	string tenmon;
	string mamon;
	char s;
	bool state = true;
	bool sCheck;
	string tb;
	int hd;
	int td;
	gotoxy(86,18);
	HienConTro();
	batPhim(s,sCheck);
	while (1)
	{
		if(s == ESC)
		{
			if(Exit(s,sCheck,75, 30) == true)
			{
				system("cls");
				veNutMenu(3,30,2,2,"QUAN LY LOP HOC",128);
				veNutMenu(3,30,40,2,"IN DANH SACH LOP", 128);
				veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",128);
				veNutMenu(3,30,110,2,"QUAN LY MON HOC",95);
				veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",128);
				veNutMenu(3,30,180,2,"DANH SACH DIEM",128);
				gotoxy(50,5);
//	
//	
//				//QUAN LY LOP HOC
				veNutMenu(3, 30, 2, 6, "Them", 176);
				veNutMenu(3, 30, 2, 10, "Xoa", 176);
				veNutMenu(3, 30, 2, 14, "Sua", 176);
				//QUAN LY SINH VIEN
				veNutMenu(3, 30, 75, 6, "Them", 176);
				veNutMenu(3, 30, 75, 10, "Xoa", 176);
				//QUAN LY MON HOC
				veNutMenu(3, 30, 110, 6, "Them", 90);
				veNutMenu(3, 30, 110, 10, "Xoa", 176);
				veNutMenu(3, 30, 110, 14, "Sua", 176);
				//QUAN LY CAU HOI THI
				veNutMenu(3, 30, 145, 6, "Them", 176);
				veNutMenu(3, 30, 145, 10, "Xoa", 176);
				veNutMenu(3, 30, 145, 14, "Sua", 176);
				break;
			}
			else
			{
				if (state == true)
				{
					gotoxy(86+mamon.length(),18);
				}
				else gotoxy(86+tenmon.length(),21);
				HienConTro();
				batPhim(s,sCheck);
			}
		}
		
		if (s == UP && sCheck == false)
		{
			if (state == false)
			{
				gotoxy(86+mamon.length(),18);
				state = true;
			}
		}
		if (s == DOWN && sCheck == false)
		{
			if (state == true)
			{
				gotoxy(86+tenmon.length(),21);
				state = false;
			}
		}
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')  ) && sCheck == true)
		{
			HienConTro();
			if (state == false )
			{
				if (tenmon.length() < 30)
				{
					cout << InHoa(s);
					tenmon += InHoa(s);
				}
			}
			else 
			{
				if (mamon.length() < 20)
				{
					cout << InHoa(s);
					mamon += InHoa(s);
				}
			}
		}
		if(s == ' ')
		{
			if(state == false)
				{
					if(tenmon.length() == 0)
					{
						gotoxy(86+tenmon.length(),21);
					}
					else if(tenmon[tenmon.length()-1]!= ' ')
					{
						cout << InHoa(s);
						tenmon += InHoa(s);	
					}
				}
		}
		if (s == BACKSPACE)
		{
			if (state == false)
			{
				if (tenmon.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					tenmon.erase(tenmon.length()-1);
				}
			}
			else
			{
				if (mamon.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					mamon.erase(mamon.length()-1);
				}
			}
		}
	
	
		if (s == ENTER)
		{
			AnConTro();
			ChuanHoaTen(tenmon);
			if(tenmon.length() == 0 || mamon.length() == 0)
			{
				Message(75, 35, "Ban chua nhap ten mon hoac ma mon, vui long dien day du thong tin");
				AnConTro();
				Sleep(750);
				DeleteMessage(75, 35);
				gotoxy(17+mamon.length(),42);
			}
			else
			{
				if(CheckMonNhap(dsm,mamon,tenmon) == false)
				{
					Message(75, 35, "Ma mon hoac ten mon da bi trung, vui long nhap lai");
					AnConTro();
					Sleep(750);
					DeleteMessage(75, 35);
					gotoxy(17+mamon.length(),42);
				}
				else
				{
					monHoc mh ;
					mh.MAMH = mamon;
					mh.TENMH = tenmon;
					InsertMon(dsm,mh);
					AnConTro();
					Message(75, 35, "Them mon vao danh sach thanh cong");
					AnConTro();
					Sleep(750);
					DeleteMessage(75, 35);
					HienConTro();
				}
			}
			
			mamon = "";
			tenmon = "";
			gotoxy(86, 18);
			cout <<"                              ";
			gotoxy(86, 21);
			cout <<"                              ";
			gotoxy(86+mamon.length(),18);
			HienConTro();
			state = true;
		}
		batPhim(s,sCheck);	
	}
	
	AnConTro();

}
//THEM MON
void ThemMonHoc(DSMH &dsm, int page)
{
	int n = dsm.somon;
	if(n  == MAXMH)
	{
		gotoxy(130,26);
		Message(75, 35, "Khong the them mon hoc, danh sach mon hoc da day");
		AnConTro();
		Sleep(750);
		DeleteMessage(75, 35);
	}
	else
	{
		NhapMonHoc(dsm,page);
	}
}
//CHECK MON DA THI
bool CheckDaThi (string mamon,dslop dsl)
{
	for(int i = 0; i < dsl.solop; i++)
	{
		for(nodeSV *k = dsl.l[i]->danhsach.First;k != NULL ;k=k->pNext)
		{
			for(nodediemThi *p = k->info.diem.First; p != NULL; p=p->pNext)
			{
				if(p->info.MAMH.compare(mamon)== 0)
				{
					return true;// co thi roi
				}
			}
		}
	}
	return false;
}
bool CheckCH_mon(NODECH q, string mamon)
{
	NODECH p;
	p = q;
	if(p != NULL)  
	{ 
		if (p->info.MAMH.compare(mamon) == 0)
		{
			return false;
		}
		if(CheckCH_mon(p->pLeft,mamon) == false) return false;
		if(CheckCH_mon(p->pRight,mamon) == false) return false;
	}
	return true;
}
void NhapMonXoaNew(DSMH &dsm,int &page, dslop dsl,NODECH &dsch)
{
	HienConTro();
	string tb;
	int maxpage;
	gotoxy(110, 10);
	vekhungDS(34,100,2);
	gotoxy(100, 10);
	if(dsm.somon != 0)
	{
		InDSMon(dsm, page, 125, 12);
	}
	char s;
	bool sCheck;
	bool check = false;
	int state = 0;
	string mamon;
	string tenmon;
	veNutMenu(1, 25, 10, 8, "Xoa Mon", 176);// nut Subject
	gotoxy(10, 10);
	veKhung(15, 60);
	gotoxy(20, 12);
	veKhung(3, 40);	
	gotoxy(20, 15);
	veKhung(3, 40);
	veNutMenu(1, 5, 14, 13, "MA MON", 176);
	veNutMenu(1, 5, 14, 16, "TEN MON", 176);
	veNutMenu(3, 20, 30, 19, "XOA", 176);
	gotoxy(21, 13); // Dua con tro den vi tri Ma Mon
	
	batPhim(s, sCheck);
	while(s != ESC)
	{
		if(s == UP && sCheck == false)	
		{
			if (check == true)
			{
				gotoxy(21+mamon.length(),13);
				check = !check;
			}
		}
		
		if(s == DOWN && sCheck == false)
		{
			if(check == false)
			{
				gotoxy(21+tenmon.length(),16);
				check = !check;
			}
		}
			
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')) && sCheck == true)
		{
			HienConTro();
			if (check == false)
			{
				if (mamon.length() < 20)
				{
					cout << InHoa(s);
					mamon += InHoa(s);
				}
			}
			else
			{
				if (tenmon.length() < 20)
				{
					cout << InHoa(s);
					tenmon += InHoa(s);
				}
			}
		}
		
		if(s == ' ')
		{
			if(check == true)
				{
					if(tenmon.length() == 0)
					{
						gotoxy(21+tenmon.length(),16);
					}
					else if(tenmon[tenmon.length()-1]!= ' ')
					{
						cout << InHoa(s);
						tenmon += InHoa(s);	
					}
				}
		}
		
		if (s == BACKSPACE)
		{
			if (check == false)
			{
				if (mamon.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					mamon.erase(mamon.length()-1);
				}
			}
			else
			{
				if (tenmon.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					tenmon.erase(tenmon.length()-1);
				}
			}
		}
		if (s == PAGEDOWN && sCheck == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 29;i++)
				{
					gotoxy(115,14+i);
					cout << "                            ";
					gotoxy(165,14+i);
					cout << "                                      ";
				}
				page ++;
				int hd = wherex();
				int td = wherey();
				InDSMon(dsm,page,125, 12);
				gotoxy(hd,td);
			}
		}
		if(s == PAGEUP && sCheck == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 29;i++)
				{
					gotoxy(115,14+i);
					cout << "                            ";
					gotoxy(165,14+i);
					cout << "                                      ";
				}
				page--;
				int hd = wherex();
				int td = wherey();
				InDSMon(dsm,page,125,12);
				gotoxy(hd,td);
			}
		}
		if(s == ENTER)
		{
			int vitri;
			if(CheckMonNhapNew(dsm, mamon, tenmon, vitri) == false)
			{
				if(CheckDaThi(dsm.m[vitri]->MAMH, dsl) == true)
				{
					Message(10, 30, "Mon hoc da thi, khong the xoa");
				}
				else if(CheckCH_mon(dsch, dsm.m[vitri]->MAMH) == false)
				{
					Message(10, 30, "Mon hoc da co cau hoi, khong the xoa");
				}
				else 
				{
					for (int i = vitri; i < dsm.somon; i++)
					{
						dsm.m[i] = dsm.m[i+1];
					}
					dsm.somon--;
					Message(10, 30, "Xoa mon hoc thanh cong");
					Sleep(750);
					DeleteMessage(10 ,30);
				}
			}
			else
			{
				Message(10, 30, "Ma Mon hoac Ten Mon sai");
				Sleep(750);
				DeleteMessage(10, 30);
			}
			for(int i = 0; i < 28;i++)
				{
					gotoxy(115,14+i);
					cout << "                                        ";
					gotoxy(165,14+i);
					cout << "                                        ";
				}	
			page = 0;
			int hd = wherex();
			int td = wherey();
			InDSMon(dsm,page, 125, 12);
		}
		batPhim(s, sCheck);
	}
}

//XOA MON HOC
void XoaMonHoc (DSMH &dsm, dslop dsl, NODECH &dsch)
{
	string tb;
	int page = 0;
	if(dsm.somon == 0)
	{
		Message(10, 30, "Danh sach mon hien tai dang trong");
		AnConTro();
		Sleep(750);
		DeleteMessage(10, 30);
	}
	else
	{
		NhapMonXoaNew(dsm,page,dsl,dsch);
	}
}
void SuaMon(monHoc *&m)
{
	veNutMenu(1, 25, 120, 3, "Sua Mon", 176);// nut Subject
	gotoxy(120, 5); // 10 10
	veKhung(15, 60);
	gotoxy(130, 7);// 20 12
	veKhung(3, 40);	
	gotoxy(130, 10);
	veKhung(3, 40);
	veNutMenu(1, 5, 124, 8, "MA MON", 176);
	veNutMenu(1, 5, 124, 11, "TEN MON", 176);
	veNutMenu(3, 20, 140, 14, "SUA", 176);
	bool state = true;
	char s;
	bool sCheck;
	string tenmon = m->TENMH;
	string mamon = m->MAMH;
	gotoxy(132,8);
	cout << mamon;
	gotoxy(132,11);
	cout << tenmon;
	gotoxy(132+mamon.length(),8);
	HienConTro();
	batPhim(s,sCheck);
	while(1)
	{
		if(s == ESC)
		{
			if(Exit(s,sCheck,5,40) == true)
			{
				break;
			}
			else
			{
				if (state == true)
				{
					gotoxy(132+mamon.length(),8);
				}
				else gotoxy(132+tenmon.length(),11);
				HienConTro();
				batPhim(s,sCheck);
			}
		}
		if (s == UP && sCheck == false)
		{
			if (state == false)
			{
				gotoxy(132+mamon.length(),8);
				state = true;
			}
		}
		if (s == DOWN && sCheck == false)
		{
			if (state == true)
			{
				gotoxy(132+tenmon.length(),11);
				state = false;
			}
		}
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')) && sCheck == true)
		{
			HienConTro();
			if (state == true)
			{
				if (mamon.length() < 10)
				{
					cout << InHoa(s);
					mamon += InHoa(s);
				}
			}
			else
			{
				if (tenmon.length() < 30)
				{
					cout << InHoa(s);
					tenmon += InHoa(s);
				}
			}
		}
		if(s == ' ')
		{
			if(state == false)
				{
					if(tenmon.length() == 0)
					{
						gotoxy(132+tenmon.length()-1,11);
					}
					if(tenmon[tenmon.length()-1] != ' ')
					{
						cout << InHoa(s);
						tenmon += InHoa(s);	
					}
				}
		}
		if (s == BACKSPACE)
		{
			if (state == false)
			{
				if (tenmon.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					tenmon.erase(tenmon.length()-1);
				}
			}
			else
			{
				if (mamon.length()> 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					mamon.erase(mamon.length()-1);
				}
			}
		}
		if(s == ENTER)
		{
			if(mamon.length() == 0 || tenmon.length() == 0)
			{
				Message(150, 40, "Vui long nhap day du thong tin");
				Sleep(500);
				
				AnConTro();
				DeleteMessage(150, 40);
			}
			else
			{
				m->TENMH= tenmon;
				m->MAMH = mamon;
				break;
			}
			mamon = "";
			tenmon = "";
			gotoxy(132,8);
			cout << "                           ";
			gotoxy(132,11);
			cout << "                           ";
			gotoxy(132,8);
			state = true;
		}
		batPhim(s,sCheck);
	}
	AnConTro();
//	for(int i = 0; i < 5; i++)
//	{
//		gotoxy(5,40+i);
//		cout << "                                                                                                                        ";
//	}
}
// NHAP MON CHINH
void NhapMonChinh(DSMH &dsm , int &page, NODECH &dsch, dslop dsl)
{
	int maxpage;
	gotoxy(5,2);
	vekhungDS(34,100,2);
	gotoxy(26, 3);
	cout<<"MA MON";
	gotoxy(70, 3);
	cout<<"TEN MON";
	InDSMon(dsm,page, 15, 4);
	char s;
	int state = 0;
	bool sCheck;
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
					InDSMon(dsm,page, 15, 4);
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
							cout<<"                                        ";
							gotoxy(60,6+i);
							cout<<"                                        ";
						}
					}
					page++;
					InDSMon(dsm,page, 15 ,4);
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
					cout<<"                                        ";
					gotoxy(60,6+i);
					cout<<"                                        ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				int hd = wherex();
				int td = wherey();
				InDSMon(dsm,page,15,4);
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
					cout<<"                                        ";
					gotoxy(60,6+i);
					cout<<"                                        ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				int hd = wherex();
				int td = wherey();
				InDSMon(dsm,page, 15, 4);
				gotoxy(hd,td);
			}
		}
		if (s == ENTER)
		{
			if( CheckDaThi(dsm.m[state + page*10]->MAMH,dsl) == true)
			{
				Message(120, 30, "Mon hoc da co thi, khong the sua!");
				Sleep(750);
				DeleteMessage(120, 30);
				gotoxy(7,6+(state*3));
				cout << " ";
				state = 0;
				gotoxy(7,6);
				cout << muiten;
			}
			else if(CheckCH_mon(dsch,dsm.m[state+page*10]->MAMH)== false) //mon chua thi nhung co cau hoi trong dsch
			{
				Message(120, 30, "Mon hoc da co cau hoi,khong the sua!");
				Sleep(750);
				DeleteMessage(120, 30);
				gotoxy(7,6+(state*3));
				cout << " ";
				state = 0;
				gotoxy(7,6);
				cout << muiten;
			}
			else
			{
				
				SuaMon(dsm.m[state + page * 10]);
				for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout<<"                                        ";
						gotoxy(60,6+i);
						cout<<"                                        ";
					}
				page = 0;
				int hd = wherex();
				int td = wherey();
				InDSMon(dsm,page, 15, 4);
				gotoxy(hd,td);
				cout << " ";
				state = 0;
				gotoxy(7,6);
				cout << muiten;
			}
			
		}
	batPhim(s,sCheck);
	}
	for(int i = 0; i < 10; i++)
	{
		gotoxy(7,6+i*3);
		cout << " ";
	}
}
//CHINH MON
void ChinhMon(DSMH &dsm, int &page, NODECH dsch,dslop dsl )
{
	int n = dsm.somon;
	if(n  == 0)
	{
		Message(120, 30, "Danh sach mon hien tai dang trong");
		AnConTro();
		Sleep(750);
		DeleteMessage(120, 30);
	}
	else
	{
		NhapMonChinh(dsm, page,dsch,dsl);
	}
}



void QUANLYMONHOC(DSMH &dsm, dslop dsl, NODECH &dsch)
{
	int page = 0;
	char s;
	bool sCheck;
	int state = 0;
	veNutMenu(3, 30, 110, 6, "Them", 90);
	veNutMenu(3, 30, 110, 10, "Xoa", 176);
	veNutMenu(3, 30, 110, 14, "Sua", 176);
	batPhim(s, sCheck);
	while(s != ESC)
	{
		if(s == UP && sCheck == false)
		{
			switch(state)
			{
				case 0:
					{
						break;
					}
				case 1:
					{
						state--;
						veNutMenu(3, 30, 110, 6, "Them", 90);
						veNutMenu(3, 30, 110, 10, "Xoa", 176);
						break;
					}
				case 2:
					{
						state--;
						veNutMenu(3, 30, 110, 10, "Xoa", 90);
						veNutMenu(3, 30, 110, 14, "Sua", 176);
						break;
					}
			}
		}
		
		if(s == DOWN && sCheck == false)
		{
			switch(state)
			{
				case 0:
					{
						state++;
						veNutMenu(3, 30, 110, 6, "Them", 176);
						veNutMenu(3, 30, 110, 10, "Xoa", 90);
						break;
					}
				case 1:
					{
						state++;
						veNutMenu(3, 30, 110, 10, "Xoa", 176);
						veNutMenu(3, 30, 110, 14, "Sua", 90);
						break;
					}
				case 2:
					{
						break;
					}
			}
		}
		
		if(s == ENTER)
		{
			switch(state)
			{
				case 0:
					{
						system("cls");
						ThemMonHoc(dsm, page);
						break;
					}
				case 1:
					{	
						system("cls");
						XoaMonHoc(dsm, dsl, dsch);
						AnConTro();
						system("cls");
						veNutMenu(3,30,2,2,"QUAN LY LOP HOC",128);
						veNutMenu(3,30,40,2,"IN DANH SACH LOP", 128);
						veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",128);
						veNutMenu(3,30,110,2,"QUAN LY MON HOC",95);
						veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",128);
						veNutMenu(3,30,180,2,"DANH SACH DIEM",128);
						gotoxy(50,5);
//	//QUAN LY LOP HOC
						veNutMenu(3, 30, 2, 6, "Them", 176);
						veNutMenu(3, 30, 2, 10, "Xoa", 176);
						veNutMenu(3, 30, 2, 14, "Sua", 176);
	//QUAN LY SINH VIEN
						veNutMenu(3, 30, 75, 6, "Them", 176);
						veNutMenu(3, 30, 75, 10, "Xoa", 176);
	//QUAN LY MON HOC
						veNutMenu(3, 30, 110, 6, "Them", 176);
						veNutMenu(3, 30, 110, 10, "Xoa", 90);
						veNutMenu(3, 30, 110, 14, "Sua", 176);
	//QUAN LY CAU HOI THI
						veNutMenu(3, 30, 145, 6, "Them", 176);
						veNutMenu(3, 30, 145, 10, "Xoa", 176);
						veNutMenu(3, 30, 145, 14, "Sua", 176);
						break;
					}
				case 2:
					{
						system("cls");
						ChinhMon(dsm, page, dsch, dsl);
						system("cls");
						veNutMenu(3,30,2,2,"QUAN LY LOP HOC",128);
						veNutMenu(3,30,40,2,"IN DANH SACH LOP", 128);
						veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",128);
						veNutMenu(3,30,110,2,"QUAN LY MON HOC",95);
						veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",128);
						veNutMenu(3,30,180,2,"DANH SACH DIEM",128);
						gotoxy(50,5);
//	//QUAN LY LOP HOC
						veNutMenu(3, 30, 2, 6, "Them", 176);
						veNutMenu(3, 30, 2, 10, "Xoa", 176);
						veNutMenu(3, 30, 2, 14, "Sua", 176);
	//QUAN LY SINH VIEN
						veNutMenu(3, 30, 75, 6, "Them", 176);
						veNutMenu(3, 30, 75, 10, "Xoa", 176);
	//QUAN LY MON HOC
						veNutMenu(3, 30, 110, 6, "Them", 176);
						veNutMenu(3, 30, 110, 10, "Xoa", 176);
						veNutMenu(3, 30, 110, 14, "Sua", 90);
	//QUAN LY CAU HOI THI
						veNutMenu(3, 30, 145, 6, "Them", 176);
						veNutMenu(3, 30, 145, 10, "Xoa", 176);
						veNutMenu(3, 30, 145, 14, "Sua", 176);
						break;
					}
			}
		}
		batPhim(s, sCheck);
	}
}

//LUU FILE MON
void GhiFileDSMon(DSMH ds, string filename)
{
	ofstream fileOut;
	fileOut.open(filename.c_str(), ios_base::out);
	if (!fileOut.is_open()) {
		cout << "Khong mo duoc file " << filename << endl;
		return;
	}
	for (int i = 0; i < ds.somon; i++)
	{
		if(i == ds.somon -1)
		{
			fileOut << ds.m[i]->MAMH << '\n';
			fileOut << ds.m[i]->TENMH;
			break;
		}
		fileOut << ds.m[i]->MAMH << '\n';
		fileOut << ds.m[i]->TENMH << '\n';
	}
	fileOut.close();
	return;
}

#endif
