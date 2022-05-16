#include "MyComplier.h"



// 在语句部分检查标识符是否定义过
bool CheckIdentifierExist() {
    // 此时的读头指向一个确认的二元式
    if (mpIdentifierTable.find(wdNextWord.strValue) == mpIdentifierTable.end()) {
        PrintMissingSemicolon("undefined identifier!");
        return false;
    }
    return true;
}


void UpdateIdentifierList(string type) {
    // 对于在标识符列表中的重复定义 就不将标识符添加入列表中
    if (mpIdentifierTable.find(wdNextWord.strValue) != mpIdentifierTable.end()) {
        bHaveError = true;
        PrintMissingSemicolon("duplicate defination");
        return;
    }
    mpIdentifierTable[wdNextWord.strValue] = -1;
    return;
}



// 出错管理
void FixUnknownType()
{
    wdNextWord.strValue = "int";
    wdNextWord.iType = mpName2Num[wdNextWord.strValue];
}

void PrintMissingSemicolon(string w) {
    if (bHaveError) {
        cout << "【syntax error】: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "  \"" + w + "\"" << endl;
        stckError.push("【syntax error】: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "  \"" + w + "\"\n");
        bHaveError = false;
    }
}

// ,string errorType 有待改进
void printUtils(string msg, const char* s) {
    cout << s << endl;
    //cout << "【"<<errorType<<"】" << "there is something wrong with your " + msg + "  at  ";
    cout << "line: " << wdNextWord.iLine << " have an error!!" << " error message: " << wdNextWord.strValue << " at the " << iCur << "th letter" << endl;
    bHaveError = false;
}

// 检查变量 检查在进行对临时标识符进行赋值的时候参与运算的变量（常量）是否是合法的
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


// 在条件语句中用来判断四元式的逻辑值
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


// 词法分析的出错  iHaveError = 1



void ErrorManagement() {
    // 判断iHaveError的值来进行错误处理
    switch (iHaveError) {
    case 1:
        cout << "【lexical error】: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "\"" << endl;
        stckError.push("【lexical error】: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "\"\n");
        //bHaveError = false;
        break;
    }

}
