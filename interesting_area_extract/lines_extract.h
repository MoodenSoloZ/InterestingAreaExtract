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
class lines_extract//找到感兴趣区域四边形的四条边
{
private:
	int GAP;
public:
	lines_extract(int gap);
	int get_width_down(Mat img,int gap);//对于向外延伸的每个点都计算其到边界的距离
	int get_width_up(Mat img,int gap);
	int get_length_right(Mat img,int gap);
	int get_length_left(Mat img,int gap);

	Vec4f get_line_left(Mat img);//返回四边形左侧的边所在的直线的参数
	Vec4f get_line_right(Mat img);
	Vec4f get_line_up(Mat img);
	Vec4f get_line_down(Mat img);

};