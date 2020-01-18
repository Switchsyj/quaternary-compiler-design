// Dlg1.cpp : implementation file
//

#include "stdafx.h"
#include "CompilerDesign.h"
#include "Dlg1.h"
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<string>
#define MAX 100
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg1 dialog


CDlg1::CDlg1(CWnd* pParent /*=NULL*/)
: CDialog(CDlg1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg1)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg1)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg1, CDialog)
//{{AFX_MSG_MAP(CDlg1)
	ON_BN_CLICKED(IDC_OK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg1 message handlers
int m = 0, sum = 0;//sum用于计算运算符的个数
//m用于标记输入表达式中所有字符的个数
char JG = 'A';
char var[MAX];//用于存输入变量
CString str[MAX];		//存储输入表达式
int  token = 0;//左括号的标志
CString str0 = "( ";
CString str1 = "    ";
CString str2 = " )\r\n";
/***********用于更改计算后数组中的值**************/

void CDlg1::change(int e)
{

	int f = e + 2;
	CString cs = str[f];
	if (cs >= "A"&& cs <= "Z")
	{
		for (int l = 0; l < m + 10; l++)
		{
			if (str[l] == cs) 
				str[l] = (CString)JG;
		}
	}

	if (str[e] >= "A"&&str[e] <= "Z")
	{
		for (int i = 0; i < m; i++)
		{
			if (str[i] == str[e])
				str[i] = (CString)JG;
		}
	}

}

void CDlg1::change_double(int e)
{

	int f = e + 3;
	CString cs = str[f];
	if (cs >= "A"&& cs <= "Z")
	{
		for (int l = 0; l < m + 10; l++)
		{
			if (str[l] == cs)
				str[l] = (CString)JG;
		}
	}

	if (str[e] >= "A"&&str[e] <= "Z")
	{
		for (int i = 0; i < m; i++)
		{
			if (str[i] == str[e])
				str[i] = (CString)JG;
		}
	}

}


void CDlg1::first_rev(int i, int m)		//逆运算
{
	i++;
	for (; i < m - 1; i++) {
		if (str[i] == '!') {
			CString str00;
			CString strget;
			GetDlgItemText(IDC_OUT, strget);
			CString str01 = str[i];
			CString str02 = str[i + 1];
			CString str04 = JG;
			str00 = str0 + str01 + str1 + str02 + str1 + str1 + str1 + str04 + str2;
			SetDlgItemText(IDC_OUT, strget + str00);
			//change(i + 1);		//优先级最高不用处理比他先转换完成的字母
			str[i] = str[i + 1] = JG;
			sum--;
			JG = (char)(int)JG++;
		}
	}
}


void CDlg1::first_cc(int i, int m)		//处理左右括号之间的乘除运算
{
	//cout << i << "!!!" << endl;
	i++;
	for (; i <= m - 1; i++)//处理乘除运算
	{
		if (str[i] == "*" || str[i] == "/")
		{
			CString str00;
			CString strget;
			GetDlgItemText(IDC_OUT, strget);
			CString str01 = str[i];
			CString str02 = str[i - 1];
			CString str03 = str[i + 1];
			CString str04 = JG;
			str00 = str0 + str01 + str1 + str02 + str1 + str03 + str1 + str04 + str2;
			SetDlgItemText(IDC_OUT, strget + str00);
			//cout << "(" << str[i] << "  " << str[i - 1] << "  " << str[i + 1] << "  " << JG << ")" <<"*****//////" <<endl;
			change(i - 1);		//从括号之间第一个字符开始替换
			str[i - 1] = str[i] = str[i + 1] = str04;
			sum--;
			JG = (char)(int)JG++;
		}
	}
}


void CDlg1::first_jj(int j, int m)
{
	j++;
	for (; j <= m - 1; j++)//处理加减运算
	{
		if (str[j] == "+" || str[j] == "-")
		{
			CString str00;
			CString strget;
			GetDlgItemText(IDC_OUT, strget);
            CString str01 = str[j];
			CString str02 = str[j - 1];
			CString str03 = str[j + 1];
			CString str04 = JG;
			str00 = str0 + str01 + str1 + str02 + str1 + str03 + str1 + str04 + str2;
			SetDlgItemText(IDC_OUT, strget + str00);

			//cout << "(" << str[j] << "  " << str[j - 1] << "  " << str[j + 1] << "  " << JG << ")" << endl;
			change(j - 1);
			str[j - 1] = str[j] = str[j + 1] = str04;
			sum--;
			JG = (char)(int)JG++;
		}
	}
}

void CDlg1::first_comp(int i, int m)
{
	i++;
	for (; i <= m - 1; i++) {		//处理比较运算符
		if (str[i] == "<" || str[i] == ">") {
			if (str[i + 1] == "=") {
				CString str00;
				CString strget;
				GetDlgItemText(IDC_OUT, strget);
				CString str01 = str[i];
				CString str011 = str[i + 1];
				CString str02 = str[i - 1];
				CString str03 = str[i + 2];
				CString str04 = JG;
				str00 = str0 + str01 + str011 + str1 + str02 + str1 + str03 + str1 + str04 + str2;
				SetDlgItemText(IDC_OUT, strget + str00);

				//cout << "(" << str[j] << "  " << str[j - 1] << "  " << str[j + 1] << "  " << JG << ")" << endl;
				change_double(i - 1);
				str[i - 1] = str[i] = str[i + 1] = str[i + 2] = str04;
				sum = sum - 2;
				JG = (char)(int)JG++;
				i++;
			}
			else {
				CString str00;
				CString strget;
				GetDlgItemText(IDC_OUT, strget);
				CString str01 = str[i];
				CString str02 = str[i - 1];
				CString str03 = str[i + 1];
				CString str04 = JG;
				str00 = str0 + str01 + str1 + str02 + str1 + str03 + str1 + str04 + str2;
				SetDlgItemText(IDC_OUT, strget + str00);
				change(i - 1);
				str[i - 1] = str[i] = str[i + 1] = str04;
				sum--;
				JG = (char)(int)JG++;
			}
		}

	}
}

void CDlg1::first_noe(int i, int m)		//处理==, !=
{
	i++;
	for (; i <= m - 1; i++) {
		if (str[i] == "=" || str[i] == "!") {
			if (str[i + 1] == "=") {
				CString str00;
				CString strget;
				GetDlgItemText(IDC_OUT, strget);
				CString str01 = str[i];
				CString str011 = str[i + 1];
				CString str02 = str[i - 1];
				CString str03 = str[i + 2];
				CString str04 = JG;
				str00 = str0 + str01 + str011 + str1 + str02 + str1 + str03 + str1 + str04 + str2;
				SetDlgItemText(IDC_OUT, strget + str00);

				//cout << "(" << str[j] << "  " << str[j - 1] << "  " << str[j + 1] << "  " << JG << ")" << endl;
				change_double(i - 1);
				str[i - 1] = str[i] = str[i + 1] = str[i + 2] = str04;
				sum = sum - 2;
				JG = (char)(int)JG++;
				i++;
			}
		}
	}
}

void CDlg1::first_logand(int i, int m)		//处理&&
{
	i++;
	for (; i <= m - 1; i++) {
		if (str[i] == "&" && str[i + 1] == "&") {
			CString str00;
			CString strget;
			GetDlgItemText(IDC_OUT, strget);
			CString str01 = str[i];
			CString str011 = str[i + 1];
			CString str02 = str[i - 1];
			CString str03 = str[i + 2];
			CString str04 = JG;
			str00 = str0 + str01 + str011 + str1 + str02 + str1 + str03 + str1 + str04 + str2;
			SetDlgItemText(IDC_OUT, strget + str00);

			//cout << "(" << str[j] << "  " << str[j - 1] << "  " << str[j + 1] << "  " << JG << ")" << endl;
			change_double(i - 1);
			str[i - 1] = str[i] = str[i + 1] = str[i + 2] = str04;
			sum = sum - 2;
			JG = (char)(int)JG++;
			i++;
		}
	}
}

void CDlg1::first_logor(int i, int m)		//处理 ||
{
	i++;
	for (; i <= m - 1; i++) {
		if (str[i] == "|" && str[i + 1] == "|") {
			CString str00;
			CString strget;
			GetDlgItemText(IDC_OUT, strget);
			CString str01 = str[i];
			CString str011 = str[i + 1];
			CString str02 = str[i - 1];
			CString str03 = str[i + 2];
			CString str04 = JG;
			str00 = str0 + str01 + str011 + str1 + str02 + str1 + str03 + str1 + str04 + str2;
			SetDlgItemText(IDC_OUT, strget + str00);

			//cout << "(" << str[j] << "  " << str[j - 1] << "  " << str[j + 1] << "  " << JG << ")" << endl;
			change_double(i - 1);
			str[i - 1] = str[i] = str[i + 1] = str[i + 2] = str04;
			sum = sum - 2;
			JG = (char)(int)JG++;
			i++;
		}
	}
}

/*扫描一遍从文件中读入表达式*/

void CDlg1::scan(FILE *fin)		//先处理括号和括号里面的四元式
{
	int p[MAX];		//记录括号位置
	char ch = 'a';
	int c = -1, q = 0;
	while (ch != EOF)
	{
		ch = getc(fin);
		while (ch == ' ' || ch == '\n' || ch == '\t')
			ch = getc(fin);//消除空格和换行符
		if (ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9' || ch >= 'A' && ch <= 'Z') {
			int pos = 0;
			while (ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9' || ch >= 'A' && ch <= 'Z') {
				var[pos++] = ch;
				ch = getc(fin);
			}
			var[pos] = '\0';	
			str[m++].Format(var);		//CString数组一个位置记录一个CString变量或者一个运算符号
		}
		while (ch == ' ' || ch == '\n' || ch == '\t')
			ch = getc(fin);//消除变量后读到的空格和换行符，BUG
		str[m++] = (CString)ch;
		if (ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '!' || ch == '>' || ch == '<' || ch == '&' || ch == '|') {
			sum++;
		}
		else if (ch == '(')		//记录左括号位置
		{
			p[++c] = m - 1;
		}
		else if (ch == ')')
		{
			q = m - 1;
			first_rev(p[c], q);
			first_cc(p[c], q);//从左括号处理到右括号
			first_jj(p[c], q);
			first_comp(p[c], q);
			first_noe(p[c], q);
			first_logand(p[c], q);
			first_logor(p[c], q);
			JG = (char)(int)JG--;
			str[p[c]] = str[m - 1] = (CString)JG;		//括号变成字母，括号处理完成
			c--;
			JG = (char)(int)JG++;
		}
		for (int i = 0; i < m; i++) {
			cout << (LPCTSTR)str[i];
		}
		cout << endl;
	}
}

/*对表达是进行处理并输出部分四元式*/

void CDlg1::trans_simple()		//处理无括号的表达式
{
	for (int i = 0; i < m - 1; i++) {
		if (str[i] == "!") {
			CString str00;
			CString strget;
			GetDlgItemText(IDC_OUT, strget);
			CString str01 = str[i];
			CString str02 = str[i + 1];
			CString str04 = JG;
			str00 = str0 + str01 + str1 + str02 + str1 + str1 + str1 + str04 + str2;
			SetDlgItemText(IDC_OUT, strget + str00);
			//change(i + 1);
			str[i] = str[i + 1] = JG;
			sum--;
			JG = (char)(int)JG++;
		}
	}
	for (int i = 0; i <= m - 1; i++)//处理乘除运算
	{
		if (str[i] == "*" || str[i] == "/")
		{
			CString str00;
			CString strget;
			GetDlgItemText(IDC_OUT, strget);
            CString str01 = str[i];
			CString str02 = str[i - 1];
			CString str03 = str[i + 1];
			CString str04 = JG;
			str00 = str0 + str01 + str1 + str02 + str1 + str03 + str1 + str04 + str2;
			SetDlgItemText(IDC_OUT, strget + str00);
			//cout << "(" << str[i] << "  " << str[i - 1] << "  " << str[i + 1] << "  " << JG << ")" << endl;
			change(i - 1);
			str[i - 1] = str[i] = str[i + 1] = str04;
			sum--;
			JG = (char)(int)JG++;
		}

	}

	for (int j = 0; j <= m - 1; j++)//处理加减运算
	{
		if (str[j] == "+" || str[j] == "-")
		{
			CString str00;
			CString strget;
			GetDlgItemText(IDC_OUT, strget);
            CString str01 = str[j];
			CString str02 = str[j - 1];
			CString str03 = str[j + 1];
			CString str04 = JG;
			str00 = str0 + str01 + str1 + str02 + str1 + str03 + str1 + str04 + str2;
			SetDlgItemText(IDC_OUT, strget + str00);
			//SetDlgItemText(IDC_OUT,"???????");
			//cout << "(" << str[j] << "  " << str[j - 1] << "  " << str[j + 1] << "  " << JG << ")" << endl;
			change(j - 1);
			str[j - 1] = str[j] = str[j + 1] = str04;
			sum--;
			JG = (char)(int)JG++;
		}

	}

	for (int i = 0; i <= m - 1; i++) {		//处理比较运算符
		if (str[i] == "<" || str[i] == ">") {
			if (str[i + 1] == "=") {
				CString str00;
				CString strget;
				GetDlgItemText(IDC_OUT, strget);
				CString str01 = str[i];
				CString str011 = str[i + 1];
				CString str02 = str[i - 1];
				CString str03 = str[i + 2];
				CString str04 = JG;
				str00 = str0 + str01 + str011 + str1 + str02 + str1 + str03 + str1 + str04 + str2;
				SetDlgItemText(IDC_OUT, strget + str00);

				//cout << "(" << str[j] << "  " << str[j - 1] << "  " << str[j + 1] << "  " << JG << ")" << endl;
				change_double(i - 1);
				str[i - 1] = str[i] = str[i + 1] = str[i + 2] = str04;
				sum = sum - 2;
				JG = (char)(int)JG++;
				i++;
			}
			else {
				CString str00;
				CString strget;
				GetDlgItemText(IDC_OUT, strget);
				CString str01 = str[i];
				CString str02 = str[i - 1];
				CString str03 = str[i + 1];
				CString str04 = JG;
				str00 = str0 + str01 + str1 + str02 + str1 + str03 + str1 + str04 + str2;
				SetDlgItemText(IDC_OUT, strget + str00);
				change(i - 1);
				str[i - 1] = str[i] = str[i + 1] = str04;
				sum--;
				JG = (char)(int)JG++;
			}
		}

	}

	for (int i = 0; i <= m - 1; i++) {		//处理==, !=
		if (str[i] == "=" || str[i] == "!") {
			if (str[i + 1] == "=") {
				CString str00;
				CString strget;
				GetDlgItemText(IDC_OUT, strget);
				CString str01 = str[i];
				CString str011 = str[i + 1];
				CString str02 = str[i - 1];
				CString str03 = str[i + 2];
				CString str04 = JG;
				str00 = str0 + str01 + str011 + str1 + str02 + str1 + str03 + str1 + str04 + str2;
				SetDlgItemText(IDC_OUT, strget + str00);

				//cout << "(" << str[j] << "  " << str[j - 1] << "  " << str[j + 1] << "  " << JG << ")" << endl;
				change_double(i - 1);
				str[i - 1] = str[i] = str[i + 1] = str[i + 2] = str04;
				sum = sum - 2;
				JG = (char)(int)JG++;
				i++;
			}
		}
	}

	for (int i = 0; i <= m - 1; i++) {		//处理&&
		if (str[i] == "&" && str[i + 1] == "&") {
			CString str00;
			CString strget;
			GetDlgItemText(IDC_OUT, strget);
			CString str01 = str[i];
			CString str011 = str[i + 1];
			CString str02 = str[i - 1];
			CString str03 = str[i + 2];
			CString str04 = JG;
			str00 = str0 + str01 + str011 + str1 + str02 + str1 + str03 + str1 + str04 + str2;
			SetDlgItemText(IDC_OUT, strget + str00);

			//cout << "(" << str[j] << "  " << str[j - 1] << "  " << str[j + 1] << "  " << JG << ")" << endl;
			change_double(i - 1);
			str[i - 1] = str[i] = str[i + 1] = str[i + 2] = str04;
			sum = sum - 2;
			JG = (char)(int)JG++;
			i++;
		}
	}

	for (int i = 0; i <= m - 1; i++) {		//处理||
		if (str[i] == "|" && str[i + 1] == "|") {
			CString str00;
			CString strget;
			GetDlgItemText(IDC_OUT, strget);
			CString str01 = str[i];
			CString str011 = str[i + 1];
			CString str02 = str[i - 1];
			CString str03 = str[i + 2];
			CString str04 = JG;
			str00 = str0 + str01 + str011 + str1 + str02 + str1 + str03 + str1 + str04 + str2;
			SetDlgItemText(IDC_OUT, strget + str00);

			//cout << "(" << str[j] << "  " << str[j - 1] << "  " << str[j + 1] << "  " << JG << ")" << endl;
			change_double(i - 1);
			str[i - 1] = str[i] = str[i + 1] = str[i + 2] = str04;
			sum = sum - 2;
			JG = (char)(int)JG++;
			i++;
		}
	}

	for (int k = 0; k <= m - 1; k++)//处理赋值运算
	{
		if (str[k] == "=")
		{
			JG = (char)(int)--JG;
			CString str00;
			CString strget;
			GetDlgItemText(IDC_OUT, strget);
            CString str01 = str[k];
			CString str02 = str[k - 1];
			CString str03 = str[k + 1];
			str00 = str0 + str01 + str1 + str03 + str1 + str1 + str1 + str02 + str2;
		//	MessageBox(str00);
			SetDlgItemText(IDC_OUT, strget + str00);
			//SetDlgItemText(IDC_OUT,"!!!!!!!");
			//SetDlgItemText(IDC_OUT,"5 10 15 9 18 27 7 14 21")
			//cout << "(" << str[k] << "  " << str[k + 1] << "  " << "  " << " " << str[k - 1] << ")" << endl;
			sum--;
			change(k + 1);
			str[k - 1] = (CString)JG;
		}
	}
}

void CDlg1::OnOk()
{
    SetDlgItemText(IDC_OUT,"");
	FILE *fin; //用于指向输入输出文件的指针
	CString in_s;
    CString in_ss;
    //char in_c[100];
	string str;
	GetDlgItemText(IDC_FILENAME,in_s);
    ifstream i(in_s);
    //i>>in_c;
	getline(i, str);
    in_ss=str.c_str();
    SetDlgItemText(IDC_DISPLAY,in_ss);
	if ((fin = fopen(in_s, "r")) == NULL) //判断输入文件名是否正确
	{
		MessageBox("打开词法分析输入文件出错!");
	}
	JG = 'A'; m = 0; sum = 0;
	scan(fin);	 
	trans_simple();
	if (sum == 0)
		MessageBox("转换成功");
	else
		MessageBox("转换失败");
	fclose(fin);
	
}


