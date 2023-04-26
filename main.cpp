#include <iostream>
#include "City.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <limits>

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
			if ((symbol = getchar()) == '\n')
				symbol = getchar();
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
}

void getCitiesNames(char** map, int width, int height, vector<City*>& cities)
{
	for (int i = 0; i < cities.size(); i++)
	{
		City* city = cities[i];
		int x = city->getX();
		int y = city->getY();

		city->setName(getCityName(map, width, height, city->getX(), city->getY()));
	}
}

void convertCitiesToHashmap(vector<City*>& cities, unordered_map<string, City*>& cityMap)
{
	for (int i = 0; i < cities.size(); i++)
	{
		City* city = cities[i];
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
				q.push(Coordinates{ current_x, current_y + 1});
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
				q.push(Coordinates{ current_x, current_y - 1});
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

void buildCitiesConnections(char** map, int width, int height, unordered_map<string, City*>& cityMap)
{
	loadMap(map, width, height);

	vector<City*> cities;

	loadCities(map, width, height, cities);
	getCitiesNames(map, width, height, cities);
	convertCitiesToHashmap(cities, cityMap);

	for (int i = 0; i < cities.size(); i++)
	{
		findShortestDistancesBetweenCities(map, width, height, *cities[i], cityMap);
	}
}

int main()
{
	int width, height;
	cin >> width;
	cin >> height;
	char** map = new char* [height];

	unordered_map<string, City*> cityMap;
	buildCitiesConnections(map, width, height, cityMap);

	return 0;
}
