#pragma once
#include "lib/opencv.hpp"
#include "Parameters.h"
#include "Ant.h"

class AntColonySystem
{
public:
	AntColonySystem(Parameters parameters);
	void Run();
private:
	int maxWidth;
	int maxHeight;
	int heuristicMax;
	Parameters m_parameters;
	vector<tuple<int, int>> alreadyVisitedPositions;
	vector<unique_ptr<Ant>> ants;

	tuple<tuple<int, int>, float, float> GetMooreNeighborhood(Ant& ant, int index);
	tuple<int, int> SelectNextPixel(Ant& ant);
	void Move(Ant& ant);
	void UpdateGlobalPheromone();
	void UpdateLocalPheromone(Ant& ant);
	float GetHeuristic(tuple<int, int> position);
	void DisplayResults();
	void ResetAntsPheromone();
	float GetPheromone(tuple<int, int> position);
	void UpdatePheromone(tuple<int, int> position, float value);
	void SetPheromone(tuple<int, int> position, float value);
	static bool SortPositionValueTuple(const tuple<tuple<int, int>, int> &first, const tuple<tuple<int, int>, int> &second);
};

