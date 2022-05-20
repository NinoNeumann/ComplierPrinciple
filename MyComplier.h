
#ifndef MYCOMPILER_H
#define MYCOMPILER_H

//#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <map>
#include <stack>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;



#define ll long long

/* 0    <constant>
 * 1    int
 * 2    if
 * 3    else
 * 4    then
 * 5    while
 * 6    do
 * 7    begin
 * 8    end
 * 9    +
 * 10   *
 * 11   =
 * 12   (
 * 13   )
 * 14   <
 * 15   >
 * 16   !=
 * 17   >=
 * 18   <=
 * 19   ==
 * 20   ,
 * 21   ;
 * 22   <Identifiers>
 * */


 /*
 命名规范：主要针对一些重要的变量
     严格按照 匈牙利表示法 其中前缀的表示规则如下：
     mp-  :  mp      前缀 表示 map<>类型 其中的具体的映射关系主要从命名逻辑上表示  例如mpName2Num  表示Name 到 Num的map 那就是string 到 int 的一个映射关系（关于这样的hash表的内部映射字段的类型声明我省略了）
     uset-:  uset    前缀 表示 unordered_set<>类型
     str- :  str     前缀 表示 string类型
     i-   :  i       前缀 表示 int类型
     wd-  :  wd      前缀 表示 word（自定义的结构体）类型  详细见下面的函数定义
     -arr-:  arr     前缀 表示 数组类型 可以在前面添加其他的类型组合成不同类型的数组  例如 str_arr ：string类型的数组。
     b-   :  b       前缀 表示 bool类型
 */




// 第一部分  宏定义返回值 让某些值的意义更加明显
// 给各个符号进行如下的赋值  这里进行宏定义的目的是为了作为后面程序返回值的一个标识
#define ID_IDENTIFIER 22
#define LETTER 1
#define NUMBER 2
#define CHARACTER 3
#define OTHER 4 
#define N 5000


// 使用一个结构体保存word的value iType  和所在的行
struct word {
    string  strValue;
    int     iType;
    int     iLine;
};

struct tmpVar {
    string name;
    ll value;
    tmpVar(string n,ll v):name(n),value(v) {}
    tmpVar() {
        name = "empty";
        value = -1;
    }
};


// 定义四元式
struct quaternary {
    string op;
    string arg1;
    string arg2;
    string res;
    quaternary(string op, string a1, string a2, string res):op(op),arg1(a1),arg2(a2),res(res) {}
};


// 全局变量的声明
// 第二部分 类型声明部分
extern map<string, int> mpName2Num;  // 定义标签映射的函数
extern map<int, string> mpNum2Name;
// 确定保留字
extern map<string,ll> mpIdentifierTable;
extern unordered_set<string> usetConstantsTable;
extern string str_arrVariableStatement[1];
extern string str_arrKeywords[7];
extern string str_arrMathOperator[5];
extern string str_arrSeperator[2];
extern string str_arrLogicalOperator[6];
extern word wdNextWord;
extern string str_arrLetters[N];      // 存放单词的buffer
extern int iFileLength;        // 文件长度总数
extern int iCur;                // 指向当前字母位置的指针
extern int iCurLine;       // 当前指针所在的行数
extern string strCurWord;        // 当前指针所表示的单词
extern int iHaveError;// 出错管理
extern int depth;       // 输出的行
extern stack<string> stckError;
extern vector<quaternary> qua;
extern int tmpVarNum;
extern map<string, int> mpTmpVar;   // 可以decrapty
extern int falseExit, trueExit;
extern int sj;
extern string cpy_f;






// 功能函数部分
// 将各个确定标签存放进映射的map中
void InitMap();
int IsReserved(string);
int IsSymbol(string);
bool IsDigits(string);
bool IsLetter(string);
string ConcatReserved(string, int);
string ConcatSymbol(string, int);
string ConcatIdentifier(string, int);
string ConcatDigits(string, int);
int JudgeType(string s);
void Scanner();



// 语义分析部分

void Match(string,const bool);                 // 匹配函数                                                   【实现】

void ParseProgram();                // 解析程序部分                                                          【实现】
void ParseVariableDeclaration();   // 解析变量声明部分                                                      【实现】

// <语句部分> → <语句部分><语句>;|<语句>;
void ParsePhrasePart();             // 解析语句部分                                                          【实现】
void ParsePhrasePart1();            // 解析语句部分1  消除左递归                                             【实现】


// <标识符列表> → <标识符列表>,<标识符>|<标识符>
void ParseIdentifiersList(string);        // 解析标识符列表部分                                                    【实现】
void ParseIdentifiersList1(string);       // 由于解析标识符列表是一个左递归所以需要做这样的改变消除递归            【实现】


// <语句> → <赋值语句>|<条件语句>|<循环语句>
void ParsePhrase();                 // 解析语句                                                              【实现】
void ParsePhrase1();                // 解析语句1  消除左递归                                                 【实现】
void ParseAssignmentPhrase();       // 解析赋值语句                                                          【实现】
    //  <表达式> → <项>|<表达式><加法运算符><项>
tmpVar ParseExpressionPhrase();       // 解析表达式                                                            【实现】
tmpVar ParseExpressionPhrase1(tmpVar);      // 解析表达式1
        // <项> → <因子>|<项><乘法运算符><因子>
tmpVar ParseItem();                   // 解析 项                                                               【实现】
tmpVar ParseItem1(tmpVar);                  // 解析 项1                                                              【实现】
            // <因子> → <标识符>|<常量>|(<表达式>)
tmpVar ParseFactor();                 // 解析因子                                                              【实现】

// <条件语句> → if （<条件>） then <嵌套语句>; else <嵌套语句>
void ParseConditionPhrase();        // 解析条件语句                                                          【实现】
    
    // <条件> → <表达式><关系运算符><表达式>
tmpVar ParseCondition();              // 条件                                                                  【实现】
    // <嵌套语句> → <语句>|<复合语句>
void ParseNestedPhrase();           // 嵌套语句                                                              【实现】
void ParseMultiPhrase();            // 复合语句                                                              【实现】


void ParseLoopPhrase();             // 解析循环语句



// 更新标识符列表
void UpdateIdentifierList(string);
bool CheckIdentifierExist();
bool CheckArgsLegal(string);


// 出错管理：
//  当在变量声明的时候出现未定义的类型错误
void FixUnknownType();               // 由于这里的架空语句比较简单只有一个类型种类 int 所以给出的修正过程仅供参考
void PrintMissingSemicolon(string);
int JudgePhrase(tmpVar, tmpVar, string);

void printUtils(string);
bool ErrorManagement(string);
void ErrorManagementAssistant(string, string);
int ErrorProcessMatchKeyWord(string);


void Anstyle();





#endif // !MYCOMPILER_H
