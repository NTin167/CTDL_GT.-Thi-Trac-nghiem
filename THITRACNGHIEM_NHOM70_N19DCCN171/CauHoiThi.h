#ifndef _CAUHOITHI_H
#define _CAUHOITHI_H
#include<iostream>
#include<string.h>
#include<fstream>
#include<time.h>
#include <sstream>
#include"struct.h"
#include"mylib.h"
#include"Thi.h"
#include"MonHoc.h"
void KhoiTaoCH(NODECH &root)
{
	root = NULL;
}

NODECH NewNode(void)
{
	NODECH p;
	p = new nodecauHoi;
	return p;
}
// -XOA CAU HOI TRUONG HOP3 
void remove_case_3(NODECH &r, NODECH &rp) // nut p can xoa co 2 cay con
{
	if(r->pLeft != NULL)
	{
		remove_case_3(r->pLeft, rp);
	}
	//den day r la nut cuc trai cua cay con ben phai co nut goc la rp
	else
	{
		rp->id = r->id;
		rp->info = r->info; //Chep noi dung cua r sang rp ";
		rp = r;  			//  de lat nua delete(rp)
		r = rp->pRight;
	}
}
// XOA 1 CAU HOI THI
void remove(int x, NODECH &p)
{
	NODECH rp;
	if(p == NULL)
		cout <<"Khong tim thay!";
		// node CH NULL;
	else
	{
		if(x< p->id)
			remove(x, p->pLeft); //de qui den node can xoa
		else
		{
			if(x > p->id)
				remove(x, p->pRight);
			else //p->id = x
			{
				rp = p;
				if(rp->pRight == NULL)
					p = rp->pLeft;
				// p la node la hoac node chi co ca con ben trai
				else
				{
					if(rp->pLeft == NULL)
						p = rp->pRight;// p la node co node con ben phai
					else 
						remove_case_3(rp->pRight, rp);
				}
				delete rp;
			}
		}
	}
}
// - INSERT NODE CHT
void Insert_node(NODECH &p, int x, cauHoi a)
{
	if(x == -1)
		return;
	if(p == NULL)
	{
		p = new nodecauHoi;
		p->id = x;
		p->info = a;
		p->pLeft = NULL;
		p->pRight = NULL;
	}
	else
	{
		if(x < p->id)
			Insert_node(p->pLeft, x , a);
		else if(x > p->id)
			Insert_node(p->pRight, x, a);
	}
}
//  TIM KIEM CAU HOI THI DUA THEO KEY LA ID
NODECH Search_CH(NODECH p, int id)
{
	while(p!= NULL && p->id !=id)
		if(id < p->id)
			p = p->pLeft;
		else
			p = p->pRight;
	return p;
}
// DEM CAU HOI THI		
int countNode(NODECH root)   // LNR
{
	NODECH Stack[STACKSIZE];
	NODECH p = root;
	int i = 0;
	int sp = -1; // Stack rong
	do
	{
		while (p != NULL)
		{
			Stack[++sp] = p;
			p = p->pLeft;
		}
		if (sp != -1)
		{
			p = Stack[sp--];
			++i;
			p = p->pRight;
		}
		else 
			break;
	} while (1);
	return i;
}	

// DOC FILE CAU HOI 
void DocFileCauHoi (NODECH &tree, int arr1[], int arr2[])
{														
	ifstream fileIn;
	fileIn.open("InputCauHoiThi.txt", ios_base :: in );
	if(fileIn.fail()) 
		cout << "Failed to open this file!";
	cauHoi ch;
	while(!fileIn.eof())
	{
		int id;
		string temp;
		getline(fileIn,temp,'\n');
		id = StringToInt(temp); 
		getline(fileIn,ch.MAMH,'\n');
		getline(fileIn,ch.NOIDUNG,'\n');
		getline(fileIn,ch.A,'\n');
		getline(fileIn,ch.B,'\n');
		getline(fileIn,ch.C,'\n');
		getline(fileIn,ch.D,'\n');
		getline(fileIn,ch.DAPAN,'\n');
		Insert_node(tree,id,ch);
	}
	fileIn.close();
}

// -KIEM TRA ID CAU HOI THI
bool Inorder(NODECH p, int x) // Duyet LNR
{
	NODECH q;
	p = q;
	if(p != NULL)
	{
		if(p->id == x)
			return false;
	if(Inorder(p->pLeft, x) == false) return false;
	if(Inorder(p->pRight, x) == false) return false;
	}
	return true;
}


// TAO MANG RANDOM
void createArray (int arr[], int min, int max)
{
	for(int i = min; i <= max ; i++)
	{
		if(min == 1 )
		{
			arr[i-1] = i;	
		}
		else if (min == 5001)
		{
			arr[i-5000-1] = i;
		}
	}
}
//RANDOM MOT SO
int random(int minN, int maxN)
{
	srand((int)time(0));
    return minN + rand() % (maxN + 1 - minN);
}

//random 1 so tu 0 toi 4998-sch
//RANDOM MANG
int rdMang (int arr[], int sch)
{
	int x = random(0,4998-sch);
	swap(arr[x],arr[4998-sch]);
	return arr[4998-sch];
}

//- THEM MOT CAU HOI
/*TIM PHUONG PHAP TOI UU RANDOM:
	NGAU NHIEN 
	KHONG TRUNG
	PHU HOP VOI ID CAU HOI*/
