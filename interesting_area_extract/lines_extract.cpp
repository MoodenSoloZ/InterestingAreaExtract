#include"lines_extract.h"


lines_extract::lines_extract(int gap)
{
	this->GAP = gap;
}

int lines_extract::get_width_down(Mat img,int gap)
{

	int row, col;
	int width_down = 0;

	for (row = 0.5*img.rows - gap; row < img.rows; row++)
	{

		width_down++;
		//cout << int(img.at<uchar>(row, 0.5*img.cols));
		if (int(img.at<uchar>(row, 0.5*img.cols + gap))>50) break;//直到找到四边形的边界为止

	}

	return width_down;
}

int lines_extract::get_width_up(Mat img,int gap)
{
	int row, col;
	int width_up = 0;

	for (row = 0.5*img.rows - gap; row > 0; row--)
	{
		width_up++;
		if (int(img.at<uchar>(row, 0.5*img.cols + gap))>50) break;
	}
	return width_up;
}

int lines_extract::get_length_right(Mat img,int gap)
{
	int row, col;
	int length_right = 0;

	for (col = 0.5*img.cols + gap; col < img.cols; col++)
	{

		length_right++;
		//cout << int(img.at<uchar>(0.5*img.rows, col));
		if (int(img.at<uchar>(0.5*img.rows - gap, col))>50) break;

	}

	return length_right;
}

int lines_extract::get_length_left(Mat img,int gap)
{
	int row, col;
	int length_left = 0;
	for (col = 0.5*img.cols + gap; col > 0; col--)
	{

		length_left++;
		//cout << int(img.at<uchar>(0.5*img.rows, col));
		if (int(img.at<uchar>(0.5*img.rows - gap, col))>50) break;

	}
	return length_left;
}

Vec4f lines_extract::get_line_left(Mat img)
{
	Vec4f line_para;
	vector<Point> points;
	for (int gap = 0; gap < GAP; gap++)//向外侧延伸GAP个点
	{
		int length_left = get_length_left(img,gap);
		int pointx = 0.5*img.cols + gap - length_left;
		int pointy = 0.5*img.rows - gap;
		//cout << pointx << endl;
		//cout << pointy << endl;
		points.push_back(Point(pointx, pointy));


	}

	fitLine(points, line_para, DIST_L2, 0, 1e-2, 1e-2);

	return line_para;
}

Vec4f lines_extract::get_line_right(Mat img)
{
	Vec4f line_para;
	vector<Point> points;
	for (int gap = 0; gap < GAP; gap++)
	{
		int length_right = get_length_right(img,gap);
		int pointx = 0.5*img.cols + gap + length_right;
		int pointy = 0.5*img.rows - gap;
		//cout << pointx << endl;
		//cout << pointy << endl;
		points.push_back(Point(pointx, pointy));


	}
	fitLine(points, line_para, DIST_L2, 0, 1e-2, 1e-2);

	return line_para;
}

Vec4f lines_extract::get_line_up(Mat img)
{
	Vec4f line_para;
	vector<Point> points;
	for (int gap = 0; gap < GAP; gap++)
	{
		int width_up = get_width_up(img,gap);
		int pointx = 0.5*img.cols + gap;
		int pointy = 0.5*img.rows - gap - width_up;
		//cout << pointx << endl;
		//cout << pointy << endl;
		points.push_back(Point(pointx, pointy));


	}

	fitLine(points, line_para, DIST_L2, 0, 1e-2, 1e-2);

	return line_para;
}

Vec4f lines_extract::get_line_down(Mat img)
{
	Vec4f line_para;
	vector<Point> points;
	for (int gap = 0; gap < GAP; gap++)
	{
		int width_down = get_width_down(img,gap);
		int pointx = 0.5*img.cols + gap;
		int pointy = 0.5*img.rows - gap + width_down;
		//cout << pointx << endl;
		//cout << pointy << endl;
		points.push_back(Point(pointx, pointy));


	}
	fitLine(points, line_para, DIST_L2, 0, 1e-2, 1e-2);

	return line_para;
}

