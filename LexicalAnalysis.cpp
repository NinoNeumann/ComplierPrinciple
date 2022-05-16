#include "MyComplier.h"


// ��ʼֵ��Ĭ�ϸ�ֵ
// δ�����ı�����  
//      δ�����ı�������δ���
// ������������δ����� ��ʶ��
// �Ȳ�����Ԫʽ������Ԫʽ����һ��ִ�� �޸����� ����


void Match(string letter,const bool mode = true) {
    // ��Match������ִ����ʱ��ͻᱨ�� ����wdNextword����ʱͣ���ڴ�����ֵĵط�
    if (mode) {
        if (wdNextWord.strValue != letter)iHaveError = 2;               // ֵ��ƥ��  ���ڷָ��� �ؼ���
    }
    else {
        if (mpNum2Name[wdNextWord.iType]!=letter)iHaveError = 2;        // ���Ͳ�ƥ��  �߼������  ��ʶ��
    }
    //if (bHaveError) {
    //    throw  letter.c_str();    // ��Ҫ��throw error ��ʱ��Ҫ��Ҫ��ͣ������?
    //}
    return;
}


void ParseProgram() {
    // ���Ƚ������������������岿��
    // ������;��
    // ������䲿��
    // ParseProgram���ֵ��õ��Ӻ��������Լ�catch�Լ����Ӻ�����throw�ı�����Ϣ��
    cout << depth++ <<":���﷨�Ƶ��� " << ": <����> ��<����˵������>;<��䲿��>\n";
    

    ParseVariableDeclaration();
    Match(";",true);
    if (bHaveError) {
        cout << "��syntax error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue <<"  missing \";\"" << endl;
        stckError.push("��syntax error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue+"  missing \";\"\n");
        bHaveError = false;
    }
    Scanner();
    ParsePhrasePart();
    
}                // �������򲿷�


void ParseVariableDeclaration() {

    // <����˵��> �� int
    cout << depth++ << ":���﷨�Ƶ��� " << ": <����˵������> �� <����˵��><��ʶ���б�>\n";
    // ����������Ҫ���ǵĳ����������Ͳ������ͱ�����  ������ߵ�����ֻ��intһ������

    Match("��������",false);  // ����˵��
    if (bHaveError) {
        cout << "��syntax error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue << endl;
        stckError.push("��syntax error��: at line:"+to_string(wdNextWord.iLine)+" the "+to_string(iCur)+" th letter; error word: "+wdNextWord.strValue+"\n");
        bHaveError = false;
        FixUnknownType();
        //system("pause");
    }
    string type = wdNextWord.strValue;
    
    Scanner();
    
    ParseIdentifiersList(type); // ƥ���ʶ���б�
}

void ParsePhrasePart() {
    // <��䲿��> �� <��䲿��><���>;|<���>;
    cout << depth++ << ":���﷨�Ƶ��� " << ": <��䲿��> �� <���>;<��䲿��prime>\n";
    ParsePhrase();
    Match(";",true);
    PrintMissingSemicolon("missing ;");
    Scanner();
    ParsePhrasePart1();
}


void ParsePhrasePart1() {
    if (wdNextWord.iType == mpName2Num["identifier"] ||
        (wdNextWord.strValue == "if") ||
        (wdNextWord.strValue == "while")) {  // �������׷����Ļ� �����֧
        cout << depth++ << ":���﷨�Ƶ��� " << ": <��䲿��prime> �� <���>;<��䲿��prime>\n";
        ParsePhrase();
        Match(";",true);
        PrintMissingSemicolon("missing ;");
        Scanner();
        ParsePhrasePart1();
    }
    else {
        cout << depth++ << ":���﷨�Ƶ��� " << ": <��䲿��prime> �� <�մ�>\n";
        // do nothing
    }
    return;
}






void ParseIdentifiersList(string type) {
    // <��ʶ���б�> �� <��ʶ���б�>,<��ʶ��>|<��ʶ��>
    cout << depth++ << ":���﷨�Ƶ��� " << ": <��ʶ���б�> �� <��ʶ��><��ʶ���б�prime>\n";


    //Scanner();
    Match("identifier",false);
    if (bHaveError) {
        PrintMissingSemicolon(" not an identifier!");
        Scanner();
        return;
    }
    UpdateIdentifierList(type);
    Scanner();
    // ���ʶ��ɹ���һ����ʶ�� ��ô�������ʶ�����뵽��ʶ���б��в����ж���û���ظ�������
    ParseIdentifiersList1(type);

                   // ����һ�δʷ���������
    
}        // ������ʶ���б���



