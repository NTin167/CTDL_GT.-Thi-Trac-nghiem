#ifndef _SINHVIEN_H
#define _SINHVIEN_H
#include"Lop.h"
#include"struct.h"



// KIEM TRA NHAP DU HO TEN 
bool CheckFormTen (string text)
{
	for(int i = 0; i < text.length();i++)
	{
		if(text[i] == ' ')
		{
			return true;
		}
	}
	return false;
}
//  XOA SINH VIEN DAU 
void DeleteFirst_SV(dssv &ds)
{
	nodeSV *s;
	if(ds.First== NULL)
	{
		return;
	}
	s = ds.First;
	ds.First = s->pNext;
	delete s;
		
	
}
//XOA SINH VIEN SAU
void DeleteAfter_SV(nodeSV *s)
{
	nodeSV *svS;
	if (s == NULL || s->pNext == NULL)
	{
		return;
	}
	svS = s->pNext;
	s->pNext = svS->pNext;
	delete svS;
	
}

//XOA SINH THEO INFO
void DeleteInfo_SV(dssv &ds , string maSV)
{
	nodeSV *s;
	nodeSV *svS;
	s = search_SV(ds,maSV);
	if ( s == NULL)
	{
		return;
	}
	if (s == ds.First)
	{
		DeleteFirst_SV(ds);
	}
	else 
	{
		svS = ds.First;
		while(svS->pNext != s)
		{
			svS = svS->pNext;
		}
		DeleteAfter_SV(svS);
	}
}



