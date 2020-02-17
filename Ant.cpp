#include "Ant.h"

Ant::Ant(std::tuple<int, int> position, float pheromone, int visitedSize)
{
	this->position = position;
	this->pheromone = pheromone;
	this->visitedSize = visitedSize;
	visited = std::deque<std::tuple<int, int>>();
	AddPositionToQueue(position);
}

void Ant::AddPositionToQueue(std::tuple<int, int>& position)
{
	if (int(visited.size()) >= visitedSize)
		visited.pop_front();
	visited.push_back(position);
}

void Ant::Move(std::tuple<int, int>& position)
{
	this->position = position;
	AddPositionToQueue(position);
}
