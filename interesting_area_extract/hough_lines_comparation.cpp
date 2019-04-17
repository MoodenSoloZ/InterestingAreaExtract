#include"hough_lines_comparation.h"

double hough_lines_comparation::line_length(Vec4f line)
{
	return sqrt((line[0] - line[2])*(line[0] - line[2]) + (line[1] - line[3])*(line[1] - line[3]));
}

void hough_lines_comparation::get_hough_lines(Mat canny, Mat true_img,string loc)
{
	vector<Vec4f> lines;//a set to store the lines dete
	vector < Vec4f> four_output_lines;
	HoughLinesP(canny, lines, 1, CV_PI / 180, 150, 50, 50);
	//HoughLines(canny, lines, 1, CV_PI / 180, 150, 0, 0);
	double length = 0;
	cout << lines.size() << endl;
	for (int num1 = 1; num1 <= 4; num1++)//sort the lines by their length 
	{

		for (int num2 = 0; num2 < lines.size() - num1; num2++)
		{
			//cout << lines[num2][0] <<"&"<< lines[num2][2]<<endl<< lines[num2][1]<<"&"<< lines[num2][3]<< endl;
			if (line_length(lines[num2]) >= line_length(lines[num2 + 1]))
			{
				Vec4f line = lines[num2];
				lines[num2] = lines[num2 + 1];
				lines[num2 + 1] = line;

			}

		}
	}
	//push th four longest lines in set of lines to four_output_lines
	four_output_lines.push_back(lines[lines.size() - 1]);
	four_output_lines.push_back(lines[lines.size() - 2]);
	four_output_lines.push_back(lines[lines.size() - 3]);
	four_output_lines.push_back(lines[lines.size() - 4]);

	for (size_t i = 0; i < 4; i++)//draw the four longest lines detected by hough in the img
	{
		Vec4i l = lines[i];
		cout << line_length(lines[i]) << endl;
		circle(true_img, Point(l[0], l[1]), 5, Scalar(255, 255, 255), 2, 8, 0);
		circle(true_img, Point(l[2], l[3]), 5, Scalar(255, 255, 255), 2, 8, 0);
		line(true_img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 3, CV_AA);
	}
	imshow("true_img", true_img);
	imwrite(loc, true_img);

}