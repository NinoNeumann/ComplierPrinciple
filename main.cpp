#define _CRT_SECURE_NO_WARNINGS
#include "MyComplier.h"



/*
�����淶��
    �ϸ��� ��������ʾ�� ����ǰ׺�ı�ʾ�������£�
    mp-  :  mp      ǰ׺ ��ʾ map<>���� ���еľ����ӳ���ϵ��Ҫ�������߼��ϱ�ʾ  ����mpName2Num  ��ʾName �� Num��map �Ǿ���string �� int ��һ��ӳ���ϵ������������hash����ڲ�ӳ���ֶε�����������ʡ���ˣ�
    uset-:  uset    ǰ׺ ��ʾ unordered_set<>����
    str- :  str     ǰ׺ ��ʾ string����
    i-   :  i       ǰ׺ ��ʾ int����
    wd-  :  wd      ǰ׺ ��ʾ word���Զ���Ľṹ�壩����  ��ϸ������ĺ�������
    -arr-:  arr     ǰ׺ ��ʾ �������� ������ǰ�����������������ϳɲ�ͬ���͵�����  ���� str_arr ��string���͵����顣
    b-   :  b       ǰ׺ ��ʾ bool����
*/




int main() {
    // �������
    //setfill(' ');
    InitMap();
    char ch;

    ifstream i_file("in.txt");
    streambuf* in_file = cin.rdbuf();
    cin.rdbuf(i_file.rdbuf());

    iFileLength = 0;
    // ������txt���뵽letter buffer��
    while (cin>>ch && ch!=EOF) {
        str_arrLetters[iFileLength++] = ch;
    }
    cin.rdbuf(in_file);
    
    //
    cout << "File_length: " << iFileLength << endl;
    iCur = 0;
    iCurLine = 1;


    // �ʷ����������main��������
    //while (iCur != iFileLength) {
    //    try {
    //        Scanner();
    //    }
    //    catch(const char *s){
    //        cout << s << endl;
    //        cout<< "line: " << wdNextWord.iLine << " have an error!!" << " error message: " << wdNextWord.strValue << " at the " << iCur << "th letter" << endl;
    //        bHaveError = false;
    //    }
    //    
    //    // �����Ǵʷ�������������ִ���ı�����
    //    /*if (bHaveError) {
    //        cout <<"line: "<< wdNextWord.iLine << " have an error!!"<<" error message: "<< wdNextWord.strValue<<" at the "<<iCur<<"th letter"<<endl;
    //    }
    //    bHaveError = false;*/
    //    
    //    // ����ʷ����������г��ֵĶ�Ԫʽ
    //    cout <<"(" << mpNum2Name[wdNextWord.iType] << "," << wdNextWord.strValue << ")" << endl;
    //}
    // 
    

    // �﷨�������򲿷ֵ�main����
    Scanner();
    ParseProgram();



    cout << endl;
    // ��� ��ʶ��table
    cout << "identifier table:";
    map<string, ll>::iterator it;
    for (it = mpIdentifierTable.begin(); it != mpIdentifierTable.end(); it++) {
        string s = it->first;
        printf("(int, %s, %d)", s.data(), it->second);
    }
    cout << ";\n";
    // �������table
    cout << "constant table: ";
    for (auto x:usetConstantsTable) {
        cout << x<<" ";
    }
    cout << ";\n";
    // ������
    while (!stckError.empty()) {
        cout << stckError.top() << endl;
        stckError.pop();
    }
    cout << endl;

    // �����Ԫʽ
    
    for (int i = 0; i < qua.size(); ++i) {
        cout <<"("<< setw(2) << setiosflags(ios::left) << i<<")  ("
            <<setw(3)<<setiosflags(ios::left)<< qua[i].op << ", " 
            <<setw(5) << setiosflags(ios::left) << qua[i].arg1 << ", " 
            << setw(5) << setiosflags(ios::left) << qua[i].arg2 << ", " 
            << setw(5) << setiosflags(ios::left) << qua[i].res <<")" << endl;
    

    }

    // ����Ԫʽ������ļ�
    ofstream outf("out.txt");
    streambuf* strmBuf = cout.rdbuf();
    cout.rdbuf(outf.rdbuf());
    for (int i = 0; i < qua.size(); ++i) {
        cout << "(" << setw(2) << setiosflags(ios::left) << i << ")  ("
            << setw(3) << setiosflags(ios::left) << qua[i].op << ", "
            << setw(5) << setiosflags(ios::left) << qua[i].arg1 << ", "
            << setw(5) << setiosflags(ios::left) << qua[i].arg2 << ", "
            << setw(5) << setiosflags(ios::left) << qua[i].res << ")" << endl;
    }
    cout.rdbuf(strmBuf);
    system("pause");
    return 0;
}