void ParseIdentifiersList1(string type) {
    if (wdNextWord.iType == mpName2Num[","]) {
         cout << depth++ << ":���﷨�Ƶ��� " << ": <��ʶ���б�prime> �� <��ʶ��>,<��ʶ���б�prime>\n";
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
        cout << depth++ << ":���﷨�Ƶ��� " << ": <��ʶ���б�1> �� <�մ�>\n";
        // nothing
    }
    
}      // ���ڽ�����ʶ���б���һ����ݹ�������Ҫ�������ĸı������ݹ�
// ����ݹ�����г������쳣����զ�� �᷵�ظ��ݹ�ջ��������һ�� �����е�trycatch����

void ParsePhrase() {
    // <���> �� <��ֵ���>|<�������>|<ѭ�����>
    //cout << depth++ << ":���﷨�Ƶ��� " << ": <���> �� <��ֵ���>|<�������>|<ѭ�����>\n";

    if (wdNextWord.iType == mpName2Num["identifier"]) {
        cout << depth++ << ":���﷨�Ƶ��� " << ": <���> �� <��ֵ���>\n";
        ParseAssignmentPhrase();
    }
    else if (wdNextWord.strValue == "if") {
        cout << depth++ << ":���﷨�Ƶ��� " << ": <���> �� <�������>\n";
        ParseConditionPhrase();
    }
    else if (wdNextWord.strValue == "while") {
        cout << depth++ << ":���﷨�Ƶ��� " << ": <���> �� <ѭ�����>\n";
        ParseLoopPhrase();
    }
    return;
}

void ParseAssignmentPhrase() {
    // <��ֵ���> �� <��ʶ��>=<���ʽ>

    cout << depth++ << ":���﷨�Ƶ��� " << ": <��ֵ���> �� <��ʶ��>=<���ʽ>\n";

    Match("identifier",false);
    if (!CheckIdentifierExist())return;     // �����ʶ�������ھ�ֱ��return
    string tVar = wdNextWord.strValue;
    Scanner();
    Match("=",true);
    PrintMissingSemicolon("missing  =");
    Scanner();
    tmpVar arg1 = ParseExpressionPhrase();
    qua.push_back(quaternary("=", arg1.name, "null", tVar));

    // ���±�ʶ���б����
    mpIdentifierTable[tVar] = arg1.value;



    cout << "��ʶ���б���³ɹ�  ��ֵ���" << "  id:" << tVar << "  value:" << arg1.value << endl;

}


tmpVar ParseExpressionPhrase() {

    cout << depth++ << ":���﷨�Ƶ��� " << ": <���ʽ> �� <��><���ʽprime>\n";
    tmpVar arg1 = ParseItem();
    tmpVar ret = ParseExpressionPhrase1(arg1);
    return ret;

}

tmpVar ParseExpressionPhrase1(tmpVar arg) {

    tmpVar ret = arg;
    tmpVar to_pass;

    if (wdNextWord.strValue == "+") {
        cout << depth++ << ":���﷨�Ƶ��� " << ": <���ʽprime> �� <�ӷ������><��><���ʽprime>\n";
        Match("+",true);
        Scanner();
        tmpVar arg2 = ParseItem();
        string var_name = "tmp" + to_string(tmpVarNum++);
        qua.push_back(quaternary("+", arg.name, arg2.name, var_name));
        // ��������arg  �� arg1 ���п�����һ������
        //mpTmpVar[var_name] = mpTmpVar[arg] + mpTmpVar[arg2];
        ret.name = var_name;
        ret.value = arg.value + arg2.value;
        to_pass = ret;
        ret = ParseExpressionPhrase1(to_pass);
    }
    else {
        cout << depth++ << ":���﷨�Ƶ��� " << ": <���ʽprime> �� <�մ�>\n";
        // nothing to do
    }
    return ret;
}


tmpVar ParseItem() {
    cout << depth++ << ":���﷨�Ƶ��� " << ": <��> �� <����><��prime>\n";

    tmpVar arg1 = ParseFactor();
    tmpVar ret = ParseItem1(arg1);
    return ret;
}

