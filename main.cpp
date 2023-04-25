#include <iostream>
#include "City.hpp"
#include <string>
#include <vector>

using namespace std;

int main()
{
	int width, height;
	cin >> width;
	cin >> height;
	char **map = new char*[height];

	char symbol;
	vector<City*> cities;
	for (int i = 0; i < height; i++)
	{
		map[i] = new char[width];
		for (int j = 0; j < width; j++)
		{
			if((symbol = getchar()) == '\n')
				symbol = getchar();

			map[i][j] = symbol;

			if (symbol == '*')
			{
				City* city = new City(j, i);
				cities.push_back(city);
			}
		}
	}

	cout << cities.size();

	return 0;
}
