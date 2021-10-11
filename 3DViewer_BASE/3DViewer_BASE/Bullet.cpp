#include <cmath>
#include "Bullet.h"
#include "SceneManager.h"

Bullet::Bullet(SceneManager* sceneManager)
{
}

Bullet::~Bullet()
{
}

void Bullet::Init(VECTOR pos, VECTOR angle)
{
	pos_ = pos;
	angle_ = angle;
}

void Bullet::Update(void)
{
	pos_ = VAdd(pos_, VGet(sinf(angle_.y) * BULLET_SPEED, 0.0f, cosf(angle_.y) * BULLET_SPEED));
}

void Bullet::Draw(void)
{
	DrawSphere3D(pos_, BULLET_RAD, 16, 0xffffff, 0xffffff, true);
}

void Bullet::Release(void)
{
}
