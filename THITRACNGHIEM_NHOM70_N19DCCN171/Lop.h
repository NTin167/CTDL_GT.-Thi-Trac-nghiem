#ifndef _LOP_H
#define _LOP_H
#include"Thi.h"
#include"SinhVien.h"
#include"Diem.h"

// TIM KIEM SINH VIEN 
nodeSV* search_SV(dssv &ds, string maSV)
{
	nodeSV *p;
	p = ds.First;
	while(p != NULL && p->info.MASV.compare(maSV) != 0 )
	{
		p = p->pNext;
	}
	return p;
}

// THEM DIEM THI VAO DAU DS
void Insert_Diem_First(nodediemThi *&First, diemThi diem)
{
	nodediemThi *p;
	p = new nodediemThi;
	p->info = diem;
	p->pNext = First;
	First = p;

}
//THEM DIEM VAO SAU
void Insert_Diem_after(nodediemThi *p, diemThi diem)
{	
	nodeSV *q;
	if(p == NULL) 
		cout << "Node truoc da cho khong the la NULL";
	else
	{
		nodediemThi *q = new nodediemThi;
		q->info = diem;
		q->pNext = p->pNext;
		p->pNext = q;
	}
}
// TIM LOP THEO MA LOP
lop* Search_Lop(dslop dsl, string maLop)
{
	for(int i = 0; i < dsl.solop ; i++)
	{
		if(dsl.l[i]->MALOP.compare(maLop) == 0)
		{
			return dsl.l[i];
		}
	}
}
//THEM SINH VIEN VAO DAU DS
void Insert_SV_First(nodeSV *&First, sinhVien sv)
{
	nodeSV *p;
	p = new nodeSV;
	p->info = sv;
	p->pNext = First;
	First = p;

}
// THEM SINH VIEN VAO SAU
void Insert_after_SV(nodeSV *p, sinhVien sv)
{
	nodeSV *q;
	if(p == NULL)
	{
		Message(50, 50, "Khong the them ");
		AnConTro();
		Sleep(650);
		DeleteMessage(50, 50);
	}
	else
	{ 
		nodeSV *q = new nodeSV;
		q->info = sv;
		q->pNext = p->pNext;
		p->pNext = q;
	}
}

// Tach ma so tu MSSV, 3 chu so sau
int TachMSSV (string maSV) 
{
	maSV.erase(0,maSV.length()-3);
	return StringToInt(maSV);
}

//SO SANH MA SINH VIEN
int SoSanhMaSo (sinhVien sv1, sinhVien sv2)
{
	if(TachMSSV(sv1.MASV) < TachMSSV(sv2.MASV)) 
	{
		return -1;
	}
	if (TachMSSV(sv1.MASV) > TachMSSV(sv2.MASV)) 
	{
		return 1;
	}
	if (TachMSSV(sv1.MASV) == TachMSSV(sv2.MASV)) 
	{
		return 0;
	}
}

// THEM SINH VIEN 
void Them1SinhVien(lop *l, sinhVien sv)
{ 
	nodeSV *t,*s;
	if(l->danhsach.First == NULL)
	{
		Insert_SV_First(l->danhsach.First,sv);
	}
	else 
	{
		if(SoSanhMaSo(l->danhsach.First->info,sv) > 0) //MSSV THEM < MSSV FIRST
		{
			Insert_SV_First(l->danhsach.First,sv);
		}
		else
		{
			// truoc sau
			for(s = l->danhsach.First; s != NULL && SoSanhMaSo(s->info,sv) < 0 ; t=s, s = s->pNext) ;
			Insert_after_SV(t,sv);	
		}
	}
}
//  DOC FILE 1 LOP 
void DocFileLop (lop *&l, string filename )
{
	ifstream fileIn;
	fileIn.open(filename.c_str(),ios_base :: in );
	if(fileIn.fail()) cout << "";
	sinhVien sv ;
	while(!fileIn.eof())
	{	
		if(fileIn.peek() == std::ifstream::traits_type::eof()) break; // kiem tra file trong
		getline(fileIn,sv.MASV,'\n');
		getline(fileIn,sv.HO,' ');
		getline(fileIn,sv.TEN,'\n');
		getline(fileIn,sv.PHAI,'\n');
		getline(fileIn,sv.password,'\n');
		InHoaChuoi(sv.MASV);
		InHoaChuoi(sv.HO);
		InHoaChuoi(sv.TEN);
		if(StringToInt(sv.PHAI) == 1)
		{
			sv.PHAI = "NAM";
		}
		else if(StringToInt(sv.PHAI) == 0)
		{
			sv.PHAI = "NU";
		}
		Them1SinhVien(l,sv);
	}
	fileIn.close();
}

