#ifndef _THI_H
#define _THI_H
#include<string>
#include"MonHoc.h"
#include"CauHoiThi.h"
#include"Time.h"
#include<thread>
//VE KHUNG DAP AN THI SINH DA CHON
void VeKhungDA(int page, int sct,CTdethi ctdt)
{
	gotoxy(15,38);
	int socau;
	if(sct <= 10)
	{
		socau = sct;
	}
	else if((page + 1)*10 <= sct)
	{
		socau = 10;
	}
	else socau = sct%10;
	int rong = socau*10;
	int x = rong/socau;
	int dem = 1;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < rong; j++)
		{
			if (i == 0)
			{
				if (j == 0) cout << traitren;
				else if (j == rong-1) cout << phaitren;
				else if (j == (rong/socau)*dem) cout << ngangxuong;
				else cout << ngang;
			}
			else if(i == 2)
			{
				if(j == 0) cout << docphai;
				else if (j == rong -1) cout << doctrai;
				else if (j == (rong/socau)*dem) cout << giua;
				else cout << ngang;
			}
			else if (i == 5)
			{
				if (j == 0) cout << traiduoi;
				else if (j == rong-1) cout << phaiduoi;
				else if (j == (rong/socau)*dem) cout << nganglen;
				else cout << ngang;
			}
			else if(j == (rong/socau)*dem)
			{
				cout << doc;
			}
			else
			{
				if (j == 0 || j == rong-1) cout << doc;
				else cout << " ";
			}
			if(j == dem*(rong/socau)) dem++;
			if(dem == socau) dem = 1;
		}
		gotoxy(wherex()-rong,wherey()+1);
	}
	int temp = page*10 + 1;
	for(int i = 0; i < socau ; i++)
	{
		gotoxy(15 + 4 + (i*10),38+1);
		cout << temp;
		temp ++;
	}
	for(int i = 0; i < socau; i++)
	{
		gotoxy(15 + 4 + (i*10),38+3);
		if(ctdt.dapan[(page*10) + i] == 1)
		{
			cout << "A";
		}
		else if (ctdt.dapan[(page*10) + i] == 2)
		{
			cout << "B";
		}
		else if(ctdt.dapan[(page*10) + i] == 3)
		{
			cout << "C";
		}
		else if(ctdt.dapan[(page*10) + i] == 4)
		{
			cout << "D";
		}
		else continue;
	}
}

// NHAP TG SCT
void NhapSCT_TG (int &tg, int &sct)
{
	system("cls");
	veNutMenu(1, 25, 75, 13, "NHAP THONG TIN THI", 176);
	gotoxy(75, 15);
	veKhung(15, 40);
	gotoxy(90, 17);
	veKhung(3, 15);	
	gotoxy(90, 20);
	veKhung(3, 15);
	veNutMenu(1, 5, 79, 18, "THOI GIAN", 176);
	veNutMenu(1, 5, 79, 21, "SO CAU", 176);
	veNutMenu(3, 15, 90, 24, "ENTER", 176);
	gotoxy(91,18);
	string ntg;
	string nsct;
	char s;
	bool sCheck;
	int state = 0;
	HienConTro();
	batPhim(s,sCheck);
	while(s != ESC)
	{
		if(s == UP && sCheck == false)
		{
			if(state == 1)
			{
				gotoxy(91+ntg.length(),18);
				state --;
			}
		}
		if(s == DOWN && sCheck == false)
		{
			if(state == 0)
			{
				gotoxy(91+nsct.length(),21);
				state ++;
			}
		}
		if((s >= '0' && s <= '9')  && sCheck == true)
		{
			if(state == 0 && ntg.length() < 3)
			{
				cout << s;
				ntg += s;	
			}
			else if(state == 1 && nsct.length() < 3)
			{
				cout << s;
				nsct +=s;
			}
		}
		if (s == BACKSPACE)
		{
			if (ntg.length() > 0 && state == 0)
			{
				AnConTro();
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(wherex()-1,wherey());
				HienConTro();
				ntg.erase(ntg.length()-1);
			}
			else if(nsct.length() > 0 && state == 1)
			{
				AnConTro();
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(wherex()-1,wherey());
				HienConTro();
				nsct.erase(nsct.length()-1);
			}	
		}
		if(s == ENTER)
		{
			if(ntg.length() == 0 || nsct.length() == 0)
			{
				Message(130, 30,"Thoi gian thi hoac so cau thi khong hop le");
				AnConTro();
				Sleep(750);
				DeleteMessage(130, 30);
			}
			else
			{
				if(StringToInt(ntg) > 0 && StringToInt(nsct) > 0)
					{
						tg = StringToInt(ntg);
						sct = StringToInt(nsct);
						return;	
					}
				else
				{
					Message(130, 30, "Thoi gian thi hoac so cau thi phai lon hon '0'");
					AnConTro();
					Sleep(750);
					DeleteMessage(130, 30);
				}
			}
			gotoxy(91,18);
			cout << "   ";
			gotoxy(91,21);
			cout << "   ";
			ntg = "";
			nsct = "";
			state = 0;
			gotoxy(91+ntg.length(),18);
			HienConTro();
		}
		batPhim(s,sCheck);
	}
//	return;
}

