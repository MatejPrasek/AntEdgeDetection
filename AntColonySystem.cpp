#include "AntColonySystem.h"

AntColonySystem::AntColonySystem(Parameters parameters) : m_parameters(std::move(parameters))
{
	maxWidth = m_parameters.heuristic.size();
	maxHeight = m_parameters.heuristic[0].size();

	m_parameters.pheromone = vector<vector<float>>(maxWidth, vector<float>(maxHeight));
	m_parameters.edges = vector<vector<float>>(maxWidth, vector<float>(maxHeight));

	if (!m_parameters.debug) srand(time(NULL));
	else srand(1);
	
	cv::Mat initPosition = cv::Mat(maxHeight, maxWidth, CV_8UC1);
	for (int i = 0; i < maxWidth; i++)
		for (int j = 0; j < maxHeight; j++)
		{
			initPosition.at<uchar>(j, i) = m_parameters.intensity[i][j];
		}

	heuristicMax = 0;
	for (int i = 0; i < maxWidth; i++)
		for (int j = 0; j < maxHeight; j++) 
		{
			if (heuristicMax < m_parameters.heuristic[i][j])
				heuristicMax = m_parameters.heuristic[i][j];
			m_parameters.pheromone[i][j] = m_parameters.tauini;
			m_parameters.edges[i][j] = 0;
		}

	vector<tuple<tuple<int, int>, int>> MaxHeuristic = vector<tuple<tuple<int, int>, int>>(maxWidth*maxHeight);
	
	for (int i = 0; i < maxWidth; i++)
		for (int j = 0; j < maxHeight; j++)
		{
			MaxHeuristic.emplace_back(tuple<int, int>(i, j), m_parameters.heuristic[i][j]);
		}

	sort(MaxHeuristic.begin(), MaxHeuristic.end(), SortPositionValueTuple);
	
	ants = vector<unique_ptr<Ant>>(m_parameters.ants);
	for (int i = 0; i < m_parameters.ants; ++i)
	{
		tuple<int, int> position;
		if(m_parameters.random)
			position = tuple<int, int>(rand() % maxWidth, rand() % maxHeight);
		else
		{
			position = tuple<int, int>(std::get<0>(std::get<0>(MaxHeuristic[i])), std::get<1>(std::get<0>(MaxHeuristic[i])));
		}
		ants[i] = make_unique<Ant>(position, 0, m_parameters.memory, m_parameters.constructionSteps);

		circle(initPosition, cv::Point(std::get<0>(ants[i]->position), std::get<1>(ants[i]->position)), 2, cv::Scalar(255,255,255));
	}

	namedWindow("Initial positions", cv::WINDOW_AUTOSIZE);
	imshow("Initial positions", initPosition);
	cv::waitKey(500);
}

bool AntColonySystem::SortPositionValueTuple(const tuple<tuple<int, int>, int> &first, const tuple<tuple<int, int>, int> &second)
{
	return get<1>(first) > get<1>(second);
}

tuple<tuple<int, int>, float, float> AntColonySystem::GetMooreNeighborhood(Ant& ant, int index)
{
	int width = std::get<0>(ant.position) + index % 3 - 1;
	int height = std::get<1>(ant.position) + index / 3 - 1;
	tuple<int, int> position = tuple<int, int>{ width, height };

	//current position
	if(index == 4)
		return tuple<tuple<int, int>, int, float>{ant.position, 0, 0.0};
	
	//stay inside picture
	if (width < 0 || width >= maxWidth ||
		height < 0 || height >= maxHeight)
		return tuple<tuple<int, int>, int, float>{ant.position, 0, 0.0};

	//verify that neighbor position isn't in ant's memory
	for (unsigned int i = ant.visited.size(); i > ant.visited.size() - m_parameters.memory; i--)
	{
		if (i == 0)
			break;
		if(std::get<0>(ant.visited[i-1]) == width && 
			std::get<1>(ant.visited[i-1]) == height)
			return tuple<tuple<int, int>, int, float>{position, 0, 0.0};
	}

	return tuple<tuple<int, int>, float, float>{position, GetHeuristic(position), GetPheromone(position)};
}

