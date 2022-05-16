#include "MyComplier.h"


// 初始值：默认赋值
// 未见过的保留字  
//      未见过的保留字如何处理
// 程序后面出现了未定义的 标识符
// 先产生四元式最后对四元式进行一个执行 修改数据 并且


void Match(string letter,const bool mode = true) {
    // 当Match程序出现错误的时候就会报错 并且wdNextword会暂时停留在错误出现的地方
    if (mode) {
        if (wdNextWord.strValue != letter)iHaveError = 2;               // 值不匹配  对于分隔符 关键字
    }
    else {
        if (mpNum2Name[wdNextWord.iType]!=letter)iHaveError = 2;        // 类型不匹配  逻辑运算符  标识符
    }
    //if (bHaveError) {
    //    throw  letter.c_str();    // 需要在throw error 的时候要不要暂停程序呢?
    //}
    return;
}


void ParseProgram() {
    // 首先解析变量的声明、定义部分
    // 解析“;”
    // 解析语句部分
    // ParseProgram部分调用的子函数必须自己catch自己的子函数所throw的报错信息。
    cout << depth++ <<":【语法推导】 " << ": <程序> →<变量说明部分>;<语句部分>\n";
    

    ParseVariableDeclaration();
    Match(";",true);
    if (bHaveError) {
        cout << "【syntax error】: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue <<"  missing \";\"" << endl;
        stckError.push("【syntax error】: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue+"  missing \";\"\n");
        bHaveError = false;
    }
    Scanner();
    ParsePhrasePart();
    
}                // 解析程序部分


void ParseVariableDeclaration() {

    // <变量说明> → int
    cout << depth++ << ":【语法推导】 " << ": <变量说明部分> → <变量说明><标识符列表>\n";
    // 声明部分需要考虑的出错：声明类型不在类型表里面  由于这边的类型只有int一种所以

    Match("变量声明",false);  // 变量说明
    if (bHaveError) {
        cout << "【syntax error】: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue << endl;
        stckError.push("【syntax error】: at line:"+to_string(wdNextWord.iLine)+" the "+to_string(iCur)+" th letter; error word: "+wdNextWord.strValue+"\n");
        bHaveError = false;
        FixUnknownType();
        //system("pause");
    }
    string type = wdNextWord.strValue;
    
    Scanner();
    
    ParseIdentifiersList(type); // 匹配标识符列表
}

void ParsePhrasePart() {
    // <语句部分> → <语句部分><语句>;|<语句>;
    cout << depth++ << ":【语法推导】 " << ": <语句部分> → <语句>;<语句部分prime>\n";
    ParsePhrase();
    Match(";",true);
    PrintMissingSemicolon("missing ;");
    Scanner();
    ParsePhrasePart1();
}


void ParsePhrasePart1() {
    if (wdNextWord.iType == mpName2Num["identifier"] ||
        (wdNextWord.strValue == "if") ||
        (wdNextWord.strValue == "while")) {  // 是语句的首符集的话 进入分支
        cout << depth++ << ":【语法推导】 " << ": <语句部分prime> → <语句>;<语句部分prime>\n";
        ParsePhrase();
        Match(";",true);
        PrintMissingSemicolon("missing ;");
        Scanner();
        ParsePhrasePart1();
    }
    else {
        cout << depth++ << ":【语法推导】 " << ": <语句部分prime> → <空串>\n";
        // do nothing
    }
    return;
}






void ParseIdentifiersList(string type) {
    // <标识符列表> → <标识符列表>,<标识符>|<标识符>
    cout << depth++ << ":【语法推导】 " << ": <标识符列表> → <标识符><标识符列表prime>\n";


    //Scanner();
    Match("identifier",false);
    if (bHaveError) {
        PrintMissingSemicolon(" not an identifier!");
        Scanner();
        return;
    }
    UpdateIdentifierList(type);
    Scanner();
    // 如果识别成功是一个标识符 那么将这个标识符加入到标识符列表中并且判断有没有重复声明。
    ParseIdentifiersList1(type);

                   // 调用一次词法分析程序
    
}        // 解析标识符列表部分



void ParseIdentifiersList1(string type) {
    if (wdNextWord.iType == mpName2Num[","]) {
         cout << depth++ << ":【语法推导】 " << ": <标识符列表prime> → <标识符>,<标识符列表prime>\n";
         Match(",",true);
         PrintMissingSemicolon("missing ,");
         Scanner();
         Match("identifier",false);
         if (bHaveError) {
             PrintMissingSemicolon(" not an identifier!");
             Scanner();
             return;
         }
         UpdateIdentifierList(type);
         Scanner();
         ParseIdentifiersList1(type);
    }
    else if (wdNextWord.iType == mpName2Num["identifier"]) {
        bHaveError = true;
        PrintMissingSemicolon("missing ,");
    }
    else if(wdNextWord.iType == mpName2Num[";"]) {
        cout << depth++ << ":【语法推导】 " << ": <标识符列表1> → <空串>\n";
        // nothing
    }
    
}      // 由于解析标识符列表是一个左递归所以需要做这样的改变消除递归
// 如果递归调用中出现了异常处理咋办 会返回给递归栈顶部的下一个 让其中的trycatch调用

