#include"simple_textarea_extract.h"

simple_textarea_extract::simple_textarea_extract(Mat img)
{
	img.copyTo(this->simple_text_img);
}



Mat simple_textarea_extract::extract_words(Mat input_photo)
{
	//1.Sobel算子，x方向求梯度
	Mat sobel;
	Sobel(input_photo, sobel, CV_8U, 1, 0, 3);
	//Mat canny;
	//Canny(input_photo, canny, 50, 200);
	//2.二值化
	Mat binary;
	threshold(sobel, binary, 0, 255, THRESH_OTSU + THRESH_BINARY);

	//3.膨胀和腐蚀操作核设定
	Mat element1 = getStructuringElement(MORPH_RECT, Size(30, 9));
	//控制高度设置可以控制上下行的膨胀程度，例如3比4的区分能力更强,但也会造成漏检
	Mat element2 = getStructuringElement(MORPH_RECT, Size(30, 30));
	Mat element3 = getStructuringElement(MORPH_RECT, Size(10, 3));

	//4.膨胀一次，让轮廓突出
	Mat dilate1;
	dilate(binary, dilate1, element2);

	//5.腐蚀一次，去掉细节，表格线等。这里去掉的是竖直的线
	//Mat erode1;
	//erode(dilate1, erode1, element1);
	return dilate1;

}

vector<RotatedRect> simple_textarea_extract::findTextRegion(Mat img)
{
	vector<RotatedRect> rects;
	//1.查找轮廓
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//2.筛选那些面积小的
	for (int i = 0; i < contours.size(); i++)
	{
		//计算当前轮廓的面积
		double area = contourArea(contours[i]);

		//面积小于1000的全部筛选掉
		if (area < 1000 || area>50000)
			continue;

		//轮廓近似，作用较小，approxPolyDP函数有待研究
		//double epsilon = 0.001*arcLength(contours[i], true);
		//Mat approx;
		//approxPolyDP(contours[i], approx, epsilon, true);

		//找到最小矩形，该矩形可能有方向
		RotatedRect rect = minAreaRect(contours[i]);

		//计算高和宽
		int m_width = rect.boundingRect().width;
		int m_height = rect.boundingRect().height;

		//筛选那些太细的矩形，留下扁的
		if (m_height > m_width * 1.2 || m_width<m_height * 2)
			continue;

		//符合条件的rect添加到rects集合中
		rects.push_back(rect);

	}



	return rects;
}


vector<RotatedRect> simple_textarea_extract::rect_process(vector<RotatedRect> rects)
{
	Point2f P;
	int i = 0, j = 0, k = 0, max = 0;
	for each (RotatedRect rect in rects)
	{
		max++;
	}
	for (i = 0; i<max; i++)
	{
		P = rects[i].center;
		for (j = i; j < max; j++)
		{
			if (abs(rects[j].center.y - P.y) > 20)
			{
				break;
			}
		}
		for (k = 0; k <= (j - i) / 2; k++)
		{
			RotatedRect rec;
			rec = rects[i + k];
			rects[i + k] = rects[j - 1];
			rects[j - 1] = rec;
		}
	}
	return rects;
}

void simple_textarea_extract::cut_text_area(Mat img, int i)
{
	vector<String> files;
	glob("D:/save2/*.jpg", files, false);
	int dx = files.size();

	Mat outputs;
	outputs = extract_words(img);
	vector<RotatedRect> rects = rect_process(findTextRegion(outputs));
	for each (RotatedRect rect in rects)
	{
		Point2f P[4];
		rect.points(P);
		char ad[128] = { 0 };
		int x = 10000, y = 10000;
		sprintf_s(ad, "D:\\save2\\test%d.jpg", ++dx);
		for (int i = 0; i < 4; i++)
		{
			if (P[i].x < x)
			{
				x = P[i].x;
			}
			if (P[i].y < y)
			{
				y = P[i].y;
			}
		}


		//cout << dx << "x:" << x << "y:" << y << endl;
		Rect rec(x, y, rect.boundingRect().width, rect.boundingRect().height);
		Mat ROI;
		img(rec).copyTo(ROI);
		imwrite(ad, ROI);

	}
}