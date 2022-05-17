#include "MyComplier.h"


// 初始值：默认赋值
// 未见过的保留字  
//      未见过的保留字如何处理
// 程序后面出现了未定义的 标识符



// Match返回出错代码


void InitMap() {

    int idx = 1;

    mpName2Num["number"] = 0;

    mpName2Num["identifier"] = 22;

    mpNum2Name[0] = "number";

    mpNum2Name[1] = "变量声明";

    mpNum2Name[22] = "identifier";
    mpNum2Name[-1] = "unknown";

    for (auto x : str_arrVariableStatement)mpName2Num[x] = idx++;

    for (auto x : str_arrKeywords) mpName2Num[x] = idx++;

    for (auto x : str_arrMathOperator) mpName2Num[x] = idx++;

    for (auto x : str_arrLogicalOperator) mpName2Num[x] = idx++;

    for (auto x : str_arrSeperator) mpName2Num[x] = idx++;


    for (int i = 2; i <= 8; ++i) mpNum2Name[i] = "keyword";

    for (int i = 9; i <= 13; ++i)mpNum2Name[i] = "mathOperator";

    for (int i = 14; i <= 19; ++i)mpNum2Name[i] = "logicalOperator";

    for (int i = 20; i <= 21; ++i)mpNum2Name[i] = "separator";


}

int IsReserved(string s) {
    return mpName2Num[s];
}

int IsSymbol(string s) {
    return mpName2Num[s];
}

bool IsDigits(string s) {
    if ("0" <= s && s <= "9")
        return true;
    return false;
}

bool IsLetter(string s) {
    if ("a" <= s && s <= "z")
        return true;
    return false;
}

string ConcatReserved(string s, int n) {
    int i = n + 1, tmp_i;
    bool f = false;
    string tmp;
    while (IsDigits(str_arrLetters[i]) || IsLetter(str_arrLetters[i])) {
        s = (s + str_arrLetters[i++]).c_str();
        if (IsReserved(s)) {
            iCur = i;
            return s;
//            f = true;
        }
    }
    iCur = i;
    /*while (IsDigits(str_arrLetters[i]) || IsLetter(str_arrLetters[i])) {
        s = (s + str_arrLetters[i++]).c_str();
        if (IsReserved(s)) {
            tmp_i = i;
            tmp = s;
            f = true;
        }
    }
    if (f) {
        if (tmp != "int") {
            s = tmp;
            iCur = tmp_i;
        }
        else {
            iCur = i;
        }

    }
    else {
        iCur = i;
    }*/
    return s;
}

string ConcatSymbol(string s, int n) {
    int i = n + 1;
    string ss = str_arrLetters[i];
    if (ss == ">" || ss == "=" || ss == "<" || ss == "!") {
        s = (s + str_arrLetters[i++]).c_str();
    }
    iCur = i;
    return s;
}

string ConcatIdentifier(string s, int n) {
    int i = n + 1;
    // 对标识符的第二个字符进行判断
    if (!IsLetter(str_arrLetters[i])) {
        iHaveError = 1;
        return s;
    }
    else {
        s = (s + str_arrLetters[i++]).c_str();
    }
    while (IsDigits(str_arrLetters[i]) || IsLetter(str_arrLetters[i])) {
        s = (s + str_arrLetters[i++]).c_str();
    }
    iCur = i;
    return s;
}  // 拼接标识符

string ConcatDigits(string s, int n) {
    int i = n + 1;
    while (IsDigits(str_arrLetters[i])) {
        s = (s + str_arrLetters[i++]).c_str();
    }
    iCur = i;
    return s;
}

int JudgeType(string s) {
    if (s == "$") {
        return ID_IDENTIFIER; //如果 $ 开头说明这是一个标识符
    }
    if (IsLetter(s))return 1;
    if (IsDigits(s))return 2;
    if (s == ">" || s == "=" || s == "<" || s == "!")return 3;
    if (s == "+" || s == "*" || s == "=" ||
        s == "," || s == ";" || s == "(" || s == ")")return 4;
    return 0;

}

