#include "City.hpp"

City::City()
{
	m_x = 0;
	m_y = 0;
	m_name = "";
	m_adjecentCities = forward_list<CityEdge>();
}

City::City(int x, int y)
{
	m_x = x;
	m_y = y;
	m_name = "";
	m_adjecentCities = forward_list<CityEdge>();
}

City::~City()
{
}

void City::setName(string name)
{
	m_name = name;
}

string City::getName()
{
	return m_name;
}

void City::addAdjecentCity(CityEdge cityEdge)
{
	m_adjecentCities.push_front(cityEdge);
}

forward_list<City::CityEdge> City::getAdjecentCities()
{
	return m_adjecentCities;
}

void City::setDistanceToCity(City* city, int distance)
{
	m_adjecentCities.push_front(CityEdge{ city, distance });
}

int City::getDistanceToCity(City* city)
{
	for (CityEdge& cityEdge : m_adjecentCities)
		if (cityEdge.city == city)
			return cityEdge.distance;
	return -1;
}

void City::setX(int x)
{
	m_x = x;
}

void City::setY(int y)
{
	m_y = y;
}

int City::getX()
{
	return m_x;
}

int City::getY()
{
	return m_y;
}
