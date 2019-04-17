#include"simple_textarea_extract.h"

simple_textarea_extract::simple_textarea_extract(Mat img)
{
	img.copyTo(this->simple_text_img);
}



Mat simple_textarea_extract::extract_words(Mat input_photo)
{
	//1.Sobel���ӣ�x�������ݶ�
	Mat sobel;
	Sobel(input_photo, sobel, CV_8U, 1, 0, 3);
	//Mat canny;
	//Canny(input_photo, canny, 50, 200);
	//2.��ֵ��
	Mat binary;
	threshold(sobel, binary, 0, 255, THRESH_OTSU + THRESH_BINARY);

	//3.���ͺ͸�ʴ�������趨
	Mat element1 = getStructuringElement(MORPH_RECT, Size(30, 9));
	//���Ƹ߶����ÿ��Կ��������е����ͳ̶ȣ�����3��4������������ǿ,��Ҳ�����©��
	Mat element2 = getStructuringElement(MORPH_RECT, Size(30, 30));
	Mat element3 = getStructuringElement(MORPH_RECT, Size(10, 3));

	//4.����һ�Σ�������ͻ��
	Mat dilate1;
	dilate(binary, dilate1, element2);

	//5.��ʴһ�Σ�ȥ��ϸ�ڣ�����ߵȡ�����ȥ��������ֱ����
	//Mat erode1;
	//erode(dilate1, erode1, element1);
	return dilate1;

}

vector<RotatedRect> simple_textarea_extract::findTextRegion(Mat img)
{
	vector<RotatedRect> rects;
	//1.��������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//2.ɸѡ��Щ���С��
	for (int i = 0; i < contours.size(); i++)
	{
		//���㵱ǰ���������
		double area = contourArea(contours[i]);

		//���С��1000��ȫ��ɸѡ��
		if (area < 1000 || area>50000)
			continue;

		//�������ƣ����ý�С��approxPolyDP�����д��о�
		//double epsilon = 0.001*arcLength(contours[i], true);
		//Mat approx;
		//approxPolyDP(contours[i], approx, epsilon, true);

		//�ҵ���С���Σ��þ��ο����з���
		RotatedRect rect = minAreaRect(contours[i]);

		//����ߺͿ�
		int m_width = rect.boundingRect().width;
		int m_height = rect.boundingRect().height;

		//ɸѡ��Щ̫ϸ�ľ��Σ����±��
		if (m_height > m_width * 1.2 || m_width<m_height * 2)
			continue;

		//����������rect��ӵ�rects������
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