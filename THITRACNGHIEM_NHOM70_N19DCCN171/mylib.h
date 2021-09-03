#ifndef _MYLIB_H
#define _MYLIB_H



#include<iostream>
#include<conio.h>
#include<windows.h>
#include<math.h>
#include<ctime>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define BACKSPACE 8
#define TAB 9
#define SPACE 32
#define ESC 27
#define PAGEUP 73
#define PAGEDOWN 81
#define F1 59


#define doc (char)179
#define ngang (char)196
#define traitren (char)218
#define phaitren (char)191
#define traiduoi (char)192
#define phaiduoi (char)217
#define docphai (char)195
#define doctrai (char)180
#define ngangxuong (char)194
#define nganglen (char) 193
#define giua (char) 197
#define muiten (char) 16
#define muitenlen (char) 94


#define doc1 (char)186 // ||
#define ngang1 (char)205

#define trenphai (char)187
#define duoiphai (char)188

#define trentrai (char)201
#define duoitrai (char)200

#define giua1 (char)206


#define cattrai (char)204// doc phai la cat trai
#define catphai (char)185
#define catgiua (char)206

#define ngangxuong1 (char)203
#define nganglen1 (char) 202



using namespace std;
//Fullscreen
void fullscreen()
{
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

void SetScreenBufferSize(SHORT width, SHORT height)// SET SCREEN BUFFER SIZE  bang voi window size nen thanh cuon (ScrollBar) bien mat
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(hStdout, NewSize);
}

void batPhim(char &s, bool &Check)   
{
	s = getch();
	if (s==-32 || s == 0)
	{
		s = getch();
		Check = false;   //bat cac phim ASCII 2 LEFT RIGHT UP DOWM
	}
	else
	{
		Check = true;
	}
}

void gotoxy(int x, int y) // Di chuyen toa do con tro trong he toa do De-cat
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}


void TextColor(int x)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h,x);
}
//=============================DOI INT==========================
int StringToInt(string x)
{
	if (x.length() == 0)
		return -1;
	int res = 0;
	for (int i = 0; i < x.length(); i++)
	{
		res = res*10 + (int)(x[i] - 48);
	}
	return res;
}
//=============================DOI FLOAT==========================
float StringToFloat (string s)
{
	int i = 0;
	string s1;
	while(s[i] != '.')
	{
		s1.push_back(s[i]);
		i++; 
	}
	float p = StringToInt(s1);
	i++;
	string s2;
	while(i < s.length())
	{
		s2.push_back(s[i]);
		i++;
	}
	float p1 = StringToInt(s2) / pow(10,s2.length());
	p = p + p1;
	return p;
}

int wherex()
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.X;
}
int wherey( void )
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.Y;
}
 //==================== VE KHUNG ==========================
void veKhung(int rong, int dai)
{
	for (int i = 0; i < rong; i++)
	{
		for (int j = 0; j < dai; j++)
		{
			if (i == 0)
			{
				if (j == 0) cout << traitren;
				else if (j == dai-1) cout << phaitren;
				else cout << ngang;
			}
			else if (i == rong-1)
			{
				if (j == 0) cout << traiduoi;
				else if (j == dai-1) cout << phaiduoi;
				else cout << ngang;
			}
			else
			{
				if (j == 0 || j == dai-1) cout << doc;
				else cout << " ";
			}
		}
		gotoxy(wherex()-dai,wherey()+1);
	}
}