void ParsePhrase() {
    // <语句> → <赋值语句>|<条件语句>|<循环语句>
    //cout << depth++ << ":【语法推导】 " << ": <语句> → <赋值语句>|<条件语句>|<循环语句>\n";

    if (wdNextWord.iType == mpName2Num["identifier"]) {
        cout << depth++ << ":【语法推导】 " << ": <语句> → <赋值语句>\n";
        ParseAssignmentPhrase();
    }
    else if (wdNextWord.strValue == "if") {
        cout << depth++ << ":【语法推导】 " << ": <语句> → <条件语句>\n";
        ParseConditionPhrase();
    }
    else if (wdNextWord.strValue == "while") {
        cout << depth++ << ":【语法推导】 " << ": <语句> → <循环语句>\n";
        ParseLoopPhrase();
    }
    return;
}

void ParseAssignmentPhrase() {
    // <赋值语句> → <标识符>=<表达式>

    cout << depth++ << ":【语法推导】 " << ": <赋值语句> → <标识符>=<表达式>\n";

    Match("identifier",false);
    if (!CheckIdentifierExist())return;     // 如果标识符不存在就直接return
    string tVar = wdNextWord.strValue;
    Scanner();
    Match("=",true);
    PrintMissingSemicolon("missing  =");
    Scanner();
    tmpVar arg1 = ParseExpressionPhrase();
    qua.push_back(quaternary("=", arg1.name, "null", tVar));

    // 更新标识符列表操作
    mpIdentifierTable[tVar] = arg1.value;



    cout << "标识符列表更新成功  赋值语句" << "  id:" << tVar << "  value:" << arg1.value << endl;

}


tmpVar ParseExpressionPhrase() {

    cout << depth++ << ":【语法推导】 " << ": <表达式> → <项><表达式prime>\n";
    tmpVar arg1 = ParseItem();
    tmpVar ret = ParseExpressionPhrase1(arg1);
    return ret;

}

tmpVar ParseExpressionPhrase1(tmpVar arg) {

    tmpVar ret = arg;
    tmpVar to_pass;

    if (wdNextWord.strValue == "+") {
        cout << depth++ << ":【语法推导】 " << ": <表达式prime> → <加法运算符><项><表达式prime>\n";
        Match("+",true);
        Scanner();
        tmpVar arg2 = ParseItem();
        string var_name = "tmp" + to_string(tmpVarNum++);
        qua.push_back(quaternary("+", arg.name, arg2.name, var_name));
        // 这里由于arg  和 arg1 都有可能是一个常量
        //mpTmpVar[var_name] = mpTmpVar[arg] + mpTmpVar[arg2];
        ret.name = var_name;
        ret.value = arg.value + arg2.value;
        to_pass = ret;
        ret = ParseExpressionPhrase1(to_pass);
    }
    else {
        cout << depth++ << ":【语法推导】 " << ": <表达式prime> → <空串>\n";
        // nothing to do
    }
    return ret;
}


tmpVar ParseItem() {
    cout << depth++ << ":【语法推导】 " << ": <项> → <因子><项prime>\n";

    tmpVar arg1 = ParseFactor();
    tmpVar ret = ParseItem1(arg1);
    return ret;
}

