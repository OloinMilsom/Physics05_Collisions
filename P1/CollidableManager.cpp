#include "stdafx.h"
#include "CollidableManager.h"
#include <iostream>

CollidableManager * CollidableManager::m_instance = nullptr;


CollidableManager * CollidableManager::getInstance(){
	if (m_instance == nullptr){
		m_instance = new CollidableManager;
	}
	return m_instance;
}

void CollidableManager::addObject(CollidableBody * cObj){
	m_objects.push_back(cObj);
}

sf::ConvexShape CollidableManager::getDrawAt(int i){
	return m_objects[i]->getDraw();
}


int CollidableManager::getCount(){
	return m_objects.size();
}

void CollidableManager::updateObjects(){
	int length = m_objects.size();

	int t = 0;
	for (int i = 0; i < length; i++)
	{
		m_objects[i]->update();
		
		/*if (i != length - 1)
		{
			for (int j = i + 1; j < length; j++)
			{
				t++;
				if (isColliding(m_objects[i], m_objects[j]))
				{
					hasCollided(m_objects[i], m_objects[j]);
				}
			}
		}*/

		//m_objects[i]->pull(sf::Vector2f( 400, 300));
	}
	collisionDetection(&m_objects, 0, 0, 800, 600, t);
	std::cout << t << std::endl;
}

void CollidableManager::collisionDetection(std::vector<CollidableBody *> * objects, int left, int top, int right, int bottom, int & t){
	int size = objects->size();
	if (size < 6)
	{
		for (int i = 0; i < size; i++)
		{
			if (i != size - 1)
			{
				for (int j = i + 1; j < size; j++)
				{
					t++;
					if (isColliding(objects->at(i), objects->at(j)))
					{
						hasCollided(objects->at(i), objects->at(j));
					}
				}
			}
		}
	}
	else
	{
		std::vector<CollidableBody *> nw;
		std::vector<CollidableBody *> ne;
		std::vector<CollidableBody *> se;
		std::vector<CollidableBody *> sw;
		// middle of the horizontal and vertical lines
		int midHor = left + ((right - left) / 2);
		int midVer = top + ((bottom - top) / 2);
		//sf::RectangleShape horizontal(sf::Vector2f(right - left, 4));
		//horizontal.setPosition(left, midVer - 2);
		//sf::RectangleShape vertical(sf::Vector2f(4, bottom - top));
		//vertical.setPosition(midHor - 2, top);
		//window->draw(horizontal);
		//window->draw(vertical);
		for (int i = 0; i < size; i++)
		{
			sf::Vector2f pos = objects->at(i)->getPos();
			int size = objects->at(i)->getSize();
			
			// North West
			if (pos.x + size > left && pos.x - size < midHor &&
				pos.y + size > top && pos.y - size < midVer) 
			{
				nw.push_back(objects->at(i));
			}
			// North East
			if (pos.x + size > midHor && pos.x - size < right &&
				pos.y + size > top && pos.y - size < midVer)
			{
				ne.push_back(objects->at(i));
			}
			// South East
			if (pos.x + size > midHor && pos.x - size < right &&
				pos.y + size > midVer && pos.y - size < bottom)
			{
				se.push_back(objects->at(i));
			}
			// South West
			if (pos.x + size > left && pos.x - size < midHor &&
				pos.y + size > midVer && pos.y - size < bottom)
			{
				sw.push_back(objects->at(i));
			}
		}
		collisionDetection(&nw, left, top, midHor, midVer, t);
		collisionDetection(&ne, midHor, top, right, midVer, t);
		collisionDetection(&se, midHor, midVer, right, bottom, t);
		collisionDetection(&sw, left, midVer, midHor, bottom, t);
	}
}