//NHAP SINH VIEN
void NhapSinhVien(lop *&l )
{
	AnConTro();
	int maxpage;
	gotoxy(15,3);
	cout << "MA SV";
	gotoxy(50,3);
	cout << "HO VA TEN";
	gotoxy(88,3);
	cout << "GIOI TINH";
	gotoxy(110,2);
	veKhung(20,44);
	veNutMenu(1, 40,110 , 0, "NHAP THONG TIN SINH VIEN", 96);	
	veNutMenu(1, 10, 112, 5, "MSSV", 176);
	veNutMenu(1, 10, 112, 9, "HO TEN", 176);
	veNutMenu(1, 10, 112, 13, "GIOI TINH", 176);
	veNutMenu(1, 10, 112, 17, "MAT KHAU", 176);
	
	gotoxy(122,2+2);
	veKhung(3,30);
	
	
	gotoxy(122,2+6);
	veKhung(3,30);
	
	veNutMenu(1,14,123,13,"NAM",192);
	veNutMenu(1,14,137,13,"NU",128);
	
	gotoxy(122,2+14);
	veKhung(3,30);
	int hd , td;
	int page = 0;
	string mk;
	string masv;
	string hoten;
	string gt = "NAM";
	char s;
	int state = 0;
	bool sCheck;
	gotoxy(124,2+3);
	HienConTro();
	batPhim(s,sCheck);
	while (1)
	{
		if(s == ESC)
		{
			if(Exit(s,sCheck,60,40) == true)
			{
				break;
			}
			else
			{
				switch(state)
				{
					case 0:
						{
							gotoxy(124+masv.length(),3+2);
							break;
						}
					case 1:	
						{
							gotoxy(124+hoten.length(),3+6);
							break;
						}
					case 2:
						{
							gotoxy(124+mk.length(),3+14);
							break;
						}	
				}
				HienConTro();
				batPhim(s,sCheck);
				
			}
		}
		if(DemSV(l->danhsach) < 10)
		{
			maxpage = 0;
		}
		else if(DemSV(l->danhsach) % 10 == 0)
		{
			maxpage = DemSV(l->danhsach)/10 - 1;
		}
		else maxpage = DemSV(l->danhsach)/10;
		HienConTro();
		if(s == LEFT )
		{
			hd = wherex();
			td = wherey();
			veNutMenu(1,14,123,13,"NAM",192);
			veNutMenu(1,14,137,13,"NU",128);
			gotoxy(hd,td);
			gt = "NAM";
			
		}
		if(s == RIGHT )
		{
			hd = wherex();
			td = wherey();
			veNutMenu(1,14,123,13,"NAM",128);
			veNutMenu(1,14,137,13,"NU",192);
			gotoxy(hd,td);
			gt = "NU";
		}
		if (s == UP && sCheck == false)
		{
			HienConTro();
			switch(state)
			{
				case 1:
					{
						gotoxy(124+masv.length(),3+2);
						state --;
						break;
					}
				case 2:	
					{
						gotoxy(124+hoten.length(),3+6);
						state --;
						break;
					}
			}
		}
		if (s == DOWN && sCheck == false)
		{
			HienConTro();
			switch(state)
			{
				case 0:
					{
						gotoxy(124+hoten.length(),3+6);
						state ++;
						break;
					}
				case 1:	
					{
						gotoxy(124+mk.length(),3+14);
						state ++;
						break;
					}
			}
		}
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9'))  && sCheck == true)
		{
			HienConTro();
			switch(state)
			{
				case 0:
					{
						if(masv.length() < 11)
						{
							cout << InHoa(s);
							masv += InHoa(s);
						}
						break;
					}
				case 1:	
					{
						if(hoten.length() < 26)
						{
							cout << InHoa(s);
							hoten += InHoa(s);
						}
						break;
					}
				case 2:
					{
						if(mk.length() < 26)
						{
							cout << s;
							mk += s;	
						}
						break;
					}	
			}
		}
		if(s == ' ')
		{
			if(state == 1)
				{
					if(hoten.length() == 0)
					{
						gotoxy(124+hoten.length()-1,3+6);
					}
					if(hoten[hoten.length()-1]!= ' ')
					{
						cout << InHoa(s);
						hoten += InHoa(s);	
					}
				}
		}
		if (s == BACKSPACE)
		{
			switch(state)
			{
				case 0:
					{
						if (masv.length() > 0)
						{
							AnConTro();
							gotoxy(wherex()-1,wherey());
							cout << " ";
							gotoxy(wherex()-1,wherey());
							HienConTro();
							masv.erase(masv.length()-1);
						}
						break;
					}
				case 1:
					{
						if (hoten.length() > 0)
						{
							AnConTro();
							gotoxy(wherex()-1,wherey());
							cout << " ";
							gotoxy(wherex()-1,wherey());
							HienConTro();
							hoten.erase(hoten.length()-1);
						}
						break;
					}
				case 2:
					{
						if (mk.length() > 0)
						{
							AnConTro();
							gotoxy(wherex()-1,wherey());
							cout << " ";
							gotoxy(wherex()-1,wherey());
							HienConTro();
							mk.erase(mk.length()-1);
						}
						break;
					}	
			}	
		}
		if (s == PAGEDOWN && sCheck == false)
		{
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                      ";
					gotoxy(31,6+i);
					cout << "                                             ";
					gotoxy(81,6+i);
					cout << "                      ";
				}
				page ++;
				InDSSV(l,page);
				gotoxy(124+masv.length(),3+2);
				HienConTro();
			}
		}
		if(s == PAGEUP && sCheck == false)
		{
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                      ";
					gotoxy(31,6+i);
					cout << "                                             ";
					gotoxy(81,6+i);
					cout << "                      ";
				}
				page--;
				InDSSV(l,page);
				gotoxy(124+masv.length(),3+2);
				HienConTro();
			}
		}
		if (s == ENTER)
		{
			for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                      ";
					gotoxy(31,6+i);
					cout << "                                             ";
					gotoxy(81,6+i);
					cout << "                      ";
				}
			bool ktten = false;
			ChuanHoaTen(hoten);
			sinhVien sv;
			sv.MASV = masv;
			sv.HO = TachHoSV(hoten);
			gotoxy(1,1);
			sv.TEN = TachTenSV(hoten);
			sv.password = mk;
			sv.PHAI = gt;
			for(int i = 0; i < hoten.length(); i ++)				// can it nhat 1 dau cach de phan biet ho va ten
			{
				if (hoten[i] == ' ')
				{
					ktten = true;
					break;
				}
			}	
			if (masv.length() == 0 || hoten.length() == 0 || mk.length() == 0)
			{
				Message(132, 30 ,"Vui long dien day du thong tin sinh vien");
				AnConTro();
				Sleep(750);
				DeleteMessage(132, 30);
			}
			else
			{
				if(CheckFormMaSv(masv) == true)
				{
						if(CheckMaSV(l,masv) == false)
						{
							Message(132, 30, "Ma sinh vien da co trong danh sach");
							AnConTro();
							Sleep(750);
							DeleteMessage(132,30);
						}
						else
						{
							if(ktten == true)
							{
								Them1SinhVien(l,sv);
								Message(132, 30, "Them sinh vien vao danh sach thanh cong");
								AnConTro();
								Sleep(750);
								DeleteMessage(132, 30);
							}
							else
							{
								Message(132, 30,  "Ho ten khong dung dinh dang, vui long nhap lai");
								AnConTro();
								Sleep(750);
								DeleteMessage(132, 30);
							}
						} 
				}
				else
				{
					Message(132, 30, "Ma sinh vien khong dung dinh dang, vui long nhap lai");
					AnConTro();
					Sleep(750);
					DeleteMessage(132, 30);
				}
			}			
			InDSSV(l,page);
			masv = "";
			hoten = "";
			mk = "";
			gotoxy(124+masv.length(),3+2);
			cout << "                           ";
			gotoxy(124+masv.length(),7+2);
			cout << "                           ";
			gotoxy(124+masv.length(),15+2);
			cout << "                           ";
			gotoxy(124+masv.length(),3+2);
			HienConTro();
			state = 0;
		}
	batPhim(s,sCheck);
	}
	for (int i=2; i<23; i++)
	{
		gotoxy(110,i);
		cout << "                                             ";
	}
	AnConTro();
}