void Them1CauHoi(NODECH &tree, cauHoi ch, int maxid, int arr1[], int arr2[])
{
	int x;
	if(tree == NULL)
	{
		x = maxid / 2;
		Insert_node(tree, x, ch);
	}
	else
	{
		// khi sai thi random 1 so 
		if(countNode(tree->pLeft) < countNode(tree->pRight))
		{ 
			int nt = countNode(tree->pLeft);
			x = rdMang(arr1, nt);
		}
		else 
		{
			int np = countNode(tree->pRight);
			x = rdMang(arr2, np);
		}
		Insert_node(tree, x, ch);
	}
}
//IN 1 CAU HOI
void In1CH(NODECH ch, int k)
{
	gotoxy(16,4+k);
	cout << ch->id;
	gotoxy(40,4+k);
	cout << ch->info.MAMH;
	gotoxy(55,4+k);
	if(ch->info.NOIDUNG.length() < 63)
	{
		cout << ch->info.NOIDUNG;
	}
	else
	{
		string temp = ch->info.NOIDUNG.substr(0,63);
		cout << temp << "...";
	}
}

void InDSCH(NODECH root, int page, int *arr[])
{
	int k = 2;
	int maxpage;
	int sl = countNode(root);
	if(sl <= 10)
	{
		maxpage = 0;
	}
	else if (sl % 10 == 0)
	{
		maxpage = sl/10 - 1;
	}
	else maxpage = sl/10;
	for(int j = page*10; (j < (page + 1)*10) && (j<sl);j++)
	{
		NODECH temp = Search_CH(root,*arr[j]);
		In1CH(temp,k);
		k += 3;
	}
	gotoxy(125/2,36);
	cout << "Trang " << page + 1 << "/" << maxpage + 1;
}


