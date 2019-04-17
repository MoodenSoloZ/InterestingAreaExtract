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
class lines_extract//find four sides of the interesting area  
{
private:
	int GAP;
public:
	lines_extract(int gap);
	int get_width_down(Mat img,int gap);//get the width of every point alonging the gap
	int get_width_up(Mat img,int gap);
	int get_length_right(Mat img,int gap);
	int get_length_left(Mat img,int gap);

	Vec4f get_line_left(Mat img);//get the parameter of each line
	Vec4f get_line_right(Mat img);
	Vec4f get_line_up(Mat img);
	Vec4f get_line_down(Mat img);

};