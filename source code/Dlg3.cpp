// Dlg3.cpp : implementation file
//

#include "stdafx.h"
#include "CompilerDesign.h"
#include "Dlg3.h"
#include"stdafx.h"
#include <iomanip>
#include "windows.h"
#include<iostream>
#include <fstream>
//#include<cctype>
#include<stack>
#include "conio.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg3 dialog


CDlg3::CDlg3(CWnd* pParent /*=NULL*/)
: CDialog(CDlg3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg3)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
}


void CDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg3)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg3, CDialog)
//{{AFX_MSG_MAP(CDlg3)
ON_BN_CLICKED(IDC_OK, OnOk)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg3 message handlers

BOOL CDlg3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
	m_list.InsertColumn(0,"状态",LVCFMT_CENTER);
	m_list.InsertColumn(1,"符号栈",LVCFMT_CENTER);
	m_list.InsertColumn(2,"输入串",LVCFMT_CENTER);
	
	m_list.SetColumnWidth(0,200);
	m_list.SetColumnWidth(1,150);
	m_list.SetColumnWidth(2,150);	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//ofstream coutf("cifa.txt", ios::out);//结果输出至文件cifa.txt
//ofstream couty("yufa.txt", ios::out);//结果输出至文件yufa.txt
//ofstream couts("obj.txt", ios::out);//结果输出至文件obj.txt
char shuru[100], tmp;
char sr[100];
char b[10], op[10], rop[10];
char a[10];
int qq = 0;

struct Table{
	char act_0[10];
	int act_1[10];
	int go[4];
}action[18];

struct  obj{
	char f;
	char op1;
	char op2;
	char result;
}equ[10];

void Init(){
	/*---------------       ACTION      -----------------------*/
	action[0].act_0[0] = 's';       action[0].act_1[0] = 2;
	action[1].act_0[9] = 'Z';
	action[2].act_0[1] = 's';       action[2].act_1[1] = 3;
	action[3].act_0[5] = 's';       action[3].act_1[5] = 5;
	action[4].act_0[2] = 's';       action[4].act_1[2] = 6;
	action[5].act_0[2] = 'r';       action[5].act_1[2] = 7;
	action[5].act_0[7] = 's';       action[5].act_1[7] = 7;
	action[6].act_0[3] = 's';       action[6].act_1[3] = 9;
	action[7].act_0[5] = 's';       action[7].act_1[5] = 8;
	action[8].act_0[2] = 'r';       action[8].act_1[2] = 6;
	action[9].act_0[5] = 's';       action[9].act_1[5] = 14;
	action[10].act_0[4] = 'r';      action[10].act_1[4] = 3;
	action[10].act_0[5] = 's';      action[10].act_1[5] = 14;
	action[11].act_0[4] = 's';      action[11].act_1[4] = 12;
	action[12].act_0[9] = 'r';      action[12].act_1[9] = 1;
	action[13].act_0[4] = 'r';      action[13].act_1[4] = 2;
	action[14].act_0[8] = 's';      action[14].act_1[8] = 17;
	action[14].act_0[6] = 's';      action[14].act_1[6] = 15;
	action[15].act_0[5] = 's';      action[15].act_1[5] = 14;
	action[16].act_0[4] = 'r';     action[16].act_1[4] = 4;
	action[16].act_0[5] = 'r';     action[16].act_1[5] = 4;
	action[17].act_0[4] = 'r';     action[17].act_1[4] = 5;
	action[17].act_0[5] = 'r';     action[17].act_1[5] = 5;
	
	/*--------------------     GOTO      -------------------------*/
	action[0].go[0] = 1;
	action[3].go[2] = 4;;
	action[9].go[1] = 11;
	action[9].go[3] = 10;
	action[10].go[1] = 13;
	action[10].go[3] = 10;
	action[15].go[3] = 16;
	
}

void CDlg3::analyse_word()
{
	int i = 0, j = 0, k = 0, m = 0;
	for (qq = 5; qq<strlen(sr); qq++)
	{
		tmp = sr[qq];
		if (tmp >= '0'&&tmp <= '9' || tmp >= 'a'&&tmp <= 'z' || tmp >= 'A'&&tmp <= 'Z')
			a[i++] = tmp;
		else if (tmp == '+' || tmp == '-' || tmp == '/' || tmp == '*')
			op[j++] = tmp;
		else if (tmp == '>' || tmp == '<')
			rop[k++] = tmp;
		else if (tmp == '(' || tmp == ')' || tmp == '{' || tmp == '}' || tmp == ';')
			b[m++] = tmp;
	}
    CString str00;
    str00="关键字： while\r\n变量名：";
	for (i = 0; i<strlen(a); i++)
	{
        CString temp_str;
        temp_str=a[i];
		str00=str00+temp_str+ " ";
	}
	str00=str00+"\r\n表达式运算符：";
	for (i = 0; i<strlen(op); i++)
	{
		CString temp_str;
        temp_str=op[i];
        str00=str00+temp_str+ " ";
	}
    str00=str00+"\r\n比较运算符：";
	for (i = 0; i<strlen(rop); i++)
	{
        CString temp_str;
        temp_str=rop[i];
        str00=str00+temp_str+" ";
	}
	str00=str00+"\r\n界符：";
	for (i = 0; i<strlen(b); i++)
	{       
        CString temp_str;
        temp_str=b[i];
        str00=str00+temp_str+" ";
	}
	SetDlgItemText(IDC_CF,str00);
}

