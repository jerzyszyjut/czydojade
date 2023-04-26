#include <iostream>
#include "City.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

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

void loadCities(char** map, int width, int height, vector<City*>& cities)
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

string getCityName(char** map, int width, int height, int x, int y)
{
	for (int j = -1; j <= 1; j++)
	{
		for (int k = -1; k <= 1; k++)
		{
			if (j == 0 && k == 0)
				continue;

			if (x + j >= 0 && x + j < width && y + k >= 0 && y + k < height)
			{
				if (map[y + k][x + j] >= 'A' && map[y + k][x + j] <= 'Z')
				{
					string name = "";
					if (x + j + 1 < width && map[y + k][x + j + 1] >= 'A' && map[y + k][x + j + 1] <= 'Z')
					{
						name += map[y + k][x + j];
						for (int l = x + j + 1; l < width; l++)
						{
							if (map[y + k][l] >= 'A' && map[y + k][l] <= 'Z')
								name += map[y + k][l];
							else
								break;
						}
					}
					else if (x + j - 1 >= 0 && map[y + k][x + j - 1] >= 'A' && map[y + k][x + j - 1] <= 'Z')
					{
						name += map[y + k][x + j];
						for (int l = x + j - 1; l >= 0; l--)
						{
							if (map[y + k][l] >= 'A' && map[y + k][l] <= 'Z')
								name += map[y + k][l];
							else
								break;
						}

						string reversed_name = "";
						for (int l = name.length() - 1; l >= 0; l--)
							reversed_name += name[l];

						name = reversed_name;
					}

					return name;
				}
			}
		}
	}
	return "";
}

void getCitiesNames(char** map, int width, int height, vector<City*>& cities)
{
	for (int i = 0; i < (int)cities.size(); i++)
	{
		City* city = cities[i];

		city->setName(getCityName(map, width, height, city->getX(), city->getY()));
	}
}

void convertCitiesToHashmap(vector<City*>& cities, unordered_map<string, City*>& cityMap)
{
	for (int i = 0; i < (int)cities.size(); i++)
	{
		City* city = cities[i];
		city->setId(i);
		cityMap[city->getName()] = city;
	}
}

/*
Example input:
20 20
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
*/

void findShortestDistancesBetweenCities(char** map, int width, int height, City& city, unordered_map<string, City*>& cityMap)
{
	int current_x = city.getX(), current_y = city.getY(), current_distance = 0;

	queue<Coordinates> q;
	int** visited = new int* [height];
	for (int i = 0; i < height; i++)
	{
		visited[i] = new int[width];
		for (int j = 0; j < width; j++)
			visited[i][j] = -1;
	}

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
				string name = getCityName(map, width, height, current_x + 1, current_y);
				City* foundCity = cityMap[name];
				if (&city != foundCity && (foundCity->getDistanceToCity(&city) == -1 || foundCity->getDistanceToCity(&city) > current_distance + 1))
				{
					foundCity->setDistanceToCity(&city, current_distance + 1);
					city.setDistanceToCity(foundCity, current_distance + 1);
				}
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
				string name = getCityName(map, width, height, current_x - 1, current_y);
				City* foundCity = cityMap[name];
				if (&city != foundCity && (foundCity->getDistanceToCity(&city) == -1 || foundCity->getDistanceToCity(&city) > current_distance + 1))
				{
					foundCity->setDistanceToCity(&city, current_distance + 1);
					city.setDistanceToCity(foundCity, current_distance + 1);
				}
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
				string name = getCityName(map, width, height, current_x, current_y + 1);
				City* foundCity = cityMap[name];
				if (&city != foundCity && (foundCity->getDistanceToCity(&city) == -1 || foundCity->getDistanceToCity(&city) > current_distance + 1))
				{
					foundCity->setDistanceToCity(&city, current_distance + 1);
					city.setDistanceToCity(foundCity, current_distance + 1);
				}
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
				string name = getCityName(map, width, height, current_x, current_y - 1);
				City* foundCity = cityMap[name];
				if (&city != foundCity && (foundCity->getDistanceToCity(&city) == -1 || foundCity->getDistanceToCity(&city) > current_distance + 1))
				{
					foundCity->setDistanceToCity(&city, current_distance + 1);
					city.setDistanceToCity(foundCity, current_distance + 1);
				}
			}
		}
	}
}

