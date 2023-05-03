#include "City.hpp"

City::City() : m_id(0), m_adjecentCities(JList<CityEdge>()), m_name(""), m_x(0), m_y(0)
{
}

City::City(int x, int y) : m_id(0), m_adjecentCities(JList<CityEdge>()), m_name(""), m_x(x), m_y(y)
{
}

City::City(City& other)
{
	m_id = other.getId();
	m_adjecentCities = other.getAdjecentCities();
	m_name = other.getName();
	m_x = other.getX();
	m_y = other.getY();
}

City::~City()
{
}

City& City::operator=(City& other)
{
	m_id = other.getId();
	m_adjecentCities = other.getAdjecentCities();
	m_name = other.getName();
	m_x = other.getX();
	m_y = other.getY();
	return *this;
}

void City::setName(JString& name)
{
	m_name = name;
}

void City::setName(JString&& name)
{
	m_name = name;
}

JString City::getName() const
{
	return m_name;
}

JList<City::CityEdge>& City::getAdjecentCities()
{
	return m_adjecentCities;
}

void City::setDistanceToCity(City* city, int distance)
{
	for (JList<City::CityEdge>::iterator cityEdge = m_adjecentCities.begin(); cityEdge != m_adjecentCities.end(); ++cityEdge)
		if (cityEdge->city == city && cityEdge->distance > distance)
		{
			cityEdge->distance = distance;
			return;
		}
	m_adjecentCities.push_front(CityEdge{ city, distance });
}

void City::addAdjecentCity(City* city, int distance)
{
	m_adjecentCities.push_front(CityEdge{ city, distance });
}

int City::getX() const
{
	return m_x;
}

int City::getY() const
{
	return m_y;
}

void City::setId(int id)
{
	m_id = id;
}

int City::getId() const
{
	return m_id;
}