void DocFileDiem1Lop ( lop *l)
{
	ifstream fileIn;
	fileIn.open("DiemThi"+l->MALOP+".txt", ios_base :: in);
	if(fileIn.fail())
	{
		return;	
	} 
	string masv;
	string x;
	int slt;
	nodediemThi *diem = new nodediemThi;
	while(!fileIn.eof())
	{
		getline(fileIn,masv,'\n');
		getline(fileIn,x,'\n');
		slt = StringToInt(x);
		if(slt == 0)
		{
			fileIn.ignore();
		}
		else
		{
			string temp;
			for(int i = 0; i < slt; i++)
			{
				getline(fileIn,temp,':');
				diem->info.MAMH = temp;
				getline(fileIn,temp,':');
				diem->info.DIEM = StringToFloat(temp);
				getline(fileIn,temp,':');
				diem->info.ctdt.sct = StringToInt(temp);
				diem->info.ctdt.bode = new int [diem->info.ctdt.sct];
				diem->info.ctdt.dapan = new int [diem->info.ctdt.sct];
				for(int i = 0 ; i < diem->info.ctdt.sct; i++)
				{
					getline(fileIn,temp,'@');
					diem->info.ctdt.bode[i] = StringToInt(temp);
				}
				for(int i = 0 ; i < diem->info.ctdt.sct; i++)
				{
					getline(fileIn,temp,'#');
					diem->info.ctdt.dapan[i] = StringToInt(temp);
					if(i == diem->info.ctdt.sct -1)
					{
						fileIn.ignore();
					}
				}
				diemThi diemsv;
				diemsv = diem->info;
				if (search_SV(l->danhsach,masv)->info.diem.First == NULL) 
				{
					Insert_Diem_First(search_SV(l->danhsach,masv)->info.diem.First,diemsv);
				}
				else 
				{
					nodediemThi *p = search_SV(l->danhsach,masv)->info.diem.First;
					while (p->pNext != NULL)
					{
						p = p->pNext;
					}
					Insert_Diem_after(p,diemsv);
				}
			}	
		}
	}
}


// DOC DANH SACH LOP TU FILE
void DocFileDSLop (dslop &dsl)
{
	ifstream fileIn;
	fileIn.open("InputLop.txt", ios_base :: in );
	if(fileIn.fail()) 
		cout << "Failed to open this file!";
	fileIn >> dsl.solop;
	fileIn.ignore();
	for(int i = 0; i < dsl.solop; i++)
	{
		dsl.l[i] = new lop;
		getline(fileIn,dsl.l[i]->TENLOP,'\n');
		getline(fileIn,dsl.l[i]->MALOP,'\n');
		DocFileLop(dsl.l[i],dsl.l[i]->MALOP+".txt");
		DocFileDiem1Lop(dsl.l[i]);
	}
	fileIn.close();
}
// IN DS LOP
void InDSLop (dslop dsl, int &page, int x, int y) // x = 60 | y = 12
{
	if (dsl.solop == 0)
	{
		return;
	}
	int k = 2;
	int maxpage;
	if (dsl.solop % 10 == 0)
	{
		maxpage = dsl.solop/10;
	}
	else maxpage = dsl.solop/10 +1;
	for(int i = page*10; i < (page+1)*10; i++)
	{
		if(dsl.l[i] == NULL)
		{
			break;
		}
		gotoxy(x+20,y+k);
		cout << dsl.l[i]->MALOP;
		gotoxy(x+5+50,y+k);
		cout << dsl.l[i]->TENLOP;
		k += 3;
	}
}
//  KIEM TRA MA LOP & TEN LOP TRONG DS
bool CheckLopNhap (dslop dsl, string malop, string tenlop)
{
	for(int i = 0; i < dsl.solop; i++)
	{
		if(malop.compare(dsl.l[i]->MALOP) == 0 || tenlop.compare(dsl.l[i]->TENLOP) == 0)
		{
			return false;
		}
	}
	return true;
}

