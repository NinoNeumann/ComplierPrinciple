#include "MyComplier.h"



// 在语句部分检查标识符是否定义过
bool CheckIdentifierExist() {
    // 此时的读头指向一个确认的二元式
    if (mpIdentifierTable.find(wdNextWord.strValue) == mpIdentifierTable.end()) {
        iHaveError = 12;
        ErrorManagement("");
        return false;
    }
    return true;
}


void UpdateIdentifierList(string type) {
    // 对于在标识符列表中的重复定义 就不将标识符添加入列表中
    if (mpIdentifierTable.find(wdNextWord.strValue) != mpIdentifierTable.end()) {
        iHaveError = 3;
        ErrorManagementAssistant("syntax error", "duplicate defination");
        //PrintMissingSemicolon("duplicate defination");
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
    if (iHaveError) {
        cout << "【syntax error】: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "  \"" + w + "\"" << endl;
        stckError.push("【syntax error】: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "  \"" + w + "\"\n");
        // iHaveError = false;
    }
}

// ,string errorType 有待改进
void printUtils(string msg) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_GREEN);
    cout << setw(3) << setiosflags(ios::left) << depth++ << msg <<"\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
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



bool ErrorManagement(string str) {
    // 判断iHaveError的值来进行错误处理
    
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
        // 嵌套语句报错
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

// 对报错信息进行输出并将信息压栈
void ErrorManagementAssistant(string errorType, string msg) {
    if (errorType.find("warning") != errorType.npos) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED );
    }
    cout << "【" + errorType + "】: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter;  " + msg << endl;
    stckError.push("【" + errorType + "】: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter;  " + msg);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    
}



int ErrorProcessMatchKeyWord(string str) {
    // 重置 iCur 在一个unknown字符串中找出关键字的位置并返回指向关键字下一个字符的指针
    int pos = 0;
    for (auto x : str_arrVariableStatement) {  // int 关键字的匹配
        pos = str.find(x, 0);
        if (pos != str.npos) {
            iCur -= (str.length() - (x.length() + pos));
            wdNextWord.strValue = x;
            wdNextWord.iType = mpName2Num[x];
            wdNextWord.iLine = iCurLine;
            return 1;
        }
    }
    for (auto x : str_arrKeywords) {  // int 关键字的匹配
        pos = str.find(x, 0);
        if (pos != str.npos) {
            iCur -= (str.length() - (x.length() + pos));
            wdNextWord.strValue = x;
            wdNextWord.iType = mpName2Num[x];
            wdNextWord.iLine = iCurLine;
            return 1;
        }
    }

    // 如果都不是的话直接跳过这个单词
    Scanner();
    return 0;
}