//CHECK CH DA THI
bool CheckCHDaThi (dslop dsl, int id)
{
	for(int i = 0; i < dsl.solop; i++)
	{
		for(nodeSV *k = dsl.l[i]->danhsach.First;k != NULL ;k=k->pNext)
		{
			for(nodediemThi *p = k->info.diem.First; p != NULL; p=p->pNext)
			{
				for(int j = 0; j < p->info.ctdt.sct; j++)
				{
					if(p->info.ctdt.bode[j] == id)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

//CHON CAU HOI CAN XOA
void NhapCHXoa(NODECH &dsch,int &page, int *arr[], int&idEnd,dslop dsl)
{
	gotoxy(5, 2);
	vekhungDSCH(34,120,5);
	int maxpage;
	InDSCH(dsch,page,arr);
	char s;
	int state = 0;
	bool sCheck;
	gotoxy(7,6);
	cout << muiten;
	int sl = countNode(dsch);
	batPhim(s,sCheck);
	while (s != ESC)
	{
		if(sl == 0)
		{
			Message(130, 30, "Danh sach cau hoi hien tai dang trong");
			AnConTro();
			Sleep(750);
			DeleteMessage(130, 30);
			break;
		}
		if(sl <= 10)
		{
			maxpage = 0;
		}
		else if(sl % 10 == 0) 
		{
			maxpage = sl/10 -1;
		}
		else maxpage = sl/10;
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
						cout << "                      ";
						gotoxy(54,6+i);
						cout << "                                                                    ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSCH(dsch,page,arr);
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
				if((page + 1) * 10 < sl)
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
							cout << "                      ";
							gotoxy(54,6+i);
							cout << "                                                                    ";
						}
					}
					page++;
					InDSCH(dsch,page,arr);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else 
			{
				if(state + 1 + page  * 10 < sl)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
//				if(state + (page + 1) * 10 < sl)
//				{
//					gotoxy(wherex()-1,wherey());
//					cout << " ";
//					gotoxy(7,wherey());
//					cout << muiten;
//				}
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
						cout << "                      ";
						gotoxy(31,6+i);
						cout << "                      ";
						gotoxy(54,6+i);
						cout << "                                                                    ";
					}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				int hd = wherex();
				int td = wherey();
				InDSCH(dsch,page,arr);
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
						cout << "                      ";
						gotoxy(54,6+i);
						cout << "                                                                    ";
					}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				int hd = wherex();
				int td = wherey();
				InDSCH(dsch,page,arr);
				gotoxy(hd,td);
			}
		}
		if (s == ENTER)
		{
			//neu cau hoi da co thi, khong duoc xoa
			int id = Search_CH(dsch,*arr[state+(page*10)])->id;
			if(CheckCHDaThi(dsl,id) == true)
			{
				Message(130, 30,"Khong the xoa cau hoi da thi");
				Sleep(500);
				DeleteMessage(130, 30);
			}
			else
			{
				Message(130, 30,"Ban co chac chan muon xoa cau hoi nay ? (Y/N)");
				batPhim(s,sCheck);
				while(s != ESC)
				{
					AnConTro();
					if((s == 'y' || s == 'Y')&& sCheck == true)
					{
						int id = Search_CH(dsch,*arr[state+(page*10)])->id;
						remove(id,dsch);
						for(int i = state + page*10; i < sl - 1; i++)
						{
							*arr[i] = *arr[i+1];	
						}
						sl--;
						if(sl > 0)
						{
							idEnd = *arr[sl-1];	
						}
						DeleteMessage(130, 30);
						Message(130, 30, "Xoa cau hoi thanh cong");
						Sleep(750);
						AnConTro();
						DeleteMessage(130, 30);
						if( sl % 10 == 0 && page > 0)
						{
							page--;
						}
						break;
					}
					else if((s == 'n' || s == 'N') && sCheck == true)
					{
						DeleteMessage(130, 30);
						break;
					}
					batPhim(s,sCheck);
				}
				DeleteMessage(130, 30);
			}
			for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                      ";
						gotoxy(31,6+i);
						cout << "                      ";
						gotoxy(54,6+i);
						cout << "                                                                    ";
					}
			if(sl == 0)
			{
				Message(130, 30,"Danh sach cau hoi hien tai dang trong");
				AnConTro();
				Sleep(750);
				DeleteMessage(130, 30);
				break;
			}
			int hd = wherex();
			int td = wherey();
			InDSCH(dsch,page,arr);
			state = 0;
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
//XOA MON HOC
void XoaCauHoi (NODECH &dsch, int *arr[], int &idEnd,dslop dsl)
{
	int page = 0;
	int sl = countNode(dsch);
	if(sl == 0)
	{
		Message(130, 30,"Danh sach cau hoi hien tai dang trong");
		AnConTro();
		Sleep(750);
		DeleteMessage(130, 30);
	}
	else
	{
		NhapCHXoa(dsch,page,arr,idEnd,dsl);
	}
} 

// NHAP CAU HOI THEM 
void NhapCHThem(NODECH &dsch,monHoc *mh, int *arr[], int arr1[], int arr2[])
{
	system("cls");
	gotoxy(5+(125 - mh->TENMH.length())/2,1);
	cout << mh->TENMH;
	vekhungThemCHNew();
	cauHoi ch;
	int state = 0;
	int n;
	int dem;
	int maxid = 10000;
	string temp;
	char s;
	bool sCheck;
	gotoxy(50,8);

	int hdnd,tdnd,hda,tda,hdb,tdb,hdc,tdc,hdd,tdd;
	hdnd = 50;
	tdnd = 8;
	hda = 50;
	tda = 15;
	hdb = 50;
	tdb = 21;
	hdc = 50;
	tdc = 27;
	hdd = 50;
	tdd = 33;
	HienConTro();
	batPhim(s,sCheck);
	while(1)
	{
		if(s == ESC)
		{
			if(Exit(s,sCheck,70,45) == true)
			{
				break;
			}
			else
			{
				switch(state)
				{
					case 0:
						{
							HienConTro();
							gotoxy(hdnd,tdnd);
							break;
						}
					case 1:
						{
							HienConTro();
							gotoxy(hda,tda);
							break;
						}
					case 2:
						{
							HienConTro();
							gotoxy(hdb,tdb);
							break;
						}
					case 3:
						{
							HienConTro();
							gotoxy(hdc,tdc);
							break;
						}
					case 4:
						{
							HienConTro();
							gotoxy(hdd,tdd);
							break;
						}
					case 5:
						{
							veNutMenu(3,11,105,39,"LUU",120);
							HienConTro();
							gotoxy(hdd,tdd);
							state = 4;
							break;
							
						}	
				}
				HienConTro();
				batPhim(s,sCheck);
			}
		}
		if(s == UP && sCheck == false)
		{
			if(state > 0)
			{
				switch(state)
				{
					case 1:
						{
							HienConTro();
							gotoxy(hdnd,tdnd);
							state--;
							break;
						}
					case 2:
						{
							HienConTro();
							gotoxy(hda,tda);
							state--;
							break;
						}
					case 3:
						{
							HienConTro();
							gotoxy(hdb,tdb);
							state--;
							break;
						}
					case 4:
						{
							HienConTro();
							gotoxy(hdc,tdc);
							state--;
							break;
						}
					case 5:
						{
							veNutMenu(3,11,105,39,"LUU",128);
							HienConTro();
							gotoxy(hdd,tdd);
							state--;
							break;
						}	
				}
			}
		}
		if(s == DOWN && sCheck == false)
		{
			if(state < 5)
			{
				switch(state)
				{
					case 0:
						{
							HienConTro();
							gotoxy(hda,tda);
							state ++;
							break;
						}
					case 1:
						{
							HienConTro();
							gotoxy(hdb,tdb);
							state ++;
							break;
						}
					case 2:
						{
							HienConTro();
							gotoxy(hdc,tdc);
							state ++;
							break;
						}
					case 3:
						{
							HienConTro();
							gotoxy(hdd,tdd);
							state ++;
							break;
						}
					case 4:
						{
							
							veNutMenu(3,11,105,39,"LUU",120);
							AnConTro();
							state ++;
							break;
						}	
				}
			}
		}
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9') || (s == '?') || (s == ','))  && sCheck == true)
		{
			HienConTro();
			switch(state)
			{
				case 0:
					{
						if(ch.NOIDUNG.length() < 330)
						{
							if(wherex() == 160 && wherey() == 8 )
							{
								n = ch.NOIDUNG.length()-1;
								temp = "";
								if(ch.NOIDUNG[n] == ' ')
								{
									gotoxy(50,8);
									cout << InHoa(s);
									ch.NOIDUNG += InHoa(s);
								}
								else
								{
									while(ch.NOIDUNG[n] != ' ')
									{
										temp += ch.NOIDUNG[n];
										gotoxy(wherex()-1,wherey());
										cout << " ";
										gotoxy(wherex()-1,wherey());
										n--;
										dem = n;
									}
									dem++;
									temp = DaoChuoi(temp);
									gotoxy(50,9);
									cout << temp;
									cout << InHoa(s);
									ch.NOIDUNG += InHoa(s);
								}
							}
							else if (wherex() == 160 && wherey() == 9)
							{
								n = ch.NOIDUNG.length()-1;
								temp = "";
								if(ch.NOIDUNG[n] == ' ')
								{
									gotoxy(50,9);
									cout << InHoa(s);
									ch.NOIDUNG += InHoa(s);
								}
								else
								{
									while(ch.NOIDUNG[n] != ' ')
									{
										temp += ch.NOIDUNG[n];
										gotoxy(wherex()-1,wherey());
										cout << " ";
										gotoxy(wherex()-1,wherey());
										n--;
									}
									temp = DaoChuoi(temp);
									gotoxy(50,10);
									cout << temp;
									cout << InHoa(s);
									ch.NOIDUNG += InHoa(s);
								}
							}
							else
							{
								cout << InHoa(s);
								ch.NOIDUNG += InHoa(s);
							}
						}
						hdnd = wherex();
						tdnd = wherey();
						break;
					}
				case 1:	
					{
						if(ch.A.length() < 110)
						{						
								cout << InHoa(s);
								ch.A += InHoa(s);
						}
						hda = wherex();
						tda = wherey();
						break;
					}
				case 2:
					{
						if(ch.B.length() < 110)
						{
								cout << InHoa(s);
								ch.B += InHoa(s);
						}
						hdb = wherex();
						tdb = wherey();
						break;
					}
				case 3:
					{
						if(ch.C.length() < 110)
						{
							cout << InHoa(s);
							ch.C += InHoa(s);
						}
						hdc = wherex();
						tdc = wherey();
						break;
					}
				case 4:
					{
						if(ch.D.length() < 110)
						{
							cout << InHoa(s);
							ch.D += InHoa(s);	
						}
						hdd = wherex();
						tdd = wherey();
						break;
					}
								
			}
		}
		if(s == ' ')
		{
			switch(state)
				{
					case 0:
						{
							if(ch.NOIDUNG.length() == 0)
							{
								gotoxy(50+ch.NOIDUNG.length()-1,8);
							}
							if(ch.NOIDUNG[ch.NOIDUNG.length()-1]!= ' ')
							{
								cout << InHoa(s);
								ch.NOIDUNG += InHoa(s);	
							}
							if(wherex() == 160 || wherex() == 161 || wherex() == 162)
							{
								if(wherey() == 8)
								{
									dem = wherex() - 20;
									gotoxy(50,9);
									cout << InHoa(s);
									ch.NOIDUNG += InHoa(s);
								}
								else if(wherey() == 9)
								{
									gotoxy(50,10);
									cout << InHoa(s);
									ch.NOIDUNG += InHoa(s);
								}									
							}
							hdnd = wherex();
							tdnd = wherey();
							break;	
						}
					case 1:
						{
							if(ch.A.length() == 0)
							{
								gotoxy(50+ch.A.length()-1,15);
							}
							if(ch.A[ch.A.length()-1]!= ' ')
							{
								cout << InHoa(s);
								ch.A += InHoa(s);	
							}
							hda = wherex();
							tda = wherey();
							break;	
						}
					case 2:
						{
							if(ch.B.length() == 0)
							{
								gotoxy(50+ch.B.length()-1,21);
							}
							if(ch.B[ch.B.length()-1]!= ' ')
							{
								cout << InHoa(s);
								ch.B += InHoa(s);	
							}
							hdb = wherex();
							tdb = wherey();
							break;	
						}
					case 3:
						{
							if(ch.C.length() == 0)
							{
								gotoxy(50+ch.C.length()-1,27);
							}
							if(ch.C[ch.C.length()-1]!= ' ')
							{
								cout << InHoa(s);
								ch.C += InHoa(s);	
							}
							hdc = wherex();
							tdc = wherey();
							break;	
						}
					case 4:
						{
							if(ch.D.length() == 0)
							{
								gotoxy(50+ch.D.length()-1,33);
							}
							if(ch.D[ch.D.length()-1]!= ' ')
							{
								cout << InHoa(s);
								ch.D += InHoa(s);	
							}
							hdd = wherex();
							tdd = wherey();
							break;	
						}				
				}
		}
		if (s == BACKSPACE)
		{
			switch(state)
			{
				case 0:
					{
						if (ch.NOIDUNG.length() > 0)
						{
							if(wherex() == 50 && wherey() == 9)
							{
								gotoxy(50 + ch.NOIDUNG.length(),8);
								hdnd = wherex();
								tdnd = wherey();
							}
							else if(wherex() == 50 && wherey() == 9)
							{
								gotoxy(50 + ch.NOIDUNG.length() - dem,10);
								hdnd = wherex();
								tdnd = wherey();
							}
							else
							{
								AnConTro();
								gotoxy(wherex()-1,wherey());
								cout << " ";
								gotoxy(wherex()-1,wherey());
								HienConTro();
								ch.NOIDUNG.erase(ch.NOIDUNG.length()-1);
								hdnd = wherex();
								tdnd = wherey();
							}
						}
						break;
					}
				case 1:
					{
						if (ch.A.length() > 0)
						{
							if(wherex() == 50)
							{
								gotoxy(50 + ch.A.length(),15);
								hda = wherex();
								tda = wherey();
							}
							else
							{
								AnConTro();
								gotoxy(wherex()-1,wherey());
								cout << " ";
								gotoxy(wherex()-1,wherey());
								HienConTro();
								ch.A.erase(ch.A.length()-1);
								hda = wherex();
								tda = wherey();
							}
						}
						break;
					}
				case 2:
					{
						if (ch.B.length() > 0)
						{
							if(wherex() == 50)
							{
								gotoxy(50 + ch.B.length(),21);
								hdb = wherex();
								tdb = wherey();
							}
							else
							{
								AnConTro();
								gotoxy(wherex()-1,wherey());
								cout << " ";
								gotoxy(wherex()-1,wherey());
								HienConTro();
								ch.B.erase(ch.B.length()-1);
								hdb = wherex();
								tdb = wherey();
							}
						}
						break;
					}
				case 3:
					{
						if (ch.C.length() > 0)
						{
							if(wherex() == 50)
							{
								gotoxy(50 + ch.C.length(),27);
								hdc = wherex();
								tdc = wherey();
							}
							else
							{
								AnConTro();
								gotoxy(wherex()-1,wherey());
								cout << " ";
								gotoxy(wherex()-1,wherey());
								HienConTro();
								ch.C.erase(ch.C.length()-1);
								hdc = wherex();
								tdc = wherey();
							}
						}
						break;					
					}
				case 4:
					{
						
						if (ch.D.length() > 0)
						{
							if(wherex() == 20)
							{
								gotoxy(50 + ch.D.length(),33);
								hdd = wherex();
								tdd = wherey();
							}
							else
							{
								AnConTro();
								gotoxy(wherex()-1,wherey());
								cout << " ";
								gotoxy(wherex()-1,wherey());
								HienConTro();
								ch.D.erase(ch.D.length()-1);
								hdd = wherex();
								tdd = wherey();
							}
						}
						break;
					}		
			}
		}
		if ( s == ENTER)
		{
			if(state == 5)
			{
				if(ch.NOIDUNG.length() == 0 || ch.A.length() == 0 || ch.B.length() == 0 || ch.C.length() == 0 || ch.D.length() == 0)
				{
					Message(50, 45, "Vui long nhap day du thong tin");
					AnConTro();
					Sleep(750);
					DeleteMessage(50, 45);
				}
				else
				{
					int state1 = 0;
					string da = "A";
					veNutMenu(1, 40, 45, 13, "A", 192);
					batPhim(s,sCheck);
					while(1)
					{
						if(s == UP && sCheck == false)
						{
							switch(state1)
							{
								case 1:
									{
										gotoxy(wherex()-1,wherey());
										veNutMenu(1, 40, 45, 13, "A", 192);
										veNutMenu(1, 40, 45, 19, "B", 128);
										veNutMenu(1, 40, 45, 25, "C", 128);
										veNutMenu(1, 40, 45, 31, "D", 128);
										state1--;
										da = "A";
										break;
									}
								case 2:
									{
										gotoxy(wherex()-1,wherey());
										veNutMenu(1, 40, 45, 13, "A", 128);
										veNutMenu(1, 40, 45, 19, "B", 192);
										veNutMenu(1, 40, 45, 25, "C", 128);
										veNutMenu(1, 40, 45, 31, "D", 128);
										state1--;
										da = "B";
										break;
									}
								case 3:
									{
										gotoxy(wherex()-1,wherey());
										veNutMenu(1, 40, 45, 13, "A", 128);
										veNutMenu(1, 40, 45, 19, "B", 128);
										veNutMenu(1, 40, 45, 25, "C", 192);
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
										gotoxy(wherex()-1,wherey());
										veNutMenu(1, 40, 45, 13, "A", 128);
										veNutMenu(1, 40, 45, 19, "B", 192);
										veNutMenu(1, 40, 45, 25, "C", 128);
										veNutMenu(1, 40, 45, 31, "D", 128);
										state1++;
										da = "B";
										break;
									}
								case 1:
									{
										gotoxy(wherex()-1,wherey());
										veNutMenu(1, 40, 45, 13, "A", 128);
										veNutMenu(1, 40, 45, 19, "B", 128);
										veNutMenu(1, 40, 45, 25, "C", 192);
										veNutMenu(1, 40, 45, 31, "D", 128);
										state1++;
										da = "C";
										break;
									}
								case 2:
									{
										gotoxy(wherex()-1,wherey());
										veNutMenu(1, 40, 45, 13, "A", 128);
										veNutMenu(1, 40, 45, 19, "B", 128);
										veNutMenu(1, 40, 45, 25, "C", 128);
										veNutMenu(1, 40, 45, 31, "D", 192);
										state1++;
										da = "D";
										break;
									}
							}
						}
						if(s == ENTER)
						{
							ch.MAMH = mh->MAMH;
							ch.DAPAN = da;
							Them1CauHoi(dsch,ch,maxid,arr1,arr2);
							Message(50, 45, "Them cau hoi thanh cong!");
							AnConTro();
							Sleep(750);
							DeleteMessage(50, 45);
							break;
						}
						batPhim(s,sCheck);
					}
				}
				
				veNutMenu(3,11,105,39,"LUU",128);
				ch.NOIDUNG = "";
				ch.A = "";
				ch.B = "";
				ch.C = "";
				ch.D = "";
				state = 0;
				gotoxy(50+ch.NOIDUNG.length(),8);
				HienConTro();
				break;
			}
		}
		batPhim(s,sCheck);
	}
}

//NHAP MA MON HOC THEM CAU HOI
monHoc *NhapMaMHThem (NODECH dsch, DSMH dsm, int *arr [])
{
	system("cls");
	gotoxy(5,2);
	vekhungDS(34,120,2);
	gotoxy(30,3);
	cout << "MA MON HOC";
	gotoxy(90,3);
	cout << "TEN MON HOC";
	int page = 0;
	int maxpage;
	InDSMon(dsm,page, 30, 4);
	string mamon;
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
					InDSMon(dsm,page, 30, 4);
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
					InDSMon(dsm,page,30,4);
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
				InDSMon(dsm,page,30,4);
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
				InDSMon(dsm,page,30,4);
				gotoxy(hd,td);
			}
		}
		if (s == ENTER)
		{
			// chon ma mon, in menu nhap cau hoi them
			return dsm.m[state + page*10];
		}
	batPhim(s,sCheck);
	}
	return NULL;
}
//THEM CAU HOI
void ThemCH(NODECH &dsch, DSMH dsm, int *arr[], int arr1[], int arr2[])
{
	ChangeColor(15);
	int n = countNode(dsch);
	if(n  == 1000)
	{
		Message(130, 30,"Khong the them cau hoi, danh sach cau hoi da day");
		AnConTro();
		Sleep(750);
		DeleteMessage(130,30);
	}
	else
	{
		monHoc *mh = NhapMaMHThem(dsch,dsm,arr);
		if(mh == NULL)
		{
			return;
		}
		//nhap cau hoi
		NhapCHThem(dsch,mh,arr,arr1,arr2);
	}
}
 //XEM CH THEO MON