//NHAP SINH VIEN
void NhapSinhVienIn(lop *&l )
{
	AnConTro();
	int maxpage;
	gotoxy(15,3);
	cout << "MA SV";
	gotoxy(50,3);
	cout << "HO VA TEN";
	gotoxy(88,3);
	cout << "GIOI TINH";
	

	
	int hd , td;
	int page = 0;
	char s;
	int state = 0;
	bool sCheck;
	batPhim(s,sCheck);
	while (1)
	{
		if(s == ESC)
		{
			if(Exit(s,sCheck,60,40) == true)
			{
				break;
			}
		}
		if(DemSV(l->danhsach) < 10)
		{
			maxpage = 0;
		}
		else if(DemSV(l->danhsach) % 10 == 0)
		{
			maxpage = DemSV(l->danhsach)/10 - 1;
		}
		else maxpage = DemSV(l->danhsach)/10;
		
		if (s == PAGEDOWN && sCheck == false)
		{
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                      ";
					gotoxy(31,6+i);
					cout << "                                             ";
					gotoxy(81,6+i);
					cout << "                      ";
				}
				page ++;
				InDSSV(l,page);
			}
		}
		if(s == PAGEUP && sCheck == false)
		{
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                      ";
					gotoxy(31,6+i);
					cout << "                                             ";
					gotoxy(81,6+i);
					cout << "                      ";
				}
				page--;
				InDSSV(l,page);
			}
		}
	batPhim(s,sCheck);
	}
	for (int i=2; i<23; i++)
	{
		gotoxy(110,i);
		cout << "                                             ";
	}
	AnConTro();
}


