// face_detection 输入 C++接口
// Function:  1. 批处理读取文件夹下image文件，
//                  2. 对每个image进行means substruction then resize的预处理，
//                  3. 字符串分隔处理，按对应名字保存.
//                                    返回C++类型接口->供->模型部署调用
// Coder: dilusense maxz
// date: 2021.12.20 , Location: Hefei, CHN.  

#include <io.h>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<string> search_folder(string folder_pth, string img_typ);                  // 函数: 索引原图所在的文件夹，并将images的path存放在vector中.
Mat img_procs(Mat temp_img, string img_pth, int means[], int size[]);             // 函数: 对原图进行预处理.
vector<string> split_ch(const string& ch, const char pattern);                    // 函数: 字符串处理，保存预处理图像，进行命名方式操作. 

int main(){
	
	string img_folder = ".......\\..........\\..........";                                  // 改成image文件夹对应的path
	string img_type = ".jpg";                                                               // 待需索取的image TYPE类型(i.e.  jpg\png\bmp and so on...)
	vector<string> imgs_path;
	int means_value[3] = { 100, 100, 100 };                                                 // 预设的均值参数
	int para_size[2] = { 224, 224 };                                                        // 预设resize的大小
	Mat img_tmp;

	imgs_path = search_folder(img_folder, img_type);                                        // 将硬盘folder中的images，读入内存处理，并保持在vector中.
	for (int i = 0; i < imgs_path.size(); i++) {
		img_tmp = img_procs(img_tmp, imgs_path[i], means_value, para_size);
	}

	return 0;
}

vector<string> search_folder(string folder_pth, string img_typ) {
	
	long long head_imgs;
	vector<string> imgs_pth;
	struct _finddata_t  folder_stc;                                    // 将folder利用一个结构体保存，其中的files可通过pointer指针按一种链表的数据结构-进行-read or process.
	string format_img, img_name;

	format_img = format_img.assign(folder_pth).append("\\*" + img_typ);
	head_imgs = _findfirst(format_img.c_str(), &folder_stc);

	if (head_imgs != -1) {
		do {
			img_name = img_name.assign(folder_pth).append("\\").append(folder_stc.name);
			imgs_pth.push_back(img_name);
		} while (_findnext(head_imgs, &folder_stc) == 0);
		_findclose(head_imgs);
	}

	return imgs_pth;
}

Mat img_procs(Mat temp_img, string img_pth, int *means, int *size) {
	Mat source_img, preprocs_img;
	string save_name;
	source_img = imread(img_pth);
	vector<string> out_ch;
	const char* pattern = ".";

	preprocs_img.create(source_img.size(), source_img.type());

	cout << "preprocessing image's shape as follows" << endl
		<< "size of : " << source_img.size() << endl
		<< "nums of channels: " << source_img.channels()
		<< endl;

	if (source_img.channels() != 3) {
		cout << "Not RGB image" << endl;
	}
	else {
		for (int c = 0; c < 3; c++) {
			for (int i = 0; i < source_img.rows; i++) {
				for (int j = 0; j < source_img.cols; j++) {
					preprocs_img.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(source_img.at<Vec3b>(i, j)[c] - means[c]);   // 注意使用 saturate_cast<uchar>的作用
				}
			}
		}
		resize(source_img, preprocs_img, Size(size[0], size[1]), INTER_CUBIC);
//		imshow("image", preprocs_img);
//		waitKey(0);
		out_ch = split_ch(img_pth, *pattern);
		int get_pos = out_ch.size() - 1;
		save_name = save_name.assign(out_ch[0]).append("_preprcs.").append(out_ch[1]);
		cout << "save_out image as : " << save_name << endl;
		
		imwrite(save_name, preprocs_img);

	}

	return preprocs_img;
}

vector<string> split_ch(const string& ch, const char pattern) {
	vector<string> res;
	stringstream input(ch);
	string temp;

	while (getline(input, temp, pattern)) {
		res.push_back(temp);
	}

	return res;
}
