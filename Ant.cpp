#include "Ant.h"

Ant::Ant(std::tuple<int, int> position, float pheromone, int memory, int constructionSteps)
{
	this->position = position;
	this->pheromone = pheromone;
	this->memory = memory;
	this->constructionSteps = constructionSteps;
	visited = std::deque<std::tuple<int, int>>();
	AddPositionToQueue(position);
}

void Ant::AddPositionToQueue(std::tuple<int, int>& position)
{
	visited.push_back(position);

	if (int(visited.size()) > (memory > constructionSteps ? memory : constructionSteps))
		visited.pop_front();
}

void Ant::Move(std::tuple<int, int>& position)
{
	this->position = position;
	AddPositionToQueue(position);
}