// XOA SINH VIEN 
void XoaSinhVien(lop *&l ,int page)
{
	for (int i=2; i<23; i++)
	{
		gotoxy(110,i);
		cout << "                                             ";
	}
	AnConTro();
	gotoxy(15,3);
	cout << "MA SV";
	gotoxy(50,3);
	cout << "HO VA TEN";
	gotoxy(88,3);
	cout << "GIOI TINH";
	gotoxy(110,2);
	gotoxy(7,6);
	cout << muiten;
	int maxpage;
	int state = 0;
	char s;
	bool sCheck;
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
						gotoxy(81,6+i);
						cout << "                      ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSSV(l,page);
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
							gotoxy(81,6+i);
							cout << "                      ";
						}
					}
					page++;
					InDSSV(l,page);
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
						gotoxy(81,6+i);
						cout << "                      ";
					}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				int hd = wherex();
				int td = wherey();
				InDSSV(l,page);
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
						gotoxy(81,6+i);
						cout << "                      ";
					}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				int hd = wherex();
				int td = wherey();
				InDSSV(l,page);
				gotoxy(hd,td);
			}
		}
		if (s == ENTER)
		{
			Message(130, 30, "Ban co chac chan muon sinh vien nay ? (Y/N)");
			nodeSV *k = l->danhsach.First;
			for (int i = 0; i < state + page*10; i++)// 
			{
				if (k->pNext != NULL)
				{
					k = k->pNext;
				}
			}
			batPhim(s,sCheck);
			while(s != ESC)
			{
				AnConTro();
				if((s == 'y' || s == 'Y')&& sCheck == true)
				{
					DeleteInfo_SV(l->danhsach, k->info.MASV);
					Message(130, 30,"Xoa sinh vien thanh cong");
					AnConTro();
					Sleep(750);
					DeleteMessage(130, 30);
					break;
					
				}
				else if((s == 'n' || s == 'N') && sCheck == true)
				{
					DeleteMessage(130,30);
					break;
				}
				batPhim(s,sCheck);
			}
			for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                      ";
						gotoxy(31,6+i);
						cout << "                                             ";
						gotoxy(81,6+i);
						cout << "                      ";
					}	
			page = 0;
			int hd = wherex();
			int td = wherey();
			if (l->danhsach.First != NULL)
			{
				InDSSV(l,page);
				gotoxy(hd,td);
				cout << " ";
				state = 0;
				gotoxy(7,6);
				cout << muiten;	
			}
			else 
			{
				break;
			}
				
		}
	batPhim(s,sCheck);
	}
	
}
void INSINHVIEN(dslop &dsl , int page)
{
	
	string malop;
	int hd;
	int td;
	gotoxy(5,37);
	veKhung2vien(8, 40);
	veNutMenu(1, 10, 8, 40, "MA LOP", 176);
	gotoxy(5+17,39);
	veKhung(3,20);
	
	veNutMenu(1, 30, 5, 0, "DANH SACH LOP ", 96);
	veNutMenu(1, 30, 5, 36, "IN DANH SACH LOP", 96);
	gotoxy(5,2);
	vekhungDS(34,100,2);
	gotoxy(26, 3);
	cout<<"MA LOP";
	gotoxy(70, 3);
	cout<<"TEN LOP";
	InDSLop(dsl,page,6,4);
	
	
	gotoxy(5+18,40);
	
	HienConTro();
	char s;
	bool sCheck;
	batPhim(s,sCheck);
	while(s != ESC)
	{
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')) && sCheck == true)
		{
			HienConTro();
			if (malop.length() < 10)
			{
				cout << InHoa(s);
				malop += InHoa(s);
			}
		}
		if (s == BACKSPACE)
		{
			if (malop.length() > 0)
			{
				AnConTro();
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(wherex()-1,wherey());
				HienConTro();
				malop.erase(malop.length()-1);
			}	
		}
		if(s == ENTER)
		{
			if(CheckFormMaLop(malop) == true)
			{
				if(CheckMaLop(dsl,malop) == true)
				{
					Message(132, 30,"Ma lop khong ton tai");
					AnConTro();
					Sleep(750);
					DeleteMessage(132, 30);
				}
				else
				{
					for(int i = 0; i < dsl.solop; i++)
					{
						if(dsl.l[i]->MALOP.compare(malop) == 0)
						{
							hd = wherex();
							td = wherey();
							system("cls");
							veNutMenu(1, 40, 5, 0, "DANH SACH SINH VIEN", 96);
							gotoxy(5,2);
							VeKhungDSLop(34,100,4);
							gotoxy(15,3);
							cout << "MA SV";
							gotoxy(50,3);
							cout << "HO VA TEN";
							gotoxy(88,3);
							cout << "GIOI TINH";
							InDSSV(dsl.l[i],0);
							NhapSinhVienIn(dsl.l[i]);
							
							gotoxy(hd,td);
						}
					}
					system("cls");
					
					gotoxy(5,37);
					veKhung2vien(8, 40);
					veNutMenu(1, 10, 8, 40, "MA LOP", 176);
					gotoxy(5+17,39);
					veKhung(3,20);
					
					veNutMenu(1, 30, 5, 0, "DANH SACH LOP ", 96);
					veNutMenu(1, 30, 5, 36, "THEM SINH VIEN", 96);
					gotoxy(5,2);
					vekhungDS(34,100,2);
					gotoxy(26, 3);
					cout<<"MA LOP";
					gotoxy(70, 3);
					cout<<"TEN LOP";
				}
			}
			else
			{
				Message(132, 20, "Sai dinh dang ma lop,vui long nhap lai");
				AnConTro();
				Sleep(750);
				DeleteMessage(132, 20);
			}
			for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                      ";
						gotoxy(56,6+i);
						cout << "                                      ";
					}
			malop = "";
			gotoxy(5+18,40);
			cout << "          ";
			gotoxy(5+18,40);
		}
		hd = wherex();
		td = wherey();
		InDSLop(dsl,page,6,4);
		gotoxy(hd,td);
		HienConTro();
		batPhim(s,sCheck);
	}
	for(int i = 0; i < 8; i++)
	{
		gotoxy(5,37+i);
		cout << "                                        ";
	}
}
// NHAP MA LOP
void NhapMaLop(dslop &dsl , int page)
{
	
	string malop;
	int hd;
	int td;
	gotoxy(5,37);
	veKhung2vien(8, 40);
	veNutMenu(1, 10, 8, 40, "MA LOP", 176);
	gotoxy(5+17,39);
	veKhung(3,20);
	
	veNutMenu(1, 30, 5, 0, "DANH SACH LOP ", 96);
	veNutMenu(1, 30, 5, 36, "THEM SINH VIEN", 96);
	gotoxy(5,2);
	vekhungDS(34,100,2);
	gotoxy(26, 3);
	cout<<"MA LOP";
	gotoxy(70, 3);
	cout<<"TEN LOP";
	InDSLop(dsl,page,6,4);
	
	
	gotoxy(5+18,40);
	
	HienConTro();
	char s;
	bool sCheck;
	batPhim(s,sCheck);
	while(s != ESC)
	{
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')) && sCheck == true)
		{
			HienConTro();
			if (malop.length() < 10)
			{
				cout << InHoa(s);
				malop += InHoa(s);
			}
		}
		if (s == BACKSPACE)
		{
			if (malop.length() > 0)
			{
				AnConTro();
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(wherex()-1,wherey());
				HienConTro();
				malop.erase(malop.length()-1);
			}	
		}
		if(s == ENTER)
		{
			if(CheckFormMaLop(malop) == true)
			{
				if(CheckMaLop(dsl,malop) == true)
				{
					Message(132, 30,"Ma lop khong ton tai");
					AnConTro();
					Sleep(750);
					DeleteMessage(132, 30);
				}
				else
				{
					for(int i = 0; i < dsl.solop; i++)
					{
						if(dsl.l[i]->MALOP.compare(malop) == 0)
						{
							hd = wherex();
							td = wherey();
							system("cls");
							veNutMenu(1, 40, 5, 0, "DANH SACH SINH VIEN", 96);
							gotoxy(5,2);
							VeKhungDSLop(34,100,4);
							gotoxy(15,3);
							cout << "MA SV";
							gotoxy(50,3);
							cout << "HO VA TEN";
							gotoxy(88,3);
							cout << "GIOI TINH";
							InDSSV(dsl.l[i],0);
							NhapSinhVien(dsl.l[i]);
							gotoxy(hd,td);
						}
					}
					system("cls");
					
					gotoxy(5,37);
					veKhung2vien(8, 40);
					veNutMenu(1, 10, 8, 40, "MA LOP", 176);
					gotoxy(5+17,39);
					veKhung(3,20);
					
					veNutMenu(1, 30, 5, 0, "DANH SACH LOP ", 96);
					veNutMenu(1, 30, 5, 36, "THEM SINH VIEN", 96);
					gotoxy(5,2);
					vekhungDS(34,100,2);
					gotoxy(26, 3);
					cout<<"MA LOP";
					gotoxy(70, 3);
					cout<<"TEN LOP";
				}
			}
			else
			{
				Message(132, 20, "Sai dinh dang ma lop,vui long nhap lai");
				AnConTro();
				Sleep(750);
				DeleteMessage(132, 20);
			}
			for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                      ";
						gotoxy(56,6+i);
						cout << "                                      ";
					}
			malop = "";
			gotoxy(5+18,40);
			cout << "          ";
			gotoxy(5+18,40);
		}
		hd = wherex();
		td = wherey();
		InDSLop(dsl,page,6,4);
		gotoxy(hd,td);
		HienConTro();
		batPhim(s,sCheck);
	}
	for(int i = 0; i < 8; i++)
	{
		gotoxy(5,37+i);
		cout << "                                        ";
	}
}

