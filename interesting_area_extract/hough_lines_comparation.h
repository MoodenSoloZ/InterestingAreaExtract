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
//���classֻ��Ϊ�˲���һ����houghֱ�߼�����������ߵ�Ч����
//������Ȼ�Ǿ���͹�����ı��ζ�ֵͼ�����Ϊ����houghֱ�߼���õ����������ֱ��


class hough_lines_comparation
{
public:
	double line_length(Vec4f line);
	void get_hough_lines(Mat canny,Mat resize,string loc);
private:

};
