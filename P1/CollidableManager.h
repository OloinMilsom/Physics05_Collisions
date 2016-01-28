#ifndef COLLIDABLEMANAGER_H
#define COLLIDABLEMANAGER_H

#include "CollidableBody.h"
#include <vector>

class CollidableManager {
private:
	std::vector<CollidableBody *> m_objects;
	static CollidableManager * m_instance;
	float m_mtd;
	sf::Vector2f m_mtv;
	void collisionDetection(std::vector<CollidableBody *> * objects, int left, int top, int right, int bottom, int & t);
	bool isColliding(CollidableBody * a, CollidableBody * b);
	void hasCollided(CollidableBody * a, CollidableBody * b);
	bool satCheck(std::vector<sf::Vector2f> * aPoints, std::vector<sf::Vector2f> * bPoints,
		std::vector<sf::Vector2f> * aSideNormals);
public:
	static CollidableManager * getInstance();
	void addObject(CollidableBody * cObj);
	sf::ConvexShape getDrawAt(int i);
	int getCount();
	void updateObjects();
};


#endif




