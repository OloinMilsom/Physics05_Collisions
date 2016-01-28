#include "stdafx.h"
#include "Matrix2.h"


Matrix2::Matrix2(float m11, float m12, float m21, float m22) 
	: m_11(m11),
	  m_12(m12),
      m_21(m21),
	  m_22(m22){	
}

void Matrix2::operator+= (Matrix2 & const other){
	m_11 += other.m_11;
	m_12 += other.m_12;
	m_21 += other.m_21;
	m_22 += other.m_22;
}

void Matrix2::operator*= (Matrix2 & const other){
	Matrix2 t(m_11 * other.m_11 + m_12 * other.m_21, m_11 * other.m_12 + m_12 * other.m_22,
		m_21 * other.m_11 + m_22 * other.m_21, m_21 * other.m_12 + m_22 * other.m_22);
	m_11 = t.m_11;
	m_12 = t.m_12;
	m_21 = t.m_21;
	m_22 = t.m_22;
}

sf::Vector2f Matrix2::operator* (sf::Vector2f & const v){
	return sf::Vector2f(m_11 * v.x + m_12 * v.y, m_21 * v.x + m_22 * v.y);
}

Matrix2 Matrix2::rotate(float angle){
	return Matrix2(std::cos(angle), -std::sin(angle), std::sin(angle), std::cos(angle));
}