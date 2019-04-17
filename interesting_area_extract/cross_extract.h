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
	//extract the cross point between two lines in an image
	Point get_cross_point(int flag, Vec4f line_para1, Vec4f line_para2, double x_max, double y_max);
	//given four points to find the longest segment consisted by any two points
	Mat MaxDistance(Point2f point1, Point2f point2, Point2f point3, Point2f point4);
private:

};