// Check ma mon 
bool CheckMaMon(DSMH dsm, string mamon)
{
	for( int i = 0 ; i< dsm.somon; i++)
	{
		if(mamon.compare(dsm.m[i]->MAMH) == 0)
		{
			return true;
		}
	}
	return false;
}
//NHAP MON THI NEW 
void NhapMonThiNew(DSMH dsm, int &tg, int & sct, string &monthi, bool &check)
{
	veNutMenu(1, 25, 75, 13, "NHAP MON THI", 176);// nut Subject
	gotoxy(75, 15);
	veKhung(13, 60);
	gotoxy(85, 17);
	veKhung(3, 40);	
	veNutMenu(1, 5, 79, 18, "MA MON", 176);
	veNutMenu(3, 20, 93, 21, "THI", 176);
	char s;
	bool sCheck;
	gotoxy(86,18);
	HienConTro();
	batPhim(s, sCheck);
	while ( s != ESC)
	{
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')  ) && sCheck == true)
		{
			HienConTro();
			if (monthi.length() < 30)
			{
				cout << InHoa(s);
				monthi += InHoa(s);
			}
		}
		
		if (s == BACKSPACE)
		{
			if(monthi.length() > 0)
			{
				AnConTro();
				gotoxy(wherex()-1, wherey());
				cout <<" ";
				gotoxy(wherex()-1, wherey());
				HienConTro();
				monthi.erase(monthi.length()-1);
			}
		}
		
		if(s == ENTER)
		{
			if(CheckMaMon(dsm, monthi) == false)
			{
				Message(5, 40, "Ma mon sai, vui long nhap lai");
				Sleep(1000);
				AnConTro();
				DeleteMessage(5, 40);
				HienConTro();
				gotoxy(86+monthi.length(), 18);
			}
			else
			{
				NhapSCT_TG(tg, sct);
				if(tg > 0 && sct > 0)
				{
					check = true;
					return;
				}
			}
		}
		batPhim(s, sCheck);
		check = false;
	}
}