tuple<int, int> AntColonySystem::SelectNextPixel(Ant& ant)
{
	const int surrounding = 9;
	vector<tuple<tuple<int, int>, float, float>> neighbors;
	for (int i = 0; i < surrounding; i++)
	{
		auto neighbor = GetMooreNeighborhood(ant, i);
		if (get<0>(neighbor) != ant.position)
			neighbors.push_back(neighbor);
	}

	float q = float(rand()) / RAND_MAX;

	//todo clean this mess
	if (q <= m_parameters.q0)
	{
		int maxIndex = 0;
		float maxValue = 0;
		for (unsigned int i = 0; i < neighbors.size(); ++i)
		{
			float value = pow(std::get<2>(neighbors[i]), m_parameters.alpha) * pow(std::get<1>(neighbors[i]), m_parameters.beta);
			if (value > maxValue)
			{
				maxValue = value;
				maxIndex = i;
			}
		}

		// No valid neighbor, return random neighbor
		if(maxValue == 0)
			return std::get<0>(neighbors[rand() % neighbors.size()]);
	
		return std::get<0>(neighbors[maxIndex]);
	}
	else
	{
		float sum = 0;
		for (unsigned int i = 0; i < neighbors.size(); ++i)
		{
			sum += pow(std::get<2>(neighbors[i]), m_parameters.alpha) * pow(std::get<1>(neighbors[i]), m_parameters.beta);
		}

		int maxIndex = 0;
		float maxValue = -1;
		for (unsigned int i = 0; i < neighbors.size(); ++i)
		{			
			float value = pow(std::get<2>(neighbors[i]), m_parameters.alpha) * pow(std::get<1>(neighbors[i]), m_parameters.beta) / sum;
			if (value > maxValue)
			{
				maxValue = value;
				maxIndex = i;
			}
		}

		// No valid neighbor, return random neighbor
		if (maxValue == 0)
			return std::get<0>(neighbors[rand() % neighbors.size()]);
		
		return std::get<0>(neighbors[maxIndex]);
	}
}

void AntColonySystem::Move(Ant& ant)
{
	tuple<int, int> nextPosition = SelectNextPixel(ant);
	
	if (std::find(alreadyVisitedPositions.begin(), alreadyVisitedPositions.end(), nextPosition) == alreadyVisitedPositions.end())
		alreadyVisitedPositions.push_back(nextPosition);

	ant.Move(nextPosition);
}

void AntColonySystem::UpdateGlobalPheromone()
{
	vector<tuple<int, int>> visitedPositions;

	ResetAntsPheromone();
	for (auto& ant : ants)
	{
		for (unsigned int i = ant->visited.size(); i > ant->visited.size() - m_parameters.constructionSteps; i--)
		{
			if (i == 0)
				break;
			ant->pheromone += float(GetHeuristic(ant->visited[i - 1]));
			visitedPositions.push_back(ant->visited[i-1]);
		}
		ant->pheromone /= float(m_parameters.constructionSteps);
	}
	
	// remove duplicated positions 
	sort(visitedPositions.begin(), visitedPositions.end());
	visitedPositions.erase(unique(visitedPositions.begin(), visitedPositions.end()), visitedPositions.end());
	
	for (auto position : visitedPositions)
	{
		float totalDeltaTau = 0;
		for (auto& ant : ants)
		{
			for (unsigned int i = ant->visited.size(); i > ant->visited.size() - m_parameters.constructionSteps; i--)
			{
				if (i == 0)
					break;
				if (position == ant->visited[i - 1])
					totalDeltaTau += ant->pheromone;
			}
		}
		SetPheromone(position, GetPheromone(position) * (1 - m_parameters.rho));
		UpdatePheromone(position, m_parameters.rho * totalDeltaTau);
	}
	
	// positions with pheromones from previous iterations
	sort(alreadyVisitedPositions.begin(), alreadyVisitedPositions.end());
	vector<tuple<int, int>> tmp(alreadyVisitedPositions.size());
	auto vectorEnd = set_difference(alreadyVisitedPositions.begin(), alreadyVisitedPositions.end(),
		visitedPositions.begin(), visitedPositions.end(), tmp.begin());
	vector<tuple<int, int>> notUpdated(tmp.begin(), vectorEnd);
	
	auto iterator = begin(notUpdated);
	while (iterator != std::end(notUpdated))
	{
		
		float newPheromoneValue = GetPheromone(*iterator) * (1 - m_parameters.rho);
		if (newPheromoneValue > m_parameters.tauini) 
		{
			SetPheromone(*iterator, newPheromoneValue);
			++iterator;
		}
		else
		{
			SetPheromone(*iterator, m_parameters.tauini);
			iterator = notUpdated.erase(iterator);
		}
	}
}

