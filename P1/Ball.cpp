#include "stdafx.h"
#include "Ball.h"


Ball::Ball() : CollidableBody(){
	
}

void Ball::update(){
	//vel.y += 0.2f;
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



