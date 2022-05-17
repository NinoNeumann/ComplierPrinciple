#include "MyComplier.h"



// ����䲿�ּ���ʶ���Ƿ����
bool CheckIdentifierExist() {
    // ��ʱ�Ķ�ͷָ��һ��ȷ�ϵĶ�Ԫʽ
    if (mpIdentifierTable.find(wdNextWord.strValue) == mpIdentifierTable.end()) {
        iHaveError = 12;
        ErrorManagement("");
        return false;
    }
    return true;
}


void UpdateIdentifierList(string type) {
    // �����ڱ�ʶ���б��е��ظ����� �Ͳ�����ʶ��������б���
    if (mpIdentifierTable.find(wdNextWord.strValue) != mpIdentifierTable.end()) {
        iHaveError = 3;
        ErrorManagementAssistant("syntax error", "duplicate defination");
        //PrintMissingSemicolon("duplicate defination");
        return;
    }
    mpIdentifierTable[wdNextWord.strValue] = -1;
    return;
}



// �������
void FixUnknownType()
{
    wdNextWord.strValue = "int";
    wdNextWord.iType = mpName2Num[wdNextWord.strValue];
}

void PrintMissingSemicolon(string w) {
    if (iHaveError) {
        cout << "��syntax error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "  \"" + w + "\"" << endl;
        stckError.push("��syntax error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "  \"" + w + "\"\n");
        // iHaveError = false;
    }
}

// ,string errorType �д��Ľ�
void printUtils(string msg) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_GREEN);
    cout << setw(3) << setiosflags(ios::left) << depth++ << msg <<"\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

// ������ ����ڽ��ж���ʱ��ʶ�����и�ֵ��ʱ���������ı������������Ƿ��ǺϷ���
bool CheckArgsLegal(string arg) {
    switch (JudgeType(arg))
    {
    case 2:
        break;
    case 1:
    case ID_IDENTIFIER:
        break;
    default:
        PrintMissingSemicolon("the variable value is unexpected.");
        break;
    }


    return false;
}


// ����������������ж���Ԫʽ���߼�ֵ
int JudgePhrase(tmpVar arg1, tmpVar arg2, string symbol) {
    int value = -1;
    if (symbol == ">=")      value = (bool)(arg1.value >= arg2.value);
    else if (symbol == "<=") value = (bool)(arg1.value >= arg2.value);
    else if (symbol == "==") value = (bool)(arg1.value >= arg2.value);
    else if (symbol == "!=") value = (bool)(arg1.value >= arg2.value);
    else if (symbol == "<")  value = (bool)(arg1.value < arg2.value);
    else if (symbol == ">")  value = (bool)(arg1.value > arg2.value);
    return value;

}


// �ʷ������ĳ���  iHaveError = 1



bool ErrorManagement(string str) {
    // �ж�iHaveError��ֵ�����д�����
    
    switch (iHaveError) {
    case 1:
        ErrorManagementAssistant("lexical error", "  error word:"+wdNextWord.strValue);
        break;
    case 2:
        ErrorManagementAssistant("syntax  error", "  Missing letter:" + str);
        break;
    case 3:
        ErrorManagementAssistant("lexical error", "  Unknown word:" + wdNextWord.strValue);
        break;
    case 4:
        ErrorManagementAssistant("syntax  error", "  Bad Phrase");
        break;
    case 5:
        ErrorManagementAssistant("syntax  error", "  Missing separator:" + str);
        break;
    case 6:
        ErrorManagementAssistant("syntax  error", "  Missing keyword:" + str);
        break;
    case 7:
        ErrorManagementAssistant("syntax  error", "  Missing mathOperator:" + str);
        break;
    case 8:
        ErrorManagementAssistant("syntax  error", "  Missing logicalOperator:" + str);
        break;
    case 9:
        // Ƕ����䱨��
        ErrorManagementAssistant("syntax  error", "  The Bad NestedPhrase");
        break;
    case 10:
        ErrorManagementAssistant("lexical  error", "  The Bad constant:"+wdNextWord.strValue);
        break;
    case 11:
        ErrorManagementAssistant("syntax  error", "  The Bad Phrase  with the start of :\"" + wdNextWord.strValue+"\"");
        break;
    case 12:
        ErrorManagementAssistant("syntax  error", "  the identifier not exsit!  :" + wdNextWord.strValue);
        break;
    case 13:
        ErrorManagementAssistant("syntax  error", "  the uninitiated identifier :" + wdNextWord.strValue);
        break;
    default:
        return false;
    }
    
    return true;
}

// �Ա�����Ϣ�������������Ϣѹջ
void ErrorManagementAssistant(string errorType, string msg) {
    if (errorType.find("warning") != errorType.npos) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED );
    }
    cout << "��" + errorType + "��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter;  " + msg << endl;
    stckError.push("��" + errorType + "��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter;  " + msg);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    
}



int ErrorProcessMatchKeyWord(string str) {
    // ���� iCur ��һ��unknown�ַ������ҳ��ؼ��ֵ�λ�ò�����ָ��ؼ�����һ���ַ���ָ��
    int pos = 0;
    for (auto x : str_arrVariableStatement) {  // int �ؼ��ֵ�ƥ��
        pos = str.find(x, 0);
        if (pos != str.npos) {
            iCur -= (str.length() - (x.length() + pos));
            wdNextWord.strValue = x;
            wdNextWord.iType = mpName2Num[x];
            wdNextWord.iLine = iCurLine;
            return 1;
        }
    }
    for (auto x : str_arrKeywords) {  // int �ؼ��ֵ�ƥ��
        pos = str.find(x, 0);
        if (pos != str.npos) {
            iCur -= (str.length() - (x.length() + pos));
            wdNextWord.strValue = x;
            wdNextWord.iType = mpName2Num[x];
            wdNextWord.iLine = iCurLine;
            return 1;
        }
    }

    // ��������ǵĻ�ֱ�������������
    Scanner();
    return 0;
}
