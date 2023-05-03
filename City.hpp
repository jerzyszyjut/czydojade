#pragma once
#include "jlist.hpp"
#include "jstring.hpp"

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
	City(City& other);
	~City();

	City& operator=(City& other);

	void setName(JString& name);
	void setName(JString&& name);
	JString getName() const;
	JList<CityEdge>& getAdjecentCities();
	void setDistanceToCity(City* city, int distance);
	void addAdjecentCity(City* city, int distance);
	int getX() const;
	int getY() const;
	void setId(int id);
	int getId() const;

	struct CityEdgeComparator
	{
		bool operator()(const CityEdge& lhs, const CityEdge& rhs) const
		{
			return lhs.distance > rhs.distance;
		}
	};

private:
	int m_id;
	JList<CityEdge> m_adjecentCities;
	JString m_name;
	int m_x, m_y;
};
