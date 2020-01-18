// Dlg4.cpp : implementation file
//

#include "stdafx.h"
#include "CompilerDesign.h"
#include "Dlg4.h"
#include "windows.h"
#include <fstream>
#include <stack>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg4 dialog


CDlg4::CDlg4(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg4::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg4)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}




BEGIN_MESSAGE_MAP(CDlg4, CDialog)
	//{{AFX_MSG_MAP(CDlg4)
		// NOTE: the ClassWizard will add message map macros here
	ON_BN_CLICKED(IDC_OK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg4 message handlers

struct Table {		//action-goto表
	int action[8];
	int go[2];
}act_go[15];

char gram_left[7];		//文法定义
string gram_right[7];
int pop_back[7];		//弹出字符个数
int t = 1;		//跳转使用

string show_CF;		//IDC_CF展示框使用
vector<CString> cs1, cs2, cs3;		//状态栈展示使用

BOOL CDlg4::OnInitDialog()		//显示栈初始化
{
	CDialog::OnInitDialog();

	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_list.InsertColumn(0, "状态", LVCFMT_CENTER);
	m_list.InsertColumn(1, "符号栈", LVCFMT_CENTER);
	m_list.InsertColumn(2, "输入串", LVCFMT_CENTER);

	m_list.SetColumnWidth(0, 200);
	m_list.SetColumnWidth(1, 150);
	m_list.SetColumnWidth(2, 150);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}		//

void init_table()
{
	ifstream infile("action.txt", ios::in);
	for (int i = 0; i < 15; i++) {
		for(int k = 0; k < 8; k++)
			infile >> act_go[i].action[k];
		for (int k = 0; k < 2; k++)
			infile >> act_go[i].go[k];
	}
	gram_left[0] = 'S'; gram_left[1] = 'S'; gram_left[2] = 's'; gram_left[3] = 's'; gram_left[4] = 's'; gram_left[5] = 's'; gram_left[6] = 's';
	gram_right[0] = "Ss"; gram_right[1] = "s"; gram_right[2] = "a;"; gram_right[3] = "is"; gram_right[4] = "ises"; gram_right[5] = "ws"; gram_right[6] = "{S}";
	pop_back[0] = 2; pop_back[1] = 1; pop_back[2] = 2; pop_back[3] = 2; pop_back[4] = 4; pop_back[5] = 2; pop_back[6] = 3;
}

vector<string> mySplit(const string& str, string sp_string)		//str为要分割的字符串
{
	vector<string> vecString;
	int sp_stringlen = sp_string.length();
	int lastPosition = 0;
	int index = -1;
	while ((index = str.find(sp_string, lastPosition)) != -1) {
		vecString.push_back(str.substr(lastPosition, index - lastPosition));
		lastPosition = index + sp_stringlen;
	}
	string lastStr = str.substr(lastPosition);
	if (!lastStr.empty()) {
		vecString.push_back(lastStr);
	}
	return vecString;
}

string myReplaceAll(const string& str, string org_str, string rep_str)		//替换函数,org_str和rep_str为源字符串和替换的字符串
{
	vector<string> delimVec = mySplit(str, org_str);
	if (delimVec.size() <= 0) {
		cout << "can not find string org_str" << endl;
		return str;
	}
	string target("");
	for (vector<string>::iterator iter = delimVec.begin(); iter != delimVec.end(); ++iter) {
		if (iter + 1 == delimVec.end())		//结尾特殊处理
			target = target + (*iter);
		else
			target = target + (*iter) + rep_str;
	}
	return target;
}

int get_prior(char c)
{
	if (c == '*' || c == '/')	return 7;
	else if (c == '+' || c == '-')	return 6;
	else if (c == '<' || c == '>' || c == '[' || c == ']' || c == '?' || c == '@')	return 5;
	else if (c == '!') return 4;
	else if (c == '&') return 3;
	else if (c == '|') return 2;
	else if (c == '(') return 1;
	else if (c == '=') return 0;
	return 0;
}

int get_index(char c)
{
	if (c == 'a')
		return 0;
	else if (c == ';')
		return 1;
	else if (c == 'i')
		return 2;
	else if (c == 'e')
		return 3;
	else if (c == 'w')
		return 4;
	else if (c == '{')
		return 5;
	else if (c == '}')
		return 6;
	else if (c == '#')
		return 7;
	return 0;
}

string reverse_poland(string s)
{
	string new_str;		//转换后的逆波兰式
	char *str = (char*)s.c_str();
	
	stack<char> op;		//符号栈
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] != '(' && str[i] != ')' && str[i] != '<' && str[i] != '>'
			&& str[i] != '=' && str[i] != '&' && str[i] != '|'
			&& str[i] != '!' && str[i] != '+' && str[i] != '-'
			&& str[i] != '*' && str[i] != '/') {
			new_str = new_str + str[i];
		}
		else {
			if (str[i] == '(' || str[i] == ')') {
				if (str[i] == '(')
					op.push(str[i]);
				else {
					while (op.top() != '(') {;
						new_str = new_str + op.top();
						op.pop();
					}
					op.pop();
				}
			}
			else {
				if (str[i] == '&' || str[i] == '|') {
					i++;
				}
				if (i + 1 < strlen(str) && (str[i] == '<' || str[i] == '>' || str[i] == '!' || str[i] == '=')
					&& str[i + 1] == '=') {
					if (str[i] == '<') str[i + 1] = '[';
					else if (str[i] == '>') str[i + 1] = ']';
					else if (str[i] == '=') str[i + 1] = '@';
					else str[i + 1] = '?';
					i++;
				}
				if (op.empty()) op.push(str[i]);
				else {
					if (get_prior(str[i]) > get_prior(op.top())) {
						op.push(str[i]);
					}
					else {
						while ((!op.empty()) && get_prior(str[i]) <= get_prior(op.top())) {
							new_str = new_str + op.top();
							op.pop();
						}
						op.push(str[i]);
					}
				}
			}
		}
	}
	while (!op.empty()) {
		new_str = new_str + op.top();
		op.pop();
	}

	return new_str;
}

