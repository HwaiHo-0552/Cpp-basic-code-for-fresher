                                            //       C++ 基础：遍历文件夹下文件 code  
                                            //   Dilusense-核心技术中心-算法工程师 Maxz
                                            //           2021.12.16 Hefei

//                                   一些说明，需要看的是C++代码的整体思路、风格，数据是如何进行存储和表达的.
//        ！！注意！！ 为了使用这个结构体将文件的信息存储到该结构体的内存空间，需要搭配使用_findfirst()、_findnext()、_findclose()三个函数使用.
//                                   ！！注意  win10中_findfirst的变量定义为  long long 类型，不然会出错！！


#include<io.h>
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;

void Find_files(string pth, string fmat, vector<string>& v_tmp);

int main(){
    
    string format = ".txt";
    string folder_pth = "F:\\code\\fileflow\\folder_img";
    vector<string> v1;

    Find_files(folder_pth, format, v1);
    cout << v1.size() << endl;

    return 0;
}

void Find_files(string pth, string fmat, vector<string>& v_tmp){
    
    long long head_f;
    struct _finddata_t f_info;                                                                       // 定义一个存储信息的struct.
    string type_j, f_name;
    type_j = type_j.assign(pth).append("\\*"+fmat);
    head_f = _findfirst(type_j.c_str(), &f_info);
    if (head_f != -1){
        do{
            f_name = f_name.assign(pth).append("\\").append(f_info.name);
            v_tmp.push_back(f_name);
            cout << f_name << endl;
            
        }while(_findnext(head_f, &f_info)==0);
        _findclose(head_f);
    }
}