#include"cross_line.h"

cross_line::cross_line(int gap)
{
	this->GAP_ = gap;
}


Mat cross_line::paint_cross_line(Mat img_Threshold)//绘制crossline
{

	double x = 0.5*img_Threshold.cols;
	double y = 0.5*img_Threshold.rows;
	Point2f p[8];//8个点，四个为图像的四个角的坐标，另外四个是图像中心的相距GAP_的点
	p[0].x = x - GAP_;
	p[0].y = y - GAP_;
	p[1].x = 0;
	p[1].y = 0;

	p[2].x = x - GAP_;
	p[2].y = y + GAP_;
	p[3].x = 0;
	p[3].y = img_Threshold.rows;

	p[4].x = x + GAP_;
	p[4].y = y - GAP_;
	p[5].x = img_Threshold.cols;
	p[5].y = 0;

	p[6].x = x + GAP_;
	p[6].y = y + GAP_;
	p[7].x = img_Threshold.cols;
	p[7].y = img_Threshold.rows;


	line(img_Threshold, p[0], p[1], Scalar(0, 255, 0), 8);//在经过二值化的图像上绘制出crossline
	line(img_Threshold, p[2], p[3], Scalar(0, 255, 0), 8);
	line(img_Threshold, p[4], p[5], Scalar(0, 255, 0), 8);
	line(img_Threshold, p[6], p[7], Scalar(0, 255, 0), 8);
	return img_Threshold;
}