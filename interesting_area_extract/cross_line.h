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

class cross_line
{
public:
	cross_line(int gap);
	Mat paint_cross_line(Mat img_Threshold);//����crossline������Ϊ��ֵ��ͼ��

private:
	int  GAP_;

};
