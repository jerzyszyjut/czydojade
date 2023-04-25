#pragma once
#include <forward_list>
#include <string>

using namespace std;

class City
{
public:
	City();
	City(int x, int y);
	~City();
	
	void setName(string name);
	string getName();
	void addAdjecentCity(City* city);
	forward_list<City*> getAdjecentCities();
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();

private:
	 forward_list<City*> m_adjecentCities;
	 string m_name;
	 int m_x, m_y;
};