string quaternary_change(string str, int &number)		//转化四元式
{
	char* strch = (char*)str.c_str();
	stack<string> strop;		//操作数和符号混合栈
	string quat = { "" };		//转化后的四元式
	int length = str.length();
	for (int i = 0; i < length; i++) {
		string str_temp = { "" };
		str_temp = str_temp + strch[i];
		strop.push(str_temp);
		int flag = 0;
		if (strch[i] == '>' || strch[i] == '<' || strch[i] == '+' || strch[i] == '-'
			|| strch[i] == '*' || strch[i] == '/' || strch[i] == '[' || strch[i] == ']'
			|| strch[i] == '@' || strch[i] == '?') {
			string op = strop.top();
			strop.pop();
			if (strch[i] == '@') {
				op = "==";
				flag = 1;
			}
			else if (strch[i] == '?') {
				op = "!=";
				flag = 1;
			}
			else if (strch[i] == '&' || strch[i] == '|') {
				op = op + op;
				flag = 1;
			}
			else if (strch[i] == '[') {
				op = "<=";
				flag = 1;
			}
			else if (strch[i] == ']') {
				op = ">=";
				flag = 1;
			}

			string source2 = strop.top();	strop.pop();		//(,*,,)
			string source1 = strop.top();	strop.pop();		//(,,*,)
			str_temp = { "" };
			if (flag == 0) {
				str_temp = str_temp + 'r' + to_string(number);
				number++;
			}
			else {
				str_temp = str_temp + "br" + to_string(number);
				number++;
			}
			strop.push(str_temp);
			string line = { "" };
			line = line + "(" + op + "," + source2 + "," + source1 + "," + str_temp + ")";
			quat = quat + line + "`";		// ` used for division
		}
		else if (strch[i] == '!') {		//(!,source, ,str_temp)
			string op = strop.top();	strop.pop();
			string source = strop.top();	strop.pop();
			str_temp = { "" };
			str_temp = str_temp + "br" + to_string(number);
			number++;
			strop.push(str_temp);
			string line = { "" };
			line = line + "(" + op + "," + source + ", ,"  + str_temp + ")";
			quat = quat + line + "`";
		}
		else if (strch[i] == '=') {		//(=,source, ,result)
			string op = strop.top();	strop.pop();
			string source = strop.top();	strop.pop();
			string result = strop.top();	strop.pop();
			string line = { "" };
			line = line + "(" + op + "," + source + ", ," + result + ")";
			quat = quat + line + "`";
		}
	}
	return quat;
}

