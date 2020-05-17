#pragma once
#include <string>

using namespace std;

struct Parameters
{
	// command line arguments
	string imagePath{};
	float alpha{};
	float beta{};
	int ants{};
	float rho{};
	float phi{};
	int constructionSteps{};
	int iterations{};
	float q0{};
	float tauini{};
	int memory{};
	bool debug{};
	bool random{};

	// images
	vector<vector<int>> intensity;
	vector<vector<int>> heuristic;
	vector<vector<float>> pheromone;
	vector<vector<float>> edges;
};
