#include "MyComplier.h"

// 第二部分 类型定义部分
map<string, int> mpName2Num;  // 定义标签映射的函数
map<int, string> mpNum2Name;
// 确定保留字
map<string,ll> mpIdentifierTable;
unordered_set<string> usetConstantsTable;

string str_arrVariableStatement[1] = { "int" };
string str_arrKeywords[7] = { "if","else","then","while","do","begin","end" };
string str_arrMathOperator[5] = { "+","*","=","(",")" };
string str_arrSeperator[2] = { ";","," };
string str_arrLogicalOperator[6] = { "==","<=",">=","<",">","!=" };
int depth = 0;
stack<string> stckError;
vector<quaternary> qua;
int tmpVarNum;
int falseExit, trueExit;
map<string, int> mpTmpVar;



word wdNextWord;

string str_arrLetters[N];      // 存放单词的buffer
int iFileLength;        // 文件长度总数
int iCur;                // 指向当前字母位置的指针
int iCurLine = 1;       // 当前指针所在的行数
string strCurWord;        // 当前指针所表示的单词
int iHaveError;// 出错管理