void veKhung2vien(int rong, int dai)
{
	for (int i = 0; i < rong; i++)
	{
		for (int j = 0; j < dai; j++)
		{
			if (i == 0)
			{
				if (j == 0) cout << trentrai;
				else if (j == dai-1) cout << trenphai;
				else cout << ngang1;
			}
			else if (i == rong-1)
			{
				if (j == 0) cout << duoitrai;
				else if (j == dai-1) cout << duoiphai;
				else cout << ngang1;
			}
			else
			{
				if (j == 0 || j == dai-1) cout << doc1;
				else cout << " ";
			}
		}
		gotoxy(wherex()-dai,wherey()+1);
	}
}
//======================= VE KHUNG TEN SV =======================
void VeKhungTenSV(int dai, int rong, int socot)
{
	int x = rong/socot;
	int dem = 1;
	for (int i = 0; i < dai; i++)
	{
		for (int j = 0; j < rong; j++)
		{
			if(dem == 1)
			{
				dem = 3;
			}
			if(dem == 4)
			{
				dem = 8;
			}
			if (i == 0)
			{
				if (j == 0) cout << traitren;
				else if (j == rong-1) cout << phaitren;
				else if (j == (rong/socot)*dem) cout << ngangxuong1;
				else cout << ngang;
			}
			else if(i == 2)
			{
				if(j == 0) cout << docphai;
				else if (j == rong -1) cout << doctrai;
				else if (j == (rong/socot)*dem) cout << giua;
				else cout << ngang;
			}
			else if (i == dai-1)
			{
				if (j == 0) cout << traiduoi;
				else if (j == rong-1) cout << phaiduoi;
				else if (j == (rong/socot)*dem) cout << nganglen;
				else cout << ngang;
			}
			else if(j == (rong/socot)*dem)
			{
				cout << doc;
			}
			else
			{
				if (j == 0 || j == rong-1) cout << doc;
				else cout << " ";
			}
			if(j == dem*(rong/socot)) dem++;
			if(dem == socot) dem = 1;
		}
		gotoxy(wherex()-rong,wherey()+1);
	}
}
// ====================== VE KHUNG XEM DIEM =======================
void VeKhungXemDiem(int dai, int rong, int socot)
{
	
	int x = rong/socot;
	int dem = 1;
	for (int i = 0; i < dai; i++)
	{
		for (int j = 0; j < rong; j++)
		{
			if(dem == 1)
			{
				dem++;
			}
			if(dem == 3)
			{
				dem = 8;
			}
			if( dem == 9)
			{
				dem = 10;
			}
			if (i == 0)
			{
				if (j == 0) cout << traitren;
				else if (j == rong-1) cout << phaitren;
				else if (j == (rong/socot)*dem) cout << ngangxuong;
				else cout << ngang;
			}
			else if(i == 2)
			{
				if(j == 0) cout << docphai;
				else if (j == rong -1) cout << doctrai;
				else if (j == (rong/socot)*dem) cout << giua;
				else cout << ngang;
			}
			else if (i == dai-1)
			{
				if (j == 0) cout << traiduoi;
				else if (j == rong-1) cout << phaiduoi;
				else if (j == (rong/socot)*dem) cout << nganglen;
				else cout << ngang;
			}
			else if(j == (rong/socot)*dem)
			{
				cout << doc;
			}
			else
			{
				if (j == 0 || j == rong-1) cout << doc;
				else cout << " ";
			}
			if(j == dem*(rong/socot)) dem++;
			if(dem == socot) dem = 1;
		}
		gotoxy(wherex()-rong,wherey()+1);
	}
}
//AN CO TRO MAN HINH CONSOLE
void AnConTro()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
//HIEN CON TRO MAN HINH CONSOLE
void HienConTro()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
//  DOI MAU CHU 
void ChangeColor(int k)
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, k);
}
//DO DAI SO DUONG
int DoDaiSoDuong(int a)
{
	if (a == 0) return 1;
	int dem = 0;
	while (a != 0)
	{
		a = a/10;
		dem++;
	}
	return dem;
}
//CHU IN HOA
char InHoa(char a)
{
	if (a >= 97 && a <= 122) // tu 'a' toi 'z'
	{
		a = a - 32;
	}
	return a;
}

