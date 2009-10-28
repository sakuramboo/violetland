#include "StandardBullet.h"

StandardBullet::StandardBullet(float x, float y) :
	Bullet(x, y, Bullet::standard) {
	Speed = 3;
	Damage = 1;
	MaxRange = 1000;
	Alpha = 1.0f;
	prevX = x;
	prevY = y;
}

void StandardBullet::process(int deltaTime) {
	if (m_active) {
		prevX = X;
		prevY = Y;
		X -= cos((Angle + 90) * M_PI / 180) * deltaTime * Speed;
		Y -= sin((Angle + 90) * M_PI / 180) * deltaTime * Speed;
	}

	m_range += Speed * deltaTime;
	Alpha = (MaxRange - m_range) / MaxRange;
	m_active = m_active && m_range < MaxRange;
	m_readyToRemove = !m_active && Alpha == 0;
}

void StandardBullet::draw() {
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	glColor4f(1.0f, 1.0f, 1.0f, Alpha);
	glVertex3f(X, Y, 0);
	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	glVertex3f(startX, startY, 0);
	glEnd();
}

bool StandardBullet::checkHit(Object* objRef) {
	if (m_active && objRef->detectCollide(prevX, prevY, X, Y)) {
		if (!BigCalibre) deactivate();
		return true;
	} else {
		return false;
	}
}
