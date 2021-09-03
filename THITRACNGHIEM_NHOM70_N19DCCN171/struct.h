#include<iostream>
#ifndef _STRUCT_H
#define _STRUCT_H

#define MAXLOP 100
#define MAXMONHOC 100
#define STACKSIZE 1000

// CAU TRUC DANH SACH MON HOC
//Danh sach tuyen tinh: MAMH, TENMH

struct monHoc{
	string MAMH;
	string TENMH;
};

struct DSMH{
	int somon = 0;
	monHoc *m[MAXMONHOC] = {NULL};
};

struct CTdethi
{
	int sct;
	int tg;
	int *bode;
	int *dapan;
};

// CAU TRUC DANH SACH DIEM THI
//Danh sach lien ket don MAMH, DIem

struct diemThi{
	string MAMH;
	float DIEM;
	CTdethi ctdt;
};

struct nodediemThi{
	diemThi info;
	nodediemThi *pNext = NULL;
};


struct dsdiemThi
{
	nodediemThi *First = NULL;
};


// CAU TRUC DANH SACH SINH VIEN
//Danh sach lien ket don (MASV, HO, TEN,  PHAI, password, con tro), con tro tro den diem cac mon da thi trac nghiem

struct sinhVien{
	string MASV;
	string HO;
	string TEN;
	string PHAI;
	string password;
	// con tro tro den cac mon da thi trac nghiem
	dsdiemThi diem;
};

struct nodeSV{
	sinhVien info;
	nodeSV *pNext = NULL;
};

struct dssv
{
	nodeSV	*First = NULL;	
};
//CAU TRUC DANH SACH LOP
//Mang con tro: MALOP, TENLOP con tro (con tro se tro den danh sach sinh vien thuoc lop do)

struct lop{
	string MALOP;
	string TENLOP;
	dssv danhsach;
};

struct dslop{
	int solop;
	lop *l [MAXLOP] = {NULL};
};
 /*CAU TRUC CAU HOI THI
cay nhi phan tim kiem: key= id Id, MA MH, Noi dung, A, B, C, D, DapAn
 A,B,C,D la 4 lua chon tuong ung noi dung cau hoi*/

struct cauHoi{
	string MAMH;
	string NOIDUNG;
	string A;
	string B;
	string C;
	string D;
	string DAPAN;
};

struct nodecauHoi
{
	int id;
	cauHoi info;
	nodecauHoi *pLeft = NULL;
	nodecauHoi *pRight = NULL;
};

typedef struct nodecauHoi *NODECH;
struct dscauhoi
{
	nodecauHoi *Root = NULL;
};
struct TG 
{
	int gio;
	int phut;
	int giay;
};
#endif
