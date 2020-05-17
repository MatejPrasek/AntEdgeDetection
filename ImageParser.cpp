#include "ImageParser.h"

using namespace cv;
using namespace std;

int CalculateHeuristic(Mat intensity, int row, int col)
{
	int weight = 0;
	int maxRow = intensity.rows;
	int maxCol = intensity.cols;

	if (row - 1 >= 0 && col - 1 >= 0 &&
		row + 1 < maxRow && col + 1 < maxCol)
		weight += abs(int(intensity.at<uchar>(row - 1, col - 1)) - int(intensity.at<uchar>(row + 1, col + 1)));

	if (row + 1 < maxRow && col - 1 >= 0 &&
		row - 1 >= 0 && col + 1 < maxCol)
		weight += abs(int(intensity.at<uchar>(row + 1, col - 1)) - int(intensity.at<uchar>(row - 1, col + 1)));

	if (col - 1 >= 0 &&
		col + 1 < maxCol)
		weight += abs(int(intensity.at<uchar>(row, col - 1)) - int(intensity.at<uchar>(row, col + 1)));

	if (row - 1 >= 0 &&
		row + 1 < maxRow)
		weight += abs(int(intensity.at<uchar>(row - 1, col)) - int(intensity.at<uchar>(row + 1, col)));

	return weight;
}

void ParseIntensity(Parameters &parameters)
{
	Mat RGBImage;
	RGBImage = imread(parameters.imagePath);

	Mat grayScaleImage(RGBImage.size(), CV_8UC1);

	cvtColor(RGBImage, grayScaleImage, COLOR_RGB2GRAY);

	ofstream intensity;
	intensity.open("intensity.txt");
	ofstream heuristic;
	heuristic.open("heuristic.txt");

	parameters.intensity = vector<vector<int>>(grayScaleImage.cols, vector<int>(grayScaleImage.rows));
	parameters.heuristic = vector<vector<int>>(grayScaleImage.cols, vector<int>(grayScaleImage.rows));

	for (int i = 0; i < grayScaleImage.cols; i++)
	{
		for (int j = 0; j < grayScaleImage.rows; j++)
		{
			parameters.intensity[i][j] = int(grayScaleImage.at<uchar>(j, i));
			parameters.heuristic[i][j] = CalculateHeuristic(grayScaleImage, j, i);

			intensity << parameters.intensity[i][j] << " ";
			heuristic << parameters.heuristic[i][j] << " ";
		}
		intensity << endl;
		heuristic << endl;
	}
	intensity.close();
	heuristic.close();
}

