// Dlg2.cpp : implementation file
//

#include "stdafx.h"
#include "CompilerDesign.h"
#include "Dlg2.h"
#include <fstream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg2 dialog


CDlg2::CDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg2, CDialog)
	//{{AFX_MSG_MAP(CDlg2)
	ON_BN_CLICKED(IDC_OK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg2 message handlers
// Trans_for.cpp : 定义控制台应用程序的入口点。

#define stack_size 50
#define stackincrement 50

struct Node
{
	char type;
	CString sValue;
	int eValue;
};
Node node[100];
int nodeSize = 0;
void outSym(CString s);
void getSym(CString &s, int &i);
char ch;
void getChar(CString &s, int &i)
{
	ch = s[i];
	i++;
}
void getSym(CString &s, int &i)
{
	if (i == s.GetLength())
		;
	else
	{
		while (isspace(s[i]))
		{
			i++;
		}
		if (isalpha(s[i]) || s[i] == '_')
		{
			CString s1;
			getChar(s, i);
			s1 = s1 + ch;
			while (isalpha(s[i]) || isdigit(s[i]))
			{
				getChar(s, i);
				s1 = s1 + ch;
			}
			outSym(s1);
			getSym(s, i);
		}
		else if (isdigit(s[i]))
		{
			int temp = 0;
			CString string1;
			getChar(s, i);
			temp = temp * 10 + (int(ch) - 48);
			string1 = string1 + ch;
			while (isdigit(s[i]))
			{
				getChar(s, i);
				string1 = string1 + ch;
				temp = temp * 10 + (int(ch) - 48);
			}
			node[nodeSize].type = 'c';
			node[nodeSize].eValue = temp;
			node[nodeSize].sValue = string1;
			nodeSize++;
			getSym(s, i);
		}
		else if (s[i] == '(')
		{
			getChar(s, i);
			node[nodeSize].type = '(';
			node[nodeSize].sValue = '(';
			nodeSize++;
			getSym(s, i);
		}
		else if (s[i] == ')')
		{
			getChar(s, i);
			node[nodeSize].type = ')';
			node[nodeSize].sValue = ')';
			nodeSize++;
			getSym(s, i);
		}
		else if (s[i] == '{')
		{
			getChar(s, i);
			node[nodeSize].type = '{';
			node[nodeSize].sValue = '{';
			nodeSize++;
			getSym(s, i);
		}
		else if (s[i] == '}')
		{
			getChar(s, i);
			node[nodeSize].type = '}';
			node[nodeSize].sValue = '}';
			nodeSize++;
			getSym(s, i);
		}
		else if (s[i] == '=')
		{
			getChar(s, i);
			node[nodeSize].type = '=';
			node[nodeSize].sValue = '=';
			nodeSize++;
			getSym(s, i);
		}
		else if (s[i] == '<')
		{
			getChar(s, i);
			node[nodeSize].type = '<';
			node[nodeSize].sValue = '<';
			nodeSize++;
			getSym(s, i);
		}
		else if (s[i] == '>')
		{
			getChar(s, i);
			node[nodeSize].type = '>';
			node[nodeSize].sValue = '>';
			nodeSize++;
			getSym(s, i);
		}
		else if (s[i] == '+')
		{
			getChar(s, i);
			node[nodeSize].type = '+';
			node[nodeSize].sValue = '+';
			nodeSize++;
			getSym(s, i);
		}
		else if (s[i] == '-')
		{
			getChar(s, i);
			node[nodeSize].type = '-';
			node[nodeSize].sValue = '-';
			nodeSize++;
			getSym(s, i);
		}
		else if (s[i] == ';')
		{
			getChar(s, i);
			node[nodeSize].type = ';';
			node[nodeSize].sValue = ';';
			nodeSize++;
			getSym(s, i);
		}
		else
		{
			;
		}
	}
}
void outSym(CString s)
{
	int i = 0;
	if (s == "for")
	{
		node[nodeSize].type = 'f';      //关键字for
		node[nodeSize].sValue = "for";
		nodeSize++;
	}
	else
	{
		node[nodeSize].type = 'i';      //其他标识符
		node[nodeSize].sValue = s;

		nodeSize++;
	}
}


////////////////////////////////////////////////////////////////////////////////////
int p = 0, q = 0, zh, sh, x;                         //全局变量
char Vn[7] = { 'S', 'E', 'F', 'G', 'X', 'Y', 'H' };   //非终结符
char Vt[14] = { 'f', '(', ';', ')', '{', '}', 'i', '=', 'c', '<', '+', '>', '-', '#' };  //终结符
CString number[5];
typedef struct {
	char *bottom;
	char *top;
	int size;
	// char data[stack_size];
}stack;

int Initstack(stack &s)        //初始化栈
{
	s.bottom = (char *)malloc(stack_size*sizeof(char));
	if (!s.bottom) exit(-1);
	s.top = s.bottom;
	s.size = stack_size;
	return(1);
}
int push(stack &s, char e)      //入栈
{
	//int i;
	if (s.top - s.bottom >= s.size){
		s.bottom = (char *)realloc(s.bottom, (stack_size + stackincrement)*sizeof(char));
		if (!s.bottom) exit(-1);
		s.top = s.bottom + s.size;
		s.size += stackincrement;

	}
	*s.top++ = e;

	//   cout<<e<<"进s栈"<<"        ";
	return(1);
}
int push2(stack &s, int e)      //入栈
{
	//int i;
	if (s.top - s.bottom >= s.size){
		s.bottom = (char *)realloc(s.bottom, (stack_size + stackincrement)*sizeof(char));
		if (!s.bottom) exit(-1);
		s.top = s.bottom + s.size;
		s.size += stackincrement;

	}
	*s.top++ = e;

	//    cout<<e<<"进t栈"<<"        ";
	return(1);
}
char pop(stack &s, char *e)       //出栈
{
	if (s.top == s.bottom) return(0);
	*e = *--s.top;
	//   cout<<*e<<"出s栈"<<"        ";
	return(*e);
}
int pop2(stack &s, int *e)       //出栈
{
	if (s.top == s.bottom) return(0);
	*e = *--s.top;

	//   cout<<*e<<"出t栈"<<"        ";
	return(1);
}
int action(int m, int n, char a)    //ACTION表
{
	int i;
	int act[45][14] = {
			{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45 },
			{ 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0 },
			{ 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 15, 0, 0 },
			{ 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103 },
			{ 0, 0, 0, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 19, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 0, 0, 0 },
			{ 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 0 },
			{ 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104 },
			{ 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106 },
			{ 0, 0, 0, 0, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 27, 0, 0, 0 },
			{ 0, 0, 0, 0, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 29, 0 },
			{ 0, 0, 0, 0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 0 },
			{ 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105 },
			{ 0, 0, 0, 0, 0, 0, 31, 0, 0, 0, 0, 0, 0, 0 },
			{ 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107 },
			{ 0, 0, 33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 34, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 37, 0, 38, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 39, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41, 0, 0, 0 },
			{ 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102 },
			{ 0, 0, 0, 0, 0, 0, 42, 0, 43, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 44, 0, 0, 0, 0, 0, 0, 0 },
			{ 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108 },
			{ 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109 },
			{ 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110 },
	};
	for (i = 0; i<n; i++)
		if (a == Vt[i])
			break;
	if (i == n && a != Vt[n - 1]) return(0);
	else
	{
		zh = act[m][i];
		//if(zh==0)cout<<"出错"<<endl;
		//else return(zh);  
		return(zh);
	}
}
int go(int m, int n, char a)    //goto表
{
	int i;
	int go[45][7] = {
			{ 1, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 4, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 8, 0, 9, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 16, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 18, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 30 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 32 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0 },

	};
	for (i = 0; i<n; i++)
		if (a == Vn[i])
			break;
	if (i == n && a != Vn[n - 1]) return(0);
	else
	{
		sh = go[m][i];
		//if(sh==0)cout<<"出错";
		//else return(sh);  
		return(sh);
	}
}

void CDlg2:: work()
{
	CString str0 = "( ";
	CString str1 = "    ";
	CString str2 = " )\r\n";
	CString zf;
	char ch, y;
	int x, e, u, ok = 1;
	int i = 0, index = 0;
	int h = 0;
	int r;
	int k1 = 0;
	char st[40];
	CString ah[40];
	stack s;
	stack t;
	SetDlgItemText(IDC_OUT,"");
	CString in_s;
    char in_c[100];
	GetDlgItemText(IDC_FILENAME,in_s);
    ifstream iii(in_s);
    iii>>in_c;
    zf=in_c;
    SetDlgItemText(IDC_DISPLAY,zf);
	//cout << "输入for语句：" << endl;
//////////////////////////////////////////////////////////////////////////////!!!!!!
	//getline(cin, zf);
	getSym(zf, i);
	r = nodeSize;
	CString str_cf;
	CString str_c;
	CString str_i;
	int count=0;
	for (i = 0; i<r; i++)
	{
		st[i] = node[i].type;
		if(st[i]=='f')
		{
			GetDlgItemText(IDC_CF,str_cf);
			CString temp_str3="关键字：for\r\n";
			SetDlgItemText(IDC_CF,str_cf+temp_str3);			
		}
		else if (st[i]=='i')
		{
			CString temp_str3=node[i].sValue;
			str_i=str_i+temp_str3+" ";
		}
		else if(st[i]=='c')
		{
			CString temp_str3=node[i].sValue;
			str_c=str_c+temp_str3+" ";
			number[count++]=node[i].sValue;
		}
	}
	GetDlgItemText(IDC_CF,str_cf);
	SetDlgItemText(IDC_CF,str_cf+"符号："+str_i+"\r\n"+"常数："+str_c+"\r\n");

	//cout << "词法分析的结果：" << endl;
	for (i = 0; i<r; i++){
		ah[i] = node[i].sValue;    //测试
		//cout << ah[i] << ",";
	}
	//cout << endl;


	Initstack(s);
	Initstack(t);


	push(s, '#');
	push2(t, 0);
	// cout<<"\t";  
	//cout << "输出的四元式：" << endl;
	SetDlgItemText(IDC_YF,"动作      符号      GOTO\r\n");
	while (ok == 1)
	{
		ch = st[index];
		index++;
		// cout<<endl<<ch<<"分析.....";
		//cout<<endl;  
		y = ch;
		if (ch == '}'){
			y = '#';
			//cout<<"q="<<q<<endl; 
			k1 = action(1, 14, y);
			//cout<<"K="<<k1<<endl;
		}
		//  cout<<"y="<<y<<endl ;  //y是终结符
		pop2(t, &q);   //这两句主要是为了得到当前的q值
		push2(t, q);
		//cout<<endl;
		//   cout<<"q="<<q<<endl ;   //q是0~9的数字

		u = action(q, 14, y);

		//   cout<<"u="<<u<<endl ;

		if (action(q, 14, y)>0 && action(q, 14, y)<45){
			CString strget;
			GetDlgItemText(IDC_YF,strget);
			CString str00;
			
			//          cout<<"移进"<<endl;
			push(s, ch);
			push2(t, zh);
			CString temp_str1=ch;
			CString temp_str2;
			temp_str2.Format("%d",zh);
			str00="移进         "+temp_str1+"           "+temp_str2+"\r\n";
			SetDlgItemText(IDC_YF,strget+str00);
			// q=zh;
		}
		if (action(q, 14, y)>100 && action(q, 14, y) <= 110)
		{
			//        cout<<"进行规约"<<endl;
			CString strget;
			GetDlgItemText(IDC_YF,strget);
			
			SetDlgItemText(IDC_YF,strget+"进行规约\r\n");
			switch (zh){

			case 101: //cout<<endl;
				for (i = 0; i<12; i++){
					pop(s, &y); pop2(t, &x);
					//cout<<endl;
				}
				push(s, 'S');
				pop2(t, &e);
				push2(t, e);
				go(e, 7, 'S');  //查询GOTO表
				push2(t, sh);  //替换后的数字
				index--;
				break;

			case 102:// cout<<endl;
				for (i = 0; i<12; i++){
					pop(s, &y); pop2(t, &x);
					//cout<<endl;
				}
				push(s, 'S');
				pop2(t, &e);
				push2(t, e);
				go(e, 7, 'S');
				push2(t, sh);
				index--;
				break;
			case 103:
				{// cout<<endl;
				char a[3]; h = h + 1;
				for (i = 0; i<3; i++){
					a[i] = pop(s, &y);
					pop2(t, &x);
					//cout<<endl;
				}


				push(s, 'E');
				pop2(t, &e);
				push2(t, e);
				go(e, 7, 'E');
				push2(t, sh);
				//	cout<<endl;	
                CString str00;
                CString strget;
                GetDlgItemText(IDC_OUT, strget);
                CString str01 =  a[1];
                CString str02 =  a[0];
                CString str03 =  a[2];
                str00 = str0 + str01 + str1 + number[0] + str1 + str1 + str1 + str03 + str2+"l:\r\n";////////////////////////2
                SetDlgItemText(IDC_OUT, strget + str00);
                //char temp[100];
                //sprintf(temp, "%d", h);
                //CString csStr(szBuf);
				//cout << "(" << h << ") (" << a[1] << "," << a[0] << ",--," << a[2] << ")" << endl;
				index--;
				}
				break;
			case 104:
			{
				//cout<<endl;
				char b[3]; h = h + 1;
				for (i = 0; i<3; i++){
					b[i] = pop(s, &y); pop2(t, &x);
					//cout<<endl;
				}

				push(s, 'F');
				pop2(t, &e);
				push2(t, e);
				go(e, 7, 'F');
				push2(t, sh);
				// cout<<endl;
                CString str00;
                CString strget;
                GetDlgItemText(IDC_OUT, strget);
                CString str02 =  b[0];
                CString str03 =  b[2];
                str00 = "(j>=   " + str03 + "    "+number[1]+"   over)\r\n";//i++时的操作
                SetDlgItemText(IDC_OUT, strget + str00);
				//cout << "(" << h << ") " << "if " << b[2] << " > " << b[0] << " goto over" << endl;
				index--;
			}
				break;
			
			case 105:
				{//cout << endl;
				h = h + 1; char c[3];
				for (i = 0; i<3; i++){
					c[i] = pop(s, &y); pop2(t, &x);
					//cout<<endl;
				}
				push(s, 'G');
				pop2(t, &e);
				push2(t, e);
				go(e, 7, 'G');
				push2(t, sh);
				//	cout<<endl;
                CString str00;
                CString strget;
                GetDlgItemText(IDC_OUT, strget);
                CString str02 =  c[0];
                CString str03 =  c[2];
                str00 = str0 + str02 + str1 + str03 + str1 + "1" + str1 + "t1" +str2;
                SetDlgItemText(IDC_OUT, strget + str00);
				//cout << "(" << h << ") (" << c[0] << "," << c[2] << ",1," << "t1" << ")" << endl;
                GetDlgItemText(IDC_OUT, strget);
                str00 = str0 + "=" + str1 + "t1" + str1 + str1 + str1 + str03 +str2;
                SetDlgItemText(IDC_OUT, strget + str00);
                //cout << "(" << h + 1 << ") (" << "=, t1, -- ," << c[2] << ")" << endl;
				index--;
				}
				break;
			case 106:
				{//cout << endl;
				h = h + 1; char d[3];
				for (i = 0; i<3; i++){
					d[i] = pop(s, &y); pop2(t, &x);
					//cout<<endl;
				}
				push(s, 'X');
				pop2(t, &e);
				push2(t, e);
				go(e, 7, 'X');
				push2(t, sh);
				//cout<<endl; 
                CString str00;
                CString strget;
                GetDlgItemText(IDC_OUT, strget);
                CString str02 =  d[0];
                CString str03 =  d[2];
                str00 = "(j<=  " + str03 + "    "+number[1] + "     over)\r\n";//i--时的操作
                SetDlgItemText(IDC_OUT, strget + str00);
				//cout << "(" << h << ") " << "if " << d[2] << " < " << d[0] << " goto over" << endl;
				index--;
				}
				break;
			case 107://cout << endl;
				{
				h = h + 1; char f[3];
				for (i = 0; i<3; i++){
					f[i] = pop(s, &y); pop2(t, &x);
					//cout<<endl;
				}
				push(s, 'Y');
				pop2(t, &e);
				push2(t, e);
				go(e, 7, 'Y');
				push2(t, sh);
				//cout<<endl;
                CString str00;
                CString strget;
                GetDlgItemText(IDC_OUT, strget);
                CString str02 =  f[0];
                CString str03 =  f[2];
                str00 = str0 + str02 + str1 + str03 + str1 + "1" + str1 + "t1" +str2;
                SetDlgItemText(IDC_OUT, strget + str00);
				//cout << "(" << h << ") (" << f[0] << "," << f[2] << ",1," << "t1" << ")" << endl;
                GetDlgItemText(IDC_OUT, strget);
                str00 = str0 + "=" + str1 + "t1" + str1 + str1 + str1 + str03 +str2;
                SetDlgItemText(IDC_OUT, strget + str00);
                //cout << "(" << h + 1 << ") (" << "= ,t1,--, " << f[2] << ")" << endl;
				index--;
				}
				break;
			case 108: 
				{//cout<<endl;
				h = h + 1; char g[5];
				for (i = 0; i<5; i++){
					g[i] = pop(s, &y); pop2(t, &x);
					//cout<<endl;
				}

				push(s, 'H');
				pop2(t, &e);
				push2(t, e);
				go(e, 7, 'H');
				push2(t, sh);
				//cout<<endl;
                CString str00;
                CString strget;
                GetDlgItemText(IDC_OUT, strget);
                CString str01 =  g[1];
                CString str02 =  g[0];
                CString str03 =  g[2];
                CString str04 =  g[3];
                CString str05 =  g[4];
                str00 = str0 + str01 + str1 + str03 + str1 + number[2] + str1 + "t2"+ "101010"+str2;
                SetDlgItemText(IDC_OUT, strget + str00);
				//cout << "(" << h + 1 << ") (" << g[1] << "," << g[2] << "," << g[0] << "," << "t2" << ")" << endl;
				GetDlgItemText(IDC_OUT, strget);
                str00 = str0 + str04 + str1 + "t2" + str1 + str1 + str1 + str05+ str2+ "goto l\r\nover11 11 11 11\r\n";
                SetDlgItemText(IDC_OUT, strget + str00);
                //cout << "(" << h + 2 << ") (" << g[3] << ",t2,--," << g[4] << ")" << endl;
				//cout << "(" << h + 2 << ")" << "goto over" << endl;
				index--;
				}
				break;
			case 109:
				{//cout<<endl;
				h = h + 1; char j[5];
				for (i = 0; i<5; i++){
					j[i] = pop(s, &y); pop2(t, &x);
					//cout<<endl;
				}
				push(s, 'H');
				pop2(t, &e);
				push2(t, e);
				go(e, 7, 'H');
				push2(t, sh);
				//cout<<endl; 
                CString str00;
                CString strget;
                GetDlgItemText(IDC_OUT, strget);
                CString str01 =  j[1];
                CString str02 =  j[0];
                CString str03 =  j[2];
                CString str04 =  j[3];
                CString str05 =  j[4];
                str00 = str0 + str01 + str1 + str03 + str1 + number[2]  + str1 + "t2"+str2;
                SetDlgItemText(IDC_OUT, strget + str00);
				//cout << "(" << h + 1 << ") (" << j[1] << "," << j[2] << "," << j[0] << "," << "t2" << ")" << endl;
				GetDlgItemText(IDC_OUT, strget);
                str00 = str0 + str04 + str1 + "t2" + str1 + str1 + str1 + str05+ str2+ "goto l\r\nover\r\n";
                SetDlgItemText(IDC_OUT, strget + str00);
				//cout << "(" << h + 2 << ") (" << j[3] << ",t2,--," << j[4] << ")" << endl;
				//cout << "(" << h + 3 << ")" << "goto over" << endl;

				index--;
				}
				break;
			case 110:
                {//cout<<endl;
				h = h + 1; char l[5];
				for (i = 0; i<5; i++){
					l[i] = pop(s, &y); pop2(t, &x);
					//cout<<endl;
				}

				push(s, 'H');
				pop2(t, &e);
				push2(t, e);
				go(e, 7, 'H');
				push2(t, sh);
				// cout<<endl;
                
                CString str00;
                CString strget;
                GetDlgItemText(IDC_OUT, strget);
                CString str01 =  l[1];
                CString str02 =  l[0];
                CString str03 =  l[2];
                CString str04 =  l[3];
                CString str05 =  l[4];
                str00 = str0 + str01 + str1 + str03 + str1 + str02 + str1 + "t2"+ "141414141414"+str2;
                SetDlgItemText(IDC_OUT, strget + str00);
				//cout << "(" << h + 1 << ") (" << l[1] << "," << l[2] << "," << l[0] << "," << "t2" << ")" << endl;
				GetDlgItemText(IDC_OUT, strget);
                str00 = str0 + str04 + str1 + "t2" + str1 + str1 + str1 + str05+ str2+ "goto over1551515151\r\n";
                SetDlgItemText(IDC_OUT, strget + str00);
				
				//cout << "(" << h + 2 << ") (" << l[3] << ",t2,--," << l[4] << ")" << endl;
				//cout << "(" << h + 3 << ")" << "goto over" << endl;


				index--;
            }
				break;
			}
		
        }// while 结束
		if (k1 == 45)
		{
			//cout << "分析成功" << endl;
			MessageBox("转化成功");
			ok = 0;
		}
		else if (u == 0) {
            //cout << "q=" << action(q, 14, y) << endl;
            //cout << "出错" << endl; 
            MessageBox("转化出错");
            break;
        }
		}
	
}


void CDlg2::OnOk() 
{
	CDlg2:: work();
}
