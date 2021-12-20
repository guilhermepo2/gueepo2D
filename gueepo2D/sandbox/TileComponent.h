#pragma once
#include <core/GameObject/Component.h>

class TileComponent : public gueepo::Component {
public:
	TileComponent(float x, float y, bool isPassable) : internalX(x), internalY(y), passable(isPassable) {}

	inline void SetPassable(bool value) { passable = value; }

	bool passable;
	float internalX;
	float internalY;

};