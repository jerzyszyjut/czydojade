#pragma once
#include <forward_list>
#include <string>

using namespace std;



class City
{
public:
	struct CityEdge
	{
		City* city;
		int distance;
	};

	City();
	City(int x, int y);
	~City();
	
	void setName(string name);
	string getName();
	void addAdjecentCity(CityEdge city);
	forward_list<CityEdge> getAdjecentCities();
	void setDistanceToCity(City* city, int distance);
	int getDistanceToCity(City* city);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void setId(int id);
	int getId();

	struct CityEdgeComparator
	{
		bool operator()(const CityEdge& lhs, const CityEdge& rhs) const
		{
			return lhs.distance > rhs.distance;
		}
	};

private:
	int m_id;
	forward_list<CityEdge> m_adjecentCities;
	string m_name;
	int m_x, m_y;
};