//KIEM TRA MA LOP TRONG DS
bool CheckMaLop (dslop dsl, string malop)
{
	for(int i = 0; i < dsl.solop; i++)
	{
		if(malop.compare(dsl.l[i]->MALOP) == 0 )
		{
			return false;
		}
	}
	return true;
}

// KIEM TRA MA LOP
bool CheckFormMaLop (string malop)   // form Ma lop la DxxCQCNxxx
{
	if (malop.length() != 9 || malop[0] != 'D')
	{
		return false;
	}
	if (malop[1] < '0' || malop[1] > '9' || malop[2] < '0' || malop[2] > '9')				
	{
		return false;
	}
	for(int i = 7; i < 9; i++)
	{
		if(malop[i] < '0' || malop[i] > '9')
		{
			return false;
		}
	}
	for(int i = 3; i < 7; i++)
	{
		if(malop[i] < 'A' || malop[i] > 'Z')
		{
			return false;
		}
	}	
	return true;
}
void NhapLopNew(dslop &dsl, int page)
{	
	veNutMenu(1, 25, 75, 13, "THEM LOP", 176);// nut Subject
	gotoxy(75, 15);
	veKhung(15, 60);
	gotoxy(85, 17);
	veKhung(3, 40);	
	gotoxy(85, 20);
	veKhung(3, 40);
	veNutMenu(1, 5, 79, 18, "MA LOP", 176);
	veNutMenu(1, 5, 79, 21, "TEN LOP", 176);
	veNutMenu(3, 20, 93, 24, "LUU", 176);
	string tenlop;
	string malop;
	char s;
	bool state = true;
	bool sCheck;
	int hd;
	int td;
	gotoxy(86,18);
	HienConTro();
	batPhim(s,sCheck);
	int check = 0;
	while (1)
	{
		if(s == ESC)
		{
			if(Exit(s,sCheck,75, 40) == true)
			{
				system("cls");
				veNutMenu(3,30,2,2,"QUAN LY LOP HOC",95);
				veNutMenu(3,30,40,2,"IN DANH SACH LOP", 128);
				veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",128);
				veNutMenu(3,30,110,2,"QUAN LY MON HOC",128);
				veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",128);
				veNutMenu(3,30,180,2,"DANH SACH DIEM",128);
				gotoxy(50,5);
//				//QUAN LY LOP HOC
				veNutMenu(3, 30, 2, 6, "Them", 90);
				veNutMenu(3, 30, 2, 10, "Xoa", 176);
				veNutMenu(3, 30, 2, 14, "Sua", 176);
				//QUAN LY SINH VIEN
				veNutMenu(3, 30, 75, 6, "Them", 176);
				veNutMenu(3, 30, 75, 10, "Xoa", 176);
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
			else
			{
				DeleteExit(75, 40);
				if(check == 0)
				{
					gotoxy(86+malop.length(),18);
				}
				else if(check == 1)
				{
					gotoxy(86+tenlop.length(),21);	
				}
				HienConTro();
				batPhim(s,sCheck);
				
			}
		}
		
		if (s == UP && sCheck == false)
		{
			if (check == 1)
			{
				gotoxy(86+malop.length(),18);
				check = 0;
			}
			else if(check == 2)
			{
				HienConTro();
				veNutMenu(3, 20, 93, 24, "LUU", 176);
				gotoxy(86+tenlop.length(),21);
				check = 1;
			}
		}
		if (s == DOWN && sCheck == false)
		{
			if (check == 0)
			{
				veNutMenu(3, 20, 93, 24, "LUU", 176);
				gotoxy(86+tenlop.length(),21);
				check = 1;
			}
			else if(check == 1)
			{
				AnConTro();
				veNutMenu(3, 20, 93, 24, "LUU", 90);
				check = 2;
			}
		}
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')  ) && sCheck == true)
		{
			HienConTro();
			if (check == 1 )
			{
				if (tenlop.length() < 30)
				{
					cout << InHoa(s);
					tenlop += InHoa(s);
				}
			}
			else if(check == 0)
			{
				if (malop.length() < 20)
				{
					cout << InHoa(s);
					malop += InHoa(s);
				}
			}
		}
		if(s == ' ')
		{
			if(check == 1)
				{
					if(tenlop.length() == 0)
					{
						gotoxy(86+tenlop.length(),21);
					}
					else if(tenlop[tenlop.length()-1]!= ' ')
					{
						cout << InHoa(s);
						tenlop += InHoa(s);	
					}
				}
		}
		if (s == BACKSPACE)
		{
			if (check == 1)
			{
				if (tenlop.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					tenlop.erase(tenlop.length()-1);
				}
			}
			else if(check == 0)
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
		}
		
		
		if (s == ENTER)
		{
			AnConTro();
			ChuanHoaTen(tenlop);
			if(tenlop.length() == 0 || malop.length() == 0)
			{
				Message(120, 35,"Vui long nhap day du thong tin");
				AnConTro();
				Sleep(750);
				DeleteMessage(120, 35);
				gotoxy(86+malop.length(),18);
			}
			else
			{
				if(CheckFormMaLop(malop) == false)
				{
					
					Message(120, 35, "Sai dinh dang, moi nhap lai");
					AnConTro();
					Sleep(750);
					DeleteMessage(120, 35);
					HienConTro();
					gotoxy(86+malop.length(),18);
					check = 0;
				}
				else
				{
					if(CheckLopNhap(dsl,malop,tenlop) == false)
					{
						Message(120, 35,"Ma lop hoac ten lop da bi trung");
						AnConTro();
						Sleep(750);
						DeleteMessage(120, 35);
						gotoxy(86+malop.length(),18);
					}
					else
					{
						int n = dsl.solop;
						dsl.l[n] = new lop;
						dsl.l[n]->MALOP = malop;
						dsl.l[n]->TENLOP = tenlop;
						dsl.solop++; 
						AnConTro();
						Message(120, 35,"Them lop vao danh sach thanh cong");
						AnConTro();
						Sleep(750);
						DeleteMessage(120, 35);
						HienConTro();
					}
				}
			}
			state = true;
			HienConTro();
		}
		batPhim(s,sCheck);
	}
	AnConTro();
}

void ThemLopNew(dslop &dsl, int page)
{
	ChangeColor(15);
	int n = dsl.solop;
	if(n  == MAXLOP)
	{
		Message(100, 35, "Khong the them lop, danh sach lop da day");
		AnConTro();
		Sleep(750);
		DeleteMessage(100, 35);
	}
	else
	{
		NhapLopNew(dsl,page);
	}
}
//DEM SO LAN THI
int DemLanThi(dsdiemThi diem)
{
	int dem = 0;
	for (nodediemThi *k = diem.First; k != NULL; k = k->pNext)
	{
		dem++;
	}
	return dem;
}
//DEM SO SV
int DemSV(dssv ds)
{
	int dem = 0;
	
	for (nodeSV *k = ds.First; k != NULL; k = k->pNext)
	{
		dem++;
	}
	return dem;
}
// TACH HO SINH VIEN
string TachHoSV(string hoten)
{
	string ho;
	for(int i = 0; i < hoten.length(); i ++)
	{
		if(hoten[i] == 32) // 32 space character
		{
			return ho;
		}
		ho += hoten[i];
	}
}
// TACH TEN SINH VIEN
string TachTenSV(string hoten)
{
	string ten ;
	for(int i = 0; i < hoten.length(); i ++)
	{
		if (hoten[i] == ' ')
		{
			for(int j = i + 1;j < hoten.length();j++)
			{
				ten += hoten[j];
			}
			return ten;
		}
	}
}
//KIEM TRA MA LOP TRONG DS
bool CheckMaSV (lop *l, string masv)
{
	for(nodeSV *k = l->danhsach.First; k != NULL; k = k->pNext)
	{
		if(masv.compare(k->info.MASV) == 0 )
		{
			return false;
		}
	}
	return true;
}
// KTRA NHAP MA SV 
bool CheckFormMaSv (string masv)
{
	if (masv.length() != 10 || masv[0] != 'N')
	{
		return false;
	}
	if (masv[1] < '0' || masv[1] > '9' || masv[2] < '0' || masv[2] > '9')				//1,2,7,8,9
	{
		return false;
	}
	for(int i = 7; i < 10; i++)
	{
		if(masv[i] < '0' || masv[i] > '9')
		{
			return false;
		}
	}
	for(int i = 3; i < 7; i++)
	{
		if(masv[i] < 'A' || masv[i] > 'Z')
		{
			return false;
		}
	}	
	
	return true;
}
// IN DANH SACH SINH VIEN
void InDSSV (lop *l,int page)
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
	
	for(int i = 0; i < 10; i++)
	{
		if (j->pNext != NULL) 
		{ 
			gotoxy(12,4+k);
			cout << j->info.MASV;
			gotoxy(40,4+k);
			cout << j->info.HO << " " << j->info.TEN;
			gotoxy(80+(25-j->info.PHAI.length())/2,4+k);
			cout << j->info.PHAI;
			k += 3;
			j = j->pNext;
		}
		else {
			gotoxy(12,4+k);
			cout << j->info.MASV;
			gotoxy(40,4+k);
			cout << j->info.HO << " " << j->info.TEN;
			gotoxy(80+(25-j->info.PHAI.length())/2,4+k);
			cout << j->info.PHAI;
			k += 3;
			break;
		}
	}
	gotoxy(125/2,36);
	cout << "Trang " << page + 1 << "/" << maxpage + 1;
}


