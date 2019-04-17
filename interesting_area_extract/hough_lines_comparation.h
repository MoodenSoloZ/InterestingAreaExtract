#pragma once
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
using namespace cv;
//这个class只是为了测试一下用hough直线检测来找四条边的效果，
//输入仍然是经过凸包的四边形二值图，输出为经过hough直线检测后得到的四条最长的直线


class hough_lines_comparation
{
public:
	double line_length(Vec4f line);
	void get_hough_lines(Mat canny,Mat resize,string loc);
private:

};