void loadAirports(unordered_map<string, City*>& cityMap)
{
	int airportsCount;
	cin >> airportsCount;
	for (int i = 0; i < airportsCount; i++)
	{
		string cityFrom, cityTo;
		cin >> cityFrom;
		cin >> cityTo;
		int distance;
		cin >> distance;
		City* city1 = cityMap[cityFrom];
		City* city2 = cityMap[cityTo];
		city1->setDistanceToCity(city2, distance);
	}
}


void buildCitiesConnections(char** map, int width, int height, unordered_map<string, City*>& cityMap, vector<City*>& cities)
{
	loadMap(map, width, height);

	loadCities(map, width, height, cities);
	getCitiesNames(map, width, height, cities);
	convertCitiesToHashmap(cities, cityMap);

	loadAirports(cityMap);

	for (int i = 0; i < (int)cities.size(); i++)
	{
		findShortestDistancesBetweenCities(map, width, height, *cities[i], cityMap);
	}
}

void deallocateMap(char** map, int height)
{
	for (int i = 0; i < height; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

struct Edge
{
	int from;
	int to;
	int cost;
};

struct EdgeComparator
{
	bool operator()(const Edge& e1, const Edge& e2)
	{
		return e1.cost > e2.cost;
	}
};

struct PathCost
{
	int cost;
	int previous_city;
};

void printShortestDistance(City* city1, City* city2, vector<City*>& cities, int displayCities)
{
	priority_queue<Edge, vector<Edge>, EdgeComparator> edges;
	vector<PathCost> pathCosts(cities.size());
	for (int i = 0; i < (int)cities.size(); i++)
	{
		pathCosts[i].cost = INT_MAX;
		pathCosts[i].previous_city = -1;
	}

	int city1Index = city1->getId();
	int city2Index = city2->getId();
	pathCosts[city1Index].cost = 0;
	edges.push(Edge{ city1Index, city1Index, 0 });

	while (!edges.empty())
	{
		Edge currentEdge = edges.top();
		edges.pop();
		if (currentEdge.to == city2Index)
		{
			break;
		}
		for (auto& city : cities[currentEdge.to]->getAdjecentCities())
		{
			int currentCost = pathCosts[currentEdge.to].cost + city.distance;
			if (currentCost < pathCosts[city.city->getId()].cost)
			{
				pathCosts[city.city->getId()].cost = currentCost;
				pathCosts[city.city->getId()].previous_city = currentEdge.to;
				edges.push(Edge{ currentEdge.to, city.city->getId(), currentCost });
			}
		}
	}

	if (pathCosts[city2Index].cost == INT_MAX)
	{
		cout << "No connection" << endl;
	}
	else
	{
		cout << pathCosts[city2Index].cost;

		if (displayCities)
		{
			vector<int> path;
			int currentCity = pathCosts[city2Index].previous_city;
			while (currentCity != city1Index)
			{
				path.push_back(currentCity);
				currentCity = pathCosts[currentCity].previous_city;
			}
			for (int i = path.size() - 1; i >= 0; i--)
			{
				cout << " " << cities[path[i]]->getName();
			}
		}
		cout << endl;
	}
}

int main()
{
	int width, height;
	cin >> width;
	cin >> height;
	char** map = new char* [height];

	vector<City*> cities;
	unordered_map<string, City*> cityMap;
	buildCitiesConnections(map, width, height, cityMap, cities);
	deallocateMap(map, height);

	int instructionsCount = 0;
	cin >> instructionsCount;

	for (int i = 0; i < instructionsCount; i++)
	{
		string city1, city2;
		int displayCities;
		cin >> city1;
		cin >> city2;
		cin >> displayCities;
		printShortestDistance(cityMap[city1], cityMap[city2], cities, displayCities);
	}

	return 0;
}