tmpVar ParseItem1(tmpVar arg) {
    tmpVar ret = arg;
    tmpVar to_pass;
    if (wdNextWord.strValue == "*") {
        cout << depth++ << ":���﷨�Ƶ��� " << ": <��prime> �� <�˷������><����><��prime>\n";
        Match("*",true);
        Scanner();
        tmpVar arg2 = ParseFactor();
        if (bHaveError) {
            cout << "��syntax error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue +" ����Ϊ�մ� * ����ȱ������ " << endl;
            stckError.push("��syntax error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "����Ϊ�մ� * ����ȱ������\n");
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
        cout << depth++ << ":���﷨�Ƶ��� " << ": <��prime> �� <�մ�>\n";
        // do nothing
    }
    return ret;
}


tmpVar ParseFactor() {
    // cout << depth++ << ":���﷨�Ƶ��� " << ": <����> �� <��ʶ��>|<����>|(<���ʽ>)\n";

    tmpVar ret;
    if (wdNextWord.iType == mpName2Num["identifier"]) {
        cout << depth++ << ":���﷨�Ƶ��� " << ": <����> �� <��ʶ��>\n";
        Match("identifier",false);
        if (!CheckIdentifierExist())return ret;
        ret.name = wdNextWord.strValue;
        ret.value = mpIdentifierTable[wdNextWord.strValue];             // �������ӵ��ӳ��������жϸñ�ʶ���Ƿ��г�ʼֵ��
        Scanner();

    }
    else if (wdNextWord.iType == mpName2Num["number"]) {
        cout << depth++ << ":���﷨�Ƶ��� " << ": <����> �� <����>\n";
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
        cout << depth++ << ":���﷨�Ƶ��� " << ": <����> �� (<���ʽ>)\n";
        Match("(",true);
        Scanner();
        ret = ParseExpressionPhrase();
        Match(")",true);
        PrintMissingSemicolon("missing  )");
        Scanner();
    }
    else {
        //cout << depth++ << ":��syntax error�� " << ": <����> �� <�մ�>  ���Ӳ���Ϊ�մ�\n";
        //bHaveError = true;      // ���Ӳ���Ϊ�մ�
        PrintMissingSemicolon("<����> �� <�մ�>  ���Ӳ���Ϊ�մ�");

    }
    return ret;
}


// Match��������������ƥ�仹���ϸ�ƥ��

void ParseConditionPhrase() {

    cout << depth++ << ":���﷨�Ƶ��� " << ": <�������> �� if ��<����>�� then <Ƕ�����>; else <Ƕ�����>\n";


    Match("if",true);
    Scanner();
    Match("(", true);
    Scanner();
    tmpVar arg1 = ParseCondition();
    qua.push_back(quaternary("jnz", arg1.name, "null", to_string(qua.size()-1 + 3))); // ��������ڵ����
    int falseExitIndex1 = qua.size();
    qua.push_back(quaternary("j", "null", "null", "����"));                         // �����ٳ��ڵ���ת���
  
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

    cout << depth++ << ":���﷨�Ƶ��� " << ": <����> �� <���ʽ><��ϵ�����><���ʽ>\n";
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

    // ��Ҫ�ҵ������׷���
    if (wdNextWord.iType == mpName2Num["identifier"] ||
        (wdNextWord.iType == mpName2Num["if"] && wdNextWord.strValue == "if") || 
        (wdNextWord.iType == mpName2Num["while"] && wdNextWord.strValue == "while")) {
        cout << depth++ << ":���﷨�Ƶ��� " << ": <Ƕ�����> �� <���>\n";
        ParsePhrase();
    }
    else if (wdNextWord.iType == mpName2Num["begin"] && wdNextWord.strValue == "begin") {
        cout << depth++ << ":���﷨�Ƶ��� " << ": <Ƕ�����> �� <�������>\n";
        ParseMultiPhrase();
    }
    else {
        // Missing Keyword
        PrintMissingSemicolon("an error occur  when  parsing NestedPhrase  missing  keyword");
    }
}


void ParseMultiPhrase() {
    cout << depth++ << ":���﷨�Ƶ��� " << ": <�������> �� begin <��䲿��> end\n";

    Match("begin", true);
    PrintMissingSemicolon("missing begin");
    Scanner();
    ParsePhrasePart();
    Match("end", true);
    PrintMissingSemicolon("missing end");
    Scanner();

}



void ParseLoopPhrase() {
    cout << depth++ << ":���﷨�Ƶ��� " << ": <ѭ�����> �� while ��<����>�� do <Ƕ�����>\n";
 
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
���������ϸ���쳣�������
*/

