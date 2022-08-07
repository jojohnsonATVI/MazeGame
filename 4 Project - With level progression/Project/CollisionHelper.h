#pragma once

#include <assert.h>

#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "ExtraLife.h"
#include "Goal.h"
#include "AudioManager.h"
#include "Player.h"
#include "Level.h"
#include "StateMachineExampleGame.h"

class CollisionHelper
{
public:

	struct CollisionInfo
	{
		Player& player;
		bool didBeatLevel;
		int newPlayerX;
		int newPlayerY;
		StateMachineExampleGame::SceneName newScene;
	};

	static void HandleCollision(PlacableActor* collidedActor, CollisionInfo& state);
private:
	static void EnemyCollision(Enemy* collidedEnemy, CollisionInfo& state);
	static void MoneyCollision(Money* collidedMoney, CollisionInfo& state);
	static void ExtraLifeCollision(ExtraLife* collidedExtraLife, CollisionInfo& state);
	static void KeyCollision(Key* collidedKey, CollisionInfo& state);
	static void DoorCollision(Door* collidedDoor, CollisionInfo& state);
	static void GoalCollision(Goal* collidedGoal, CollisionInfo& state);
};