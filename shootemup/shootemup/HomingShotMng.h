#pragma once
#include <memory>
#include <vector>
#include "Geometry.h"

struct HomingShot;
struct Trail;

class HomingShotMng
{
public:
	HomingShotMng(Position2f& enemyPos);
	~HomingShotMng();
	void AddHoming(std::shared_ptr<HomingShot> shot);
	void Update(void);
	void Draw(void);
	void AddTrail(const Trail& trail,bool flag);
private:
	std::vector<std::shared_ptr<HomingShot>> shots_;
	std::vector<unsigned short> indices_;
	Position2f& enemyPos_;
};

