#pragma once
#include <vector>
#include "Matrix2.h"

class CollidableBody
{
protected:
	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
	std::vector<sf::Vector2f> m_points;
	int m_size;
	Matrix2 m_rotate;
	const int m_NUMPOINTS;
	float m_edgeLength;
public:
	CollidableBody(int numPoints = 3);
	virtual void update();
	sf::ConvexShape getDraw() const;
	virtual std::vector<sf::Vector2f> getFaceNormals() const;
	sf::Vector2f getPos() const;
	sf::Vector2f getVel() const;
	int getSize() const;
	std::vector<sf::Vector2f> getPoints() const;
	void setPos(sf::Vector2f v);
	void setVel(sf::Vector2f v);
	void push(sf::Vector2f v);
	void pull(sf::Vector2f v);
};