void XemCHtheoMon (DSMH dsm, NODECH dsch)
{
	system("cls");
	
	int page = 0;
	char s;
	bool sCheck;
	veNutMenu(1, 40, 5, 0, "XEM CAU HOI THEO MON HOC", 96);
	gotoxy(5,2);
	int state = 0;
	vekhungDS(34,120,2);	
	gotoxy(30,3);
	cout << "MA MON HOC";
	gotoxy(90,3);
	cout << "TEN MON HOC";
	if (dsm.somon != 0) 
	{
		InDSMon(dsm,page,30,4);
	}
	int maxpage;
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
					InDSMon(dsm,page,30,4);
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
				InDSMon(dsm,page,30,4);
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
				InDSMon(dsm,page,30,4);
				gotoxy(hd,td);
			}
		}
		if (s == ENTER)
		{
			//vao danh sach cau hoi
			int *arr[10000];
			int dem=0;
			NODECH Stack[STACKSIZE];
			NODECH p = dsch;
			int sp = -1;
			do //duyet cay LNR
			{ 
				while (p != NULL)
				{
					Stack[++sp]= p;
					p = p->pLeft;
				}
				if (sp != -1)
				{
					p = Stack[sp--];
					//in vao danh sach ch
					if(p->info.MAMH.compare(dsm.m[state + page*10]->MAMH) == 0)
					{
						arr[dem] = new int;
						*arr[dem] = p->id;
						dem++;
					}
					p = p->pRight;
				}
				else break;
			} while (1);
			if(dem == 0)
			{
				Message(50, 45,"Danh sach cau hoi hien tai dang trong!");
				AnConTro();
				Sleep(750);
				DeleteMessage(50, 45);
			}
			else 
			{
				system("cls");
				int index = 0;
//				batPhim(s,sCheck);
				while (s != ESC)
				{
					if(s == LEFT && sCheck == false)
					{
						if(index > 0)
						{
							index--;
							for(int i = 0; i < 30;i++)
							{
								gotoxy(20,5+i);
								if(i == 4) i = 8;
								if (i == 11) i = 14;
								if (i == 17) i = 20;
								if (i == 23) i = 26;
								cout << "                                                                                                  ";
							}
							NODECH ch = Search_CH(dsch,*arr[index]);
							
							veNutMenu(1, 10, 10, 5, "MA MON:", 160);
							gotoxy(21, 5);
							cout << ch->info.MAMH;
							
							veNutMenu(1, 10, 10, 7, "ID", 160);
							gotoxy(21,7);
							cout << ch->id;
							
							gotoxy(5,2);
							vekhungThemCHNew();
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
							if(ch->info.DAPAN == "A")
							{
								veNutMenu(1, 40, 45, 13, "A", 64);
								veNutMenu(1, 40, 45, 19, "B", 128);
								veNutMenu(1, 40, 45, 25, "C", 128);
								veNutMenu(1, 40, 45, 31, "D", 128);	
							}
							else if(ch->info.DAPAN == "B")
							{
								veNutMenu(1, 40, 45, 13, "A", 128);
								veNutMenu(1, 40, 45, 19, "B", 64);
								veNutMenu(1, 40, 45, 25, "C", 128);
								veNutMenu(1, 40, 45, 31, "D", 128);	
							}
							else if(ch->info.DAPAN == "C")
							{
								veNutMenu(1, 40, 45, 13, "A", 128);
								veNutMenu(1, 40, 45, 19, "B", 128);
								veNutMenu(1, 40, 45, 25, "C", 64);
								veNutMenu(1, 40, 45, 31, "D", 128);	
							}
							else if(ch->info.DAPAN == "D")
							{
								veNutMenu(1, 40, 45, 13, "A", 128);
								veNutMenu(1, 40, 45, 19, "B", 128);
								veNutMenu(1, 40, 45, 25, "C", 128);
								veNutMenu(1, 40, 45, 31, "D", 64);	
							}
						}
						
					}
					if(s == RIGHT && sCheck == false)
					{
						if(index < dem - 1)
						{
							index++;
							for(int i = 0; i < 30;i++)
							{
								gotoxy(20,5+i);
								if(i == 4) i = 8;
								if (i == 11) i = 14;
								if (i == 17) i = 20;
								if (i == 23) i = 26;
								cout << "                                                                                                  ";
							}
							NODECH ch = Search_CH(dsch,*arr[index]);
							veNutMenu(1, 10, 10, 5, "MA MON:", 160);
							gotoxy(21, 5);
							cout << ch->info.MAMH;
							
							veNutMenu(1, 10, 10, 7, "ID", 160);
							gotoxy(21,7);
							cout << ch->id;
							
							vekhungThemCHNew();
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
							if(ch->info.DAPAN == "A")
							{
								veNutMenu(1, 40, 45, 13, "A", 64);
								veNutMenu(1, 40, 45, 19, "B", 128);
								veNutMenu(1, 40, 45, 25, "C", 128);
								veNutMenu(1, 40, 45, 31, "D", 128);	
							}
							else if(ch->info.DAPAN == "B")
							{
								veNutMenu(1, 40, 45, 13, "A", 128);
								veNutMenu(1, 40, 45, 19, "B", 64);
								veNutMenu(1, 40, 45, 25, "C", 128);
								veNutMenu(1, 40, 45, 31, "D", 128);	
							}
							else if(ch->info.DAPAN == "C")
							{
								veNutMenu(1, 40, 45, 13, "A", 128);
								veNutMenu(1, 40, 45, 19, "B", 128);
								veNutMenu(1, 40, 45, 25, "C", 64);
								veNutMenu(1, 40, 45, 31, "D", 128);	
							}
							else if(ch->info.DAPAN == "D")
							{
								veNutMenu(1, 40, 45, 13, "A", 128);
								veNutMenu(1, 40, 45, 19, "B", 128);
								veNutMenu(1, 40, 45, 25, "C", 128);
								veNutMenu(1, 40, 45, 31, "D", 64);	
							}
						}
					}
					if(s == ENTER)
					{
						NODECH ch = Search_CH(dsch,*arr[index]);
						veNutMenu(1, 10, 10, 5, "MA MON:", 160);
						gotoxy(21, 5);
						cout << ch->info.MAMH;
						
						veNutMenu(1, 10, 10, 7, "ID", 160);
						gotoxy(21,7);
						cout << ch->id;
						vekhungThemCHNew();
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
						if(ch->info.DAPAN == "A")
						{
							veNutMenu(1, 40, 45, 13, "A", 64);
							veNutMenu(1, 40, 45, 19, "B", 128);
							veNutMenu(1, 40, 45, 25, "C", 128);
							veNutMenu(1, 40, 45, 31, "D", 128);
						}
						else if(ch->info.DAPAN == "B")
						{
							veNutMenu(1, 40, 45, 13, "A", 128);
							veNutMenu(1, 40, 45, 19, "B", 64);
							veNutMenu(1, 40, 45, 25, "C", 128);
							veNutMenu(1, 40, 45, 31, "D", 128);
						}
						else if(ch->info.DAPAN == "C")
						{
							veNutMenu(1, 40, 45, 13, "A", 128);
							veNutMenu(1, 40, 45, 19, "B", 128);
							veNutMenu(1, 40, 45, 25, "C", 64);
							veNutMenu(1, 40, 45, 31, "D", 128);
						}
						else if(ch->info.DAPAN == "D")
						{
							veNutMenu(1, 40, 45, 13, "A", 128);
							veNutMenu(1, 40, 45, 19, "B", 128);
							veNutMenu(1, 40, 45, 25, "C", 128);
							veNutMenu(1, 40, 45, 31, "D", 64);
						}
					}
					batPhim(s,sCheck);
				}
				//ve lai
				system("cls");
				
				int page = 0;
				char s;
				bool sCheck;
				gotoxy(5,2);
				int state = 0;
				vekhungDS(34,120,2);	
				gotoxy(30,3);
				cout << "MA MON HOC";
				gotoxy(90,3);
				cout << "TEN MON HOC";
			}
			for(int i = 0; i < 10; i++)
			{
				gotoxy(7,6+i*3);
				cout << " ";
			}
			InDSMon(dsm,page,30,4);
			state = 0;
			gotoxy(7,6);
			cout << muiten;	
		}
	batPhim(s,sCheck);
	}
	
}

