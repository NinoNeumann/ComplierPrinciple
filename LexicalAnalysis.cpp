#include "MyComplier.h"


// ��ʼֵ��Ĭ�ϸ�ֵ
// δ�����ı�����  
//      δ�����ı�������δ���
// ������������δ����� ��ʶ��
// �Ȳ�����Ԫʽ������Ԫʽ����һ��ִ�� �޸����� ����


void Match(string letter,const bool mode = true) {
    // ��Match������ִ����ʱ��ͻᱨ�� ����wdNextword����ʱͣ���ڴ�����ֵĵط�
    if (mode) {
        if (wdNextWord.strValue != letter) {
            if (mpNum2Name[mpName2Num[letter]] == "separator") {
                // ����Ƿָ���ƥ����󱨴�
                iHaveError = 5;
            }
            else if (mpNum2Name[mpName2Num[letter]] == "keyword") {
                iHaveError = 6;
            }
            else if (mpNum2Name[mpName2Num[letter]] == "mathOperator") {
                iHaveError = 7;
            }
            else if (mpNum2Name[mpName2Num[letter]] == "logicalOperator") {
                iHaveError = 8;
            }
            //iHaveError = 2;
        }// ֵ��ƥ��  ���ڷָ��� �ؼ���
    }
    else {
        if (mpNum2Name[wdNextWord.iType] != letter) {
            if (letter == "number") {
                iHaveError = 10;
            }else{
                iHaveError = 2;
            }
            
        }       // ���Ͳ�ƥ��  �߼������  ��ʶ��
    }
    return;
}


void ParseProgram() {
    // ���Ƚ������������������岿��
    // ������;��
    // ������䲿��
    // ParseProgram���ֵ��õ��Ӻ��������Լ�catch�Լ����Ӻ�����throw�ı�����Ϣ��
    
    printUtils(":���﷨�Ƶ��� : <����> ��<����˵������>;<��䲿��>");
    

    ParseVariableDeclaration();
    if(ErrorManagement(""))return;
    Match(";",true);
    /*if (bHaveError) {
        cout << "��syntax error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue <<"  missing \";\"" << endl;
        stckError.push("��syntax error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue+"  missing \";\"\n");
        bHaveError = false;
    }*/
    Scanner();
    ParsePhrasePart();
    
}                // �������򲿷�


void ParseVariableDeclaration() {

    // <����˵��> �� int
    printUtils(":���﷨�Ƶ��� : <����˵������> �� <����˵��><��ʶ���б�>");
    // ����������Ҫ���ǵĳ����������Ͳ������ͱ�����  ������ߵ�����ֻ��intһ������

    Match("��������",false);  // ����˵��
    if (iHaveError) {
        ErrorManagementAssistant("lexical warning", "the unknown declaration:  \"" + wdNextWord.strValue + "\"   has been changed to \"int\"");
        wdNextWord.strValue = "int";
        wdNextWord.iType = mpName2Num[wdNextWord.strValue];
        iHaveError = 0;
    }
    string type = wdNextWord.strValue;
    
    Scanner();
    
    ParseIdentifiersList(type); // ƥ���ʶ���б�
}

void ParsePhrasePart() {
    // <��䲿��> �� <��䲿��><���>;|<���>;
    printUtils(":���﷨�Ƶ��� : <��䲿��> �� <���>;<��䲿��prime>");
    ParsePhrase();
    Match(";",true);
    if (ErrorManagement(";"))return;
    Scanner();
    ParsePhrasePart1();
}


void ParsePhrasePart1() {
    if (wdNextWord.iType == mpName2Num["identifier"] ||
        (wdNextWord.strValue == "if") ||
        (wdNextWord.strValue == "while")) {  // �������׷����Ļ� �����֧
        printUtils(":���﷨�Ƶ��� : <��䲿��prime> �� <���>;<��䲿��prime>");
        ParsePhrase();
        Match(";",true);
        if (ErrorManagement(";"))return;
        Scanner();
        ParsePhrasePart1();
    }
    else {
        printUtils(":���﷨�Ƶ��� : <��䲿��prime> �� <�մ�>");
        // do nothing
    }
    //else if(wdNextWord.strValue==";") {
    //    cout << depth++ << ":���﷨�Ƶ��� " << ": <��䲿��prime> �� <�մ�>\n";
    //    // do nothing
    //}
    //else {
    //    iHaveError = 11;
    //    ErrorManagement("");
    //}
    return;
}






