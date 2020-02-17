#include "AntColonySystem.h"

AntColonySystem::AntColonySystem(Parameters* parameters)
{
	this->parameters = parameters;

	maxWidth = parameters->heuristic.size();
	maxHeight = parameters->heuristic[0].size();

	parameters->pheromone = vector<vector<float>>(maxWidth, vector<float>(maxHeight));
	parameters->edges = vector<vector<float>>(maxWidth, vector<float>(maxHeight));

	cv::Mat initPosition = cv::Mat(maxHeight, maxWidth, CV_8UC1);
	for (int i = 0; i < maxWidth; i++)
		for (int j = 0; j < maxHeight; j++)
		{
			initPosition.at<uchar>(j, i) = parameters->intensity[i][j];
		}

	heuristicMax = 0;
	for (int i = 0; i < maxWidth; i++)
		for (int j = 0; j < maxHeight; j++) 
		{
			if (heuristicMax < parameters->heuristic[i][j])
				heuristicMax = parameters->heuristic[i][j];
			parameters->pheromone[i][j] = parameters->tauini;
			parameters->edges[i][j] = 0;
		}

	//float horizontalSegment = maxWidth / float(parameters->horizontalPartitions);
	//float verticalSegment = maxHeight / float(parameters->verticalPartitions);

	ants = vector<Ant*>(parameters->ants);
	for (int i = 0; i < parameters->ants; ++i)
	{
		//todo non-random starting position
		tuple<int, int> position = tuple<int, int>(rand() % maxWidth, rand() % maxHeight);
		
		ants[i] = new Ant(position, 0, parameters->memory);

		circle(initPosition, cv::Point(std::get<0>(ants[i]->position), std::get<1>(ants[i]->position)), 2, cv::Scalar(255,255,255));
	}

	namedWindow("Initial positions", cv::WINDOW_AUTOSIZE);
	imshow("Initial positions", initPosition);
	cv::waitKey(0);
}

tuple<tuple<int, int>, int, float> AntColonySystem::GetNeighbor(Ant* ant, int index)
{
	int width = std::get<0>(ant->position) + index % 3 - 1;
	int height = std::get<1>(ant->position) + index / 3 - 1;
	tuple<int, int> position = tuple<int, int>{ width, height };

	if (width < 0 || width >= maxWidth ||
		height < 0 || height >= maxHeight)
		return tuple<tuple<int, int>, int, float>{position, 0, 0.0};

	for (tuple<int, int> visited : ant->visited)
	{
		if(std::get<0>(visited) == width && 
			std::get<1>(visited) == height)
			return tuple<tuple<int, int>, int, float>{position, 0, 0.0};
	}

	return tuple<tuple<int, int>, int, float>{position, Heuristic(position), Pheromone(position)};
}

tuple<int, int> AntColonySystem::SelectNextPixel(Ant* ant)
{
	const int surrounding = 9;
	tuple<tuple<int, int>, int, float> neighbors[surrounding];
	for (int i = 0; i < surrounding; i++)
			neighbors[i] = GetNeighbor(ant, i);

	float q = float(rand()) / RAND_MAX;


	//todo clean this mess
	if (q <= parameters->q0)
	{
		int maxIndex = 0;
		float maxValue = 0;
		for (int i = 0; i < surrounding; ++i)
		{
			float value = pow(std::get<2>(neighbors[i]), parameters->alpha) * pow(std::get<1>(neighbors[i]), parameters->beta);
			if (value > maxValue)
			{
				maxValue = value;
				maxIndex = i;
			}
		}
		return std::get<0>(neighbors[maxIndex]);
	}
	else
	{
		float sum = 0;
		for (int i = 0; i < surrounding; ++i)
		{
			sum += pow(std::get<2>(neighbors[i]), parameters->alpha) * pow(std::get<1>(neighbors[i]), parameters->beta);
		}

		int maxIndex = 0;
		float maxValue = 0;
		for (int i = 0; i < surrounding; ++i)
		{
			float value = pow(std::get<2>(neighbors[i]), parameters->alpha) * pow(std::get<1>(neighbors[i]), parameters->beta) / sum;
			if (value > maxValue)
			{
				maxValue = value;
				maxIndex = i;
			}
		}

		return std::get<0>(neighbors[maxIndex]);
	}
}

void AntColonySystem::Move(Ant* ant)
{
	tuple<int, int> nextPosition = SelectNextPixel(ant);
	
	if (std::find(alreadyVisitedPositions.begin(), alreadyVisitedPositions.end(), nextPosition) == alreadyVisitedPositions.end())
		alreadyVisitedPositions.push_back(nextPosition);

	ant->Move(nextPosition);
}

void AntColonySystem::UpdateGlobalPheromone()
{
	//todo next
}

void AntColonySystem::UpdateLocalPheromone(Ant* ant)
{
	float updated = (1 - parameters->phi) * Pheromone(ant->position) + parameters->phi * parameters->tauini;

	parameters->pheromone[std::get<0>(ant->position)][std::get<1>(ant->position)] += updated;
	ant->pheromone += updated;
}

int AntColonySystem::Heuristic(tuple<int, int> position)
{
	return parameters->heuristic[std::get<0>(position)][std::get<1>(position)];
}

void AntColonySystem::DisplayResults()
{
	float min = 1;
	float max = 0;
	for (vector<float> pheromoneRow : parameters->pheromone)
	{
		for (float pheromone : pheromoneRow)
		{
			if (pheromone < min) min = pheromone;
			if (pheromone > max) max = pheromone;
		}
	}
	cout << "min: " << min << endl;
	cout << "max: " << max << endl;
	float diff = abs(max - min);
	
	for (tuple<int, int> position : alreadyVisitedPositions)
	{
		//todo show edges correctly
		parameters->edges[std::get<0>(position)][std::get<1>(position)] = 255; //int(round(abs((Pheromone(position) - min) / diff) * 255));
	}

	cv::Mat img = cv::Mat(maxHeight, maxWidth, CV_8UC1);
	for (int i = 0; i < maxWidth; i++)
	{
		for (int j = 0; j < maxHeight; j++)
		{
			img.at<uchar>(j, i) = uchar(parameters->edges[i][j]);
		}
	}

	cv::namedWindow("Edges", cv::WINDOW_AUTOSIZE);
	imshow("Edges", img);

	cv::waitKey(500);
}

void AntColonySystem::ResetAntsPheromone()
{
	for (Ant* ant : ants)
	{
		ant->pheromone = 0.0;
	}
}

float AntColonySystem::Pheromone(tuple<int, int> position)
{
	return parameters->pheromone[std::get<0>(position)][std::get<1>(position)];
}

void AntColonySystem::Run()
{
	std::cout << parameters->imagePath << std::endl;
	for (int i = 0; i < parameters->iterations; i++)
	{
		for (int j = 0; j < parameters->constructionSteps; j++)
		{
			for (Ant* ant : ants)
			{
				Move(ant);
				UpdateLocalPheromone(ant);
			}
		}
		UpdateGlobalPheromone();
		DisplayResults();
		ResetAntsPheromone();
		cout << "Iteration " << i + 1 << " ended." << endl;
	}
	cv::waitKey(0);
}
