/* 2351577 大数据 张宸浩 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//如有必要，可以加入其它头文件
using namespace std;

#if !ENABLE_LIB_COMMON_TOOLS //不使用lib才有效

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */

static string itos(int n) {//将int类型直接转换为string类型 只允许3位数字及以下
	string s;
	int digit = 0, sub = n;
	while (1) {
		if (!sub)
			break;
		sub %= 10;
		digit++;
	}
	if (!digit)
		return "0";
	char* cc = new(nothrow) char[digit];
	if (cc == NULL) {
		cout << "ERROR" << endl;
	}
	for (int i = 0; i < digit; i++) {
		cc[i] = char('0' + n % 10);
		n /= 10;
	}
	for (int i = 0; i < digit; i++)
		s[i] = cc[digit - i - 1];

	delete[]cc;
	return s;
}

static string u_int_to_str(u_int n) {
	return to_string(n / 256 / 256 / 256) + '.' + to_string(n / 256 / 256 % 256) + '.' + to_string(n / 256 % 256) + '.' + to_string(n % 256);
}

static u_int str_to_u_int(string s) {
	int p1 = 0;
	while (s[p1] != '.') {
		p1++;
	}
	string s1 = s.substr(0, p1);
	int p2 = p1 + 1;
	while (s[p2] != '.') {
		p2++;
	}
	string s2 = s.substr(p1 + 1, p2 - p1 - 1);
	int p3 = p2 + 1;
	while (s[p3] != '.') {
		p3++;
	}
	string s3 = s.substr(p2 + 1, p3 - p2 - 1);
	string s4 = s.substr(p3 + 1, s.size() - p3);
	return (unsigned int)(stoi(s4) + stoi(s3) * 256 + stoi(s2) * 256 * 256 + stoi(s1) * 256 * 256 * 256);
}

static string typetos(ST_EXTARGS_TYPE type) {//将type转化为string输出
	string s;

	switch (type) {
		case ST_EXTARGS_TYPE::boolean:
			s = "Bool";
			break;
		case ST_EXTARGS_TYPE::int_with_default:
			s = "IntWithDefault";
			break;
		case ST_EXTARGS_TYPE::int_with_error:
			s = "IntWithError";
			break;
		case ST_EXTARGS_TYPE::int_with_set_default:
			s = "IntSETWithDefault";
			break;
		case ST_EXTARGS_TYPE::int_with_set_error:
			s = "IntSETWithError";
			break;
		case ST_EXTARGS_TYPE::double_with_default:
			s = "DoubleWithDefault";
			break;
		case ST_EXTARGS_TYPE::double_with_error:
			s = "DoubleWithError";
			break;
		case ST_EXTARGS_TYPE::double_with_set_default:
			s = "DoubleSETWithDefault";
			break;
		case ST_EXTARGS_TYPE::double_with_set_error:
			s = "DoubleSETWithError";
			break;
		case ST_EXTARGS_TYPE::str:
			s = "String";
			break;
		case ST_EXTARGS_TYPE::str_with_set_default:
			s = "StringSETWithDefault";
			break;
		case ST_EXTARGS_TYPE::str_with_set_error:
			s = "StringSETWithError";
			break;
		case ST_EXTARGS_TYPE::ipaddr_with_default:
			s = "IPAddrWithDefault";
			break;
		case ST_EXTARGS_TYPE::ipaddr_with_error:
			s = "IPAddrWithError";
			break;
		default:
			s = "ERROR";
			break;
	}

	return s;
}

static void space(int n) {//输出空格
	for (int i = 0; i < n; i++)
		cout << ' ';
	return;
}
static void space(unsigned int n) {//输出空格
	for (unsigned int i = 0; i < n; i++)
		cout << ' ';
	return;
}

static string bool_de_s(bool n) {//将bool转换为str输出
	if (n)
		return "true";
	else
		return "false";
}

static string str_de_s(string s) {//将str中空串变为斜杠
	if (s == "")
		return "/";
	else
		return s;
}

static string bool_va_s(bool n, int exist) {//value中的转换，但好像两种都一样
	if (!exist)
		return "/";
	else
		return "true";
}

static string int_va_s(int value, int exist) {//int转换
	if (!exist)
		return "/";
	else
		return to_string(value);
}

static string double_va_s(double value, int exist) {
	if (!exist)
		return "/";
	else
		return to_string(value);
}

static string str_va_s(string value, int exist) {
	if (!exist)
		return "/";
	else
		return value;
}

static string ip_va_s(u_int value, int exist) {
	if (!exist)
		return "/";
	else
		return u_int_to_str(value);
}
//rs
static string rs_int_range(int max, int min) {
	return "[" + to_string(min) + ".." + to_string(max) + "]";
}

static string rs_int_set(int* set) {
	int* p = set;
	string s;
	while (*p != INVALID_INT_VALUE_OF_SET) {
		s += to_string(*p);
		if (*(p + 1) != INVALID_INT_VALUE_OF_SET)
			s += '/';
		p++;
	}
	return s;
}

static string rs_double_range(double max, double min) {
	return "[" + to_string(min) + ".." + to_string(max) + "]";
}

static string rs_double_set(double* set) {
	double* p = set;
	string s;
	while (*p != INVALID_DOUBLE_VALUE_OF_SET) {
		s += to_string(*p);
		if (*(p + 1) != INVALID_DOUBLE_VALUE_OF_SET)
			s += '/';
		p++;
	}
	return s;
}