void ParseIdentifiersList(string type) {
    // <��ʶ���б�> �� <��ʶ���б�>,<��ʶ��>|<��ʶ��>
    printUtils(":���﷨�Ƶ��� : <��ʶ���б�> �� <��ʶ��><��ʶ���б�prime>");
    //Scanner();
    Match("identifier", false);
    if (iHaveError) {
        ErrorManagementAssistant("lexical error", " the illegal identifier:" + wdNextWord.strValue);
        Scanner();
        if (wdNextWord.strValue == ",") {
            Scanner();
            if (wdNextWord.iType != mpName2Num["identifier"]) {
                iHaveError = 4;  // �﷨����
                return;
            }
        }
        else {
            if (wdNextWord.strValue == ";") {
                return;
            }
            else {
                iHaveError = 4;
                ErrorManagementAssistant("syntax error", " the bad identifier please check!  identifier:" + wdNextWord.strValue);
                return;
            }
        }
        iHaveError = 0;
    }
    UpdateIdentifierList(type);
    Scanner();
    // ���ʶ��ɹ���һ����ʶ�� ��ô�������ʶ�����뵽��ʶ���б��в����ж���û���ظ�������
    ParseIdentifiersList1(type);

                   // ����һ�δʷ���������
    
}        // ������ʶ���б���



void ParseIdentifiersList1(string type) {
    if (wdNextWord.iType == mpName2Num[","]) {
         printUtils(":���﷨�Ƶ��� : <��ʶ���б�prime> �� <��ʶ��>,<��ʶ���б�prime>");
         Match(",",true);
         //PrintMissingSemicolon("missing ,");
         Scanner();
         Match("identifier",false);
         if (iHaveError) {
             ErrorManagementAssistant("lexical error", " the illegal identifier:" + wdNextWord.strValue);
             Scanner();
             if (wdNextWord.strValue == ",") {
                 Scanner();
                 if (wdNextWord.iType != mpName2Num["identifier"]) {
                     iHaveError = 4;  // �﷨����
                     return;
                 }
             }
             else {
                 if (wdNextWord.strValue == ";") {
                     return;
                 }
                 else {
                     iHaveError = 4;
                     ErrorManagementAssistant("syntax error", " the bad identifier please check!  identifier:"+wdNextWord.strValue);
                     return;
                 }
             }
             iHaveError = 0;
             
         }
         UpdateIdentifierList(type);
         Scanner();
         ParseIdentifiersList1(type);
    }
    else if (wdNextWord.iType != mpName2Num[";"]) {   // ��ʶ���б���ȱ��","   ԭ����wdNextWord.iType == mpName2Num["identifier"]
        iHaveError = 2;                                 // �﷨����
        //PrintMissingSemicolon("missing ,");
        ErrorManagement(",");

    }
    else if(wdNextWord.iType == mpName2Num[";"]) {
        printUtils(":���﷨�Ƶ��� : <��ʶ���б�1> �� <�մ�>");
        // nothing
    }
    
}      // ���ڽ�����ʶ���б���һ����ݹ�������Ҫ�������ĸı������ݹ�
// ����ݹ�����г������쳣����զ�� �᷵�ظ��ݹ�ջ��������һ�� �����е�trycatch����

void ParsePhrase() {
    // <���> �� <��ֵ���>|<�������>|<ѭ�����>
    //cout << depth++ << ":���﷨�Ƶ��� " << ": <���> �� <��ֵ���>|<�������>|<ѭ�����>\n";

    if (wdNextWord.iType == mpName2Num["identifier"]) {
        printUtils(":���﷨�Ƶ��� : <���> �� <��ֵ���>");
        ParseAssignmentPhrase();
    }
    else if (wdNextWord.strValue == "if") {
        
        printUtils(":���﷨�Ƶ��� : <���> �� <�������>");
        ParseConditionPhrase();
    }
    else if (wdNextWord.strValue == "while") {
        printUtils(":���﷨�Ƶ��� : <���> �� <ѭ�����>");
        ParseLoopPhrase();
    }
    else if (iCur!=iFileLength) {
        iHaveError = 11;
        ErrorManagement("");
    }
    return;
}

