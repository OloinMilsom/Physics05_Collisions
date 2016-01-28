#include "stdafx.h"
#include "CollidableBody.h"


CollidableBody::CollidableBody(int numPoints) : m_NUMPOINTS(numPoints)
{
	m_pos = sf::Vector2f(rand() % 800, rand() % 600);
	m_vel = sf::Vector2f(rand() % 7 - 3, rand() % 7 - 3);
	if (m_vel.x == 0 && m_vel.y == 0)
	{
		m_vel.x = 1;
	}
	m_size = rand() % 10 + 18;
	float pi = std::acos(-1);
	//m_rotate = Matrix2::rotate(pi / (rand() % 25 + 20));

	float step = (2 * pi) / m_NUMPOINTS;

	for (int i = 0; i < m_NUMPOINTS; i++)
	{
		m_points.push_back(sf::Vector2f(m_size * cos(step * i), m_size * sin(step * i)));
	}
	sf::Vector2f v = m_points[1] - m_points[0];
	m_edgeLength = sqrt(v.x * v.x + v.y * v.y);
}

void CollidableBody::update(){
	for (int i = 0; i < m_NUMPOINTS; i++)
	{
		m_points[i] = m_rotate * m_points[i];
	}
	m_pos += m_vel;
	if (m_pos.x < 0){
		m_vel.x = -m_vel.x;
		m_pos.x = 0;
	}
	if (m_pos.x > 800 - m_size){
		m_vel.x = -m_vel.x;
		m_pos.x = 800 - m_size;
	}
	if (m_pos.y < 0){
		m_vel.y = -m_vel.y;
		m_pos.y = 0;
	}
	if (m_pos.y > 600 - m_size){
		m_vel.y = -m_vel.y;
		m_pos.y = 600 - m_size;
	}
}

sf::ConvexShape CollidableBody::getDraw() const{
	sf::ConvexShape s(m_NUMPOINTS);
	for (int i = 0; i < m_NUMPOINTS; i++)
	{
		s.setPoint(i, m_pos + m_points[i]);
	}
	s.setFillColor(sf::Color::White);
	return s;
}

sf::Vector2f CollidableBody::getPos() const{
	return m_pos;
}

sf::Vector2f CollidableBody::getVel() const{
	return m_vel;
}

int CollidableBody::getSize() const{
	return m_size;
}

std::vector<sf::Vector2f> CollidableBody::getPoints() const{
	std::vector<sf::Vector2f> vs = m_points;
	for (int i = 0; i < vs.size(); i++)
	{
		vs[i] += m_pos;
	}
	return vs;
}

std::vector<sf::Vector2f> CollidableBody::getFaceNormals() const{
	std::vector<sf::Vector2f> vs;
	int n = m_NUMPOINTS;
	if (n % 2 == 0) {
		n = n / 2;
	}
	for (int i = 0; i < n; i++)
	{
		int j;
		if (i < m_NUMPOINTS - 1)
			j = i + 1;
		else
			j = 0;
		sf::Vector2f v = m_points[j] - m_points[i];
		v = sf::Vector2f(-v.y, v.x);
		v = v / m_edgeLength;
		vs.push_back(v);
	}
	return vs;
}

void CollidableBody::setPos(sf::Vector2f v){
	m_pos = v;
}

void CollidableBody::setVel(sf::Vector2f v){
	m_vel = v;
}

void CollidableBody::push(sf::Vector2f v){
	sf::Vector2f d = m_pos - v;
	float dLength = sqrt(d.x * d.x + d.y * d.y);
	d = (d / dLength) * (1 / dLength * dLength) * 0.12f;
	m_vel += d;
}

void CollidableBody::pull(sf::Vector2f v){
	sf::Vector2f d = v - m_pos;
	float dLength = sqrt(d.x * d.x + d.y * d.y);
	d = (d / dLength) * (1 / dLength * dLength) * 0.12f;
	m_vel += d;
}