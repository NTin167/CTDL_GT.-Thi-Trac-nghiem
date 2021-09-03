#include<iostream>
#include<string>
#include"mylib.h"
#include"struct.h"
#include"XuLy.h"
#include"CauHoiThi.h"
using namespace std;

int main()
{
	DisableSelection();
	SetConsoleTitle("THI TRAC NGHIEM");
	int arr1[4999];
	int arr2[4999];
	createArray(arr1,1,4999);
	createArray(arr2,5001,9999);
	dssv ds;
	dslop dsl;
	DSMH dsm;
	NODECH dsch;
	KhoiTaoCH(dsch);
	ThiTracNghiem(dsl,ds,dsm,dsch,arr1,arr2);

	return 0;
} 
