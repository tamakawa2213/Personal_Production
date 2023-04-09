#include "RootJob.h"
#include "SceneManager.h"
#include "../../IntegratedEngine/Engine/Debug.h"
#include "../../IntegratedEngine/Engine/RootUI.h"

RootJob::RootJob(GameObject* parent) : GameObject()
{
}

RootJob::RootJob(GameObject* parent, const std::string& name) : GameObject(parent, name)
{
}

RootJob::~RootJob()
{
}

void RootJob::Initialize()
{
	Instantiate<RootUI>(this);
	Instantiate<SceneManager>(this);
}

void RootJob::DebugMode()
{
	Debug::BranchMode();
}