void InHoaChuoi(string &s)
{
	for(int i=0;i<s.length();i++)
    {
    	s[i]=toupper(s[i]);
	}
}
// SO SANH CHUOI SO 
int SoSanhChuoiSo(string &a, string &b)
{
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] > b[i])
		{
			return 1;
		}
		if (a[i] < b[i])
		{
			return -1;
		}
	}
	return 0;
}
//  VE NUT
void veNutMenu(int chieudoc, int chieungang, int x, int y, string text, int mau )
{
	for(int i = 0; i < chieudoc; i++)
	{
		ChangeColor(mau);
		gotoxy(x,y+i);
		for(int j = 0; j < chieungang; j++)
		{
			gotoxy(x+j, y+i);
			cout << " ";
		}
//		cout << "                              ";
		
	}
	ChangeColor(mau);
	gotoxy(x+(chieungang-text.length())/2, y+(chieudoc/2));
	cout << text;
	ChangeColor(15);
}
//  VE KHUNG THEO SO COT
void vekhungDS(int dai, int rong, int socot) // doc - ngang
{
	int x = rong/socot;
	int dem = 1;
	for (int i = 0; i < dai; i++)
	{
		for (int j = 0; j < rong; j++)
		{
			if (i == 0)
			{
				if (j == 0) cout << trentrai;
				else if (j == rong-1) cout << trenphai;
				else if (j == (rong/socot)*dem) cout << ngangxuong1;
				else cout << ngang1;
			}
			else if(i == 2)
			{
				if(j == 0) cout << cattrai; //doc phai
				else if (j == rong -1) cout << catphai;
				else if (j == (rong/socot)*dem) cout << giua1;
				else cout << ngang1;
			}
			else if (i == dai-1)
			{
				if (j == 0) cout << duoitrai;
				else if (j == rong-1) cout << duoiphai;
				else if (j == (rong/socot)*dem) cout << nganglen1;
				else cout << ngang1;
			}
			else if(j == (rong/socot)*dem)
			{
				cout << doc1;
			}
			else
			{
				if (j == 0 || j == rong-1) cout << doc1;
				else cout << " ";
			}
			if(j == dem*(rong/socot)) dem++;
			if(dem == socot) dem = 1;
		}
		gotoxy(wherex()-rong,wherey()+1);
	}
}
// VE KHUNG LOP THEO SO COT
void VeKhungDSLop(int dai, int rong, int socot)

