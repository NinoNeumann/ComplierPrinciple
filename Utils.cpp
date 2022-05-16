#include "MyComplier.h"



// ����䲿�ּ���ʶ���Ƿ����
bool CheckIdentifierExist() {
    // ��ʱ�Ķ�ͷָ��һ��ȷ�ϵĶ�Ԫʽ
    if (mpIdentifierTable.find(wdNextWord.strValue) == mpIdentifierTable.end()) {
        PrintMissingSemicolon("undefined identifier!");
        return false;
    }
    return true;
}


void UpdateIdentifierList(string type) {
    // �����ڱ�ʶ���б��е��ظ����� �Ͳ�����ʶ��������б���
    if (mpIdentifierTable.find(wdNextWord.strValue) != mpIdentifierTable.end()) {
        bHaveError = true;
        PrintMissingSemicolon("duplicate defination");
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
    if (bHaveError) {
        cout << "��syntax error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "  \"" + w + "\"" << endl;
        stckError.push("��syntax error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "  \"" + w + "\"\n");
        bHaveError = false;
    }
}

// ,string errorType �д��Ľ�
void printUtils(string msg, const char* s) {
    cout << s << endl;
    //cout << "��"<<errorType<<"��" << "there is something wrong with your " + msg + "  at  ";
    cout << "line: " << wdNextWord.iLine << " have an error!!" << " error message: " << wdNextWord.strValue << " at the " << iCur << "th letter" << endl;
    bHaveError = false;
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



void ErrorManagement() {
    // �ж�iHaveError��ֵ�����д�����
    switch (iHaveError) {
    case 1:
        cout << "��lexical error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "\"" << endl;
        stckError.push("��lexical error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "\"\n");
        //bHaveError = false;
        break;
    }

}