// XOA KHUNG DAP AN THI SINH DA CHON
void XoaDA()
{
	for(int i = 0; i < 6; i++)
	{
		gotoxy(14,38+i);
		cout <<"                                                                                                     "; 
	}
}
// CAP NHAP BANG DAP AN THI SINH DA CHON 
void InDA(int page, int sct, CTdethi ctdt)
{
	int socau;
	if(sct <= 10)
	{
		socau = sct;
	}
	else if((page + 1)*10 <= sct)
	{
		socau = 10;
	}
	else socau = sct%10;
	for(int i = 0; i < socau; i++)
	{
		gotoxy(15 + 4 + (i*10),38+3);
		if(ctdt.dapan[(page*10) + i] == 1)
		{
			cout << "A";
		}
		else if (ctdt.dapan[(page*10) + i] == 2)
		{
			cout << "B";
		}
		else if(ctdt.dapan[(page*10) + i] == 3)
		{
			cout << "C";
		}
		else if(ctdt.dapan[(page*10) + i] == 4)
		{
			cout << "D";
		}
		else continue;
	}
}
void In1CauThi (NODECH dsch, int id)
{
	for(int i = 0; i < 3;i++)
	{
		gotoxy(50,8+i);
		cout << "                                                                                                  ";
	}
	gotoxy(50,15);
	cout << "                                                                                                  ";
	gotoxy(50,21);
	cout << "                                                                                                  ";
	gotoxy(50,27);
	cout << "                                                                                                  ";
	gotoxy(50,33);
	cout << "                                                                                                  ";
	NODECH ch = Search_CH(dsch,id);
	
	InNDCH(ch->info.NOIDUNG, 50, 8);
	gotoxy(50,15); // 20 14 => 50 15
	InDA_XemCH(ch->info.A);
	gotoxy(50,21);
	InDA_XemCH(ch->info.B);
	gotoxy(50,27);
	InDA_XemCH(ch->info.C);
	gotoxy(50,33);
	InDA_XemCH(ch->info.D);
}
// LAY DE THI THEO MA MON HOC
int *LayDeThi(NODECH dsch, int sct, string mamon)
{
	int temp[10000];
	int *dethi = new int [sct];
	int dem = 0;
	int i=0;
	NODECH Stack[STACKSIZE];
	NODECH p = dsch;
	int sp = -1;
	do
	{ 
		while (p != NULL)
		{
			Stack[++sp]= p;
			p = p->pLeft;
		}
		if (sp != -1)
		{
			p = Stack[sp--];
			if(p->info.MAMH.compare(mamon) == 0)
			{	
				temp[dem] = p->id;
				dem++;
			}
			i++;
			p = p->pRight;
		}
		else break;
	} while (1);
	if(dem < sct)
	{
		Message(5, 40,"Khong du cau hoi de thi");
		AnConTro();
		Sleep(750);
		DeleteMessage(5, 40);
		return NULL;
	}
	else
	{
		for(int j = 0; j < sct; j++)
		{
			int r = random(0,dem-j-1);
			dethi[j] = temp[r];
			//doi vi tri
			swap(temp[r],temp[dem-1-j]); 
		}
	}
	return dethi;
}
//TINH DIEM 
int TinhDiem(CTdethi ctdt, NODECH dsch)
{
	int socaudung = 0;
	string dapan="";
	for(int i = 0; i < ctdt.sct ; i++)
	{
		NODECH p = Search_CH(dsch,ctdt.bode[i]);
		if(ctdt.dapan[i] == 1)
		{
			dapan = "A";
		}
		else if(ctdt.dapan[i] == 2)
		{
			dapan = "B";
		}
		else if(ctdt.dapan[i] == 3)
		{
			dapan = "C";
		}
		else if(ctdt.dapan[i] == 4)
		{
			dapan = "D";
		}
		if(p->info.DAPAN.compare(dapan) == 0)
		{
			socaudung++;
		}
		dapan="";
	}
	return socaudung;
}
void ketThucBaiThi (CTdethi ctdt, NODECH dsch)
{
	system("cls");

	int scd = (TinhDiem(ctdt, dsch)*10);
	int sct = ctdt.sct;
	gotoxy(45, 30);
	veKhung2vien(3, 40);
	gotoxy(50,30);
	ChangeColor(240);
	veNutMenu(1, 20, 50, 31, "DIEM THI LA:", 66);
	gotoxy(75, 31);
	cout << (scd/sct);
	ChangeColor(15);
	getch();
}
//FUNCTION THI
void THI(NODECH dsch,int tg, int sct, string monthi,string &diem, CTdethi &ctdt)
{
	if(sct == 0 && tg == 0)
	{
		return ;
	}
	ctdt.sct = sct;
	ctdt.tg = tg;
	for(int i = 0; i < sct; i++)
	{
		ctdt.dapan[i] = 0;
	}
	ctdt.bode = LayDeThi(dsch,sct,monthi);
	if(ctdt.bode == NULL)
	{
		return;
	}
	thread clock;
	clock = thread(printClock,tg);
	gotoxy(50,1);
	cout << "BAI THI MON: " << monthi;
	if(ctdt.bode == NULL)
	{
		return ;
	}
	int cauthi = 0;
	int page = 0;
	int maxpage;
	if(sct <= 10)
	{
		maxpage = 0;
	}
	else if(sct > 10 && sct % 10 == 0)
	{
		maxpage = (sct/10) - 1;
	}
	else maxpage = sct/10;
	
	
	// chieu ngang 210 doc 53     
	// khung cau hoi se la 120  can giua 2 ben la 45
	system("cls");
	veNutMenu(1, 40, 45, 5, "NOI DUNG CAU HOI", 160);
	gotoxy(45, 7);
	veKhung2vien(5, 120); // khung noi dung cau hoi
	
	veNutMenu(1, 40, 45, 13, "A", 64);
	gotoxy(45, 14);
	veKhung2vien(3, 120);
	
	veNutMenu(1, 40, 45, 19, "B", 128);
	gotoxy(45, 20);
	veKhung2vien(3, 120);
	
	veNutMenu(1, 40, 45, 25, "C", 128);
	gotoxy(45, 26);
	veKhung2vien(3, 120);
	
	veNutMenu(1, 40, 45, 31, "D", 128);
	gotoxy(45, 32);
	veKhung2vien(3, 120);
	
	
	
	NODECH ch = Search_CH(dsch,ctdt.bode[cauthi]);
	gotoxy(50, 10);
	InNDCH(ch->info.NOIDUNG, 50, 8);
	gotoxy(50,15); // 20 14 => 50 15
	InDA_XemCH(ch->info.A);
	gotoxy(50,21);
	InDA_XemCH(ch->info.B);
	gotoxy(50,27);
	InDA_XemCH(ch->info.C);
	gotoxy(50,33);
	InDA_XemCH(ch->info.D);
	VeKhungDA(page,sct,ctdt);
	gotoxy(35,7);
	cout << "CAU " << cauthi + 1;
	
	gotoxy(19 + (cauthi%10)*10,44);
	cout << muitenlen;
	
	AnConTro();
	int state1 = 0;
	char s;
	bool sCheck;
	bool qt = false;
	batPhim(s,sCheck);
	string da = "A";
	gotoxy(19,44);
	cout << muitenlen;
	gotoxy(4,14);
	while ((cauthi < sct ) && s != ESC )
	{
		
		if(s == PAGEUP)
		{
			if(page > 0 )
			{
				gotoxy(19 + (cauthi%10)*10,44);
				cout << " ";
				cauthi -= 10;
				gotoxy(19 + (cauthi%10)*10,44);
				cout << muitenlen;
				page --;
				XoaDA();
				VeKhungDA(page,sct,ctdt);
				In1CauThi(dsch,ctdt.bode[cauthi]);
				for(int i = 0; i < 33; i += 6)
					{
						gotoxy(4,14+i);
						cout << " ";
					}
				switch(ctdt.dapan[cauthi])
				{
					case 1:
						{
							state1 = 0;
							break;
						}
					case 2:
						{
							state1 = 1;
							break;
						}
					case 3:
						{
							state1 = 2;
							break;
						}
					case 4:
						{
							state1 = 3;
							break;
						}			
				}
				if(state1 == 0)
				{
					veNutMenu(1, 40, 45, 13, "A", 64);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 128);	
				}
				else if(state1 == 1)
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 64);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 128);
				}
				else if(state1 == 2)
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 64);
					veNutMenu(1, 40, 45, 31, "D", 128);
				}
				else
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 64);
				}
			}
		}
		if(s == PAGEDOWN)
		{
			if(page < maxpage )
			{
				gotoxy(19 + (cauthi%10)*10,44);
				cout << " ";
				if(cauthi < sct - 10)
				{
					cauthi += 10;
					gotoxy(19 + (cauthi%10)*10,44);
					cout << muitenlen;
				}
				else cauthi += sct - cauthi - 1;
				gotoxy(19 + (cauthi%10)*10,44);
				cout << muitenlen;
				page ++;
				XoaDA();
				VeKhungDA(page,sct,ctdt);
				In1CauThi(dsch,ctdt.bode[cauthi]);
				for(int i = 0; i < 33; i += 6)
					{
						gotoxy(4,14+i);
						cout << " ";
					}
				switch(ctdt.dapan[cauthi])
				{
					case 1:
						{
							state1 = 0;
							break;
						}
					case 2:
						{
							state1 = 1;
							break;
						}
					case 3:
						{
							state1 = 2;
							break;
						}
					case 4:
						{
							state1 = 3;
							break;
						}			
				}
				if(state1 == 0)
				{
					veNutMenu(1, 40, 45, 13, "A", 64);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 128);	
				}
				else if(state1 == 1)
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 64);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 128);	
				}
				else if(state1 == 2)
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 64);
					veNutMenu(1, 40, 45, 31, "D", 128);	
				}
				else
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 64);	
				}
			}
		}
		if (s == LEFT && sCheck == false)
		{
			if(page > 0 && (cauthi + 1) % 10 == 1)
			{
				page--;
				qt = true;
			}
			if (qt == true)
			{
				XoaDA();
				VeKhungDA(page,sct,ctdt);
				qt = false;
			}
			else InDA(page,sct,ctdt);
			if (cauthi > 0)
			{
				gotoxy(19 + (cauthi%10)*10,44);
				cout << " ";
				cauthi--;
				gotoxy(19 + (cauthi%10)*10,44);
				cout << muitenlen;
				gotoxy(35,7);
				cout << "CAU " << cauthi + 1;
				In1CauThi(dsch,ctdt.bode[cauthi]);
				for(int i = 0; i < 33; i += 6)
					{
						gotoxy(4,14+i);
						cout << " ";
					}
				switch(ctdt.dapan[cauthi])
				{
					case 1:
						{
							state1 = 0;
							break;
						}
					case 2:
						{
							state1 = 1;
							break;
						}
					case 3:
						{
							state1 = 2;
							break;
						}
					case 4:
						{
							state1 = 3;
							break;
						}			
				}
				if(state1 == 0)
				{
					veNutMenu(1, 40, 45, 13, "A", 64);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 128);		
				}
				else if(state1 == 1)
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 64);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 128);	;
				}
				else if(state1 == 2)
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 64);
					veNutMenu(1, 40, 45, 31, "D", 128);	
				}
				else
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 64);	
				}
			}
		}
		if (s == RIGHT && sCheck == false)
		{
			if(page < maxpage && (cauthi + 1) % 10 == 0)
			{
				page++;
				qt = true;
			}
			if (qt == true)
			{
				XoaDA();
				VeKhungDA(page,sct,ctdt);
				qt = false;
			}
			else InDA(page,sct,ctdt);
			if (cauthi < sct - 1)
			{
				gotoxy(19 + (cauthi%10)*10,44);
				cout << " ";
				cauthi++;
				gotoxy(19 + (cauthi%10)*10,44);
				cout << muitenlen;
				gotoxy(10,1);
				cout << "            ";
				gotoxy(35,7);
				cout << "CAU " << cauthi + 1;
				In1CauThi(dsch,ctdt.bode[cauthi]);
				for(int i = 0; i < 33; i += 6)
					{
						gotoxy(4,14+i);
						cout << " ";
					}
				switch(ctdt.dapan[cauthi])
				{
					case 1:
						{
							state1 = 0;
							break;
						}
					case 2:
						{
							state1 = 1;
							break;
						}
					case 3:
						{
							state1 = 2;
							break;
						}
					case 4:
						{
							state1 = 3;
							break;
						}			
				}
				if(state1 == 0)
				{
					veNutMenu(1, 40, 45, 13, "A", 64);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 128);	
				}
				else if(state1 == 1)
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 64);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 128);	
				}
				else if(state1 == 2)
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 64);
					veNutMenu(1, 40, 45, 31, "D", 128);	
				}
				else
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 64);	
				}
			}
		}
		if(s == UP && sCheck == false)
		{
			switch(state1)
			{
				case 1:
					{
						AnConTro();
						veNutMenu(1, 40, 45, 13, "A", 64);
						veNutMenu(1, 40, 45, 19, "B", 128);
						veNutMenu(1, 40, 45, 25, "C", 128);
						veNutMenu(1, 40, 45, 31, "D", 128);
						state1--;
						da = "A";
						break;
					}
				case 2:
					{
						AnConTro();
						veNutMenu(1, 40, 45, 13, "A", 128);
						veNutMenu(1, 40, 45, 19, "B", 64);
						veNutMenu(1, 40, 45, 25, "C", 128);
						veNutMenu(1, 40, 45, 31, "D", 128);
						state1--;
						da = "B";
						break;
					}
				case 3:
					{
						AnConTro();
						veNutMenu(1, 40, 45, 13, "A", 128);
						veNutMenu(1, 40, 45, 19, "B", 128);
						veNutMenu(1, 40, 45, 25, "C", 64);
						veNutMenu(1, 40, 45, 31, "D", 128);
						state1--;
						da = "C";
						break;
					}
			}	
		}
		if(s == DOWN && sCheck == false)
		{
			switch(state1)
			{
				case 0:
					{
						AnConTro();
						veNutMenu(1, 40, 45, 13, "A", 128);
						veNutMenu(1, 40, 45, 19, "B", 64);
						veNutMenu(1, 40, 45, 25, "C", 128);
						veNutMenu(1, 40, 45, 31, "D", 128);
						state1++;
						da = "B";
						break;
					}
				case 1:
					{
						AnConTro();
						veNutMenu(1, 40, 45, 13, "A", 128);
						veNutMenu(1, 40, 45, 19, "B", 128);
						veNutMenu(1, 40, 45, 25, "C", 64);
						veNutMenu(1, 40, 45, 31, "D", 128);	
						state1++;
						da = "C";
						break;
					}
				case 2:
					{
						AnConTro();
						veNutMenu(1, 40, 45, 13, "A", 128);
						veNutMenu(1, 40, 45, 19, "B", 128);
						veNutMenu(1, 40, 45, 25, "C", 128);
						veNutMenu(1, 40, 45, 31, "D", 64);
						state1++;
						da = "D";
						break;
					}
			}
		}
		if(s == ENTER)
		{
			if(da == "A")
			{
				ctdt.dapan[cauthi] = 1;
			}
			else if(da == "B")
			{
				ctdt.dapan[cauthi] = 2;
			}
			else if(da == "C")
			{
				ctdt.dapan[cauthi] = 3;
			}
			else if (da == "D")
			{
				ctdt.dapan[cauthi] = 4;
			}
			
			
			if (cauthi < sct -1)
			{
				if(page < maxpage && (cauthi + 1) % 10 == 0)
				{
					page++;
					qt = true;
				}
				if (qt == true)
				{
					XoaDA();
					VeKhungDA(page,sct,ctdt);
					qt = false;
				}
				else InDA(page,sct,ctdt);
				gotoxy(19 + (cauthi%10)*10,44);
				cout << " ";
				cauthi++;
				gotoxy(19 + (cauthi%10)*10,44);
				cout << muitenlen;
				gotoxy(10,1);
				cout << "    ";
				gotoxy(35,7);
				cout << "CAU " << cauthi + 1;
				In1CauThi(dsch,ctdt.bode[cauthi]);
				state1 = 0;
				da = "A";
				for(int i = 0; i < 33; i += 6)
					{
						gotoxy(4,14+i);
						cout << " ";
					}	
				veNutMenu(1, 40, 45, 13, "A", 64);
				veNutMenu(1, 40, 45, 19, "B", 128);
				veNutMenu(1, 40, 45, 25, "C", 128);
				veNutMenu(1, 40, 45, 31, "D", 128);
			}
			else if(cauthi == sct -1)
			{
				InDA(page,sct,ctdt);
				gotoxy(19 + (cauthi%10)*10,44);
				cout << " ";
				gotoxy(19 + (cauthi%10)*10,44);
				cout << muitenlen;
				gotoxy(10,1);
				switch(ctdt.dapan[cauthi])
				{
					case 1:
						{
							state1 = 0;
							break;
						}
					case 2:
						{
							state1 = 1;
							break;
						}
					case 3:
						{
							state1 = 2;
							break;
						}
					case 4:
						{
							state1 = 3;
							break;
						}			
				}
				if(state1 == 0)
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 128);		
				}
				else if(state1 == 1)
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 128);	
				}
				else if(state1 == 2)
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 128);	
				}
				else
				{
					veNutMenu(1, 40, 45, 13, "A", 128);
					veNutMenu(1, 40, 45, 19, "B", 128);
					veNutMenu(1, 40, 45, 25, "C", 128);
					veNutMenu(1, 40, 45, 31, "D", 128);	;
				}
			}
		}
		if ((s == F1  && sCheck == false) || s == ESC)
		{
			Message(130, 40,"Ban chac chan muon nop bai ? (Y/N)");
			batPhim(s,sCheck);
			while(s != ESC)
			{
				if((s == 'y' || s == 'Y')&& sCheck == true)
				{
				 	stop = 0;
					clock.join();//					
					ketThucBaiThi(ctdt,dsch);
					return;
				}
				else if((s == 'n' || s == 'N') && sCheck == true)
				{
					DeleteMessage(130, 40);
					break;
				}
				batPhim(s,sCheck);
			}
			Message(130, 40,"Ban chac chan muon nop bai ? (Y/N)");
		}
		if(s == ESC)
		{
			int socaudung = TinhDiem(ctdt,dsch);// kieu int
			cout << socaudung;
			
			int s = (socaudung/sct);
			diem = IntToString(s);
			cout << " " << diem;
			veNutMenu(10, 10, 50, 50, "BAM NUT THOAT", 33);
			return ;
		}
		if(stop == 0)
		{
			clock.join();
			Message(130, 30, "Het thoi gian lam bai, bam phim bat ky de ket thuc!");
			ketThucBaiThi(ctdt,dsch);
			return;
		}
		batPhim(s,sCheck);
	}
	stop = 0;
	clock.join();
}

#endif
