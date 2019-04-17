#include"cross_extract.h"
#include"cross_line.h"
#include"hough_lines_comparation.h"
#include"lines_extract.h"
#include"simple_textarea_extract.h"
#include"init.h"

int main(int argc, char**argv)
{

	vector<String> files;
	glob(Resouce_Img_Read_FileLocation"/*.JPG", files, false);//将Resouce_Img_Read_FileLocation中的图片文件地址都加载到files中
	int files_size = files.size();
	//cout << files_size << endl;
	for (int dx = 1; dx <= files_size; dx++)//对每张图片进行处理
	{
		char input_img_name[128] = { 0 };

		sprintf_s(input_img_name, Resouce_Img_Read_FileLocation"/%d.JPG", dx);
		cout << input_img_name << endl;

		Mat img_init;//初始图像集中的图像，彩色三通道
		Mat img_gray;//经过缩放后再灰度化的图像，单通道
		Mat img_resize;//缩放后的图像
		Mat img_contrast;// 可以改变图像的对比度
		Mat img_medianBlur_1st;//两次中值滤波的第一次
		Mat img_medianBlur_2nd;
		Mat img_threshold;//二值化图像
		Mat img_cross;//经过绘制crossline的二值化图像
		img_init = imread(input_img_name, 1);
		if (img_init.cols*img_init.rows <= 1000 * 1500)
			resize(img_init, img_resize, Size(img_init.cols, img_init.rows), 1, 1);
		else if ((img_init.cols*img_init.rows > 1000 * 1500) && (img_init.cols*img_init.rows <= 2500 * 3750))
			resize(img_init, img_resize, Size(img_init.cols / 2, img_init.rows / 2), 0.5, 0.5);
		else if ((img_init.cols*img_init.rows > 2500 * 3750))
			resize(img_init, img_resize, Size(img_init.cols / 4, img_init.rows / 4), 0.25, 0.25);

		cvtColor(img_resize, img_gray, COLOR_BGR2GRAY);

		img_contrast = 1 * img_gray;

		medianBlur(img_contrast, img_medianBlur_1st, 25);
		medianBlur(img_medianBlur_1st, img_medianBlur_2nd, 25);
		//imshow("medianBlur", img_medianBlur_2nd);
		threshold(img_medianBlur_2nd, img_threshold, 120, 255, THRESH_BINARY);
		//imshow("threshold", img_threshold);

		cross_line crossline(GAP);
		img_cross = crossline.paint_cross_line(img_threshold);
		

		vector<vector<Point> > contours_init;
		vector<vector<Point> > contours_bigger;
		vector<Vec4i> hierarchy;
		findContours(img_cross, contours_init, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
		for (int i = 0; i < contours_init.size(); i++)
		{
			double area = contourArea(contours_init[i]);
			//cout << area << endl;
			if (area>img_cross.rows*img_cross.cols / 5)// 将所有比整幅图面积的五分之一大的轮廓都筛选出
				contours_bigger.push_back(contours_init[i]);
		}

		vector<vector<Point> >hull(contours_bigger.size());
		for (int i = 0; i < contours_bigger.size(); i++)     //凸包计算
		{
			convexHull(contours_bigger[i], hull[i]);
		}
		Mat simple_lines = Mat::zeros(img_cross.size(), CV_8UC3);
		for (int i = 0; i < hull.size(); i++)
		{
			//cout << hull[i].size() << endl;
			drawContours(simple_lines, hull, i, (0, 0, 255), 4, 8, vector<Vec4i>(), 0);

		}
		cvtColor(simple_lines, simple_lines, COLOR_BGR2GRAY);
		threshold(simple_lines, simple_lines, 10, 255, THRESH_BINARY);
		//if(dx==1)
		//	imshow("hull", simple_lines);
		lines_extract linesofsides(GAP);

		Vec4f  line_para_left = linesofsides.get_line_left(simple_lines);
		Vec4f  line_para_right = linesofsides.get_line_right(simple_lines);
		Vec4f  line_para_up = linesofsides.get_line_up(simple_lines);
		Vec4f  line_para_down = linesofsides.get_line_down(simple_lines);
		cross_extract vertexes;

		Point cross_point_lu = vertexes.get_cross_point(1, line_para_up, line_para_left, simple_lines.cols, simple_lines.rows);
		Point cross_point_ld = vertexes.get_cross_point(2, line_para_down, line_para_left, simple_lines.cols, simple_lines.rows);
		Point cross_point_ru = vertexes.get_cross_point(3, line_para_up, line_para_right, simple_lines.cols, simple_lines.rows);
		Point cross_point_rd = vertexes.get_cross_point(4, line_para_down, line_para_right, simple_lines.cols, simple_lines.rows);


		/*
		if (dx == 4) //观察单张图片的效果
		{	
			Mat img_resize_empty;
			img_resize.copyTo(img_resize_empty);
			hough_lines_comparation paint_hough_lines;
			paint_hough_lines.get_hough_lines(simple_lines, img_resize, Hough_Compare_Img);
		
	  	    circle(img_resize_empty, cross_point_lu, 5, Scalar(255, 255, 255), 2, 8, 0);
		    circle(img_resize_empty, cross_point_ld, 5, Scalar(255, 255, 255), 2, 8, 0);
	     	circle(img_resize_empty, cross_point_ru, 5, Scalar(255, 255, 255), 2, 8, 0);
	     	circle(img_resize_empty, cross_point_rd, 5, Scalar(255, 255, 255), 2, 8, 0);
			line(img_resize_empty, cross_point_lu, cross_point_ld, Scalar(186, 88, 255), 5, CV_AA);
			line(img_resize_empty, cross_point_ru, cross_point_rd, Scalar(186, 88, 255), 5, CV_AA);
			line(img_resize_empty, cross_point_lu, cross_point_ru, Scalar(186, 88, 255), 5, CV_AA);
			line(img_resize_empty, cross_point_ld, cross_point_rd, Scalar(186, 88, 255), 5, CV_AA);

			imwrite("d:\\result.jpg", img_resize_empty);

			

		}*/


		Point2f src[4];//感兴趣区域的四个顶点
		Point2f dst[4];//经过透视变换后图像的四个顶点，与src相互对应
		src[0] = cross_point_lu;
		src[1] = cross_point_ld;
		src[2] = cross_point_ru;
		src[3] = cross_point_rd;

		Mat new_img = vertexes.MaxDistance(cross_point_lu, cross_point_ru, cross_point_ld, cross_point_rd);

		dst[0] = Point2f(0, 0);
		dst[1] = Point2f(0, new_img.rows);
		dst[2] = Point2f(new_img.cols, 0);
		dst[3] = Point2f(new_img.cols, new_img.rows);
		Mat p = getPerspectiveTransform(src, dst);
		Mat result1, result2;
		warpPerspective(img_gray, result1, p, new_img.size());//result1 是感兴趣区域的输出

		char output_img_name[128] = { 0 };
		sprintf_s(output_img_name, Processed_Img_Save_FileLocation"/result%d.jpg", dx);
		imwrite(output_img_name, result1);
	}
	waitKey(0);

	return 0;
}