void QUANLYCAUHOI(NODECH &dsch, DSMH dsm, dslop dsl, int &idEnd, int arr1[], int arr2[])
{
	int page = 0;
	char s;
	bool sCheck;
	int state = 0;
	veNutMenu(3, 30, 145, 6, "Them", 90);
	veNutMenu(3, 30, 145, 10, "Xoa", 176);
	veNutMenu(3, 30, 145, 14, "Xem CH", 176);
	
	int sl = countNode(dsch);
	int *arr [sl];
	for(int i = 0; i < sl; i++)
	{
		arr[i] = new int;
	}
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
			//in vao danh sach ch
			*arr[i] = p->id;
			i++;
			p = p->pRight;
		}
		else break;
	} while (1);
	if(sl > 0)
	{
		idEnd = *arr[sl-1];	
	}
	
	
	
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
						veNutMenu(3, 30, 145, 6, "Them", 90);
						veNutMenu(3, 30, 145, 10, "Xoa", 176);
						break;
					}
				case 2:
					{
						state--;
						veNutMenu(3, 30, 145, 10, "Xoa", 90);
						veNutMenu(3, 30, 145, 14, "Xem CH", 176);
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
						veNutMenu(3, 30, 145, 6, "Them", 176);
						veNutMenu(3, 30, 145, 10, "Xoa", 90);
						break;
					}
				case 1:
					{
						state++;
						veNutMenu(3, 30, 145, 10, "Xoa", 176);
						veNutMenu(3, 30, 145, 14, "Xem CH", 90);
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
						ThemCH(dsch, dsm, arr, arr1, arr2); 
						int sl = countNode(dsch);
						for(int i = 0; i < sl; i++)
						{
							arr[i] = new int;
						}
						int i=0;
						NODECH Stack[STACKSIZE]; // LNR 
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
								//in vao danh sach ch
								*arr[i] = p->id;
								i++;
								p = p->pRight;
							}
							else break;
						} while (1);
						idEnd = *arr[sl-1];
						system("cls");
						AnConTro();
						veNutMenu(3,30,2,2,"QUAN LY LOP HOC",128);
						veNutMenu(3,30,40,2,"IN DANH SACH LOP", 128);
						veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",128);
						veNutMenu(3,30,110,2,"QUAN LY MON HOC",128);
						veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",95);
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
						veNutMenu(3, 30, 145, 6, "Them", 90);
						veNutMenu(3, 30, 145, 10, "Xoa", 176);
						veNutMenu(3, 30, 145, 14, "Xem CH", 176);
						break;
					}
				case 1:
					{
						system("cls");
						XoaCauHoi(dsch, arr, idEnd, dsl);
						AnConTro();
						system("cls");
						veNutMenu(3,30,2,2,"QUAN LY LOP HOC",128);
						veNutMenu(3,30,40,2,"IN DANH SACH LOP", 128);
						veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",128);
						veNutMenu(3,30,110,2,"QUAN LY MON HOC",128);
						veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",95);
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
						veNutMenu(3, 30, 145, 10, "Xoa", 90);
						veNutMenu(3, 30, 145, 14, "Xem CH", 176);
						break;
					}
				case 2:
					{
						system("cls");
						XemCHtheoMon(dsm, dsch);
						system("cls");
						veNutMenu(3,30,2,2,"QUAN LY LOP HOC",128);
						veNutMenu(3,30,40,2,"IN DANH SACH LOP", 128);
						veNutMenu(3,30,75,2,"QUAN LY SINH VIEN",128);
						veNutMenu(3,30,110,2,"QUAN LY MON HOC",128);
						veNutMenu(3,30,145,2,"QUAN LY CAU HOI THI",95);
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
						veNutMenu(3, 30, 145, 14, "Xem CH", 90);
						break;
					}
			}
		}
		batPhim(s, sCheck);
	}
}