//ofstream couty;
void CDlg3::LR(){
	int Tai[50], len = 1;
	int i, j, k, l, m, tmp_n = 0, num = 0;
	int X;
	char temp;
	char fuhao[50] = { "#" };
	char*W[] = { "7", "SW(B){E}", "EAE", "EA", "AiPA", "Ai;", "BiTi", "Bi" };
	num = strlen(shuru);
	Tai[0] = 0;
	//couty << "状态                 符号                    输入串    " << endl;
	for (i = 0; i<num;){
		j = Tai[len - 1];
		temp = shuru[i];
		switch (temp){
		case '+':
		case '-':
		case '*':
		case '/':
		case '=': temp = 'P';  break;
		case '<':
		case '>':   temp = 'T';  break;
		}
		if (temp != 'P'&&temp != 'T'&&temp != 'w')
			if (temp >= '0'&&temp <= '9' || temp >= 'a'&&temp <= 'z' || temp >= 'A'&&temp <= 'Z')
				temp = 'i';
			
			switch (temp){
			case 'w':    k = 0;	 break;
			case '(':    k = 1;    break;
			case ')':    k = 2; 	 break;
			case '{':    k = 3; 	 break;
			case '}':    k = 4;    break;
			case 'i':    k = 5; 	 break;
			case 'P':    k = 6; 	 break;
			case 'T':    k = 7; 	 break;
			case ';':    k = 8; 	 break;
			case '#':    k = 9;   break;
			}
			if (action[j].act_0[k] == 's'){
                int row = m_list.GetItemCount();
                m_list.InsertItem(row, "");
				//couty<<"!"<<i<<"!"<<"       ";/////////////////////////
				Tai[len++] = action[j].act_1[k];
				tmp_n = strlen(fuhao) - 1;
				fuhao[++tmp_n] = shuru[i++];


				CString str00="";
                for (l = 0; l<len; l++){
                    CString temp_str1;
                    temp_str1.Format("%d",Tai[l]);
                    str00=str00+temp_str1;                    
                    
                }
                m_list.SetItemText(row, 0, str00);
                CString str11=fuhao;
				m_list.SetItemText(row, 1, str11);
				CString str22="";
                for (l = i; l<num; l++){
                    CString temp_str2=shuru[l];
                    str22=str22+temp_str2;
                }
                m_list.SetItemText(row, 2, str22);
			}
			else if (action[j].act_0[k] == 'r'){
                int row = m_list.GetItemCount();
                m_list.InsertItem(row, "");
				X = strlen(W[action[j].act_1[k]]) - 1;
				len -= X;
				for (m = len; m<len + X; m++)
					fuhao[m] = '\0';
				fuhao[len] = W[action[j].act_1[k]][0];
				
				switch (W[action[j].act_1[k]][0]){
				case 'S':
					l = 0;
					break;
				case 'E':
					l = 1;
					break;
				case 'B':
					l = 2;
					break;
				case 'A':
					l = 3;
					break;
				}
				len += 1;
				
				Tai[len - 1] = action[Tai[len - 2]].go[l];
				CString str00="";
				for (l = 0; l<len; l++){
                    CString temp_str1;
                    temp_str1.Format("%d",Tai[l]);
                    str00=str00+temp_str1;   
				}
                m_list.SetItemText(row, 0, str00);
                CString str11=fuhao;
				m_list.SetItemText(row, 1, str11);
				CString str22="";
				for (l = i; l<num; l++)
                {
                    CString temp_str2=shuru[l];
                    str22=str22+temp_str2;
                }
                m_list.SetItemText(row, 2, str22);
			}
			else if (action[j].act_0[k] == 'Z'){
				break;
			}
			else{

			}
	}
}

