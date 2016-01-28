#ifndef MATRIX2_H
#define MATRIX2_H

#include "stdafx.h"

class Matrix2 {
public:
	float m_11;
	float m_12;
	float m_21;
	float m_22;
	Matrix2(float m11 = 1.0f, float m12 = 0, float m21 = 0, float m22 = 1.0f);
	void operator+= (Matrix2 & const);
	void operator*= (Matrix2 & const);
	sf::Vector2f operator* (sf::Vector2f & const);
	static Matrix2 rotate(float angle);
};

#endif