bool CollidableManager::isColliding(CollidableBody * a, CollidableBody * b){
	int radii = (a->getSize() + b->getSize());
	float distanceSquared = (a->getPos().x - b->getPos().x) * (a->getPos().x - b->getPos().x) +
		(a->getPos().y - b->getPos().y) * (a->getPos().y - b->getPos().y);
	m_mtd = std::numeric_limits<float>::max();
	//broad phase
	if (radii * radii > distanceSquared)
	{
		std::vector<sf::Vector2f> aPoints = a->getPoints();
		std::vector<sf::Vector2f> bPoints = b->getPoints();
		std::vector<sf::Vector2f> aSideNormals = a->getFaceNormals();
		std::vector<sf::Vector2f> bSideNormals = b->getFaceNormals();
		if (satCheck(&aPoints, &bPoints, &aSideNormals) == false || satCheck(&bPoints, &aPoints, &bSideNormals) == false)
			return false;
		return true;
	}
	//return true;
	return false;
}

void CollidableManager::hasCollided(CollidableBody * a, CollidableBody * b){
	sf::Vector2f vA = a->getVel();
	sf::Vector2f vB = b->getVel();
	sf::Vector2f d = a->getPos() - b->getPos();
	float dLength = sqrt(d.x * d.x + d.y * d.y);
	sf::Vector2f normalD = d / dLength;
	sf::Vector2f t1 = ((d.x * vA.x + d.y * vA.y) / dLength  /** 0.95f*/) * normalD;
	sf::Vector2f t2 = ((d.x * vB.x + d.y * vB.y) / dLength  /** 0.95f*/) * normalD;
	vA -= t1;
	vB -= t2;
	vA += t2;
	vB += t1;
	a->setVel(vA);
	b->setVel(vB);
	//float collisionD = a->getSize() + b->getSize() - dLength;
	//a->setPos(a->getPos() + collisionD * normalD * 0.5f);
	//b->setPos(b->getPos() - collisionD * normalD * 0.5f);
	if (d.x * m_mtv.x + d.y * m_mtv.y > 0){
		a->setPos(a->getPos() + m_mtv * (m_mtd * 0.5f));
		b->setPos(b->getPos() - m_mtv * (m_mtd * 0.5f));
	}
	else {
		a->setPos(a->getPos() - m_mtv * (m_mtd * 0.5f));
		b->setPos(b->getPos() + m_mtv * (m_mtd * 0.5f));
	}
}

bool CollidableManager::satCheck(std::vector<sf::Vector2f> * aPoints, std::vector<sf::Vector2f> * bPoints,
								std::vector<sf::Vector2f> * aSideNormals){
	
	for (int i = 0; i < aSideNormals->size(); i++)
	{
		float aDotMax = -std::numeric_limits<float>::max();
		float aDotMin = std::numeric_limits<float>::max();
		float bDotMax = -std::numeric_limits<float>::max();
		float bDotMin = std::numeric_limits<float>::max();
		for (int j = 0; j < aPoints->size(); j++)
		{
			float t = aSideNormals->at(i).x * aPoints->at(j).x + aSideNormals->at(i).y * aPoints->at(j).y;
			if (t > aDotMax)
				aDotMax = t;
			if (t < aDotMin)
				aDotMin = t;
		}
		for (int k = 0; k < bPoints->size(); k++)
		{
			float t = aSideNormals->at(i).x * bPoints->at(k).x + aSideNormals->at(i).y * bPoints->at(k).y;
			if (t > bDotMax)
				bDotMax = t;
			if (t < bDotMin)
				bDotMin = t;
		}
		if (aDotMax < bDotMin || aDotMin > bDotMax)// || (aDotMin < bDotMin && aDotMax > bDotMin))
		{
			return false;
		}
		float overlap;
		if (aDotMax < bDotMax) {
			overlap = aDotMax - bDotMin;
		}
		else {
			overlap = bDotMax - aDotMin;
		}
		if (overlap < m_mtd)
		{
			m_mtd = overlap;
			m_mtv = aSideNormals->at(i);
		}
	}
	return true;
}