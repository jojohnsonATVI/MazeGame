#pragma once
#include "PlacableActor.h"
class ExtraLife : public PlacableActor
{
public:
	ExtraLife(int x, int y);

	virtual ActorType GetType() override { return ActorType::ExtraLife; }
	virtual void Draw() override;
};