static string rs_str_set(string* set) {
	string* p = set;
	string s;
	while (*p != "") {
		s += *p;
		if (*(p + 1) != "")
			s += "/";
		p++;
	}
	return s;
}
//rs
static bool if_int_belongset(int n, int* set) {//判断n是否属于集合set
	int* p = set;
	while (*p != INVALID_INT_VALUE_OF_SET) {
		if (n == *p) {
			return true;
			break;
		}
		p++;
	}
	return false;
}

static bool if_double_belongset(double n, double* set) {
	double* p = set;
	while (*p != INVALID_DOUBLE_VALUE_OF_SET) {
		if (n == *p) {
			return true;
			break;
		}
		p++;
	}
	return false;
}

static bool if_str_belongset(string n, string* set) {
	string* p = set;
	while (*p != "") {
		if (n == *p) {
			return true;
			break;
		}
		p++;
	}
	return false;
}

static bool ItIsInt(const char* s) {//判断是不是整数类型
	try {
		size_t pos;
		int result = stoi(s, &pos); // 将返回值存储在一个变量中
		return pos == strlen(s); // 如果整个字符串都被转换，则是整数
	}
	catch (...) {
		return false; // 转换失败，不是整数
	}
}

static bool ItIsDouble(const char* s) {//判断是不是浮点
	try {
		size_t pos;
		double result = stod(s, &pos);
		return pos == strlen(s); // 如果整个字符串都被转换，则是浮点
	}
	catch (...) {
		return false;
	}
}

static bool ItIsIp(const char* s) {
	int p = 0;
	//先判断有没有除了数字和.以外的字符
	while (s[p] != 0) {
		if ((s[p] < '0' || s[p] > '9') && s[p] != '.') {
			return false;
			break;
		}
		p++;
	}
	p = 0;
	//统计.的个数
	int count = 0;
	while (s[p] != 0) {
		if (s[p] == '.')
			count++;
		p++;
	}
	if (count != 3)
		return false;
	//检查数字
	string num;
	int old_p = 0;
	p = 0;
	while (s[p] != '.') {
		num += s[p];
		p++;
	}
	old_p += p + 1;
	if (stoi(num) > 255 || stoi(num) < 0)
		return false;

	p = 0;
	num = "";
	while (s[p + old_p] != '.') {
		num += s[p + old_p];
		p++;
	}
	old_p += p + 1;
	if (stoi(num) > 255 || stoi(num) < 0)
		return false;

	p = 0;
	num = "";
	while (s[p + old_p] != '.') {
		num += s[p + old_p];
		p++;
	}
	old_p += p + 1;
	if (stoi(num) > 255 || stoi(num) < 0)
		return false;

	p = 0;
	num = "";
	while (s[p + old_p] != 0) {
		num += s[p + old_p];
		p++;
	}
	if (stoi(num) > 255 || stoi(num) < 0)
		return false;

	return true;
}