{
	
	int x = rong/socot;
	int dem = 1;
	for (int i = 0; i < dai; i++)
	{
		for (int j = 0; j < rong; j++)
		{
			if(dem == 2)
			{
				dem++;
			}
			if (i == 0)
			{
				if (j == 0) cout << traitren;
				else if (j == rong-1) cout << phaitren;
				else if (j == (rong/socot)*dem) cout << ngangxuong;
				else cout << ngang;
			}
			else if(i == 2)
			{
				if(j == 0) cout << docphai;
				else if (j == rong -1) cout << doctrai;
				else if (j == (rong/socot)*dem) cout << giua;
				else cout << ngang;
			}
			else if (i == dai-1)
			{
				if (j == 0) cout << traiduoi;
				else if (j == rong-1) cout << phaiduoi;
				else if (j == (rong/socot)*dem) cout << nganglen;
				else cout << ngang;
			}
			else if(j == (rong/socot)*dem)
			{
				cout << doc;
			}
			else
			{
				if (j == 0 || j == rong-1) cout << doc;
				else cout << " ";
			}
			if(j == dem*(rong/socot)) dem++;
			if(dem == socot) dem = 1;
		}
		gotoxy(wherex()-rong,wherey()+1);
	}
}
//VE KHUNG LOP THEO SO COT
void VeKhungDSLop1(int dai, int rong, int socot)
{
	
	int x = rong/socot;
	int dem = 1;
	for (int i = 0; i < dai; i++)
	{
		for (int j = 0; j < rong; j++)
		{
			if(dem == 1)
			{
				dem++;
			}
			if(dem == 3)
			{
				dem = 8;
			}
			if( dem == 9)
			{
				dem ++;
			}
			if (i == 0)
			{
				if (j == 0) cout << traitren;
				else if (j == rong-1) cout << phaitren;
				else if (j == (rong/socot)*dem) cout << ngangxuong;
				else cout << ngang;
			}
			else if(i == 2)
			{
				if(j == 0) cout << docphai;
				else if (j == rong -1) cout << doctrai;
				else if (j == (rong/socot)*dem) cout << giua;
				else cout << ngang;
			}
			else if (i == dai-1)
			{
				if (j == 0) cout << traiduoi;
				else if (j == rong-1) cout << phaiduoi;
				else if (j == (rong/socot)*dem) cout << nganglen;
				else cout << ngang;
			}
			else if(j == (rong/socot)*dem)
			{
				cout << doc;
			}
			else
			{
				if (j == 0 || j == rong-1) cout << doc;
				else cout << " ";
			}
			if(j == dem*(rong/socot)) dem++;
			if(dem == socot) dem = 1;
		}
		gotoxy(wherex()-rong,wherey()+1);
	}
}
//IN NOI DUNG CAU HOI 
void InNDCH (string text, int x, int y)
{
	int i = 0;
	int j = 0;
	int k = 0;
	string temp1;
	gotoxy(x,y);
	if (text.length() < 95)
	{
		gotoxy(x,y);
		cout << text;
	}
	else
	{
		while(text.length() >= 95)
		{
			for(i = 0; i < 96; i++)
			{
				if (text[i] == ' ')
				{
					j = i;
				}
			}
			if(text [95] != ' ')
			{
				temp1 = text.substr(0,j);
				text.erase(0,j+1);
				gotoxy(x,y+k);
				cout << temp1;
			}
			else
			{
				temp1 = text.substr(0,i);
				text.erase(0,i);
				gotoxy(x,y+k);
				cout << temp1;
			}
			k += 2;
			if (k > y)
			{
				break;
			}
		}
		if(k < y)
		{
			gotoxy(x,y+k);
			cout << text;
		}
	}
}
// IN NOI DUNG CAU HOI
void InDA_XemCH (string text)
{
	int i = 0;
	int j = 0;
	int k = 0;
	string temp1;
	if (text.length() < 95)
	{
		cout << text;
	}
	else
	{
		while(text.length() >= 95)
		{
			for(i = 0; i < 96; i++)
			{
				if (text[i] == ' ')
				{
					j = i;
				}
			}
			if(text [95] != ' ')
			{
				temp1 = text.substr(0,j);
				text.erase(0,j+1);
				gotoxy(20,wherey()+k);
				cout << temp1;
			}
			else
			{
				temp1 = text.substr(0,i);
				text.erase(0,i);
				gotoxy(20,wherey()+k);
				cout << temp1;
			}
			k += 2;
			if (k > 3)
			{
				break;
			}
		}
		if(k < 3)
		{
			gotoxy(20,wherey()+k);
			cout << text;
		}
	}
}
//VE KHUNG CH THEO SO COT 
void vekhungDSCH(int dai, int rong, int socot)
{
	int x = rong/socot;
	int dem = 1;
	for (int i = 0; i < dai; i++)
	{
		for (int j = 0; j < rong; j++)
		{
			if (i == 0)
			{
				if (j == 0) cout << traitren;
				else if (j == rong-1) cout << phaitren;
				else if (j == (rong/socot)*dem) cout << ngangxuong;
				else cout << ngang;
			}
			else if(i == 1)
			{
				if (j == 0|| j == 24 || j== 48 || j == rong-1) cout << doc;
				else if(j == 11)
				{
					cout << "ID";
					j += 1;
				}
				else if(j == 24+ 10)
				{
					cout << "MA MH";
					j += 4;
				}
				else if(j == 48 + 28)
				{
					cout << "NOI DUNG CAU HOI";
					j += 15;
				}
				else cout << " ";
			}
			else if(i == 2)
			{
				if(j == 0) cout << docphai;
				else if (j == rong -1) cout << doctrai;
				else if (j == (rong/socot)*dem) cout << giua;
				else cout << ngang;
			}
			else if (i == dai-1)
			{
				if (j == 0) cout << traiduoi;
				else if (j == rong-1) cout << phaiduoi;
				else if (j == (rong/socot)*dem) cout << nganglen;
				else cout << ngang;
			}
			else if(j == (rong/socot)*dem)
			{
				cout << doc;
			}
			else
			{
				if (j == 0 || j == rong-1) cout << doc;
				else cout << " ";
			}
			if(j == dem*(rong/socot)) dem++;
			if(dem == 3) dem = 1;
		}
		gotoxy(wherex()-rong,wherey()+1);
	}
}
// DAO CHUOI
string DaoChuoi(string text)
{
	int i = 0;
	string temp = text;
	for(int j = text.length()-1; j > -1; j--)
	{
		temp[i] = text[j];
		i++;
	}
	return temp;
}
void vekhungThemCHNew()
{
	veNutMenu(1, 40, 45, 5, "NOI DUNG CAU HOI", 160);
	gotoxy(45, 7);
	veKhung2vien(5, 120); // khung noi dung cau hoi
	
	veNutMenu(1, 40, 45, 13, "A", 128);
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
	veNutMenu(3,11,105,39,"LUU",128);
}
void DeleteExit(int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		gotoxy(x, y+i);
		cout<<"                                        ";
	}
}