void NhapLopXoaNew(dslop &dsl, int &page)
{
	HienConTro();
	int maxpage;
	gotoxy(110, 10);
	vekhungDS(34,100,2);
	gotoxy(100, 10);
	gotoxy(130, 11);
	cout <<"MA LOP";
	gotoxy(165, 11);
	cout <<"TEN LOP";
	if(dsl.solop != 0)
	{
		InDSLop(dsl, page, 110, 12);
	}
	char s;
	bool sCheck;
	bool check = false;
	int state = 0;
	string malop;
	string tenlop;	
	veNutMenu(1, 25, 10, 8, "Xoa Lop", 176);// nut Subject
	gotoxy(10, 10);
	veKhung(15, 60);
	gotoxy(20, 12);
	veKhung(3, 40);	
	gotoxy(20, 15);
	veKhung(3, 40);
	veNutMenu(1, 5, 14, 13, "MA LOP", 176);
	veNutMenu(1, 5, 14, 16, "TEN LOP", 176);
	veNutMenu(3, 20, 30, 19, "XOA", 176);
	gotoxy(21, 13); // Dua con tro den vi tri Ma Lop
	batPhim(s,sCheck);
	while (s != ESC)
	{
		if(s == UP && sCheck == false)	
		{
			if (check == true)
			{
				gotoxy(21+malop.length(),13);
				check = !check;
			}
		}
		
		if(s == DOWN && sCheck == false)
		{
			if(check == false)
			{
				gotoxy(21+tenlop.length(),16);
				check = !check;
			}
		}
			
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')) && sCheck == true)
		{
			HienConTro();
			if (check == false)
			{
				if (malop.length() < 20)
				{
					cout << InHoa(s);
					malop += InHoa(s);
				}
			}
			else
			{
				if (tenlop.length() < 20)
				{
					cout << InHoa(s);
					tenlop += InHoa(s);
				}
			}
		}
		if (s == BACKSPACE)
		{
			if (check == false)
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
			else
			{
				if (tenlop.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					tenlop.erase(tenlop.length()-1);
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
					cout << "                            ";
				}
				page ++;
				int hd = wherex();
				int td = wherey();
				InDSLop(dsl,page,110, 12);
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
					cout << "                            ";
				}
				page--;
				int hd = wherex();
				int td = wherey();
				InDSLop(dsl,page,110,12);
				gotoxy(hd,td);
			}
		}
		if (s == ENTER)
		{
			for(int i = 0; i < dsl.solop; i++)
			{
				if(malop.compare(dsl.l[i]->MALOP) == 0)
				{
					if(DemSV(dsl.l[i]->danhsach) > 0)
					{
						Message(20, 35, "Lop co sinh vien, k the xoa");
						Sleep(1000);
						DeleteMessage(20, 35);
//						HienConTro();
					}
					else
					{
						for(int j = i; j < dsl.solop; j++)
						{
							dsl.l[j] = dsl.l[j+1];
						}
						dsl.solop--;
						Message(20, 35, " Xoa lop thanh cong");
						Sleep(1000);
						DeleteMessage(20, 35);
						for(int i = 0; i < 29;i++)
						{
							gotoxy(115,14+i);
							cout << "                            ";
							gotoxy(165,14+i);
							cout << "                            ";
						}
//						HienConTro();
					}
					break;
				}
				else if(malop.compare(dsl.l[i]->MALOP) != 0 && i == (dsl.solop-1)) 
				{
					Message(20, 35, "Ma Lop Sai");
					Sleep(500); // 500 * dsl.solop;
					DeleteMessage(20, 35);
//					HienConTro();
				}
			}
//			system("cls");
			InDSLop(dsl, page, 110, 12);
			HienConTro();
		}
	batPhim(s, sCheck);
	}		
}