void AntColonySystem::UpdateLocalPheromone(Ant& ant)
{
	float updated = (1 - m_parameters.phi) * GetPheromone(ant.position) + m_parameters.phi * m_parameters.tauini;
	SetPheromone(ant.position, updated);
	ant.pheromone += updated;
}

float AntColonySystem::GetHeuristic(tuple<int, int> position)
{
	return float(m_parameters.heuristic[std::get<0>(position)][std::get<1>(position)]) / heuristicMax;
}

void AntColonySystem::DisplayResults(int iter)
{
	const int threshold = 0;
	float min = 1;
	float max = 0;
	for (vector<float> pheromoneRow : m_parameters.pheromone)
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
		m_parameters.edges[std::get<0>(position)][std::get<1>(position)] = int(round(abs((GetPheromone(position) - min) / diff) * 255));
	}

	cv::Mat img = cv::Mat(maxHeight, maxWidth, CV_8UC1);
	for (int i = 0; i < maxWidth; i++)
	{
		for (int j = 0; j < maxHeight; j++)
		{
			if(m_parameters.edges[i][j] > threshold)
				img.at<uchar>(j, i) = 0;
			else
				img.at<uchar>(j, i) = 255;
		}
	}
	
	cv::namedWindow("Edges", cv::WINDOW_AUTOSIZE);
	imshow("Edges", img);

	cv::imwrite( "RESULTS/Iteration" + std::to_string(iter) + ".png", img);
	
	cv::waitKey(500);
}

void AntColonySystem::ResetAntsPheromone()
{
	for (auto& ant : ants)
	{
		ant->pheromone = 0.0;
	}
}

float AntColonySystem::GetPheromone(tuple<int, int> position)
{
	return m_parameters.pheromone[std::get<0>(position)][std::get<1>(position)];
}


void AntColonySystem::UpdatePheromone(tuple<int, int> position, float value)
{
	m_parameters.pheromone[std::get<0>(position)][std::get<1>(position)] += value;
}

void AntColonySystem::SetPheromone(tuple<int, int> position, float value)
{
	m_parameters.pheromone[std::get<0>(position)][std::get<1>(position)] = value;
}

void AntColonySystem::Run()
{
	std::cout << m_parameters.imagePath << std::endl;
	for (int i = 0; i < m_parameters.iterations; i++)
	{
		for (int j = 0; j < m_parameters.constructionSteps; j++)
		{
			for (auto& ant : ants)
			{
				Move(*ant);
				UpdateLocalPheromone(*ant);
			}
		}
		UpdateGlobalPheromone();
		DisplayResults(i+1);
		ResetAntsPheromone();
		cout << "Iteration " << i + 1 << " ended." << endl;
	}
	cv::waitKey(500);
}