bool Exit( char &s, bool &sCheck, int x, int y)
{
	AnConTro();
	veNutMenu(1, 40, x, y, "EXIT" , 92);
	veNutMenu(4, 40, x, y+1, " ", 240);
	veNutMenu(1, 10, x+3, y+2, "yes", 48);
	veNutMenu(1, 10, x+27, y+2, "no", 224);
	bool state = true;
//	batPhim(s, sCheck);
	while(1)
	{
		if(s == LEFT && sCheck == false)
		{
			veNutMenu(1, 10, x+3, y+2, "yes", 48);
			veNutMenu(1, 10, x+27, y+2, "no", 224);
			state = true;
		}
		if(s == RIGHT && sCheck == false)
		{
			veNutMenu(1, 10, x+3, y+2, "yes", 224);
			veNutMenu(1, 10, x+27, y+2, "no", 48);
			state = false;
		}
		if (s == ENTER)
		{	
			for (int i = 0; i < 5; i++)
			{
				gotoxy(x, y+i);
				cout<<"                                        ";
			}
			return state;
			
		}
		batPhim(s, sCheck); // bat phim ESC
	}

}
void ChuanHoaTen (string &text)
{
	if(text[0] == 32)
	{
		text.erase(0,1);
		ChuanHoaTen(text);
	}
	if(text[text.length()-1] == 32)
	{
		text.erase(text.length()-1,1);
		ChuanHoaTen(text);
	}
}
//HAM THAY THE COUT IN RA 1 CHUOI TRANH XUNG DOT VOI HAM COUT O CHUONG TRINH CHINH
// XUNG DOT LUONG XU LY
void WriteBlockChar(char *Arraych,int x, int y,int color)
{
	CHAR_INFO *charater = new CHAR_INFO[8];
	for (int i = 0; i < 8; i++)
	{
		charater[i].Attributes = color;
		charater[i].Char.AsciiChar = Arraych[i];
	}
	COORD sizebuff = { 8,1 };
	COORD pos = { 0,0 };
	SMALL_RECT earea = { x,y,x + 8 - 1,y + 1 - 1 }; // vung dem
	WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), charater, sizebuff, pos, &earea);
	delete[] charater;
}
// CHIA STRING
int doiso( char n)
{
    return n - '0';
}
char doichar (int n)
{
	return (char)(n+48);
}
string IntToString(int s)
{
	int x;
	string p;
	while(s>=10)
	{
		x = s%10;
		p.insert(0,1,doichar(x));
		s = s/10;
	}
	p.insert(0,1,doichar(s));
	return p;
}


void strdelete(char *s,int vt,int sl)
{
    int n=strlen(s),i;
    for (i=vt; i<=n-sl; ++i)
        s[i]=s[i+sl];
}
char* ChuanHoa(char a[])
{
    int i;
    while(a[strlen(a)-1]==' ')// xoa het cac ki tu trong o cuoi chuoi
        a[strlen(a)-1]=0;
    while(a[0]==' ')          //xoa het cac ki tu trong o dau chuoi
        strdelete(a,0,1);

    i=0;
    while(i<strlen(a))                //xoa hai ki tu trong lien tiep
        if((a[i]==' ')&&(a[i+1]==' '))
            strdelete(a,i,1);
        else ++i;

    return a;
}
//CAM BOI DEN
void DisableSelection()
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}
//AN THANH CUON
//void ShowScrollbar(BOOL Show)
//{
//    HWND hWnd = GetConsoleWindow();
//    ShowScrollBar(hWnd, SB_BOTH, Show);
//}
void Message(int x, int y, string text)
{
	AnConTro();
	veNutMenu(1, 20, x, y, "Messege", 64);
	gotoxy(x, y + 1);
	TextColor(4);
	veKhung2vien(4, 55);
	TextColor(15);
	gotoxy(x+2,y + 2);
	TextColor(1);
	cout << text;
	TextColor(15);
}
void DeleteMessage(int x, int y)
{
	AnConTro();
	for(int i = 0; i < 7; i++)
	{
		gotoxy(x, y+i);
		cout <<"                                                       ";
	}
}
#endif
