#pragma once
#include <string>
#include<vector>

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
	int threshold{};
	
	// images
	std::vector<std::vector<int>> intensity;
	std::vector<std::vector<int>> heuristic;
	std::vector<std::vector<float>> pheromone;
	std::vector<std::vector<float>> edges;
};
