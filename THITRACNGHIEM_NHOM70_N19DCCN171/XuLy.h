#ifndef _XULY_H
#define _XULY_H
#include"Diem.h"
#include"CauHoiThi.h"
#include"Lop.h"
#include"MonHoc.h"
#include"SinhVien.h"
#include"Thi.h"
#include"Time.h"


int DangNhap(dslop &dsl ,string &masv)
{
	system("cls");
    gotoxy(70,20);//
	TextColor(14);
	veKhung2vien(15, 65);
	gotoxy(70+3,20+3);
	TextColor(0);
	veNutMenu(1, 10, 70+3, 20+3, "User:", 176);
	gotoxy(70+17,20+2);
	TextColor(14);
	veKhung(3,30);//Khung tai khoan
	TextColor(15);
	gotoxy(70+3,20+7);
	cout << "MAT KHAU:";
	veNutMenu(1, 10, 70+3, 20+7, "Password:", 95);
	gotoxy(70+17,20+6);
	veKhung(3,30);//Khung Mat khau
	veNutMenu(1, 10, 70+18, 20+10, "ENTER", 95);
	veNutMenu(1, 10, 70+36, 20+10, "ESC", 95);

	

	
	
	string user;
	string pass;
	char s;
	bool state = false;
	bool sCheck;
	gotoxy(70+18,20+3);
	batPhim(s,sCheck);
	
	
	while (s != ESC)
	{
		if (s == UP && sCheck == false)
		{
			if (state == true)
			{
				veNutMenu(1, 10, 70+3, 20+3, "User:", 176);
				veNutMenu(1, 10, 70+3, 20+7, "Password:", 95);
				gotoxy(70+18+user.length(),20+3);
				state = !state;
			}
		}
		
		if (s == DOWN && sCheck == false)
		{
			if (state == false)
			{
				veNutMenu(1, 10, 70+3, 20+3, "User:", 95);
				veNutMenu(1, 10, 70+3, 20+7, "Password:", 176);
				gotoxy(70+18+pass.length(),20+7);
				state = !state;
			}
		}


		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')) && sCheck == true)
		{
			HienConTro();
			if (state == true)
			{
				if (pass.length() < 20)
				{
					cout << "*";
					pass += s;
				}
			}
			else
			{
				if (user.length() < 20)
				{
					cout << InHoa(s);
					user += InHoa(s);
				}
			}
		}
		if (s == BACKSPACE)
		{
			if (state == true)
			{
				if (pass.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					pass.erase(pass.length()-1);
				}
			}
			else
			{
				if (user.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					user.erase(user.length()-1);
				}
			}
		}
		if (s == ENTER)
		{
			if((user == "GV" && pass == "GV") || (user == "GV") && (pass == "gv"))
			{
				return 1;
			}
			// 0 la quyen SV => chuc nang thi
			//  2 la quyen GV => Quan ly
			else
			{	
				for(int i = 0; i < dsl.solop; i++)
				{
					for(nodeSV *k = dsl.l[i]->danhsach.First; k != NULL; k = k->pNext)
					{
						string x;
						for (int i = 0; i < k->info.MASV.length(); i++)
						{
							x += InHoa(k->info.MASV[i]);
						}
						string y = k->info.password;
						if(x == user && y == pass)
						{
							masv = user;
							return 0;
						}
					}
				}
				return 2;
			}
		}
	batPhim(s,sCheck);
	}
	return -1;
}
// MENU GIANG VIEN
int MenuGV()
{
	ChangeColor(15);
	system("cls");
	veNutMenu(3,30,2,2,"QUAN LY LOP HOC",95);
	veNutMenu(3,30,40,2,"IN DANH SACH LOP", 128);
	veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",128);
	veNutMenu(3,30,110,2,"QUAN LY MON HOC",128);
	veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",128);
	veNutMenu(3,30,180,2,"DANH SACH DIEM",128);
	gotoxy(50,5);
	
	
	//QUAN LY LOP HOC
	veNutMenu(3, 30, 2, 6, "Them", 176);
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
	veNutMenu(3, 30, 145, 14, "Xem CH", 176);
	
	
	
	AnConTro();
	int choose = 0;
	char s;
	bool sCheck;
	batPhim(s,sCheck);
	while(1)
	{
		if (s == ESC)
		{
			system("cls");
			return -1;
		}
		//------VE O CHUC NANG DONG----
		if (s == LEFT && sCheck == false )
		{
			if(choose > 0 )
			{
				switch(choose)
				{
					case 1:
						{
							veNutMenu(3,30,2,2,"QUAN LY LOP HOC",95);
							veNutMenu(3,30, 40, 2, "IN DANH SACH LOP", 143);
							break;
						}
					case 2:
						{
							veNutMenu(3,30, 40, 2, "IN DANH SACH LOP", 95);
							veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",143);
							break;
						}
					case 3:
						{
							veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",95);
							veNutMenu(3,30,110,2,"QUAN LY MON HOC",143);
							break;
						}
					case 4:
						{
							veNutMenu(3,30,110,2,"QUAN LY MON HOC",95);
							veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",143);
							break;
						}
					case 5:
						{
							veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",95);
							veNutMenu(3,30,180,2,"DANH SACH DIEM",143);
							break;
						}			
				}
				choose --;
			}
		}
		if (s == RIGHT && sCheck == false )
		{
			if(choose < 5 )
			{
				switch(choose)
				{
					case 0:
						{
							veNutMenu(3,30,2,2,"QUAN LY LOP HOC",143);
							veNutMenu(3,30, 40, 2, "IN DANH SACH LOP", 95);
							break;
						}
					case 1:
						{
							veNutMenu(3,30, 40, 2, "IN DANH SACH LOP", 143);
							veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",95);
							break;
						}
					case 2:
						{
							veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",143);
							veNutMenu(3,30,110,2,"QUAN LY MON HOC",95);
							break;
						}
					case 3:
						{
							veNutMenu(3,30,110,2,"QUAN LY MON HOC",143);
							veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",95);
							break;
						}
					case 4:
						{
							veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",143);
							veNutMenu(3,30,180,2,"DANH SACH DIEM",95);
							break;
						}	
				}
				choose ++;
			}
		}
		if (s == ENTER)
		{
			return choose;
		}
		batPhim(s,sCheck);
	}
	return -1;
}

