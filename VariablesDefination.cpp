#include "MyComplier.h"

// �ڶ����� ���Ͷ��岿��
map<string, int> mpName2Num;  // �����ǩӳ��ĺ���
map<int, string> mpNum2Name;
// ȷ��������
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

string str_arrLetters[N];      // ��ŵ��ʵ�buffer
int iFileLength;        // �ļ���������
int iCur;                // ָ��ǰ��ĸλ�õ�ָ��
int iCurLine = 1;       // ��ǰָ�����ڵ�����
string strCurWord;        // ��ǰָ������ʾ�ĵ���
int iHaveError;// �������