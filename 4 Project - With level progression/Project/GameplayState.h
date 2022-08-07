#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"

#include <windows.h>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>


class StateMachineExampleGame;

class GameplayState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	
	Player m_player;
	Level* m_pLevel;

	bool m_didBeatLevel;
	int m_skipFrameCount;
	static constexpr int kFramesToSkip = 2;

	int m_currentLevel;

	std::vector<std::string> m_LevelNames;

public:
	GameplayState(StateMachineExampleGame* pOwner);
	~GameplayState();

	virtual void Enter() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;
protected:
	void ProcessInput() override;
	void CheckBeatLevel();

private:
	void RedrawThreadingInitial();
	void ProcessInputThreadingInitial();
	void HandleCollision(int newPlayerX, int newPlayerY, bool proccessInput = false);
	bool Load();
	void DrawHUD(const HANDLE& console);

	std::mutex m_collisionGuard;
	std::mutex m_DrawGuard;
	std::mutex m_CVSleepGuard;
	std::mutex m_ProcessInputGuard;

	std::condition_variable m_CVSleep;
};