vector<string> lr_parser(vector<string> s, vector<char> input)
{
	init_table();		//初始化act_go表
	stack<int> status;		//状态栈
	stack<char> instr;		//输入符号栈
	stack<string> infinstr;		//分析栈

	string str_cs1;	string str_cs2;	string str_cs3;		//压入vector前使用

	status.push(0);
	instr.push('#');

	str_cs1 = { "0" };		//初始化m_list的状态栏、符号栈、输入串
	str_cs2 = { "#" };
	for (vector<char>::iterator iter = input.begin() + 1; iter != input.end(); iter++)
		str_cs3 = str_cs3 + (*iter);
	cs1.push_back((CString)str_cs1.c_str());
	cs2.push_back((CString)str_cs2.c_str());
	cs3.push_back((CString)str_cs3.c_str());

	vector<string>::iterator iter_str = s.begin();
	string s_now = { "" };
	vector<char>::iterator iter_ch = input.begin();
	iter_ch++;
	char c_now = (*iter_ch);
	bool jump = 1;
	int t = 1;

	while (jump) {
		int action = act_go[status.top()].action[get_index(c_now)];
		if (action == -1) break;
		if (action == 0) {
			cout << "Get the wrong parser!" << endl;
			vector<string> error = { "" };
			return error;
		}
		else if ((action / 100) == 1) {
			action = action - 100;
			status.push(action);
			instr.push(c_now);

			str_cs1 = str_cs1 + to_string(action);		//显示栈操作
			str_cs2 = str_cs2 + c_now;
			str_cs3 = str_cs3.substr(1, str_cs3.length() - 1);

			++iter_ch;
			c_now = (*iter_ch);
			if (iter_str != s.end()) s_now = (*iter_str++);
			if (s_now.length() > 0) infinstr.push(s_now);

			cs1.push_back((CString)str_cs1.c_str());		//显示栈操作
			cs2.push_back((CString)str_cs2.c_str());
			cs3.push_back((CString)str_cs3.c_str());
		}
		else if ((action / 100) == 2) {
			action = action - 200;
			int popnum = pop_back[action - 1];

			str_cs1 = str_cs1.substr(0, str_cs1.length() - popnum);
			str_cs2 = str_cs2.substr(0, str_cs2.length() - popnum);

			while (popnum > 0) {
				status.pop();
				instr.pop();
				popnum--;
			}
			instr.push(gram_left[action - 1]);
			str_cs2 = str_cs2 + gram_left[action - 1];		//显示栈操作

			int nowstatus = status.top();		//GOTO
			if (instr.top() == 'S') {
				status.push(act_go[nowstatus].go[0]);
				str_cs1 = str_cs1 + to_string(act_go[nowstatus].go[0]);		//显示栈操作
			}
			else if (instr.top() == 's') {
				status.push(act_go[nowstatus].go[1]);
				str_cs1 = str_cs1 + to_string(act_go[nowstatus].go[0]);		//显示栈操作
			}
			cs1.push_back((CString)str_cs1.c_str());		//显示栈操作
			cs2.push_back((CString)str_cs2.c_str());
			cs3.push_back((CString)str_cs3.c_str());
			
			switch (action) {
			case 1: {
				string str1 = infinstr.top();	infinstr.pop();		//stmt
				string str2 = infinstr.top();	infinstr.pop();		//stmts
				infinstr.push(str2 + str1);
				break;
			}
			case 4: {
				string str1 = infinstr.top();	infinstr.pop();		//stmt
				string str2 = infinstr.top();	infinstr.pop();		//if(bool)
				string find_bool = { "" };
				for (int i = str2.length() - 1; str2.at(i) != ','; i--) {		//找到bool表达式
					if (str2.at(i) != ')' && str2.at(i) != '`')
						find_bool = str2.at(i) + find_bool;
				}
				string str3 = str2 + "(j!, " + find_bool + ", ,jump" + to_string(t) 
					+ ")`" + str1 + "[j" + to_string(t) + "]`";
				infinstr.push(str3);
				t++;
				break;
			}
			case 5: {
				string str1 = infinstr.top();	infinstr.pop();		//Stmt
				string str2 = infinstr.top();	infinstr.pop();		//else
				string str3 = infinstr.top();	infinstr.pop();		//if(bool)stmt
				string find_bool = { "" };
				for (int i = str3.length() - 1; str3.at(i) != ','; i--) {
					if (str3.at(i) != ')' && str3.at(i) != '`')
						find_bool = str3.at(i) + find_bool;
				}
				string str4 = str3 + "(j!, " + find_bool + ", ,jump" + to_string(t + 1) + ")`" 
					+ str2 + "[j" + to_string(t + 1) + "]`" + str1;
				infinstr.push(str4);
				t = t + 2;
				break;
			}
			case 6: {
				string str1 = infinstr.top();	infinstr.pop();		//Stmt
				string str2 = infinstr.top();	infinstr.pop();		//while(bool)
				string find_bool = { "" };
				for (int i = str2.length() - 1; str2.at(i) != ','; i--) {		//找到bool表达式
					if (str2.at(i) != ')' && str2.at(i) != '`')
						find_bool = str2.at(i) + find_bool;
				}
				string str3 = str2 + "(j!, " + find_bool + ", ,jump" + to_string(t) + ")`" + "[j" + to_string(t + 1) 
					+ "]`" + str1 + str2 + "(j, " + find_bool + ", ,jump" + to_string(t + 1) + ")`" + "[j" + to_string(t) + "]`";
				infinstr.push(str3);
				t = t + 2;
				break;
			}
			}
		}
	}
	string final = infinstr.top();	infinstr.pop();
	t = 101;
	unordered_map<int, int> jump_map;
	vector<string> final_result;
	vector<string> fin_4 = mySplit(final, "`");
	s.clear();

	for (vector<string>::iterator iter = fin_4.begin(); iter != fin_4.end(); ++iter) {
		string str = (*iter);
		if (str.at(0) == '(') {
			s.push_back(to_string(t) + ":" + str);
			t++;
		}
		else if (str.at(0) == '[') {
			int jump_to = stoi(str.substr(2, str.length() - 3));
			jump_map.insert({jump_to, t});
		}
	}
	s.push_back(to_string(t) + ":");	t++;
	for (vector<string>::iterator iter = s.begin(); iter != s.end(); ++iter) {
		string jump_fix = (*iter);
		if (jump_fix.find("jump") != jump_fix.npos) {
			int jump_num;
			char* jump_fixch = (char*)jump_fix.c_str();
			string stringnum = { "" };
			for (int i = strlen(jump_fixch) - 1; jump_fixch[i] != 'p'; i--) {
				if (jump_fixch[i] != ')') {
					stringnum = jump_fixch[i] + stringnum;
				}
			}
			jump_num = stoi(stringnum);
			jump_num = jump_map[jump_num];
			//final_result.push_back(jump_fix);
			final_result.push_back(myReplaceAll(jump_fix, ("jump" + stringnum), to_string(jump_num)));
		}
		else {
			final_result.push_back(jump_fix);
		}
	}
	for (vector<string>::iterator iter = final_result.begin(); iter != final_result.end(); ++iter) {
		cout << (*iter) << endl;
	}
	return final_result;
}

