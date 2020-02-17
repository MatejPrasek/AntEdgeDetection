#pragma once
//#include "../../../vcpkg-master/packages/cxxopts_x86-windows/include/cxxopts.hpp"
#include <D:/vcpkg-master/packages/cxxopts_x86-windows/include/cxxopts.hpp>
#include <D:/vcpkg-master/packages/opencv4_x86-windows/include/opencv2/core/core.hpp>
#include <D:/vcpkg-master/packages/opencv4_x86-windows/include/opencv2/opencv.hpp>
#include <D:/vcpkg-master/packages/opencv4_x86-windows/include/opencv2/imgproc/imgproc.hpp>
#include <D:/vcpkg-master/packages/opencv4_x86-windows/include/opencv2/highgui/highgui.hpp>
#include "Parameters.h"
#include "Ant.h"

class AntColonySystem
{
public:
	AntColonySystem(Parameters* parameters);
	void Run();
private:
	int maxWidth;
	int maxHeight;
	int heuristicMax;
	Parameters* parameters;
	vector<tuple<int, int>> alreadyVisitedPositions;
	vector<Ant*> ants;

	tuple<tuple<int, int>, int, float> GetNeighbor(Ant* ant, int index);
	tuple<int, int> SelectNextPixel(Ant* ant);
	void Move(Ant* ant);
	void UpdateGlobalPheromone();
	void UpdateLocalPheromone(Ant* ant);
	int Heuristic(tuple<int, int> position);
	void DisplayResults();
	void ResetAntsPheromone();
	float Pheromone(tuple<int, int> position);
};

