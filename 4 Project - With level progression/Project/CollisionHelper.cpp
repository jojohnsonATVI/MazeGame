#include "CollisionHelper.h"

void CollisionHelper::HandleCollision(PlacableActor* collidedActor, CollisionInfo& state)
{
	switch (collidedActor->GetType())
	{
	case ActorType::Enemy:
	{
		Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
		assert(collidedEnemy);
		EnemyCollision(collidedEnemy, state);
		break;
	}
	case ActorType::Money:
	{
		Money* collidedMoney = dynamic_cast<Money*>(collidedActor);
		assert(collidedMoney);
		MoneyCollision(collidedMoney, state);
		break;
	}
	case ActorType::ExtraLife:
	{
		ExtraLife* collidedExtraLife = dynamic_cast<ExtraLife*>(collidedActor);
		assert(collidedExtraLife);
		ExtraLifeCollision(collidedExtraLife, state);
		break;
	}
	case ActorType::Key:
	{
		Key* collidedKey = dynamic_cast<Key*>(collidedActor);
		assert(collidedKey);
		KeyCollision(collidedKey, state);
		break;
	}
	case ActorType::Door:
	{
		Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
		assert(collidedDoor);
		DoorCollision(collidedDoor, state);
		break;
	}
	case ActorType::Goal:
	{
		Goal* collidedGoal = dynamic_cast<Goal*>(collidedActor);
		assert(collidedGoal);
		GoalCollision(collidedGoal, state);
		break;
	}
	default:
		break;
	}
}

void CollisionHelper::EnemyCollision(Enemy* collidedEnemy, CollisionInfo& state)
{
	collidedEnemy->Remove();
	state.player.SetPosition(state.newPlayerX, state.newPlayerY);
	AudioManager::GetInstance()->PlayLoseLivesSound();
	state.player.DecrementLives();
	if (state.player.GetLives() < 0)
	{
		//TODO: Go to game over screen
		AudioManager::GetInstance()->PlayLoseSound();
		state.newScene = StateMachineExampleGame::SceneName::Lose;
	}
}

void CollisionHelper::MoneyCollision(Money* collidedMoney, CollisionInfo& state)
{
	AudioManager::GetInstance()->PlayMoneySound();
	collidedMoney->Remove();
	state.player.AddMoney(collidedMoney->GetWorth());
	state.player.SetPosition(state.newPlayerX, state.newPlayerY);

}

void CollisionHelper::ExtraLifeCollision(ExtraLife* collidedExtraLife, CollisionInfo& state)
{
	AudioManager::GetInstance()->PlayExtraLifeSound();
	state.player.IncrementLives();
	collidedExtraLife->Remove();
	state.player.SetPosition(state.newPlayerX, state.newPlayerY);

}

void CollisionHelper::KeyCollision(Key* collidedKey, CollisionInfo& state)
{
	if (!state.player.HasKey())
	{
		state.player.PickupKey(collidedKey);
		collidedKey->Remove();
		state.player.SetPosition(state.newPlayerX, state.newPlayerY);
		AudioManager::GetInstance()->PlayKeyPickupSound();
	}
}

void CollisionHelper::DoorCollision(Door* collidedDoor, CollisionInfo& state)
{
	if (!collidedDoor->IsOpen())
	{
		if (state.player.HasKey(collidedDoor->GetColor()))
		{
			collidedDoor->Open();
			collidedDoor->Remove();
			state.player.UseKey();
			state.player.SetPosition(state.newPlayerX, state.newPlayerY);
			AudioManager::GetInstance()->PlayDoorOpenSound();
		}
		else
		{
			AudioManager::GetInstance()->PlayDoorClosedSound();
		}
	}
	else
	{
		state.player.SetPosition(state.newPlayerX, state.newPlayerY);
	}
}

void CollisionHelper::GoalCollision(Goal* collidedGoal, CollisionInfo& state)
{
	collidedGoal->Remove();
	state.player.SetPosition(state.newPlayerX, state.newPlayerY);
	state.didBeatLevel = true;
}