// XOA LOP
void XoaLop(dslop &dsl, int &page){
	int n = dsl.solop;
	if(n  == 0)
	{
		system("cls");
		Message(100, 30, "Danh sach lop trong");
		Sleep(750);
		DeleteMessage(100, 30);
	}
	else
	{	
		NhapLopXoaNew(dsl, page);
	}
}
// SUA LOP
void SuaLop(lop *&l)
{
	veNutMenu(1, 25, 120, 3, "Sua Lop", 176);// nut Subject
	gotoxy(120, 5); // 10 10
	veKhung(15, 60);
	gotoxy(130, 7);// 20 12
	veKhung(3, 40);	
	gotoxy(130, 10);
	veKhung(3, 40);
	veNutMenu(1, 5, 124, 8, "MA LOP", 176);
	veNutMenu(1, 5, 124, 11, "TEN LOP", 176);
	veNutMenu(3, 20, 140, 14, "SUA", 176);
	
	bool state = true;
	char s;
	bool sCheck;
	string tenlop = l->TENLOP;
	string malop = l->MALOP;
	gotoxy(132,8);
	cout << malop;
	gotoxy(132,11);
	cout << tenlop;
	gotoxy(132+malop.length(),8);
	HienConTro();
	batPhim(s,sCheck);
	// vi tri o ma lop 15 41
	//vi tri ten lop ma lop 17 42
	
	while(1)
	{
		if(s == ESC)
		{
			if(Exit(s,sCheck, 75, 40) == true)
			{
				DeleteExit(75, 40);
				break;
			}
			else
			{
				DeleteExit(75, 40);
				if(state == true)
				{
					gotoxy(132+malop.length(),8);
				}
				else
				{
					gotoxy(132+tenlop.length(),11);	
				}
				HienConTro();
				batPhim(s,sCheck);
				
			}
		}
		if (s == UP && sCheck == false)
		{
			if (state == false)
			{
				gotoxy(132+malop.length(),8);
				state = true;
			}
		}
		if (s == DOWN && sCheck == false)
		{
			if (state == true)
			{
				gotoxy(132+tenlop.length(),11);
				state = false;
			}
		}
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')) && sCheck == true)
		{
			HienConTro();
			if (state == true)
			{
				if (malop.length() < 10)
				{
					cout << InHoa(s);
					malop += InHoa(s);
				}
			}
			else
			{
				if (tenlop.length() < 30)
				{
					cout << InHoa(s);
					tenlop += InHoa(s);
				}
			}
		}
		if(s == ' ')
		{
			if(state == false)
				{
					if(tenlop.length() == 0)
					{
						gotoxy(132+tenlop.length()-1,11);
					}
					if(tenlop[tenlop.length()-1] != ' ')
					{
						cout << InHoa(s);
						tenlop += InHoa(s);	
					}
				}
		}
		if (s == BACKSPACE)
		{
			if (state == false)
			{
				if (tenlop.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					tenlop.erase(tenlop.length()-1);
				}
			}
			else
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
		}
		if(s == ENTER)
		{
			if(malop.length() == 0 || tenlop.length() == 0)
			{
				Message(150, 40, "Vui long nhap du thong tin");
				Sleep(500);
				DeleteMessage(150, 40);
			}
			else
			{
				if(CheckFormMaLop(malop) == false)
				{
					Message(150, 40, "Ma lop sai dinh danng");
					Sleep(500);
					DeleteMessage(150, 40);
				}
				else
				{
					l->TENLOP = tenlop;
					l->MALOP = malop;
					break;
				}
			}
			malop = "";
			tenlop = "";
			gotoxy(132,8);
			cout << "                           ";
			gotoxy(132,11);
			cout << "                           ";
			state = true;
		}
		batPhim(s,sCheck);
	}
	AnConTro();
}
//  NHAP LOP CHINH
void NhapLopChinh(dslop &dsl , int &page)
{
	int maxpage;
	gotoxy(5,2);
	vekhungDS(34,100,2);
	gotoxy(26, 3);
	cout<<"MA LOP";
	gotoxy(70, 3);
	cout<<"TEN LOP";
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
			if( DemSV(dsl.l[state + page * 10]->danhsach) > 0)
			{
				Message(120, 40, "Lop ton tai sinh vien, khong the chinh sua");
				AnConTro();
				Sleep(750);
				DeleteMessage(120, 40);
			}
			else
			{
				// ham nhap thong tin de sua
				SuaLop(dsl.l[state + page * 10]);
			}
			for(int i = 0; i < 28;i++)
			{
				gotoxy(6,6+i);
				cout << "                                 ";
				gotoxy(58,6+i);
				cout << "                                           ";
			}
			page = 0;
			int hd = wherex();
			int td = wherey();
			InDSLop(dsl,page,6,4);
			gotoxy(hd,td);
			cout << " ";
			state = 0;
			gotoxy(7,6);
			cout << muiten;
		}
	batPhim(s,sCheck);
	}
}

