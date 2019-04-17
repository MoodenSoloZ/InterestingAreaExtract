#include"cross_line.h"

cross_line::cross_line(int gap)
{
	this->GAP_ = gap;
}


Mat cross_line::paint_cross_line(Mat img_Threshold)//����crossline
{

	double x = 0.5*img_Threshold.cols;
	double y = 0.5*img_Threshold.rows;
	Point2f p[8];//8���㣬�ĸ�Ϊͼ����ĸ��ǵ����꣬�����ĸ���ͼ�����ĵ����GAP_�ĵ�
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


	line(img_Threshold, p[0], p[1], Scalar(0, 255, 0), 8);//�ھ�����ֵ����ͼ���ϻ��Ƴ�crossline
	line(img_Threshold, p[2], p[3], Scalar(0, 255, 0), 8);
	line(img_Threshold, p[4], p[5], Scalar(0, 255, 0), 8);
	line(img_Threshold, p[6], p[7], Scalar(0, 255, 0), 8);
	return img_Threshold;
}