//
void XoaSV(lop *&l ,int page)
{
	system("cls");
	veNutMenu(1, 40, 5, 0, "XOA SINH VIEN", 96);
	char s;
	bool sCheck;
	gotoxy(5,2);
	int state = 0;
	gotoxy(5,2);
	VeKhungDSLop(34,100,4);
	gotoxy(15,3);
	cout << "MA SV";
	gotoxy(50,3);
	cout << "HO VA TEN";
	gotoxy(88,3);
	cout << "GIOI TINH";
	InDSSV(l,page);
	int maxpage;
	batPhim(s,sCheck);
	while(s != ESC)
	{
		if(DemSV(l->danhsach) < 10)
		{
			maxpage = 0;
		}
		else if(DemSV(l->danhsach) % 10 == 0)
		{
			maxpage = DemSV(l->danhsach)/10 - 1;
		}
		else maxpage = DemSV(l->danhsach)/10;
		if (s == PAGEDOWN && sCheck == false)
		{
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                      ";
					gotoxy(31,6+i);
					cout << "                                             ";
					gotoxy(81,6+i);
					cout << "                      ";
				}
				page ++;
				InDSSV(l,page);
				AnConTro();
			}
		}
		if(s == PAGEUP && sCheck == false)
		{
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                      ";
					gotoxy(31,6+i);
					cout << "                                             ";
					gotoxy(81,6+i);
					cout << "                      ";
				}
				page--;
				InDSSV(l,page);
				AnConTro();
			}
		}
		if(s == ENTER)
		{
			if (l->danhsach.First == NULL)
			{
				Message(130, 30, "Danh sach SV trong! Khong the xoa!");
				AnConTro();
				Sleep(750);
				DeleteMessage(130, 30);
				break;
			}
			else 
			{
				gotoxy(120,10);
				cout << "               ";
				cout << "               ";
				cout << "               ";
				gotoxy(120,15);
				cout << "               ";
				cout << "               ";
				cout << "               ";
				XoaSinhVien(l,page);	
				gotoxy(15,3);
				cout << "MA SV";
				gotoxy(50,3);
				cout << "HO VA TEN";
				gotoxy(88,3);
				cout << "GIOI TINH";
				if (l->danhsach.First == NULL)
				{
					Message(130, 30, "Danh sach SV trong! Khong the xoa!");
					AnConTro();
					Sleep(750);
					DeleteMessage(130, 30);
					gotoxy(7,6);
					cout << " ";
					break;
				}
				else 
				{
					InDSSV(l,page);	
					gotoxy(7,6);
					cout << " ";	
					break;	
				}							
			}
		}
	batPhim(s,sCheck);	
	}
}


