#include <tuple>
#include <deque>

class Ant
{
public:
	std::tuple<int, int> position;
	std::deque<std::tuple<int, int>> visited;
	float pheromone;

	Ant(std::tuple<int, int> position, float pheromone, int visitedSize, int constructionSteps);

	void Move(std::tuple<int, int>& position);

private:
	int memory;
	int constructionSteps;
	
	void AddPositionToQueue(std::tuple<int, int>& position);
};