static bool ItIsName(const char* s, args_analyse_tools* const args) {//查看是否属于可变参数
	for (int i = 0; (args[i].get_name())[0] != 0; i++) 
		if (args[i].get_name() == s) {
			return true;
			break;
		}
	return false;
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：null
 ***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
	this->args_name[0] = 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
	if (type == ST_EXTARGS_TYPE::boolean) {//初始化bool类型
		this->args_name = name;
		this->extargs_type = type;
		this->extargs_num = ext_num;
		this->extargs_bool_default = def;
		this->args_existed = 0;
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_default、int_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max)
{
	this->args_name = name;
	this->extargs_type = type;
	this->extargs_num = ext_num;
	if (type == ST_EXTARGS_TYPE::int_with_default)//int 带默认
		this->extargs_int_default = def;
	this->extargs_int_min = _min;
	this->extargs_int_max = _max;

	this->extargs_int_value = def;
	this->args_existed = 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_set_default、int_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set)
{
	this->args_name = name;
	this->extargs_type = type;
	this->extargs_num = ext_num;
	
	int setsize = 0;
	while (1) {
		if (set[setsize] != INVALID_INT_VALUE_OF_SET)
			setsize++;
		else
			break;
	}
	if (type == ST_EXTARGS_TYPE::int_with_set_default || type == ST_EXTARGS_TYPE::int_with_set_error) {
		if (def_of_set_pos >= setsize)
			this->extargs_int_default = set[0];
		else
			this->extargs_int_default = set[def_of_set_pos];
	}
	this->extargs_int_set = (int *)set;

	this->extargs_int_value = this->extargs_int_default;
	this->args_existed = 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str、ipaddr_with_default、ipaddr_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const string def)
{
	this->args_name = name;
	this->extargs_type = type;
	this->extargs_num = ext_num;
	this->extargs_string_default = def;
	if (type == ST_EXTARGS_TYPE::ipaddr_with_default || type == ST_EXTARGS_TYPE::ipaddr_with_error) {
		if (def == "")
			this->extargs_ipaddr_default = 0;
		else
			this->extargs_ipaddr_default = str_to_u_int(def);

		this->extargs_ipaddr_value = this->extargs_ipaddr_default;
	}
	if (type == ST_EXTARGS_TYPE::str)
		this->extargs_string_value = this->extargs_string_default;

	this->args_existed = 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str_with_set_default、str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set)
{
	this->args_name = name;
	this->extargs_type = type;
	this->extargs_num = ext_num;

	int setsize = 0;
	while (1) {
		if (set[setsize] != "")
			setsize++;
		else
			break;
	}
	if (type == ST_EXTARGS_TYPE::str_with_set_default || type == ST_EXTARGS_TYPE::str_with_set_error) {
		if (def_of_set_pos >= setsize)
			this->extargs_string_default = set[0];
		else
			this->extargs_string_default = set[def_of_set_pos];
	}

	this->extargs_string_value = this->extargs_string_default;
	this->args_existed = 0;
	this->extargs_string_set = (string*)set;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：double_with_default、double_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const double	def, const double _min, const double _max)
{
	this->args_name = name;
	this->extargs_type = type;
	this->extargs_num = ext_num;
	if (type == ST_EXTARGS_TYPE::double_with_default || type == ST_EXTARGS_TYPE::double_with_error)
		this->extargs_double_default = def;
	this->extargs_double_min = _min;
	this->extargs_double_max = _max;

	this->extargs_double_value = this->extargs_double_default;
	this->args_existed = 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：double_with_set_default、double_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const double* const set)
{
	this->args_name = name;
	this->extargs_type = type;
	this->extargs_num = ext_num;

	int setsize = 0;
	while (1) {
		if (set[setsize] != INVALID_DOUBLE_VALUE_OF_SET)
			setsize++;
		else
			break;
	}
	if (type == ST_EXTARGS_TYPE::double_with_set_default || type == ST_EXTARGS_TYPE::double_with_set_error) {
		if (def_of_set_pos >= setsize)
			this->extargs_double_default = set[0];
		else
			this->extargs_double_default = set[def_of_set_pos];
	}
	this->extargs_double_set = (double *)set;

	this->extargs_double_value = this->extargs_double_default;
	this->args_existed = 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
}

/* ---------------------------------------------------------------
	 允许AAT中自定义成员函数的实现（private）
   ---------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return this->args_name;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：加!!后，只能是0/1
			已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!this->args_existed;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return this->extargs_int_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const double args_analyse_tools::get_double() const
{
	return this->extargs_double_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return this->extargs_string_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return this->extargs_ipaddr_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：将 extargs_ipaddr_value 的值从 0x7f000001 转为 "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{
	return u_int_to_str(this->extargs_ipaddr_value);
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：follow_up_args：是否有后续参数
			0  ：无后续参数
			1  ：有后续参数
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_process(const int argc, const char* const *const argv, args_analyse_tools* const args, const int follow_up_args)
{
	//返回的是到可变参数的argc的值
	//有无固定参数都需要先分析可变参数
	int args_size;//args的个数
	for (args_size = 0; args[args_size].args_name[0] != 0; args_size++);

	int cur_argc = 1;
	//判断有没有可变或固定参数
	if (argc == 1)
		return 1;
	while (1) {
		//是否已经超出argc范围
		if (cur_argc >= argc) {
			return cur_argc;
			break;
		}
		//比较是不是--可变参数，不是则给出提示并退出
		int i;
		for (i = 0; args[i].args_name[0] != 0; i++) {
			if (args[i].args_name == argv[cur_argc])
				break;
		}
		if (i >= args_size) {//不是--类型的可变参数
			if (!follow_up_args) {//follow_up_args为0
				cout << "参数[" << argv[cur_argc] << "]格式非法(不是--开头的有效内容)." << endl;
				return -1;
				break;
			}
			else {//follow_up_aargs为1
				return cur_argc;
				break;
			}
		}
		//如果是，判断可变参数的类型，是否需要附加值
		//需要附加值的类型则要cur_argc++使得其指向下一个argv
		args[i].args_existed++;//防止重复
		if (args[i].args_existed > 1) {
			cout << "参数[" << args[i].args_name << "]重复." << endl;
			return -1;
			break;
		}

		//参数分类
		if (args[i].extargs_type == ST_EXTARGS_TYPE::boolean);//目前已经把具有0或1个附加参数写死了，后续可能需要更改


		else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_default) {
			//先判断后续有没有参数  参数[--intdef]的附加参数不足. (类型:int, 范围[0..65535] 缺省:12345)
			if (cur_argc == (argc - 1)) {
				cout << "参数[" << args[i].args_name << "]的附加参数不足. (类型:int, 范围[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "] 缺省:" << args[i].extargs_int_default << ")" << endl;
				return -1;
				break;
			}
			cur_argc++;
			//判断是不是整数
			if (!ItIsInt(argv[cur_argc])) {
				//如果不是整数，看下一个是不是可变参数  参数[--intdef]缺少附加参数. (类型:int, 范围[0..65535] 缺省:12345)
				if (ItIsName(argv[cur_argc], args)) {
					cout<<"参数[" << args[i].args_name << "]缺少附加参数. (类型:int, 范围[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "] 缺省:" << args[i].extargs_int_default << ")" << endl;
					return -1;
					break;
				}
				//参数[--intdef]的附加参数不是整数. (类型:int, 范围[0..65535] 缺省:12345)
				cout << "参数[" << args[i].args_name << "]的附加参数不是整数. (类型:int, 范围[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "] 缺省:" << args[i].extargs_int_default << ")" << endl;
				return -1;
				break;
			}

			int value = stoi(argv[cur_argc]);
			if (value<args[i].extargs_int_min || value>args[i].extargs_int_max)
				value = args[i].extargs_int_default;
			args[i].extargs_int_value = value;
		}


		else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
			//先判断后续有没有参数  参数[--intdef]的附加参数不足. (类型:int, 范围[0..65535])
			if (cur_argc == (argc - 1)) {
				cout << "参数[" << args[i].args_name << "]的附加参数不足. (类型:int, 范围[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "])" << endl;
				return -1;
				break;
			}
			cur_argc++;
			//判断是不是整数
			if (!ItIsInt(argv[cur_argc])) {
				//如果不是整数，看下一个是不是可变参数  参数[--intdef]缺少附加参数. (类型:int, 范围[0..65535])
				if (ItIsName(argv[cur_argc], args)) {
					cout << "参数[" << args[i].args_name << "]缺少附加参数. (类型:int, 范围[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "])" << endl;
					return -1;
					break;
				}
				//参数[--intdef]的附加参数不是整数. (类型:int, 范围[0..65535])
				cout << "参数[" << args[i].args_name << "]的附加参数不是整数. (类型:int, 范围[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "])" << endl;
				return -1;
				break;
			}

			int value = stoi(argv[cur_argc]);
			//判断值是否合法
			if (value<args[i].extargs_int_min || value>args[i].extargs_int_max) {
				cout << "参数[" << args[i].args_name << "]的附加参数值(" << value << ")非法. (类型:int, 范围[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "])" << endl;
				return -1;
				break;
			}
			args[i].extargs_int_value = value;
		}


		else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_default) {
			//先判断后续有没有参数  参数[--intsetdef]的附加参数不足. (类型:int, 可取值[11/22/33/123/345] 缺省:33)
			if (cur_argc == (argc - 1)) {
				cout << "参数[" << args[i].args_name << "]的附加参数不足. (类型:int, 可取值[" << rs_int_set(args[i].extargs_int_set) << "] 缺省:" << args[i].extargs_int_default << ")" << endl;
				return -1;
				break;
			}
			cur_argc++;
			//判断是不是整数
			if (!ItIsInt(argv[cur_argc])) {
				//如果不是整数，看下一个是不是可变参数  参数[--intsetdef]缺少附加参数. (类型:int, 可取值[11/22/33/123/345] 缺省:33)
				if (ItIsName(argv[cur_argc], args)) {
					cout << "参数[" << args[i].args_name << "]缺少附加参数. (类型:int, 可取值[" << rs_int_set(args[i].extargs_int_set) << "] 缺省:" << args[i].extargs_int_default << ")" << endl;
					return -1;
					break;
				}
				//参数[--intsetdef]的附加参数不是整数. (类型:int, 可取值[11/22/33/123/345] 缺省:33)
				cout << "参数[" << args[i].args_name << "]的附加参数不是整数. (类型:int, 可取值[" << rs_int_set(args[i].extargs_int_set) << "] 缺省:" << args[i].extargs_int_default << ")" << endl;
				return -1;
				break;
			}

			int value = stoi(argv[cur_argc]);
			if (!if_int_belongset(value, args[i].extargs_int_set)) 
				value = args[i].extargs_int_default;
			args[i].extargs_int_value = value;
		}


		else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
			//先判断后续有没有参数  参数[--intsetdef]的附加参数不足. (类型:int, 可取值[11/22/33/123/345])
			if (cur_argc == (argc - 1)) {
				cout << "参数[" << args[i].args_name << "]的附加参数不足. (类型:int, 可取值[" << rs_int_set(args[i].extargs_int_set) << "])" << endl;
				return -1;
				break;
			}
			cur_argc++;
			//判断是不是整数
			if (!ItIsInt(argv[cur_argc])) {
				//如果不是整数，看下一个是不是可变参数  参数[--intsetdef]缺少附加参数. (类型:int, 可取值[11/22/33/123/345])
				if (ItIsName(argv[cur_argc], args)) {
					cout << "参数[" << args[i].args_name << "]缺少附加参数. (类型:int, 可取值[" << rs_int_set(args[i].extargs_int_set) << "])" << endl;
					return -1;
					break;
				}
				//参数[--intsetdef]的附加参数不是整数. (类型:int, 可取值[11/22/33/123/345])
				cout << "参数[" << args[i].args_name << "]的附加参数不是整数. (类型:int, 可取值[" << rs_int_set(args[i].extargs_int_set) << "])" << endl;
				return -1;
				break;
			}

			int value = stoi(argv[cur_argc]);
			if (!if_int_belongset(value, args[i].extargs_int_set)) {
				//参数[--intseterr]的附加参数值(12)非法. (类型:int, 可取值[11/22/33/123/345])
				cout << "参数[" << args[i].args_name << "]的附加参数值(" << value << ")非法. (类型:int, 可取值[" << rs_int_set(args[i].extargs_int_set) << "])" << endl;
				return -1;
				break;
			}
			args[i].extargs_int_value = value;
		}
		//end of int


		else if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_default) {
			//先判断后续有没有参数  参数[--doubledef]的附加参数不足. (类型:double, 范围[-2.5..99.9] 缺省:1.23)
			if (cur_argc == (argc - 1)) {
				cout << "参数[" << args[i].args_name << "]的附加参数不足. (类型:double, 范围[" << args[i].extargs_double_min << ".." << args[i].extargs_double_max << "] 缺省:" << args[i].extargs_double_default << ")" << endl;
				return -1;
				break;
			}
			cur_argc++;
			//判断是不是浮点
			if (!ItIsDouble(argv[cur_argc])) {
				//如果不是，看下一个是不是可变参数  参数[--doubledef]缺少附加参数. (类型:double, 范围[-2.5..99.9] 缺省:1.23)
				if (ItIsName(argv[cur_argc], args)) {
					cout << "参数[" << args[i].args_name << "]缺少附加参数. (类型:double, 范围[" << args[i].extargs_double_min << ".." << args[i].extargs_double_max << "] 缺省:" << args[i].extargs_double_default << ")" << endl;
					return -1;
					break;
				}
				//参数[--doubledef]的附加参数不是浮点数. (类型:double, 范围[-2.5..99.9] 缺省:1.23)
				cout << "参数[" << args[i].args_name << "]的附加参数不是浮点数. (类型:double, 范围[" << args[i].extargs_double_min << ".." << args[i].extargs_double_max << "] 缺省:" << args[i].extargs_double_default << ")" << endl;
				return -1;
				break;
			}

			double value = stod(argv[cur_argc]);
			if (value<args[i].extargs_double_min || value>args[i].extargs_double_max)
				value = args[i].extargs_double_default;
			args[i].extargs_double_value = value;
		}


		else if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_error) {
			//先判断后续有没有参数  参数[--doubledef]的附加参数不足. (类型:double, 范围[-2.5..99.9] 缺省:1.23)
			if (cur_argc == (argc - 1)) {
				cout << "参数[" << args[i].args_name << "]的附加参数不足. (类型:double, 范围[" << args[i].extargs_double_min << ".." << args[i].extargs_double_max << "])" << endl;
				return -1;
				break;
			}
			cur_argc++;
			//判断是不是浮点
			if (!ItIsDouble(argv[cur_argc])) {
				//如果不是，看下一个是不是可变参数  参数[--doubledef]缺少附加参数. (类型:double, 范围[-2.5..99.9] 缺省:1.23)
				if (ItIsName(argv[cur_argc], args)) {
					cout << "参数[" << args[i].args_name << "]缺少附加参数. (类型:double, 范围[" << args[i].extargs_double_min << ".." << args[i].extargs_double_max << "])" << endl;
					return -1;
					break;
				}
				//参数[--doubledef]的附加参数不是浮点数. (类型:double, 范围[-2.5..99.9] 缺省:1.23)
				cout << "参数[" << args[i].args_name << "]的附加参数不是浮点数. (类型:double, 范围[" << args[i].extargs_double_min << ".." << args[i].extargs_double_max << "])" << endl;
				return -1;
				break;
			}

			double value = stod(argv[cur_argc]);
			if (value<args[i].extargs_double_min || value>args[i].extargs_double_max) {
				//参数[--doubleerr]的附加参数值(100)非法. (类型:double, 范围[-2.5..99.9])
				cout << "参数[" << args[i].args_name << "]的附加参数值(" << value << ")非法. (类型:double, 范围[" << args[i].extargs_double_min << ".." << args[i].extargs_double_max << "])" << endl;
				return -1;
				break;
			}
			args[i].extargs_double_value = value;
		}


		else if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_default) {
			//先判断后续有没有参数  参数[--doublesetdef]的附加参数不足. (类型:double, 可取值[1.1/2.2/3.3/12.3/3.45] 缺省:3.3)
			if (cur_argc == (argc - 1)) {
				cout << "参数[" << args[i].args_name << "]的附加参数不足. (类型:double, 可取值[" << args[i].extargs_double_min << ".." << args[i].extargs_double_max << "] 缺省:" << args[i].extargs_double_default << ")" << endl;
				return -1;
				break;
			}
			cur_argc++;
			//判断是不是浮点
			if (!ItIsDouble(argv[cur_argc])) {
				//如果不是，看下一个是不是可变参数  参数[--doublesetdef]缺少附加参数. (类型:double, 可取值[1.1/2.2/3.3/12.3/3.45] 缺省:3.3)
				//double没有不是浮点型的输出
				cout << "参数[" << args[i].args_name << "]缺少附加参数. (类型:double, 可取值[" << rs_double_set(args[i].extargs_double_set) << "] 缺省:" << args[i].extargs_double_default << ")" << endl;
				return -1;
				break;
			}

			double value = stod(argv[cur_argc]);
			if (!if_double_belongset(value, args[i].extargs_double_set))
				value = args[i].extargs_double_default;
			args[i].extargs_double_value = value;
		}


		else if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) {
			//先判断后续有没有参数  参数[--doublesetdef]的附加参数不足. (类型:double, 可取值[1.1/2.2/3.3/12.3/3.45] 缺省:3.3)
			if (cur_argc == (argc - 1)) {
				cout << "参数[" << args[i].args_name << "]的附加参数不足. (类型:double, 可取值[" << args[i].extargs_double_min << ".." << args[i].extargs_double_max << "])" << endl;
				return -1;
				break;
			}
			cur_argc++;
			//判断是不是浮点
			if (!ItIsDouble(argv[cur_argc])) {
				//如果不是，看下一个是不是可变参数  参数[--doublesetdef]缺少附加参数. (类型:double, 可取值[1.1/2.2/3.3/12.3/3.45] 缺省:3.3)
				//double没有不是浮点型的输出
				cout << "参数[" << args[i].args_name << "]缺少附加参数. (类型:double, 可取值[" << rs_double_set(args[i].extargs_double_set) << "])" << endl;
				return -1;
				break;
			}

			double value = stod(argv[cur_argc]);
			if (!if_double_belongset(value, args[i].extargs_double_set)) {
				//参数[--doubleseterr]的附加参数值(1)非法. (类型:double, 可取值[1.1/2.2/3.3/12.3/3.45])
				cout << "参数[" << args[i].args_name << "的附加参数值(" << value << ")非法. (类型:double, 可取值[" << rs_double_set(args[i].extargs_double_set) << "])" << endl;
				return -1;
				break;
			}
			args[i].extargs_double_value = value;
		}
		//end of double


		else if (args[i].extargs_type == ST_EXTARGS_TYPE::str) {
			//先判断后续有没有参数  参数[--str1]的附加参数不足. (类型:string)
			if (cur_argc == (argc - 1)) {
				cout << "参数[" << args[i].args_name << "]的附加参数不足. (类型:string)" << endl;
				return -1;
				break;
			}
			cur_argc++;
			//判断是不是name
			if (ItIsName(argv[cur_argc], args)) {
				//如果是  参数[--str1]缺少附加参数. (类型:string)
				cout << "参数[" << args[i].args_name << "]缺少附加参数. (类型:string)" << endl;
				return -1;
				break;
			}

			args[i].extargs_string_value = argv[cur_argc];
		}


		else if (args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default) {
			//先判断后续有没有参数  参数[--strsetdef]的附加参数不足. (类型:string, 可取值[md5/sha1/sha224/sha256/sha384/sha512/all] 缺省:sha256)
			if (cur_argc == (argc - 1)) {
				cout << "参数[" << args[i].args_name << "]的附加参数不足. (类型:string, 可取值[" << rs_str_set(args[i].extargs_string_set) << "] 缺省:" << args[i].extargs_string_default << ")" << endl;
				return -1;
				break;
			}
			cur_argc++;
			//判断是不是name
			if (ItIsName(argv[cur_argc], args)) {
				//如果是  参数[--strsetdef]缺少附加参数. (类型:string, 可取值[md5/sha1/sha224/sha256/sha384/sha512/all] 缺省:sha256)
				cout << "参数[" << args[i].args_name << "]缺少附加参数. (类型:string, 可取值[" << rs_str_set(args[i].extargs_string_set) << "] 缺省:" << args[i].extargs_string_default << ")" << endl;
				return -1;
				break;
			}

			if (!if_str_belongset(argv[cur_argc], args[i].extargs_string_set))
				args[i].extargs_string_value = args[i].extargs_string_default;
			else
				args[i].extargs_string_value = argv[cur_argc];
		}


		else if (args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
			//先判断后续有没有参数  参数[--strseterr]的附加参数不足. (类型:string, 可取值[md5/sha1/sha224/sha256/sha384/sha512/all])
			if (cur_argc == (argc - 1)) {
				cout << "参数[" << args[i].args_name << "]的附加参数不足. (类型:string, 可取值[" << rs_str_set(args[i].extargs_string_set) << "])" << endl;
				return -1;
				break;
			}
			cur_argc++;
			//判断是不是name
			if (ItIsName(argv[cur_argc], args)) {
				//如果是  参数[--strseterr]缺少附加参数. (类型:string, 可取值[md5/sha1/sha224/sha256/sha384/sha512/all])
				cout << "参数[" << args[i].args_name << "]缺少附加参数. (类型:string, 可取值[" << rs_str_set(args[i].extargs_string_set) << "])" << endl;
				return -1;
				break;
			}

			//参数[--strseterr]的附加参数值(1)非法. (类型:string, 可取值[md5/sha1/sha224/sha256/sha384/sha512/all])
			if (!if_str_belongset(argv[cur_argc], args[i].extargs_string_set)) {
				cout << "参数[" << args[i].args_name << "的附加参数值(" << argv[cur_argc] << ")非法. (类型:string, 可取值[" << rs_str_set(args[i].extargs_string_set) << "])" << endl;
				return -1;
				break;
			}
			args[i].extargs_string_value = argv[cur_argc];
		}
		//end of str


		else if (args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default) {
			//先判断后续有没有参数  参数[--ipdef]的附加参数不足. (类型:IP地址 缺省:192.168.80.230)
			if (cur_argc == (argc - 1)) {
				cout << "参数[" << args[i].args_name << "]的附加参数不足. (类型:IP地址, 缺省:" << u_int_to_str(args[i].extargs_ipaddr_default) << ")" << endl;
				return -1;
				break;
			}
			cur_argc++;
			//判断是不是name
			if (ItIsName(argv[cur_argc], args)) {
				//如果是  参数[--ipdef]缺少附加参数. (类型:IP地址 缺省:192.168.80.230)
				cout << "参数[" << args[i].args_name << "]缺少附加参数. (类型:IP地址, 缺省:" << u_int_to_str(args[i].extargs_ipaddr_default) << ")" << endl;
				return -1;
				break;
			}

			if (!ItIsIp(argv[cur_argc]))
				args[i].extargs_ipaddr_value = args[i].extargs_ipaddr_default;
			else
				args[i].extargs_ipaddr_value = str_to_u_int(argv[cur_argc]);
		}


		else if (args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
			//先判断后续有没有参数  参数[--iperr]的附加参数不足. (类型:IP地址)
			if (cur_argc == (argc - 1)) {
				cout << "参数[" << args[i].args_name << "]的附加参数不足. (类型:IP地址)" << endl;
				return -1;
				break;
			}
			cur_argc++;
			//判断是不是name
			if (ItIsName(argv[cur_argc], args)) {
				//如果是  参数[--iperr]缺少附加参数. (类型:IP地址)
				cout << "参数[" << args[i].args_name << "]的附加参数不足. (类型:IP地址)" << endl;
				return -1;
				break;
			}

			//参数[--iperr]的附加参数值(1)非法. (类型:IP地址)
			if (!ItIsIp(argv[cur_argc])) {
				cout << "参数[" << args[i].args_name << "的附加参数值(" << argv[cur_argc] << ")非法. (类型:IP地址)" << endl;
				return -1;
				break;
			}
			else
				args[i].extargs_ipaddr_value = str_to_u_int(argv[cur_argc]);
		}
		//end of ip


		else {
			cout << "ERROR" << endl;
			break;
		}

		cur_argc++;
	}

	return 0; //此句根据需要修改
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_print(const args_analyse_tools* const args)
{
	int args_size = 0;
	for (int i = 0; args[i].args_name[0] != 0; i++)
		args_size++;

	int name_len = 0, type_len = 0, default_len = 0, exist_len = 0, value_len = 0, rs_len = 0;
	for (int i = 0; args[i].args_name[0] != 0; i++)
		name_len = (name_len > (int)args[i].args_name.size() ? name_len : args[i].args_name.size());
	name_len = (name_len > 4 ? name_len : 4);

	for (int i = 0; args[i].args_name[0] != 0; i++)
		type_len = (type_len > (int)typetos(args[i].extargs_type).size() ? type_len : typetos(args[i].extargs_type).size());
	type_len = (type_len > 4 ? type_len : 4);

	string* de = new(nothrow) string[args_size];
	if (de == NULL) {
		cout << "ERROR" << endl;
	}
	for (int i = 0; i < args_size; i++) {
		switch (args[i].extargs_type) {
		case ST_EXTARGS_TYPE::boolean:
			de[i] = bool_de_s(args[i].extargs_bool_default);
			break;
		case ST_EXTARGS_TYPE::int_with_default:
			de[i] = to_string(args[i].extargs_int_default);
			break;
		case ST_EXTARGS_TYPE::int_with_error:
			de[i] = "/";
			break;
		case ST_EXTARGS_TYPE::int_with_set_default:
			de[i] = to_string(args[i].extargs_int_default);
			break;
		case ST_EXTARGS_TYPE::int_with_set_error:
			de[i] = "/";
			break;
		case ST_EXTARGS_TYPE::double_with_default:
			de[i] = to_string(args[i].extargs_double_default);
			break;
		case ST_EXTARGS_TYPE::double_with_error:
			de[i] = "/";
			break;
		case ST_EXTARGS_TYPE::double_with_set_default:
			de[i] = to_string(args[i].extargs_double_default);
			break;
		case ST_EXTARGS_TYPE::double_with_set_error:
			de[i] = "/";
			break;
		case ST_EXTARGS_TYPE::str:
			de[i] = str_de_s(args[i].extargs_string_default);
			break;
		case ST_EXTARGS_TYPE::str_with_set_default:
			de[i] = str_de_s(args[i].extargs_string_default);
			break;
		case ST_EXTARGS_TYPE::str_with_set_error:
			de[i] = "/";
			break;
		case ST_EXTARGS_TYPE::ipaddr_with_default:
			de[i] = args[i].extargs_string_default;
			break;
		case ST_EXTARGS_TYPE::ipaddr_with_error:
			de[i] = "/";
			break;
		default:
			de[i] = "ERROR";
			break;
		}
		default_len = (default_len > (int)de[i].size() ? default_len : de[i].size());
	}
	default_len = (default_len > 7 ? default_len : 7);

	exist_len = 6;

	string* va = new(nothrow) string[args_size];
	if (va == NULL) {
		cout << "ERROR" << endl;
	}
	for (int i = 0; i < args_size; i++) {
		switch (args[i].extargs_type) {//利用args_exist来区分输出值还是斜杠
		case ST_EXTARGS_TYPE::boolean:
			va[i] = bool_va_s(args[i].extargs_bool_default, args[i].args_existed);
			break;
		case ST_EXTARGS_TYPE::int_with_default:
			va[i] = int_va_s(args[i].extargs_int_value, args[i].args_existed);
			break;
		case ST_EXTARGS_TYPE::int_with_error:
			va[i] = int_va_s(args[i].extargs_int_value, args[i].args_existed);
			break;
		case ST_EXTARGS_TYPE::int_with_set_default:
			va[i] = int_va_s(args[i].extargs_int_value, args[i].args_existed);
			break;
		case ST_EXTARGS_TYPE::int_with_set_error:
			va[i] = int_va_s(args[i].extargs_int_value, args[i].args_existed);//到此int结束
			break;
		case ST_EXTARGS_TYPE::double_with_default:
			va[i] = double_va_s(args[i].extargs_double_value, args[i].args_existed);
			break;
		case ST_EXTARGS_TYPE::double_with_error:
			va[i] = double_va_s(args[i].extargs_double_value, args[i].args_existed);
			break;
		case ST_EXTARGS_TYPE::double_with_set_default:
			va[i] = double_va_s(args[i].extargs_double_value, args[i].args_existed);
			break;
		case ST_EXTARGS_TYPE::double_with_set_error:
			va[i] = double_va_s(args[i].extargs_double_value, args[i].args_existed);//到此double结束
			break;
		case ST_EXTARGS_TYPE::str:
			va[i] = str_va_s(args[i].extargs_string_value, args[i].args_existed);
			break;
		case ST_EXTARGS_TYPE::str_with_set_default:
			va[i] = str_va_s(args[i].extargs_string_value, args[i].args_existed);
			break;
		case ST_EXTARGS_TYPE::str_with_set_error:
			va[i] = str_va_s(args[i].extargs_string_value, args[i].args_existed);//到此str结束
			break;
		case ST_EXTARGS_TYPE::ipaddr_with_default:
			va[i] = ip_va_s(args[i].extargs_ipaddr_value, args[i].args_existed);
			break;
		case ST_EXTARGS_TYPE::ipaddr_with_error:
			va[i] = ip_va_s(args[i].extargs_ipaddr_value, args[i].args_existed);
			break;
		default:
			va[i] = "ERROR";
			break;
		}
		value_len = (value_len > (int)va[i].size() ? value_len : va[i].size());
	}
	value_len = (value_len > 5 ? value_len : 5);

	rs_len = 44;
	string* rs = new(nothrow) string[args_size];
	if (rs == NULL) {
		cout << "ERROR" << endl;
	}
	for (int i = 0; i < args_size; i++) {
		switch (args[i].extargs_type) {//利用args_exist来区分输出值还是斜杠
		case ST_EXTARGS_TYPE::boolean:
			rs[i] = "/";
			break;
		case ST_EXTARGS_TYPE::int_with_default:
			rs[i] = rs_int_range(args[i].extargs_int_max, args[i].extargs_int_min);
			break;
		case ST_EXTARGS_TYPE::int_with_error:
			rs[i] = rs_int_range(args[i].extargs_int_max, args[i].extargs_int_min);
			break;
		case ST_EXTARGS_TYPE::int_with_set_default:
			rs[i] = rs_int_set(args[i].extargs_int_set);
			break;
		case ST_EXTARGS_TYPE::int_with_set_error:
			rs[i] = rs_int_set(args[i].extargs_int_set);//到此int结束
			break;
		case ST_EXTARGS_TYPE::double_with_default:
			rs[i] = rs_double_range(args[i].extargs_double_max, args[i].extargs_double_min);
			break;
		case ST_EXTARGS_TYPE::double_with_error:
			rs[i] = rs_double_range(args[i].extargs_double_max, args[i].extargs_double_min);
			break;
		case ST_EXTARGS_TYPE::double_with_set_default:
			rs[i] = rs_double_set(args[i].extargs_double_set);
			break;
		case ST_EXTARGS_TYPE::double_with_set_error:
			rs[i] = rs_double_set(args[i].extargs_double_set);//到此double结束
			break;
		case ST_EXTARGS_TYPE::str:
			rs[i] = "/";
			break;
		case ST_EXTARGS_TYPE::str_with_set_default:
			rs[i] = rs_str_set(args[i].extargs_string_set);
			break;
		case ST_EXTARGS_TYPE::str_with_set_error:
			rs[i] = rs_str_set(args[i].extargs_string_set);//到此str结束
			break;
		case ST_EXTARGS_TYPE::ipaddr_with_default:
			rs[i] = "/";
			break;
		case ST_EXTARGS_TYPE::ipaddr_with_error:
			rs[i] = "/";
			break;
		default:
			rs[i] = "ERROR";
			break;
		}
		rs_len = (rs_len > (int)rs[i].size() ? rs_len : rs[i].size());
	}
	rs_len = (rs_len > 5 ? rs_len : 5);

	//第一行横线
	for (int i = 0; i < (1 + name_len + 1 + type_len + 1 + default_len + 1 + exist_len + 1 + value_len + 1 + rs_len + 1); i++)
		cout << '=';
	cout << endl;
	//目录
	cout << " name";
	space(name_len - 4);
	cout << " type";
	space(type_len - 4);
	cout << " default";
	space(default_len - 7);
	cout << " exists";
	space(exist_len - 6);
	cout << " value";
	space(value_len - 5);
	cout << " range/set";
	cout << endl;
	//第二行横线
	for (int i = 0; i < (1 + name_len + 1 + type_len + 1 + default_len + 1 + exist_len + 1 + value_len + 1 + rs_len + 1); i++)
		cout << '=';
	cout << endl;
	//内容
	for (int i = 0; args[i].args_name[0] != 0; i++) {
		cout << ' ';
		cout << args[i].args_name;
		space(name_len - args[i].args_name.size());
		cout << ' ';
		cout << typetos(args[i].extargs_type);
		space(type_len - typetos(args[i].extargs_type).size());
		cout << ' ';
		cout << de[i];
		space(default_len - de[i].size());
		cout << ' ';
		cout << args[i].args_existed;
		space(exist_len);
		cout << ' ';
		cout << va[i];
		space(value_len - va[i].size());
		cout << ' ';
		cout << rs[i];
		space(rs_len - rs[i].size());
		cout << ' ';

		cout << endl;
	}
	//底线
	for (int i = 0; i < (1 + name_len + 1 + type_len + 1 + default_len + 1 + exist_len + 1 + value_len + 1 + rs_len + 1); i++)
		cout << '=';
	cout << endl;
	cout << endl;

	delete[]rs;
	delete[]va;
	delete[]de;
	return 0; //此句根据需要修改
}

#endif // !ENABLE_LIB_COMMON_TOOLS
