#include <iostream>
#include <iomanip>
#include "Book.h"

#define CMD_CLOS 80
#define CMD_LINES 25
using namespase std;

void SetScreenGrid();//设置屏幕显示的行数和列数 
void ClearScreen();//清除屏幕信息
void SetSysCaption(const char *pText);//设置窗体标题栏
void ShowWelcome();//显示欢迎信息
void ShowRootMenu();//显示开始菜单
void WaitView(int iCurPage);//浏览数据时等待用户操作
void WaitUser();//等待用户操作
void GuideInput();//使用向导添加图书信息
int GetSelect();//获取用户菜单选择
long GetFileLength(ifstream &ifs);//获取文件长度
void ViewData(int iSelPage);//浏览所有图书信息
void DeleteBookFromFile();//在文件中产生图书记录
void mainloop();//主循环
int mian()
{
	SetScreenGrid();
	SetSysCaption("图书管理系统");
	mainloop();
}

void SetScreenGrid()
{
	char sysSetBuf[80];
	sprint(sysSetBuf, "mode con cols=%d line=%d", CMD_CLOS, CMD_LINES);
	system();
}
void ClearScreen()
{
	system("cls");
}
void SetSysCaption()
{
	system("title Sample");
}
void SetSysCaption(const char *pText)
{
	char sysSetBuff[80];
	sprintf(sysSetBuff, "title %s", pText);
	system(sysSetBuff);
}

void ShowWelcome()
{
	for(int i = 0; i < 7; i++){
		cout << endl;
	}
	cout << setw(40);
	cout << "******************" << endl;
	cout << setw(40);
	cout << "***图书管理系统***" << endl;
	cout << setw(40);
	cout << "******************" << endl;
}
void ShowRootMenu()
{
	cout << setw(35);
	cout << "请选择功能" << endl;
	cout << endl;
	cout << setw(35);
	cout << "1 添加新书" << endl;
	cout << emdl;
	cout << setw(35);
	cout << "2 浏览全部" << endl;
	cout << endl;
	cout << setw(35);
	cout << "3 删除图书" << endl;
	cout << endl;
}
void WaitView(int iCurPage)
{
	char buf[256];
	gets_s(buf);
	if(buf[0] == 'q')
		system("exit");
	if(buf[0] == 'm')
		mainloop();
	if(buf[0] == 'n')
		ViewData(iCurPage);
}
void WaitUser()
{
	int iInputPage = 0;
	cout << "enter 返回主菜单 q退出" << endl;
	char buf[256];
	gets_s(buf);
	if(buf[0] == 'q')
		system("exit");
}
void GuideInput()
{
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];

	cout << "输入书名" << endl;
	cin << inName;
	cout << "输入Isbn" << endl;
	cin << inIsbn;
	cout << "输入价格" << endl;
	cin << inPrice;
	cout << "输入作者" << endl;
	cin << inAuthor;

	CBook book(inName, inIsbn, inPrice, inAuthor);
	book.WriteData();
	cout << "Write Finish" << endl;
	WaitUser();
}
int GetSelect()
{
	char buf[256];
	get_s(buf);
	return atoi(buf);
}
long GetFileLength(ifstream &ifs)
{
	long temppos;
	long respos;
	temppos = ifs.tellg();
	ifs.seekg(0, ios::end);
	respos = ifs.tellg();
	ifs.seekg(temppos, ios::beg);
	return respos;
}
void ViewData(int iSelPage)
{
	int iPage = 0;
	int iCurPage = 0;
	int iDataCount = 0;
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];
	bool bIndex = false;
	int iFileLength;
	iCurPage = iSelPage;
	ifstream ifile;
	ifile.open("book.dat", ios::binary);
	iFileLength = GetFileLength(ifile);
	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 +NUM2);
	if(iDataCount >= 1)
		bIndex = true;
	iPage = iDataCount / 20 + 1;
	ClearScreen();
	cout << "共有记录" << iDataCount << " ";
	cout << "共有页数" << iPage << " ";
	cout << "当前页数" << iCurPage << " ";
	cout << "n 显示下一页 m 返回" << endl;
	cout << setw(3) << "Index";
	cout << setw(20) << "Name" << setw(24) << "Isbn";
	cout << setw(15) << "Price" << setw(13) << "Author";
	cout << endl;
	try{
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		if(!ifile.fail()){
			for(int i = 1; i < 21; i++){
				memset(inName, 0, 128);
				memset(inIsbn, 0, 128);
				memset(inPrice, 0, 50);
				memset(inAuthor, 0, 50);
				if(bIndex){
					cout << setw(3) << ((iCurPage -1) * 20 + i);
					ifile.read(inName, NUM1);
					cout << setw(24) << inName;
					ifile.read(inIsbn, NUM1);
					cout << setw(24) << inIsbn;
					ifile.read(inPrice, NUM2);
					cout << setw(12) << inPrice;
					ifile.read(inAuthor, NUM2);
					cout << setw(12) << inAuthor;
					cout << endl;
				}
				if(ifile.tellg() < 0)
					bIndex = false;
				else 
					bIndex = true;
			}
		}
	}
	catch(...){
		cout << "throw file exception" << endl;
		throw "file error occurred";
		ifile.close();
	}
	if(iCurPage < iPage){
		iCurPage = iCurPage + 1;
		WaitView(iCurPage);
	}
	else{
		WaitView(iCurPage);
	}
	ifile.close();
}
void DeleteBookFromFile()
{
	int iDelCount;
	cin << iDelCount;
	CBook tmpBook;
	tmpBook.DeleteData(iDelCount);
	cout << "Delete finish" << endl;
	WaitUser();
}
void mainloop()
{
	ShowWelcome();
	while(1){
		ClearScreen();
		ShowWelcome();
		ShowRootMenu();
		switch(GetSelect()){
			case 1:
				ClearScreen();
				GuideInput();
				break;
			case 2:
				ClearScreen();
				ViewData();
				break;
			case 3:
				ClearScreen();
				DeleteBookFromFile();
				break;
		}
	}
	
}