void XoaSinhViencase1(dslop &dsl, lop *&l)
{
	int page = 0;
	int maxpage;
	int hd;
	int td;	
	veNutMenu(1, 40, 5, 0, "XOA SINH VIEN LOP", 96);
	gotoxy(5,2);
	vekhungDS(34,100,2);
	gotoxy(26, 3);
	cout<<"MA LOP";
	gotoxy(70, 3);
	cout<<"TEN LOP";
	InDSLop(dsl,page, 6, 4);
	string malop = "";
	gotoxy(7,6);
	cout << muiten;
	int state = 0;
	char s;
	bool sCheck;
	batPhim(s,sCheck);
	while(s != ESC)
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
		ChangeColor(15);
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
						cout << "                                      ";
						gotoxy(58,6+i);
						cout << "                                      ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSLop(dsl,page, 6 , 4);
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
					
						for(int i = 0; i < 28;i++)
						{
							gotoxy(6,6+i);
							cout << "                                      ";
							gotoxy(58,6+i);
							cout << "                                      ";
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
					cout << "                                      ";
					gotoxy(58,6+i);
					cout << "                                      ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				hd = wherex();
				td = wherey();
				InDSLop(dsl,page, 6, 4);
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
					cout << "                                      ";
					gotoxy(58,6+i);
					cout << "                                      ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				hd = wherex();
				td = wherey();
				InDSLop(dsl,page,6 ,4);
				gotoxy(hd,td);
			}
		}
		if ( s == ENTER)
		{
			//qua phai ve 2 nut them sinh vien, xoa sinh vien, enter chon chuc nang (giong funclop)
			XoaSV(dsl.l[state + page*10],page);
			system("cls"); 
			gotoxy(5,2);
			vekhungDS(34,100,2);
			gotoxy(26, 3);
			cout<<"MA LOP";
			gotoxy(70, 3);
			cout<<"TEN LOP";
			InDSLop(dsl,page, 6, 4);
			state = 0;
			AnConTro();
			gotoxy(7,6);
			cout << muiten;	
		}
		batPhim(s, sCheck);
	}
}
void QUANLYSINHVIEN(dslop &dsl)
{
	int page = 0;
	char s;
	bool sCheck;
	int state = 0;
	veNutMenu(3, 30, 75, 6, "Them", 90);
	veNutMenu(3, 30, 75, 10, "Xoa", 176);
	batPhim(s,sCheck);
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
						veNutMenu(3, 30, 75, 6, "Them", 90);
						veNutMenu(3, 30, 75, 10, "Xoa", 176);
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
						veNutMenu(3, 30, 75, 6, "Them", 176);
						veNutMenu(3, 30, 75, 10, "Xoa", 90);
						break;
					}
				case 1:
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
						//HAM THEM SINH VIEN VAO LOP
						NhapMaLop(dsl, page);
						system("cls");
						AnConTro();
						veNutMenu(3,30,2,2,"QUAN LY LOP HOC",128);
						veNutMenu(3,30,40,2,"IN DANH SACH LOP", 128);
						veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",90);
						veNutMenu(3,30,110,2,"QUAN LY MON HOC",128);
						veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",128);
						veNutMenu(3,30,180,2,"DANH SACH DIEM",128);
						gotoxy(50,5);
	//QUAN LY LOP HOC
						veNutMenu(3, 30, 2, 6, "Them", 176);
						veNutMenu(3, 30, 2, 10, "Xoa", 176);
						veNutMenu(3, 30, 2, 14, "Sua", 176);
	//QUAN LY SINH VIEN
						veNutMenu(3, 30, 75, 6, "Them", 90);
						veNutMenu(3, 30, 75, 10, "Xoa", 176);
	//QUAN LY MON HOC
						veNutMenu(3, 30, 110, 6, "Them", 176);
						veNutMenu(3, 30, 110, 10, "Xoa", 176);
						veNutMenu(3, 30, 110, 14, "Sua", 176);
	//QUAN LY CAU HOI THI
						veNutMenu(3, 30, 145, 6, "Them", 176);
						veNutMenu(3, 30, 145, 10, "Xoa", 176);
						veNutMenu(3, 30, 145, 14, "Xem CH", 176);
						break;
					}
				case 1:
					{	
						system("cls");
						lop *l;					
						XoaSinhViencase1(dsl, l);
						system("cls");
						veNutMenu(3,30,2,2,"QUAN LY LOP HOC",128);
						veNutMenu(3,30,40,2,"IN DANH SACH LOP", 128);
						veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",95);
						veNutMenu(3,30,110,2,"QUAN LY MON HOC",128);
						veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",128);
						veNutMenu(3,30,180,2,"DANH SACH DIEM",128);
						gotoxy(50,5);
//	//QUAN LY LOP HOC
						veNutMenu(3, 30, 2, 6, "Them", 176);
						veNutMenu(3, 30, 2, 10, "Xoa", 176);
						veNutMenu(3, 30, 2, 14, "Sua", 176);
	//QUAN LY SINH VIEN
						veNutMenu(3, 30, 75, 6, "Them", 176);
						veNutMenu(3, 30, 75, 10, "Xoa", 90);
	//QUAN LY MON HOC
						veNutMenu(3, 30, 110, 6, "Them", 176);
						veNutMenu(3, 30, 110, 10, "Xoa", 176);
						veNutMenu(3, 30, 110, 14, "Sua", 176);
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

#endif