void ThiTracNghiem(dslop &dsl, dssv &ds, DSMH &dsm, NODECH &dsch, int arr1[], int arr2[])
{	
	fullscreen();
	SetScreenBufferSize(251, 53); // An thanh Scrollbar
	string masv;
	DocFileCauHoi(dsch,arr1,arr2);
	DocFileDSLop(dsl);
	DocFileDSMH(dsm);
	int idEnd;
	while(1)
	{
		HienConTro();
		switch(DangNhap(dsl,masv))
		{
		case 0:
			{
				system("cls");
				int tg = 0;
				int sct = 0;
				string monthi;
				bool check;
				NhapMonThiNew(dsm, tg, sct, monthi, check);// return tg, sct, monthi, check
				if(check == false)
				{
					break;
				}
				//THI
				int sch = countNode(dsch);
				if (sct > sch)
				{
					Message(130, 30, "So cau hoi khong du!");
					AnConTro();
					Sleep(1500);
					DeleteMessage(130, 30);
					break;
				}
				string diem;
				CTdethi ctdt;
				ctdt.bode = new int [sct];
				ctdt.dapan = new int [sct];
				
				THI(dsch,tg,sct,monthi,diem,ctdt);
				stop = 1; 
				if(ctdt.bode != NULL)
				{
					
					float diemthi = StringToFloat(diem);
					cout << diem << " " << stop;
					nodeSV *sv;
					for(int i = 0; i < dsl.solop; i++)
					{
						sv = search_SV(dsl.l[i]->danhsach,masv);
						if(sv == NULL)
						{
							continue;
						}
						else
						{
							break;
						}
					}
					cout << sv->info.MASV;
					diemThi diemsv;
					diemsv.ctdt = ctdt;
					diemsv.DIEM = diemthi;
					diemsv.MAMH = monthi;
					if (sv->info.diem.First == NULL) 
					{
						Insert_Diem_First(sv->info.diem.First,diemsv);
					}
					else 
					{
						nodediemThi *p = sv->info.diem.First;
						while (p->pNext != NULL)
						{
							p = p->pNext;
						}
						Insert_Diem_after(p, diemsv);
					}
				}
				else break;
				system("cls");
				break;
			}
		case 1:
			{
				system("cls");
				bool check = true;
				while(check != false)
				{
					switch(MenuGV())
					{
						case 0: //LOP
						{
							QUANLYLOPHOC(dsl);
							break;
						}
						case 1:	//IN DANH SACH LOP
						{
							system("cls");
							int page = 0;
							INSINHVIEN(dsl, page);
							break;
						}
						case 2: //SINH VIEN
						{
							QUANLYSINHVIEN(dsl);
							break;
						}
						case 3://MON HOC
						{
							
							QUANLYMONHOC(dsm, dsl, dsch);
							break;
						}
						case 4://CAU HOI
						{
							QUANLYCAUHOI(dsch, dsm, dsl, idEnd, arr1, arr2);
							break;
						}	
						case 5://DIEM
						{
							system("cls");
							QUANLYDIEM(dsl,ds,dsm,dsch);
							break;	
						}
						case 6:
						{
							system("cls");
							break;
						}	
						case -1://THOAT
						{
							check = false;
							break;
						}
					}
				}
				break;
			}
		case 2:
			{
				AnConTro();
				Message(120, 40, "TAI KHOAN HOAC MAT KHU KHONG DUNG");
				Sleep(500);
				DeleteMessage(120, 40);
				HienConTro();
				break;
			}	
		case -1:
			{
					GhiFileDSlop(dsl,"InputLop.txt",dsch);
					GhiFileDSMon(dsm,"InputMonHoc.txt");
					GhiFileCH(dsch,"InputCauHoiThi.txt",idEnd);
					system("cls");
					return;
			}
		}
			
	}
}
#endif	