// CHINH LOP 
void ChinhLop(dslop &dsl, int &page)
{
	int n = dsl.solop;
	if(n  == 0)
	{
		Message(100, 20,"Danh sach lop hien tai dang trong");
		AnConTro();
		Sleep(750);
		DeleteMessage(100, 20);
	}
	else
	{
		NhapLopChinh(dsl, page);
	}
}

void QUANLYLOPHOC(dslop &dsl)
{
	int maxpage;
	int page = 0;
	char s;
	bool sCheck;
	int state = 0;
	veNutMenu(3, 30, 2, 6, "Them", 90);
	veNutMenu(3, 30, 2, 10, "Xoa", 176);
	veNutMenu(3, 30, 2, 14, "Sua", 176);
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
						veNutMenu(3, 30, 2, 10, "Xoa", 176);
						veNutMenu(3, 30, 2, 6, "Them", 90);
						break;
					}
				case 2:
					{
						state--;
						veNutMenu(3, 30, 2, 14, "Sua", 176);
						veNutMenu(3, 30, 2, 10, "Xoa", 90);
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
						veNutMenu(3, 30, 2, 6, "Them", 176);
						veNutMenu(3, 30, 2, 10, "Xoa", 90);
						break;
					}
				case 1:
					{
						state++;
						veNutMenu(3, 30, 2, 10, "Xoa", 176);
						veNutMenu(3, 30, 2, 14, "Sua", 90);
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
						ThemLopNew(dsl,page);
						AnConTro();
						break;
					}
				case 1:
					{
						system("cls");
											
						
						XoaLop(dsl,page);
						AnConTro();
						system("cls");
						veNutMenu(3,30,2,2,"QUAN LY LOP HOC",95);
						veNutMenu(3,30,40,2,"IN DANH SACH LOP", 128);
						veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",128);
						veNutMenu(3,30,110,2,"QUAN LY MON HOC",128);
						veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",128);
						veNutMenu(3,30,180,2,"DANH SACH DIEM",128);
						gotoxy(50,5);
//	//QUAN LY LOP HOC
						veNutMenu(3, 30, 2, 6, "Them", 176);
						veNutMenu(3, 30, 2, 10, "Xoa", 90);
						veNutMenu(3, 30, 2, 14, "Sua", 176);
	//QUAN LY SINH VIEN
						veNutMenu(3, 30, 75, 6, "Them", 176);
						veNutMenu(3, 30, 75, 10, "Xoa", 176);
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
				case 2:
					{
						system("cls");
						ChinhLop(dsl,page);
						for(int i = 0; i < 28;i++)
						{
							gotoxy(6,6+i);
							cout << "                                      ";
							gotoxy(58,6+i);
							cout << "                                      ";
						}
						InDSLop(dsl,page,6,4);
						AnConTro();
						system("cls");
						veNutMenu(3,30,2,2,"QUAN LY LOP HOC",95);
						veNutMenu(3,30,40,2,"IN DANH SACH LOP", 128);
						veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",128);
						veNutMenu(3,30,110,2,"QUAN LY MON HOC",128);
						veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",128);
						veNutMenu(3,30,180,2,"DANH SACH DIEM",128);
						gotoxy(50,5);
//	//QUAN LY LOP HOC
						veNutMenu(3, 30, 2, 6, "Them", 176);
						veNutMenu(3, 30, 2, 10, "Xoa", 176);
						veNutMenu(3, 30, 2, 14, "Sua", 90);
	//QUAN LY SINH VIEN
						veNutMenu(3, 30, 75, 6, "Them", 176);
						veNutMenu(3, 30, 75, 10, "Xoa", 176);
	//QUAN LY MON HOC
						veNutMenu(3, 30, 110, 6, "Them", 176);
						veNutMenu(3, 30, 110, 10, "Xoa", 176);
						veNutMenu(3, 30, 110, 14, "Sua", 176);
	//QUAN LY CAU HOI THI
						veNutMenu(3, 30, 145, 6, "Them", 176);
						veNutMenu(3, 30, 145, 10, "Xoa", 176);
						veNutMenu(3, 30, 145, 14, "Sua", 176);
						AnConTro();
						break;
					}	
			}
		}
		batPhim(s, sCheck);
	}
}

