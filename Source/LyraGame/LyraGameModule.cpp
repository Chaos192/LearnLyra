#include "Modules/ModuleManager.h"

class FLyraGameMode : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{

	}

	virtual void ShutdownModule() override
	{

	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FLyraGameMode, LyraGame, "LyraGame");