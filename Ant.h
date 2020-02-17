#pragma once
#include <tuple>
#include <vector>
#include <deque>

class Ant
{
public:
	std::tuple<int, int> position;
	std::deque<std::tuple<int, int>> visited;
	//std::vector<std::tuple<int, int>> visited;
	float pheromone;

	Ant(std::tuple<int, int> position, float pheromone, int visitedSize);

	void Move(std::tuple<int, int>& position);

private:
	int visitedSize;
	
	void AddPositionToQueue(std::tuple<int, int>& position);
};