void ParseAssignmentPhrase() {
    // <��ֵ���> �� <��ʶ��>=<���ʽ>
    printUtils(":���﷨�Ƶ��� : <��ֵ���> �� <��ʶ��>=<���ʽ>");

    Match("identifier",false);
    if (!CheckIdentifierExist())return;     // �����ʶ�������ھ�ֱ��return
    string tVar = wdNextWord.strValue;
    Scanner();
    Match("=",true);
    //PrintMissingSemicolon("missing  =");
    Scanner();
    tmpVar arg1 = ParseExpressionPhrase();
    qua.push_back(quaternary("=", arg1.name, "null", tVar));

    // ���±�ʶ���б����
    mpIdentifierTable[tVar] = arg1.value;



    cout << "��ʶ���б���³ɹ�  ��ֵ���" << "  id:" << tVar << "  value:" << arg1.value << endl;

}


tmpVar ParseExpressionPhrase() {
    printUtils(":���﷨�Ƶ��� : <���ʽ> �� <��><���ʽprime>");
    tmpVar arg1 = ParseItem();
    tmpVar ret = ParseExpressionPhrase1(arg1);
    return ret;

}

tmpVar ParseExpressionPhrase1(tmpVar arg) {

    tmpVar ret = arg;
    tmpVar to_pass;

    if (wdNextWord.strValue == "+") {
     
        printUtils(":���﷨�Ƶ��� : <���ʽprime> �� <�ӷ������><��><���ʽprime>");
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
        printUtils(":���﷨�Ƶ��� : <���ʽprime> �� <�մ�>");
        // nothing to do
    }
    return ret;
}


tmpVar ParseItem() {

    printUtils(":���﷨�Ƶ��� : <��> �� <����><��prime>");

    tmpVar arg1 = ParseFactor();
    tmpVar ret = ParseItem1(arg1);
    return ret;
}

tmpVar ParseItem1(tmpVar arg) {
    tmpVar ret = arg;
    tmpVar to_pass;
    if (wdNextWord.strValue == "*") {
        printUtils(":���﷨�Ƶ��� : <��prime> �� <�˷������><����><��prime>");
        Match("*",true);
        if (ErrorManagement("*"))return ret;
        Scanner();
        tmpVar arg2 = ParseFactor();
        /*if (bHaveError) {
            cout << "��syntax error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue +" ����Ϊ�մ� * ����ȱ������ " << endl;
            stckError.push("��syntax error��: at line:" + to_string(wdNextWord.iLine) + " the " + to_string(iCur) + " th letter; error word: " + wdNextWord.strValue + "����Ϊ�մ� * ����ȱ������\n");
            bHaveError = false;
        }*/
        ErrorManagement(" ��������ʱ����");
        string var_name = "tmp" + to_string(tmpVarNum++);

        qua.push_back(quaternary("*", arg.name, arg2.name, var_name));
        ret.name = var_name;
        ret.value = arg.value * arg2.value;
        to_pass = ret;
        ret = ParseItem1(to_pass);
    }
    else {
        printUtils(":���﷨�Ƶ��� : <��prime> �� <�մ�>");
        // do nothing
    }
    return ret;
}


tmpVar ParseFactor() {
    // cout << depth++ << ":���﷨�Ƶ��� " << ": <����> �� <��ʶ��>|<����>|(<���ʽ>)\n";

    tmpVar ret;
    if (wdNextWord.iType == mpName2Num["identifier"]) {
        printUtils(":���﷨�Ƶ��� : <����> �� <��ʶ��>");
        Match("identifier",false);
        if (!CheckIdentifierExist())return ret;
        if (mpIdentifierTable[wdNextWord.strValue] == -1) {
            iHaveError = 13;
            ErrorManagement("");
            return ret;
        }
        ret.name = wdNextWord.strValue;
        ret.value = mpIdentifierTable[wdNextWord.strValue];             // �������ӵ��ӳ��������жϸñ�ʶ���Ƿ��г�ʼֵ��
        Scanner();

    }
    else if (wdNextWord.iType == mpName2Num["number"]) {
        printUtils(":���﷨�Ƶ��� : <����> �� <����>");
        Match("number",false);
        /*if (iHaveError) {
            PrintMissingSemicolon("the number is unregualr!");
            ErrorManagementAssistant("")
            return ret;
        }*/
        ret.name = wdNextWord.strValue;
        ret.value = iHaveError ? -1:stoll(ret.name);
        if(ErrorManagement("number"))return ret;
        Scanner();
    }
    else if (wdNextWord.strValue == "(") {
        printUtils(":���﷨�Ƶ��� : <����> �� (<���ʽ>)");
        Match("(",true);
        if (ErrorManagement("("))return ret;
        Scanner();
        ret = ParseExpressionPhrase();
        Match(")",true);
        if (ErrorManagement(")"))return ret;
        Scanner();
    }
    else {
        ErrorManagementAssistant("syntax  error", "  ���Ӳ���Ϊ�մ�");
    }
    return ret;
}


