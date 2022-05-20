
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
 �����淶����Ҫ���һЩ��Ҫ�ı���
     �ϸ��� ��������ʾ�� ����ǰ׺�ı�ʾ�������£�
     mp-  :  mp      ǰ׺ ��ʾ map<>���� ���еľ����ӳ���ϵ��Ҫ�������߼��ϱ�ʾ  ����mpName2Num  ��ʾName �� Num��map �Ǿ���string �� int ��һ��ӳ���ϵ������������hash����ڲ�ӳ���ֶε�����������ʡ���ˣ�
     uset-:  uset    ǰ׺ ��ʾ unordered_set<>����
     str- :  str     ǰ׺ ��ʾ string����
     i-   :  i       ǰ׺ ��ʾ int����
     wd-  :  wd      ǰ׺ ��ʾ word���Զ���Ľṹ�壩����  ��ϸ������ĺ�������
     -arr-:  arr     ǰ׺ ��ʾ �������� ������ǰ�����������������ϳɲ�ͬ���͵�����  ���� str_arr ��string���͵����顣
     b-   :  b       ǰ׺ ��ʾ bool����
 */




// ��һ����  �궨�巵��ֵ ��ĳЩֵ�������������
// ���������Ž������µĸ�ֵ  ������к궨���Ŀ����Ϊ����Ϊ������򷵻�ֵ��һ����ʶ
#define ID_IDENTIFIER 22
#define LETTER 1
#define NUMBER 2
#define CHARACTER 3
#define OTHER 4 
#define N 5000


// ʹ��һ���ṹ�屣��word��value iType  �����ڵ���
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


// ������Ԫʽ
struct quaternary {
    string op;
    string arg1;
    string arg2;
    string res;
    quaternary(string op, string a1, string a2, string res):op(op),arg1(a1),arg2(a2),res(res) {}
};


// ȫ�ֱ���������
// �ڶ����� ������������
extern map<string, int> mpName2Num;  // �����ǩӳ��ĺ���
extern map<int, string> mpNum2Name;
// ȷ��������
extern map<string,ll> mpIdentifierTable;
extern unordered_set<string> usetConstantsTable;
extern string str_arrVariableStatement[1];
extern string str_arrKeywords[7];
extern string str_arrMathOperator[5];
extern string str_arrSeperator[2];
extern string str_arrLogicalOperator[6];
extern word wdNextWord;
extern string str_arrLetters[N];      // ��ŵ��ʵ�buffer
extern int iFileLength;        // �ļ���������
extern int iCur;                // ָ��ǰ��ĸλ�õ�ָ��
extern int iCurLine;       // ��ǰָ�����ڵ�����
extern string strCurWord;        // ��ǰָ������ʾ�ĵ���
extern int iHaveError;// �������
extern int depth;       // �������
extern stack<string> stckError;
extern vector<quaternary> qua;
extern int tmpVarNum;
extern map<string, int> mpTmpVar;   // ����decrapty
extern int falseExit, trueExit;
extern int sj;
extern string cpy_f;






// ���ܺ�������
// ������ȷ����ǩ��Ž�ӳ���map��
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



// �����������

void Match(string,const bool);                 // ƥ�亯��                                                   ��ʵ�֡�

void ParseProgram();                // �������򲿷�                                                          ��ʵ�֡�
void ParseVariableDeclaration();   // ����������������                                                      ��ʵ�֡�

// <��䲿��> �� <��䲿��><���>;|<���>;
void ParsePhrasePart();             // ������䲿��                                                          ��ʵ�֡�
void ParsePhrasePart1();            // ������䲿��1  ������ݹ�                                             ��ʵ�֡�


// <��ʶ���б�> �� <��ʶ���б�>,<��ʶ��>|<��ʶ��>
void ParseIdentifiersList(string);        // ������ʶ���б���                                                    ��ʵ�֡�
void ParseIdentifiersList1(string);       // ���ڽ�����ʶ���б���һ����ݹ�������Ҫ�������ĸı������ݹ�            ��ʵ�֡�


// <���> �� <��ֵ���>|<�������>|<ѭ�����>
void ParsePhrase();                 // �������                                                              ��ʵ�֡�
void ParsePhrase1();                // �������1  ������ݹ�                                                 ��ʵ�֡�
void ParseAssignmentPhrase();       // ������ֵ���                                                          ��ʵ�֡�
    //  <���ʽ> �� <��>|<���ʽ><�ӷ������><��>
tmpVar ParseExpressionPhrase();       // �������ʽ                                                            ��ʵ�֡�
tmpVar ParseExpressionPhrase1(tmpVar);      // �������ʽ1
        // <��> �� <����>|<��><�˷������><����>
tmpVar ParseItem();                   // ���� ��                                                               ��ʵ�֡�
tmpVar ParseItem1(tmpVar);                  // ���� ��1                                                              ��ʵ�֡�
            // <����> �� <��ʶ��>|<����>|(<���ʽ>)
tmpVar ParseFactor();                 // ��������                                                              ��ʵ�֡�

// <�������> �� if ��<����>�� then <Ƕ�����>; else <Ƕ�����>
void ParseConditionPhrase();        // �����������                                                          ��ʵ�֡�
    
    // <����> �� <���ʽ><��ϵ�����><���ʽ>
tmpVar ParseCondition();              // ����                                                                  ��ʵ�֡�
    // <Ƕ�����> �� <���>|<�������>
void ParseNestedPhrase();           // Ƕ�����                                                              ��ʵ�֡�
void ParseMultiPhrase();            // �������                                                              ��ʵ�֡�


void ParseLoopPhrase();             // ����ѭ�����



// ���±�ʶ���б�
void UpdateIdentifierList(string);
bool CheckIdentifierExist();
bool CheckArgsLegal(string);


// �������
//  ���ڱ���������ʱ�����δ��������ʹ���
void FixUnknownType();               // ��������ļܿ����Ƚϼ�ֻ��һ���������� int ���Ը������������̽����ο�
void PrintMissingSemicolon(string);
int JudgePhrase(tmpVar, tmpVar, string);

void printUtils(string);
bool ErrorManagement(string);
void ErrorManagementAssistant(string, string);
int ErrorProcessMatchKeyWord(string);


void Anstyle();





#endif // !MYCOMPILER_H
