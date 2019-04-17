#include"cross_extract.h"

Point cross_extract::get_cross_point(int flag, Vec4f line_para1, Vec4f line_para2, double x_max, double y_max)
{
	Point cross_point, point1, point2;

	point1.x = line_para1[2];
	point1.y = line_para1[3];
	double k1 = line_para1[1] / line_para1[0];
	double b1 = point1.y - k1*point1.x;
	double x, dis1, dis2 = 0;


	point2.x = line_para2[2];
	point2.y = line_para2[3];
	double k2 = line_para2[1] / line_para2[0];
	double b2 = point2.y - k2*point2.x;


	for (x = 0; x < x_max; x++)
	
	{
		dis1 = (k1*x + b1) - (k2*x + b2);
		if ((dis1 < 0 && dis2 > 0) || (dis1 > 0 && dis2 < 0))
			break;
		dis2 = dis1;
	}
	//using flag to make the cross points be more precise, 
	//considering the situation that the cross points are outside of the input image

	if (flag == 1)
	{
		if (x == x_max)
		{
			-b1 / k1 > 0 ? (cross_point.x = -b1 / k1) : (cross_point.x = 0);
			cross_point.y = 0;
		}
		else
		{
			cross_point.x = x;
			cross_point.y = k1*x + b1;
		}
	}
	else if (flag = 2)
	{
		if (x == x_max)
		{
			(y_max - b1) / k1 > 0 ? (cross_point.x = (y_max - b1) / k1) : (cross_point.x = 0);
			cross_point.y = y_max;
		}
		else
		{
			cross_point.x = x;
			cross_point.y = k1*x + b1;
		}
	}
	else if (flag = 3)
	{
		if (x == x_max)
		{
			cross_point.x = x;
			(k1*x + b1) > 0 ? (cross_point.y = k1*x + b1) : (cross_point.y = 0);
		}
		else
		{
			cross_point.x = x;
			cross_point.y = k1*x + b1;
		}
	}
	else if (flag = 4)
	{
		if (x == x_max)
		{
			cross_point.x = x;
			(k1*x + b1) < y_max ? (cross_point.y = k1*x + b1) : (cross_point.y = y_max);
		}
		else
		{
			cross_point.x = x;
			cross_point.y = k1*x + b1;
		}
	}

	cout << "ºá×ø±ê" << cross_point.x << endl;
	cout << "×Ý×ø±ê" << cross_point.y << endl;

	return cross_point;

}


Mat cross_extract::MaxDistance(Point2f point1, Point2f point2, Point2f point3, Point2f point4)
{
	double max_dis1, max_dis2 = 0;
	double dis1 = sqrt((point1.x - point2.x)*(point1.x - point2.x) + (point1.y - point2.y)*(point1.y - point2.y));
	double dis2 = sqrt((point3.x - point4.x)*(point3.x - point4.x) + (point3.y - point4.y)*(point3.y - point4.y));

	if (dis1 > dis2) max_dis1 = dis1;
	else max_dis1 = dis2;

	double dis3 = sqrt((point1.x - point3.x)*(point1.x - point3.x) + (point1.y - point3.y)*(point1.y - point3.y));
	double dis4 = sqrt((point2.x - point4.x)*(point2.x - point4.x) + (point2.y - point4.y)*(point2.y - point4.y));

	if (dis3 > dis4) max_dis2 = dis3;
	else max_dis2 = dis4;

	Mat m = Mat(max_dis2, max_dis1, CV_32FC(1));

	return m;
}