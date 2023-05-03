#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "jlist.hpp"
#include "jvector.hpp"
#include "jpriorityqueue.hpp"
#include "jqueue.hpp"
#include "jhashmap.hpp"
#include "City.hpp"

#define INT_MAX 2147483647
#define BUFFER_SIZE 64

struct Coordinates
{
	int x;
	int y;

	bool operator==(const Coordinates& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Coordinates& other) const
	{
		return !(*this == other);
	}
};

void loadMap(char** map, int width, int height)
{
	char symbol;
	for (int i = 0; i < height; i++)
	{
		map[i] = new char[width];
		for (int j = 0; j < width; j++)
		{
			if ((symbol = (char)getchar()) == '\n')
				symbol = (char)getchar();
			map[i][j] = symbol;
		}
	}
}

void loadCities(char** map, int width, int height, JVector<City*>& cities)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] == '*')
			{
				City* city = new City(j, i);
				cities.push_back(city);
			}
		}
	}
}

bool is_alpha_numeric(char symbol)
{
	return (symbol >= 'A' && symbol <= 'Z') || (symbol >= '0' && symbol <= '9');
}

JString getCityName(char** map, int width, int height, int x, int y)
{
	for (int xOffset = -1; xOffset <= 1; xOffset++)
	{
		for (int yOffset = -1; yOffset <= 1; yOffset++)
		{
			if (xOffset == 0 && yOffset == 0)
				continue;

			if (x + xOffset >= 0 && x + xOffset < width && y + yOffset >= 0 && y + yOffset < height)
			{
				char symbol = map[y + yOffset][x + xOffset];

				if (!is_alpha_numeric(symbol))
					continue;

				int x_start = x + xOffset;
				int x_end = x_start;

				while (x_start >= 0 && is_alpha_numeric(map[y + yOffset][x_start]))
					x_start--;

				while (x_end < width && is_alpha_numeric(map[y + yOffset][x_end]))
					x_end++;

				JString name = JString(map[y + yOffset], x_start + 1, x_end - x_start - 1);

				return name;
			}
		}
	}
	return "";
}

void getCitiesNames(char** map, int width, int height, JVector<City*>& cities)
{
	for (int i = 0; i < (int)cities.size(); i++)
	{
		City* city = cities[i];

		city->setName(getCityName(map, width, height, city->getX(), city->getY()));
	}
}

void convertCitiesToHashmap(JVector<City*>& cities, JHashMap& cityMap)
{
	for (int i = 0; i < (int)cities.size(); i++)
	{
		City* city = cities[i];
		city->setId(i);
		cityMap.insert(city->getName(), city);
	}
}

void clearVisited(int** visited, int width, int height, int startX, int startY)
{
	JQueue<Coordinates> q;
	q.push(Coordinates{ startX, startY });
	visited[startY][startX] = -1;

	while (!q.empty())
	{
		Coordinates current = q.front();
		q.pop();
		int current_x = current.x;
		int current_y = current.y;

		if (current_x + 1 < width && visited[current_y][current_x + 1] != -1)
		{
			q.push(Coordinates{ current_x + 1, current_y });
			visited[current_y][current_x + 1] = -1;
		}
		if (current_x - 1 >= 0 && visited[current_y][current_x - 1] != -1)
		{
			q.push(Coordinates{ current_x - 1, current_y });
			visited[current_y][current_x - 1] = -1;
		}
		if (current_y + 1 < height && visited[current_y + 1][current_x] != -1)
		{
			q.push(Coordinates{ current_x, current_y + 1 });
			visited[current_y + 1][current_x] = -1;
		}
		if (current_y - 1 >= 0 && visited[current_y - 1][current_x] != -1)
		{
			q.push(Coordinates{ current_x, current_y - 1 });
			visited[current_y - 1][current_x] = -1;
		}
	}
}

void findShortestDistancesBetweenCities(char** map, int width, int height, City& city, JHashMap& cityMap, int** visited)
{
	int current_x = city.getX(), current_y = city.getY(), current_distance = 0;

	JQueue<Coordinates> q;
	clearVisited(visited, width, height, current_x, current_y);

	q.push(Coordinates{ current_x, current_y });
	visited[current_y][current_x] = current_distance;

	while (!q.empty())
	{
		Coordinates current = q.front();
		q.pop();
		current_x = current.x;
		current_y = current.y;
		current_distance = visited[current_y][current_x];

		if (current_x + 1 < width)
		{
			if (map[current_y][current_x + 1] == '#' && visited[current_y][current_x + 1] == -1)
			{
				q.push(Coordinates{ current_x + 1, current_y });
				visited[current_y][current_x + 1] = current_distance + 1;
			}
			else if (map[current_y][current_x + 1] == '*')
			{
				JString name = getCityName(map, width, height, current_x + 1, current_y);
				City* foundCity = cityMap[name];
				city.setDistanceToCity(foundCity, current_distance + 1);
				foundCity->setDistanceToCity(&city, current_distance + 1);
			}
		}
		if (current_x - 1 >= 0)
		{
			if (map[current_y][current_x - 1] == '#' && visited[current_y][current_x - 1] == -1)
			{
				q.push(Coordinates{ current_x - 1, current_y });
				visited[current_y][current_x - 1] = current_distance + 1;
			}
			else if (map[current_y][current_x - 1] == '*')
			{
				JString name = getCityName(map, width, height, current_x - 1, current_y);
				City* foundCity = cityMap[name];
				city.setDistanceToCity(foundCity, current_distance + 1);
				foundCity->setDistanceToCity(&city, current_distance + 1);
			}
		}
		if (current_y + 1 < height)
		{
			if (map[current_y + 1][current_x] == '#' && visited[current_y + 1][current_x] == -1)
			{
				q.push(Coordinates{ current_x, current_y + 1 });
				visited[current_y + 1][current_x] = current_distance + 1;
			}
			else if (map[current_y + 1][current_x] == '*')
			{
				JString name = getCityName(map, width, height, current_x, current_y + 1);
				City* foundCity = cityMap[name];
				city.setDistanceToCity(foundCity, current_distance + 1);
				foundCity->setDistanceToCity(&city, current_distance + 1);
			}
		}
		if (current_y - 1 >= 0)
		{
			if (map[current_y - 1][current_x] == '#' && visited[current_y - 1][current_x] == -1)
			{
				q.push(Coordinates{ current_x, current_y - 1 });
				visited[current_y - 1][current_x] = current_distance + 1;
			}
			else if (map[current_y - 1][current_x] == '*')
			{
				JString name = getCityName(map, width, height, current_x, current_y - 1);
				City* foundCity = cityMap[name];
				city.setDistanceToCity(foundCity, current_distance + 1);
				foundCity->setDistanceToCity(&city, current_distance + 1);
			}
		}
	}
}

