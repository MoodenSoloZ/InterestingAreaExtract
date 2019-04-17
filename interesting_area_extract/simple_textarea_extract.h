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

class simple_textarea_extract
{
public:
	simple_textarea_extract(Mat img);
	Mat extract_words(Mat input_photo);
	vector<RotatedRect> findTextRegion(Mat img);
	vector<RotatedRect> rect_process(vector<RotatedRect> rects);
	void cut_text_area(Mat img, int i);
private:
	Mat simple_text_img;

};