// Match��������������ƥ�仹���ϸ�ƥ��

void ParseConditionPhrase() {
    printUtils(":���﷨�Ƶ��� : <�������> �� if ��<����>�� then <Ƕ�����>; else <Ƕ�����>");


    Match("if",true);
    if (ErrorManagement("if"))return;
    Scanner();
    Match("(", true);
    if (ErrorManagement("("))return;
    Scanner();
    tmpVar arg1 = ParseCondition();
    qua.push_back(quaternary("jnz", arg1.name, "null", to_string(qua.size()-1 + 3))); // ��������ڵ����
    int falseExitIndex1 = qua.size();
    qua.push_back(quaternary("j", "null", "null", "����"));                         // �����ٳ��ڵ���ת���
  
    Match(")", true);
    if (ErrorManagement(")"))return;
    Scanner();
    Match("then", true);
    if (ErrorManagement("then"))return;
    Scanner();
    ParseNestedPhrase();
    int falseExitIndex2 = qua.size();
    qua.push_back(quaternary("j", "null", "null", "0"));
    qua[falseExitIndex1].res = to_string(qua.size());
    Match(";", true);
    if (ErrorManagement(";"))return;
    Scanner();
    Match("else", true);
    if (ErrorManagement("else"))return;
    Scanner();
    ParseNestedPhrase();
    qua[falseExitIndex2].res = to_string(qua.size());
  
}


tmpVar ParseCondition() {
    printUtils(":���﷨�Ƶ��� : <����> �� <���ʽ><��ϵ�����><���ʽ>");
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
    if (wdNextWord.iType == mpName2Num["identifier"] || (wdNextWord.strValue == "if") || (wdNextWord.strValue == "while")) {
        printUtils(":���﷨�Ƶ��� : <Ƕ�����> �� <���>");
        (wdNextWord.iType == mpName2Num["while"] && wdNextWord.strValue == "while")) {
        cout << depth++ << ":���﷨�Ƶ��� " << ": <Ƕ�����> �� <���>\n";
    else if (wdNextWord.strValue == "begin") {
        printUtils(":���﷨�Ƶ��� : <Ƕ�����> �� <�������>");
    else if (wdNextWord.iType == mpName2Num["begin"] && wdNextWord.strValue == "begin") {
        cout << depth++ << ":���﷨�Ƶ��� " << ": <Ƕ�����> �� <�������>\n";
        ParseMultiPhrase();
    }
    else {
        iHaveError = 9;
        ErrorManagement("");
    }
}


void ParseMultiPhrase() {
    printUtils(":���﷨�Ƶ��� : <�������> �� begin <��䲿��> end");
    Match("begin", true);
    if (ErrorManagement("begin"))return;
    Scanner();
    ParsePhrasePart();
    Match("end", true);
    if (ErrorManagement("end"))return;
    Scanner();

}



void ParseLoopPhrase() {
    printUtils(":���﷨�Ƶ��� : <ѭ�����> �� while ��<����>�� do <Ƕ�����>");
    Match("while", true);
    if (ErrorManagement("while"))return;
    Scanner();
    Match("(");
    if (ErrorManagement("("))return;
    Scanner();
    int conIdx = qua.size();
    tmpVar arg = ParseCondition();
    int idx = qua.size();
    qua.push_back(quaternary("jnz", arg.name, "null", to_string(qua.size() + 2)));
    int falseExitIndex = qua.size();
    qua.push_back(quaternary("j", "null", "null", "0"));
    Match(")");
    if (ErrorManagement(")"))return;
    Scanner();
    Match("do");
    if (ErrorManagement("do"))return;
    Scanner();
    ParseNestedPhrase();
    
    qua.push_back(quaternary("j", "null", "null", to_string(conIdx)));
    qua[falseExitIndex].res = to_string(qua.size());

}



/*
���������ϸ���쳣�������
*/