int cmp(char a, char b)//判断优先级
{
	while (a == '*' || a == '/')
	{
		switch (b)
		{
		case '+':
		case '-':
		case '=':
		case ';':
			return 1;
			break;
		case '*':
		case '/':
			return 0;
			break;
		}
	}
	while (a == '+' || a == '-')
	{
		switch (b)
		{
		case '=':
		case ';':
			return 1;
			break;
		case '*':
		case '/':
		case '+':
		case '-':
			return 0;
			break;
			
		}
	}
	while (a == '(')
	{
		switch (b)
		{
		case '=':
		case ';':
			return 1;
			break;
		case '*':
		case '/':
		case '+':
		case '-':
			return 0;
			break;
		}
	}
	while (a == '=')
	{
		switch (b)
		{
		case ';':
			return 1;
			break;
		case '*':
		case '/':
		case '+':
		case '-':
		case '=':
			return 0;
			break;
		}
	}
	while (a == ';')
	{
		switch (b)
		{
		case '*':
		case '/':
		case '+':
		case '-':
		case '=':
		case ';':
			return 0;
			break;
		}
	}
	return 1;
}


void CDlg3::produce_obj(char c[],int count)
{
	stack<char>  sf;
	stack<char>  s1;
	stack<char>  s;
	int i, j = 0;
	sf.push(';');
	char t[5] = { "ABCD" };
	for (i = 0; i<count+1; i++)
	{
		if (isalnum(c[i]))
			s1.push(c[i]);
		else if (c[i] == ';')
		{
			while (sf.top() != ';')
			{
				s1.push(sf.top());
				sf.pop();
			}
		}
		else
		{
loop:
		if (cmp(c[i], sf.top()))
			sf.push(c[i]);
		else
		{
			s1.push(sf.top());
			sf.pop();
			goto  loop;
		}
		}
	}
	while (!isalnum(s1.top()))
	{
		s.push(s1.top());
		s1.pop();
	}
	while (!s.empty())
	{
		if (s.top() == '+' || s.top() == '-' || s.top() == '*' || s.top() == '/')
		{
			equ[j].f = s.top();
			s.pop();
			equ[j].op2 = s1.top();
			s1.pop();
			equ[j].op1 = s1.top();
			s1.pop();
			equ[j].result = t[j];
			s1.push(equ[j].result);
			j++;
		}
		else
		{
			
			equ[j].f = s.top();
			s.pop();
			s1.pop();
			equ[j].result = s1.top();
			s1.pop();
			equ[j].op2 = '^';
			equ[j].op1 = equ[j - 1].result;
		}
	}
	CString str00;
    CString temp_str1=rop[0];
    CString temp_str2=a[0];
    CString temp_str3=a[1];
    str00="(j" + temp_str1+"  "+temp_str2+"  " +temp_str3 +"    )\r\n";
    if(temp_str1==">")
		str00="(j<= "+temp_str2+"  "+temp_str3+"  over)\r\nl:\r\n";
	else if(temp_str1=="<")
		str00="(j>= "+temp_str2+"  "+temp_str3+"  over)\r\nl:\r\n";
	else
	{}
	//couts << "100" << "(" << "j" << rop[0] << "," << a[0] << "," << a[1] << "," << "101" << ")" << endl;
	for (i = 0; i <= j; i++){
        CString temp_str4=equ[i].f;
        CString temp_str5=equ[i].op1;
        CString temp_str6=equ[i].op2;
        CString temp_str7=equ[i].result;
		if(i==j)
			str00=str00+"("+temp_str4+"   "+temp_str5+"   "+"   "+"   "+temp_str7+")\r\n";
		else
        str00=str00+"("+temp_str4+"    "+temp_str5+"    "+temp_str6+"    "+temp_str7+")\r\n";
		//couts << "10" << i + 1 << "(" << equ[i].f << "," << equ[i].op1 << "," << equ[i].op2 << "," << equ[i].result << ")" << endl;	
	}
	str00=str00+"goto l\r\nover\r\n";
	SetDlgItemText(IDC_OUT,str00);
}

void CDlg3::OnOk() 
{
	Init();	
    SetDlgItemText(IDC_OUT,"");
    CString in_s;
    GetDlgItemText(IDC_FILENAME,in_s);
	ifstream dic(in_s,ios::in);
    while (!dic.eof())
	{
		char m;
		m = dic.get();
		if (m != ' '){
			sr[qq] = m;
			qq++;
		}
	}
    CString display;
    display = sr;
    SetDlgItemText(IDC_DISPLAY,sr);
	sr[qq-1] = '#';
	sr[qq ] = '\0';
	analyse_word();
	shuru[0] = 'w';
	for (qq = 5; qq<strlen(sr); qq++)
		shuru[qq-4] = sr[qq];
	LR();
	int i, j = 0;
	char d[50];
	for (i = 6; shuru[i] != '}'; i++)
		d[j++] = shuru[i + 1];
	produce_obj(d,j-1);
	MessageBox("转化成功");
}