tmpVar ParseItem1(tmpVar arg) {
    tmpVar ret = arg;
    tmpVar to_pass;
    if (wdNextWord.strValue == "*") {
        cout << depth++ << ":【语法推导】 " << ": <项prime> → <乘法运算符><因子><项prime>\n";
        Match("*",true);
        Scanner();
        tmpVar arg2 = ParseFactor();
        if (bHaveError) {
            cout << "【syntax error】: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue +" 因子为空串 * 后面缺乏因子 " << endl;
            stckError.push("【syntax error】: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "因子为空串 * 后面缺乏因子\n");
            bHaveError = false;
        }
        string var_name = "tmp" + to_string(tmpVarNum++);

        qua.push_back(quaternary("*", arg.name, arg2.name, var_name));
        ret.name = var_name;
        ret.value = arg.value * arg2.value;
        to_pass = ret;
        ret = ParseItem1(to_pass);
    }
    else {
        cout << depth++ << ":【语法推导】 " << ": <项prime> → <空串>\n";
        // do nothing
    }
    return ret;
}


tmpVar ParseFactor() {
    // cout << depth++ << ":【语法推导】 " << ": <因子> → <标识符>|<常量>|(<表达式>)\n";

    tmpVar ret;
    if (wdNextWord.iType == mpName2Num["identifier"]) {
        cout << depth++ << ":【语法推导】 " << ": <因子> → <标识符>\n";
        Match("identifier",false);
        if (!CheckIdentifierExist())return ret;
        ret.name = wdNextWord.strValue;
        ret.value = mpIdentifierTable[wdNextWord.strValue];             // 解析因子的子程序中来判断该标识符是否有初始值。
        Scanner();

    }
    else if (wdNextWord.iType == mpName2Num["number"]) {
        cout << depth++ << ":【语法推导】 " << ": <因子> → <常量>\n";
        Match("number",false);
        if (bHaveError) {
            PrintMissingSemicolon("the number is unregualr!");
            return ret;
        }
        ret.name = wdNextWord.strValue;
        ret.value = stoll(ret.name);
       
        Scanner();
    }
    else if (wdNextWord.strValue == "(") {
        cout << depth++ << ":【语法推导】 " << ": <因子> → (<表达式>)\n";
        Match("(",true);
        Scanner();
        ret = ParseExpressionPhrase();
        Match(")",true);
        PrintMissingSemicolon("missing  )");
        Scanner();
    }
    else {
        //cout << depth++ << ":【syntax error】 " << ": <因子> → <空串>  因子不能为空串\n";
        //bHaveError = true;      // 因子不能为空串
        PrintMissingSemicolon("<因子> → <空串>  因子不能为空串");

    }
    return ret;
}


// Match（）这里做类型匹配还是严格匹配

void ParseConditionPhrase() {

    cout << depth++ << ":【语法推导】 " << ": <条件语句> → if （<条件>） then <嵌套语句>; else <嵌套语句>\n";


    Match("if",true);
    Scanner();
    Match("(", true);
    Scanner();
    tmpVar arg1 = ParseCondition();
    qua.push_back(quaternary("jnz", arg1.name, "null", to_string(qua.size()-1 + 3))); // 产生真出口的语句
    int falseExitIndex1 = qua.size();
    qua.push_back(quaternary("j", "null", "null", "待定"));                         // 产生假出口的跳转语句
  
    Match(")", true);
    Scanner();
    Match("then", true);
    Scanner();
    ParseNestedPhrase();
    int falseExitIndex2 = qua.size();
    qua.push_back(quaternary("j", "null", "null", "0"));
    qua[falseExitIndex1].res = to_string(qua.size());
    Match(";", true);
    Scanner();
    Match("else", true);
    Scanner();
    ParseNestedPhrase();
    qua[falseExitIndex2].res = to_string(qua.size());
  
}


tmpVar ParseCondition() {

    cout << depth++ << ":【语法推导】 " << ": <条件> → <表达式><关系运算符><表达式>\n";
    tmpVar ret;
    //int expressionIdx = qua.size();
    tmpVar arg1 = ParseExpressionPhrase();
    Match("logicalOperator",false);
    string tVar = wdNextWord.strValue;
    Scanner();
    tmpVar arg2 = ParseExpressionPhrase();
    string var_name = "tmp" + to_string(tmpVarNum++);
    qua.push_back(quaternary(tVar, arg1.name, arg2.name, var_name));
    
    // judge
    ret.name = var_name;
    ret.value = JudgePhrase(arg1, arg2, tVar);



    return ret;

}


void ParseNestedPhrase() {

    // 需要找到语句的首符集
    if (wdNextWord.iType == mpName2Num["identifier"] ||
        (wdNextWord.iType == mpName2Num["if"] && wdNextWord.strValue == "if") || 
        (wdNextWord.iType == mpName2Num["while"] && wdNextWord.strValue == "while")) {
        cout << depth++ << ":【语法推导】 " << ": <嵌套语句> → <语句>\n";
        ParsePhrase();
    }
    else if (wdNextWord.iType == mpName2Num["begin"] && wdNextWord.strValue == "begin") {
        cout << depth++ << ":【语法推导】 " << ": <嵌套语句> → <复合语句>\n";
        ParseMultiPhrase();
    }
    else {
        // Missing Keyword
        PrintMissingSemicolon("an error occur  when  parsing NestedPhrase  missing  keyword");
    }
}


void ParseMultiPhrase() {
    cout << depth++ << ":【语法推导】 " << ": <复合语句> → begin <语句部分> end\n";

    Match("begin", true);
    PrintMissingSemicolon("missing begin");
    Scanner();
    ParsePhrasePart();
    Match("end", true);
    PrintMissingSemicolon("missing end");
    Scanner();

}



void ParseLoopPhrase() {
    cout << depth++ << ":【语法推导】 " << ": <循环语句> → while （<条件>） do <嵌套语句>\n";
 
    Match("while", true);
    Scanner();
    Match("(");
    Scanner();
    int conIdx = qua.size();
    tmpVar arg = ParseCondition();
    int idx = qua.size();
    qua.push_back(quaternary("jnz", arg.name, "null", to_string(qua.size() + 2)));
    int falseExitIndex = qua.size();
    qua.push_back(quaternary("j", "null", "null", "0"));
    Match(")");
    Scanner();
    Match("do");
    Scanner();
    ParseNestedPhrase();
    qua.push_back(quaternary("j", "null", "null", to_string(conIdx)));
    qua[falseExitIndex].res = to_string(qua.size());

}



/*
加入更加详细的异常处理机制
*/