void CDlg4::analyse_show()
{
	CString show = show_CF.c_str();
	SetDlgItemText(IDC_CF, show);
}

string lexer(string code, int flag)		//词法分析，返回code符合文法标准
{
	vector<string> s4;		//去掉空格等等
	vector<string> ns4;		//if-else-while
	vector<char> input;		//向parser里面的输入串

	s4.push_back(code);
	for (vector<string>::iterator iter = s4.begin(); iter != s4.end(); ++iter) {
		string str = (*iter);
		char* strch = (char*)str.c_str();
		int length = str.length();
		for (int i = 0; i < length; i++) {		//delete' ' '\t' '\n'
			while (strch[i] == ' ' || strch[i] == '\t' || strch[i] == '\n') {
				if (i == length - 1) {
					length--;
					break;
				}
				for (int j = i; j < length - 1; j++) {
					strch[j] = strch[j + 1];
				}
				length--;
			}
		}
		if (length != 0) {		//separate{ } and ;
			string str2 = {""};
			int length_temp = 0;
			for (int i = 0; i < length; i++) {		//分开 s;
				if (strch[i] == ';') {
					ns4.push_back(str2);
					ns4.push_back(";");
					length_temp = 0;
					str2.clear();
				}
				else {
					if (strch[i] == '{' || strch[i] == '}') {		//分开{}
						if (length_temp != 0) {
							ns4.push_back(str2);
							length_temp = 0;
							str2.clear();
						}
						string s_temp;
						s_temp.push_back(strch[i]);
						ns4.push_back(s_temp);
					}
					else {
						//cout << strch[i] << endl;
						str2 = str2 + strch[i];
						length_temp++;
					}
				}
				if (i == length - 1 && strch[i] != ';' && length_temp != 0)		//可能是普通算术表达式
					ns4.push_back(str2);
			}
		}
	}
	//cout << ns4.front() << " " << s4.front() << endl;		//初始化vector如果为vector<string> str{""}则第一个元素会为空

	s4.clear();		//存放新的整合字符串
	for (vector<string>::iterator iter = ns4.begin(); iter != ns4.end(); ++iter) {		//分割if-else-while
		string str = (*iter);
		if (str.find("if") == str.npos && str.find("else") == str.npos && str.find("while") == str.npos) {
			s4.push_back(str);
			continue;
		}
		char* strch = (char*)str.c_str();
		int length = str.length();
		string str2 = { "" };
		for (int i = 0; i < length; i++) {
			if (i + 2 < length) {		//if case
				if (strch[i] == 'i' && strch[i + 1] == 'f' && strch[i + 2] == '(') {
					if (str2.length() != 0) {
						s4.push_back(str2);
						str2.clear();
					}
					str2 = "if(";
					i = i + 3;
					int t = 1;
					while (t != 0) {
						if (strch[i] == '(')
							t++;
						if (strch[i] == ')')
							t--;
						str2 = str2 + strch[i];
						i++;
					}
					s4.push_back(str2);
					str2.clear();
					i--;
					continue;
				}
			}
			if (i + 3 < length) {		//else case
				if (strch[i] == 'e' && strch[i + 1] == 'l' &&strch[i + 2] == 's' && strch[i + 3] == 'e') {
					if (str2.length() != 0) {
						s4.push_back(str2);
						str2.clear();
					}
					str2 = "else";
					i = i + 4;
					s4.push_back(str2);
					str2.clear();
					i--;
					continue;
				}
			}
			if (i + 5 < length) {		//while case
				if (strch[i] == 'w' && strch[i + 1] == 'h' && strch[i + 2] == 'i' 
					&& strch[i + 3] == 'l' && strch[i + 4] == 'e') {
					if (str2.length() != 0) {
						s4.push_back(str2);
						str2.clear();
					}
					str2 = "while(";
					i = i + 6;
					int t = 1;
					while (t != 0) {
						if (strch[i] == '(')
							t++;
						if (strch[i] == ')')
							t--;
						str2 = str2 + strch[i];
						i++;
					}
					s4.push_back(str2);
					str2.clear();
					i--;
					continue;
				}
			}

			str2 = str2 + strch[i];

			if (i == length - 1 && str2.length() != 0) {
				s4.push_back(str2);
				str2.clear();
			}
		}
	}

	string showtext = {""};
	for (vector<string>::iterator iter = s4.begin(); iter != s4.end(); ++iter) {
		string str = (*iter);
		showtext = showtext + str;
		showtext = showtext + '\n';
		show_CF = show_CF + str;
		show_CF = show_CF + "\r\n";
	}
	showtext = showtext.substr(0, showtext.length() - 1);
	myReplaceAll(showtext, "\n;", ";");		//替换符号输出

	myReplaceAll(show_CF, "\n", "\r\n");		//输出到对话框需要把\n换成文本支持换行符\r\n

	ofstream ofile;		//文件输出
	ofile.open("lexer.txt", ios::out);
	stringstream ss;
	ss << showtext;
	ofile << ss.str();
	ofile.close();

	showtext.clear();		//清空
	ns4.clear();
	input.push_back('#');
	ns4.push_back("");
	for (vector<string>::iterator iter = s4.begin(); iter != s4.end(); ++iter) {
		string str = (*iter);
		if (str.find("if") != str.npos) {
			input.push_back('i');
			ns4.push_back(str.substr(3, str.length() - 4));
		}
		else if (str.find("else") != str.npos) {
			input.push_back('e');
			ns4.push_back("");
		}
		else if (str.find("while") != str.npos) {
			input.push_back('w');
			ns4.push_back(str.substr(6, str.length() - 7));
		}
		else if (str.find(";") != str.npos) {
			input.push_back(';');
			ns4.push_back("");
		}
		else if (str.find("{") != str.npos) {
			input.push_back('{');
			ns4.push_back("");
		}
		else if (str.find("}") != str.npos) {
			input.push_back('}');
			ns4.push_back("");
		}
		else {
			input.push_back('a');
			ns4.push_back(str);
		}
	}
	input.push_back('#');
	ns4.push_back("");

	int number = 0;
	s4.clear();
	for (vector<string>::iterator iter = ns4.begin(); iter != ns4.end(); ++iter) {
		string str = (*iter);
		str = reverse_poland(str);
		str = quaternary_change(str, number);
		s4.push_back(str);
		//cout << str  << " " << number << endl;
	}
	vector<string> final_result = lr_parser(s4, input);
	for (vector<string>::iterator iter = final_result.begin(); iter != final_result.end(); ++iter) {
		showtext = showtext + (*iter);
		showtext = showtext + "\r\n";
	}
	//for (vector<char>::iterator iter = input.begin(); iter != input.end(); ++iter)
	//	cout << (*iter) << endl;
	return showtext;
}

