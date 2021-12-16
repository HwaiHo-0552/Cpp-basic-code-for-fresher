                                         //       C++ 基础：文件打开和写入 code  
                                         //   Dilusense-核心技术中心-算法工程师 Maxz
                                         //           2021.12.16 Hefei

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void sh_src_cont(string pth);
void w_2_file(string pth, string cont);

int main(){
    string file_pth = "F:\\code\\fileflow\\folder_img\\test.txt";
    string content = "Hello World";

    sh_src_cont(file_pth);
//    w_2_file(file_pth, content);

    return 0;
}

// 打开文件, 并显示原先内容.
void sh_src_cont(string pth){
    string s;
    ifstream f_tmp;                               // 调用函数，建立联系.
    f_tmp.open(pth, ios::in);                     // 将磁盘文件读入内存中.
    if(!f_tmp){
        cout << "!!ERROR!!, please give the correct file path" << endl;
    }
    else{
        cout << "File is OK for process... " << endl;
        cout << "Free Coding." << endl;

        while(getline(f_tmp, s)){               //调用getline函数，一行行判断file中的内容并显示.
            cout << s << endl;
        }
    }

    f_tmp.close();
}

// 文件写操作.
void w_2_file(string pth, string cont){
    ofstream f_tmp;
    f_tmp.open(pth, ios::app);
    cout << "written content: " << cont << ", and is finished" << endl;
    f_tmp << endl << cont << endl;

    f_tmp.close();
}