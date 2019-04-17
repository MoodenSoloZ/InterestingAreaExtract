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
class cross_extract
{
public:
	//找出四条直线的在图像内的四个交点
	Point get_cross_point(int flag, Vec4f line_para1, Vec4f line_para2, double x_max, double y_max);
	//找出四个交点所围成四边形的最大边长，用于后面做透射变换
	Mat MaxDistance(Point2f point1, Point2f point2, Point2f point3, Point2f point4);
private:

};

