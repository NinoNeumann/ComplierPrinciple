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
    InitMap();
    char ch;
    freopen("in.txt", "r", stdin);

    iFileLength = 0;
    // ������txt���뵽letter buffer��
    while (~scanf("%c", &ch)) {
        str_arrLetters[iFileLength++] = ch;
        //if (ch == ',')str_arrLetters[iFileLength++] = " ";
        //else if(ch==';')str_arrLetters[iFileLength++] = "\n";
    }
    //// �ļ�д��
    //FILE* stream;
    //if ((stream = freopen("file.txt", "w", stdout)) == NULL)
    //    exit(-1);
    //for (int i = 0; i < iFileLength; ++i)printf("%c", str_arrLetters[i].c_str());

    //fflush(stream);
    //stream = freopen("CON", "w", stdout); //stdout ��������ĩβ�Ŀ���̨�ض���
    //printf("And now back to the console once again\n");
    //// ��������������
    freopen("CON", "r", stdin);    // �ر� ��cout��Ȩ�����·Ż�console��

   /* ofstream fout("out.txt");
    for (int i = 0; i < iFileLength; ++i) {
        fout<<str_arrLetters[i].c_str();
    }
    fout.close();*/
    
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
    try {
        ParseProgram();
    }
    catch (const char* s) {
        cout << s << endl;
        cout << "line: " << wdNextWord.iLine << " have an error!!" << " error message: " << wdNextWord.strValue << " at the " << iCur << "th letter" << endl;
    }
    



    // ��� ��ʶ��table
    cout << "identifier table:";
    map<string, ll>::iterator it;
    for (it = mpIdentifierTable.begin(); it != mpIdentifierTable.end(); it++) {
        string s = it->first;
        printf("%s %d\n", s.data(), it->second);
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

    // �����Ԫʽ
    for (int i = 0; i < qua.size(); ++i) {
        cout <<"idx:"<<i<<"  "<< qua[i].op << " " << qua[i].arg1 << " " << qua[i].arg2 << " " << qua[i].res << endl;
    }
   
    system("pause");
    return 0;
}