void loadAirports(JHashMap& cityMap)
{
	int airportsCount;
	cin >> airportsCount;
	char buffer[BUFFER_SIZE];
	int counter = 0;
	getchar();
	while (counter < airportsCount && fgets(buffer, BUFFER_SIZE, stdin))
	{
		JString cityFrom, cityTo;
		int distance;

		char* token = strtok(buffer, " \n");
		cityFrom = token;
		token = strtok(NULL, " \n");
		cityTo = token;
		token = strtok(NULL, " \n");
		distance = atoi(token);

		City* city1 = cityMap[cityFrom];
		City* city2 = cityMap[cityTo];
		city1->addAdjecentCity(city2, distance);
		counter++;
	}
}

void buildCitiesConnections(char** map, int width, int height, JHashMap& cityMap, JVector<City*>& cities)
{
	loadMap(map, width, height);

	loadCities(map, width, height, cities);
	getCitiesNames(map, width, height, cities);
	convertCitiesToHashmap(cities, cityMap);

	loadAirports(cityMap);

	int** visited = new int* [height];
	for (int i = 0; i < height; i++)
	{
		visited[i] = new int[width];
		for (int j = 0; j < width; j++)
			visited[i][j] = -1;
	}

	for (int i = 0; i < (int)cities.size(); i++)
	{
		findShortestDistancesBetweenCities(map, width, height, *cities[i], cityMap, visited);
	}

	for (int i = 0; i < height; i++)
	{
		delete[] visited[i];
	}
	delete[] visited;
}

void deallocateMap(char** map, int height)
{
	for (int i = 0; i < height; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

struct PathCost
{
	int cost;
	int previous_city;
};

void printShortestDistance(City* city1, City* city2, JVector<City*>& cities, int displayCities)
{
	JPriorityQueue edges;
	PathCost* pathCosts = new PathCost[cities.size()];
	for (int i = 0; i < (int)cities.size(); i++)
	{
		pathCosts[i].cost = INT_MAX;
		pathCosts[i].previous_city = city1->getId();
	}

	pathCosts[city1->getId()].cost = 0;
	edges.push(City::CityEdge{ city1, 0 });

	while (!edges.empty())
	{
		City::CityEdge currentEdge = edges.top();
		edges.pop();
		if (currentEdge.city->getId() == city2->getId())
		{
			break;
		}
		JList<City::CityEdge> adjecentCities = currentEdge.city->getAdjecentCities();
		for (JList<City::CityEdge>::iterator it = adjecentCities.begin(); it != adjecentCities.end(); ++it)
		{
			int currentCost = pathCosts[currentEdge.city->getId()].cost + it->distance;
			if (currentCost < pathCosts[it->city->getId()].cost)
			{
				pathCosts[it->city->getId()].cost = currentCost;
				pathCosts[it->city->getId()].previous_city = currentEdge.city->getId();
				edges.push(City::CityEdge{ it->city, currentCost });
			}
		}
	}

	if (pathCosts[city2->getId()].cost == INT_MAX)
	{
		cout << "No connection" << endl;
	}
	else
	{
		cout << pathCosts[city2->getId()].cost;

		if (displayCities)
		{
			JVector<int> path;
			int currentCity = pathCosts[city2->getId()].previous_city;
			while (currentCity != city1->getId())
			{
				path.push_back(currentCity);
				currentCity = pathCosts[currentCity].previous_city;
			}
			for (int i = path.size() - 1; i >= 0; i--)
			{
				cout << " " << cities[path[i]]->getName().c_str();
			}
		}
		cout << endl;
	}

	delete[] pathCosts;
}

int main()
{
	int width, height;
	scanf("%d %d", &width, &height);
	char** map = new char* [height];

	JVector<City*> cities;
	JHashMap cityMap;
	buildCitiesConnections(map, width, height, cityMap, cities);
	deallocateMap(map, height);

	int instructionsCount = 0;
	cin >> instructionsCount;

	char buffer[BUFFER_SIZE];

	int counter = 0;
	getchar();
	while (counter < instructionsCount && fgets(buffer, BUFFER_SIZE, stdin))
	{
		JString city1, city2;
		int displayCities;

		char* token = strtok(buffer, " \n");
		city1 = token;
		token = strtok(NULL, " \n");
		city2 = token;
		token = strtok(NULL, " \n");
		displayCities = atoi(token);

		printShortestDistance(cityMap[city1], cityMap[city2], cities, displayCities);
		counter++;
	}

	return 0;
}