void CDlg4::stack_show()		//显示状态栈m_list
{
	vector<CString>::iterator iter2 = cs2.begin();
	vector<CString>::iterator iter3 = cs3.begin();
	for (vector<CString>::iterator iter1 = cs1.begin(); iter1 != cs1.end(); ++iter1) {
		int row = m_list.GetItemCount();
		string str1 = (*iter1);	string str2 = (*iter2);	string str3 = (*iter3);
		m_list.InsertItem(row, "");
		m_list.SetItemText(row, 0, (CString)str1.c_str());
		m_list.SetItemText(row, 1, (CString)str2.c_str());
		m_list.SetItemText(row, 2, (CString)str3.c_str());
		++iter2;
		++iter3;
	}
}

void CDlg4::OnOk()
{
	CString in_s;
	string code;	//读入code
	string text;
	int k = 0;
	GetDlgItemText(IDC_FILENAME, in_s);
	ifstream in(in_s);
	while (!in.eof()) {
		getline(in, text);
		code = code + text;
	}
	CString show_code = code.c_str();
	SetDlgItemText(IDC_DISPLAY, show_code);
	string showtext = lexer(code, 2);
	CString cs = showtext.c_str();
	SetDlgItemText(IDC_OUT, cs);
	analyse_show();
	stack_show();

	ofstream ofile;		//文件输出
	ofile.open("parserResult.txt", ios::out);
	stringstream ss;
	ss << showtext;
	ofile << ss.str();
	ofile.close();
}