//LUU FILE CAU HOI
void GhiFileCH(NODECH root, string filename, int idEnd) // NLR
{
	NODECH q;
	ofstream fileOut;
	fileOut.open(filename.c_str(), ios_base::out);
	if (!fileOut.is_open())
	{
		cout << "khong mo duoc";
		return;
	}
	else
	{
		if(countNode(root) == 0)
		{
			return;		
		}
		NODECH Stack[STACKSIZE];
		int sp= -1; // Khoi tao Stack rong
		NODECH p = root;
		while (p != NULL )
		{
			if(p->id == idEnd)
			{
				fileOut << p->id << endl;
				fileOut << p->info.MAMH << endl;
				fileOut << p->info.NOIDUNG << endl;
				fileOut << p->info.A << endl;
				fileOut << p->info.B << endl;
				fileOut << p->info.C << endl;
				fileOut << p->info.D << endl;
				fileOut << p->info.DAPAN;
				break;
			}
			fileOut << p->id << endl;
			fileOut << p->info.MAMH << endl;
			fileOut << p->info.NOIDUNG << endl;
			fileOut << p->info.A << endl;
			fileOut << p->info.B << endl;
			fileOut << p->info.C << endl;
			fileOut << p->info.D << endl;
			fileOut << p->info.DAPAN << endl;
			if (p->pRight != NULL)
			{
				Stack[++sp]= p->pRight;	
			}
			if (p->pLeft != NULL)
			{
				p = p->pLeft;	
			}
			else if (sp == -1)
			{
				break;	
			}
			else
			{
				p = Stack[sp--];	
			}
		}
	}
	fileOut.close();
	return ;
}

#endif
