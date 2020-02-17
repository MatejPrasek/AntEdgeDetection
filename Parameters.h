#pragma once
#include <string>

using namespace std;

class Parameters
{
public:
	// command line arguments
	string imagePath;
	float alpha{};
	float beta{};
	int ants{};
	float rho{};
	float phi{};
	int constructionSteps{};
	int iterations{};
	float q0{};
	float tauini{};
	//int horizontalPartitions{};
	//int verticalPartitions{};
	int memory{};
	bool debug{};

	// images
	vector<vector<int>> intensity;
	vector<vector<int>> heuristic;
	vector<vector<float>> pheromone;
	vector<vector<float>> edges;

};
