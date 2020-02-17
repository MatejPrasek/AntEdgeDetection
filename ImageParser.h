#pragma once
#include <string>
#include <D:/vcpkg-master/packages/opencv4_x86-windows/include/opencv2/core/core.hpp>
#include <D:/vcpkg-master/packages/opencv4_x86-windows/include/opencv2/opencv.hpp>
#include <D:/vcpkg-master/packages/opencv4_x86-windows/include/opencv2/imgproc/imgproc.hpp>
#include <D:/vcpkg-master/packages/opencv4_x86-windows/include/opencv2/highgui/highgui.hpp>
#include <fstream>
#include <iostream>
#include "Parameters.h"

using namespace cv;
using namespace std;

class ImageParser
{
public:
	ImageParser(Parameters* parameters);
	void ParseIntensity();

private:
	string path;
	Parameters* parameters;
	int CalculateHeuristic(Mat intensity, int row, int col);
};