//LUU FILE LOP 
void GhiFileLop(lop *l, string filename) 
{
	ofstream fileOut;
	fileOut.open(filename.c_str(), ios_base::out);
	if (fileOut.fail()) 
	{
		cout << "Failed to open this file! " << filename << endl;
		return;
	}

	for (nodeSV *p = l->danhsach.First; p != NULL; p = p->pNext) 
	{
		fileOut << p->info.MASV << '\n';
		fileOut << p->info.HO << ' ';
		fileOut << p->info.TEN << '\n';
		if(p->info.PHAI == "NAM")
		{
			fileOut << "1" << '\n';
		}
		else
		{
			fileOut << "0" << '\n';
		}
		fileOut << p->info.password << endl;
	}
	fileOut.close();
	return;
}
// Khi thi 1 lan -> Ghi file dung
// Thi cac lan tiep theo cung MASV thi chi ghi so lan thi->tang so lan thi len
//Cac truong con lai khong ghi duoc.
void GhiFileDiem(lop *l, string filename,NODECH dsch)
{
	ofstream fileOut;
	fileOut.open(filename.c_str(), ios_base::out);
	if (fileOut.fail())
	{
		cout << "Khong mo duoc file" << filename << endl;
		return;
	}
	else
	{
		for (nodeSV *p = l->danhsach.First; p != NULL; p = p->pNext)
		{
			fileOut << p->info.MASV << endl;
			fileOut << DemLanThi(p->info.diem) << endl;
			for (nodediemThi *pd = p->info.diem.First; pd != NULL; pd = pd->pNext)
			{
				string diemthi;
				int scd = TinhDiem(pd->info.ctdt,dsch)*10;
				int sct = pd->info.ctdt.sct;
				diemthi = IntToString(scd/sct);
				fileOut << pd->info.MAMH << ":" << diemthi << ":" << pd->info.ctdt.sct << ":";
				for(int i = 0; i < pd->info.ctdt.sct; i++)
				{
					fileOut << pd->info.ctdt.bode[i] << "@";
				}
				for(int i = 0; i < pd->info.ctdt.sct; i++)
				{
					fileOut << pd->info.ctdt.dapan[i] << "#";
				}
				if(p->pNext == NULL)
				{
					break;
				}
				else fileOut << endl;
			}
			if(p->pNext == NULL)
			{
				break;
			}
			if( DemLanThi(p->info.diem) != 0)
			{
				continue;
			}
			else
			{
				fileOut << endl;
			}
		}
	}
	fileOut.close();
}

//LUU FILE DS LOP
void GhiFileDSlop(dslop dsl, string filename,NODECH dsch)
{
	ofstream fileOut;
	fileOut.open(filename.c_str(), ios_base::out);
	if (!fileOut.is_open()) 
	{
		cout << "Failed to open this file!" << filename << endl;
		return;
	}
	fileOut << dsl.solop << endl;
	for (int i = 0; i < dsl.solop; i++) 
	{
		fileOut << dsl.l[i]->TENLOP << '\n'<< dsl.l[i]->MALOP << '\n';
		GhiFileLop(dsl.l[i], dsl.l[i]->MALOP + ".txt");
		GhiFileDiem(dsl.l[i],"DiemThi"+dsl.l[i]->MALOP+".txt",dsch);
	}
}
#endif
