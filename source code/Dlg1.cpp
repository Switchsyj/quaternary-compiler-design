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
int m = 0, sum = 0;//sum���ڼ���������ĸ���
//m���ڱ��������ʽ�������ַ��ĸ���
char JG = 'A';
char var[MAX];//���ڴ��������
CString str[MAX];		//�洢������ʽ
int  token = 0;//�����ŵı�־
CString str0 = "( ";
CString str1 = "    ";
CString str2 = " )\r\n";
/***********���ڸ��ļ���������е�ֵ**************/

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


void CDlg1::first_rev(int i, int m)		//������
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
			//change(i + 1);		//���ȼ���߲��ô��������ת����ɵ���ĸ
			str[i] = str[i + 1] = JG;
			sum--;
			JG = (char)(int)JG++;
		}
	}
}


void CDlg1::first_cc(int i, int m)		//������������֮��ĳ˳�����
{
	//cout << i << "!!!" << endl;
	i++;
	for (; i <= m - 1; i++)//����˳�����
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
			change(i - 1);		//������֮���һ���ַ���ʼ�滻
			str[i - 1] = str[i] = str[i + 1] = str04;
			sum--;
			JG = (char)(int)JG++;
		}
	}
}


void CDlg1::first_jj(int j, int m)
{
	j++;
	for (; j <= m - 1; j++)//����Ӽ�����
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
	for (; i <= m - 1; i++) {		//����Ƚ������
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

void CDlg1::first_noe(int i, int m)		//����==, !=
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

void CDlg1::first_logand(int i, int m)		//����&&
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

void CDlg1::first_logor(int i, int m)		//���� ||
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

/*ɨ��һ����ļ��ж�����ʽ*/

void CDlg1::scan(FILE *fin)		//�ȴ������ź������������Ԫʽ
{
	int p[MAX];		//��¼����λ��
	char ch = 'a';
	int c = -1, q = 0;
	while (ch != EOF)
	{
		ch = getc(fin);
		while (ch == ' ' || ch == '\n' || ch == '\t')
			ch = getc(fin);//�����ո�ͻ��з�
		if (ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9' || ch >= 'A' && ch <= 'Z') {
			int pos = 0;
			while (ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9' || ch >= 'A' && ch <= 'Z') {
				var[pos++] = ch;
				ch = getc(fin);
			}
			var[pos] = '\0';	
			str[m++].Format(var);		//CString����һ��λ�ü�¼һ��CString��������һ���������
		}
		while (ch == ' ' || ch == '\n' || ch == '\t')
			ch = getc(fin);//��������������Ŀո�ͻ��з���BUG
		str[m++] = (CString)ch;
		if (ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '!' || ch == '>' || ch == '<' || ch == '&' || ch == '|') {
			sum++;
		}
		else if (ch == '(')		//��¼������λ��
		{
			p[++c] = m - 1;
		}
		else if (ch == ')')
		{
			q = m - 1;
			first_rev(p[c], q);
			first_cc(p[c], q);//�������Ŵ���������
			first_jj(p[c], q);
			first_comp(p[c], q);
			first_noe(p[c], q);
			first_logand(p[c], q);
			first_logor(p[c], q);
			JG = (char)(int)JG--;
			str[p[c]] = str[m - 1] = (CString)JG;		//���ű����ĸ�����Ŵ������
			c--;
			JG = (char)(int)JG++;
		}
		for (int i = 0; i < m; i++) {
			cout << (LPCTSTR)str[i];
		}
		cout << endl;
	}
}

/*�Ա���ǽ��д������������Ԫʽ*/

void CDlg1::trans_simple()		//���������ŵı��ʽ
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
	for (int i = 0; i <= m - 1; i++)//����˳�����
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

	for (int j = 0; j <= m - 1; j++)//����Ӽ�����
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

	for (int i = 0; i <= m - 1; i++) {		//����Ƚ������
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

	for (int i = 0; i <= m - 1; i++) {		//����==, !=
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

	for (int i = 0; i <= m - 1; i++) {		//����&&
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

	for (int i = 0; i <= m - 1; i++) {		//����||
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

	for (int k = 0; k <= m - 1; k++)//����ֵ����
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
	FILE *fin; //����ָ����������ļ���ָ��
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
	if ((fin = fopen(in_s, "r")) == NULL) //�ж������ļ����Ƿ���ȷ
	{
		MessageBox("�򿪴ʷ����������ļ�����!");
	}
	JG = 'A'; m = 0; sum = 0;
	scan(fin);	 
	trans_simple();
	if (sum == 0)
		MessageBox("ת���ɹ�");
	else
		MessageBox("ת��ʧ��");
	fclose(fin);
	
}


