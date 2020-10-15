#include <iostream>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include"opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

Mat myLogTrans(Mat img, float c) {
	Mat res(img.rows, img.cols, img.type());

	//建立log表便于查找
	float tabel[256];
	for (int i = 0; i < 256; i++) {
		tabel[i] = c * log(i + 1);
	}

	if (img.channels() == 1) {
		float minval = 500;
		float maxval = -1;
		vector<vector<float> > val(img.rows,vector<float>(img.cols));
		for (int x = 0; x < img.rows; x++) {
			for (int y = 0; y < img.cols; y++) {
				val[x][y] = tabel[img.at<uchar>(x, y)];
				minval = min(val[x][y], minval);
				maxval = max(val[x][y], maxval);
			}
		}
		//归一化到0-255
		for (int x = 0; x < res.rows; x++) {
			for (int y = 0; y < res.cols; y++) {
				res.at<uchar>(x, y) = 255 * (val[x][y] - minval) / (maxval - minval);
			}
		}
	}
	else {
		for (int c = 0; c < img.channels(); c++) {
			float minval = 500;
			float maxval = -1;
			vector<vector<float> > val(img.rows, vector<float>(img.cols));
			for (int x = 0; x < img.rows; x++) {
				for (int y = 0; y < img.cols; y++) {
					val[x][y] = tabel[img.at<Vec3b>(x, y)[c]];
					minval = min(val[x][y], minval);
					maxval = max(val[x][y], maxval);
				}
			}
			//归一化到0-255
			for (int x = 0; x < res.rows; x++) {
				for (int y = 0; y < res.cols; y++) {
					res.at<Vec3b>(x, y)[c] = 255 * (val[x][y] - minval) / (maxval - minval);
				}
			}
		}
	}
	return res;
}

int main() {
	Mat img = imread("C://Users//Chrysanthemum//Desktop//1.png");
	float c = 2;

	Mat res = myLogTrans(img, c);

	imshow("origin pic", img);
	imshow("result pic", res);
	waitKey();
}