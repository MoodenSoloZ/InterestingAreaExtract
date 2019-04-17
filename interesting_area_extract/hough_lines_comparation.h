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
//this class is just to make a comparation between the hough lines extract and the function above 
//in this case the input is still the threshold image processed by Hull and through the hough the output are 
//four longest lines detected by hough

class hough_lines_comparation
{
public:
	double line_length(Vec4f line);
	void get_hough_lines(Mat canny,Mat resize,string loc);
private:

};