void Scanner() {
    // Scanner 是负责生成二元式的 一个词法分析程序  每次调用Scanner 都会产生一个二元式
    int tmp_f = iHaveError;
    iHaveError = 0;
    int ty;
    if (iCur < iFileLength) {
        string s1, s2;
        s1 = str_arrLetters[iCur];
        while (str_arrLetters[iCur] == " " || str_arrLetters[iCur] == "\n" || str_arrLetters[iCur] == "\t") {
            // 当当前读头指向的字符是这三个的时候表明该读下一个单词了
            if (str_arrLetters[iCur] == "\n")iCurLine++;
            if (iCur + 1 >= iFileLength)
                return;
            s1 = str_arrLetters[++iCur];
        }
        ty = JudgeType(s1);
        switch (ty) {
        case ID_IDENTIFIER:
            s2 = ConcatIdentifier(s1, iCur);
            // if (!bHaveError)mpIdentifierTable.insert(s2);     // 将标识符添加到标识符列表中  【有待分离出来】
            wdNextWord.strValue = s2;
            wdNextWord.iLine = iCurLine;
            wdNextWord.iType = ID_IDENTIFIER;
            break;
        case LETTER:  // 当读入的是一个字母的时候
            s2 = ConcatReserved(s1, iCur); // 默认开始读取保留字
            if (IsReserved(s2)) {
                wdNextWord.strValue = s2;
                wdNextWord.iLine = iCurLine;
                wdNextWord.iType = mpName2Num[s2];
            }
            else {
                iHaveError = 3;
            }
            //else {
            //    // 说明字符串S2不是保留字那就出错
            //    bHaveError = true;
            //    wdNextWord.strValue = s2;
            //    wdNextWord.iLine = iCurLine;
            //    wdNextWord.iType = -1;          // -1 是unknown type
            //}
            break;
        case NUMBER:  // 读入的第一个字符是一个数字 那么就是常量了
            s2 = ConcatDigits(s1, iCur);
            usetConstantsTable.insert(s2);                      // 将常量添加到常量表中   
            wdNextWord.strValue = s2;
            wdNextWord.iLine = iCurLine;
            wdNextWord.iType = mpName2Num["number"];
            break;
        case CHARACTER:
            s2 = ConcatSymbol(s1, iCur);
            wdNextWord.strValue = s2;
            wdNextWord.iLine = iCurLine;
            wdNextWord.iType = mpName2Num[s2];
            break;
        case OTHER: //  分隔符号和 单目运算符号 * + =
            s2 = s1;
            wdNextWord.strValue = s2;
            wdNextWord.iLine = iCurLine;
            wdNextWord.iType = mpName2Num[s2];
            iCur++;
            break;
        default:
            iHaveError = 3;
            break;
        }
        // 如果词法分析出错那么就设置报错信息
        if (iHaveError) {
            //iCur++;
            wdNextWord.strValue = s2;
            wdNextWord.iType = -1;
            wdNextWord.iLine = iCurLine;
            ErrorManagement("");
            //// 自动忽略该单词
            //cout << depth++ << ":【词法分析】 " << "warning！未知单词 (" << mpNum2Name[wdNextWord.iType] << "," << wdNextWord.strValue << ")" << endl;

            //int e = ErrorProcessMatchKeyWord(s2);
            ///*if (e)
            //    ErrorManagementAssistant("Lexical warning", " 修正未知单词:" + s2 + "  ->" + wdNextWord.strValue);
            //else*/
            //ErrorManagementAssistant("Lexical warning", " 修正未知单词:" + s2 + "  ->" + wdNextWord.strValue);
            //    //cout << depth++ << ":【词法分析】 " << "已修正未知单词 (" << mpNum2Name[wdNextWord.iType] << "," << wdNextWord.strValue << ")" << endl;

            //int e = ErrorProcessMatchKeyWord(s2);
            ///*if (e)
            //    ErrorManagementAssistant("Lexical warning", " 修正未知单词:" + s2 + "  ->" + wdNextWord.strValue);
            //else*/
            //ErrorManagementAssistant("Lexical warning", " 修正未知单词:" + s2 + "  ->" + wdNextWord.strValue);
            //    //cout << depth++ << ":【词法分析】 " << "已修正未知单词 (" << mpNum2Name[wdNextWord.iType] << "," << wdNextWord.strValue << ")" << endl;

            //iHaveError = tmp_f;
            ////Scanner();
            //return;
        }
        cout <<setw(3)<<setiosflags(ios::left)<< depth++ << ":【词法分析】 :" << "(" << setw(8) << setiosflags(ios::left) << mpNum2Name[wdNextWord.iType] << "," << setw(5) << setiosflags(ios::left) << wdNextWord.strValue << ")" << endl;
        iHaveError = tmp_f;

    }

}

