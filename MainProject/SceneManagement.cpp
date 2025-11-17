#include "stdafx.h"

#include "SceneManagement.h"
#include "Scenes/MainScene.h"

void SceneManagement::Initialize()
{
#ifdef _DEBUG
	infoDisplay.active     = true;
	infoDisplay.watermark  = true;
	infoDisplay.fpsinfo    = true;
	infoDisplay.resolution = false;
	infoDisplay.heap_allocation_counter = false;
	infoDisplay.vram_usage = true;
	infoDisplay.size       = 15;
#endif
	if (!SetCurrentDirectory(L"Assets"))
		SetCurrentDirectory(L"../Assets");

	HE::Application::Initialize();
	scene_loader_.Load(NextScene::StartScene);
}

std::unique_ptr<HE::Scene> SceneManagement::CreateScene(const NextScene nextScene)
{
	std::unique_ptr<HE::Scene> scene;
	switch (nextScene) {
	case NextScene::MainScene:	scene = std::make_unique<MainScene>();	break;
	}
	return scene;
}

void SceneManagement::SetNextScene(const NextScene nextScene, float fadeSeconds, HE::Color fadeColor)
{
	auto temp_scene = CreateScene(nextScene);
	RenderingPath = temp_scene.get();
	temp_scene->Load();
	temp_scene->init(canvas);
	temp_scene->Initialize();

	next_scene_ = std::move(temp_scene);
	RenderingPath = scene_.get();

	fade_seconds_ = fadeSeconds;
	fade_color_   = fadeColor;
	is_transition = false;
}

void SceneManagement::TransitionScene()
{
	if (next_scene_) {
		if (!is_transition) {
			ActivatePath(next_scene_.get(), fade_seconds_, fade_color_);
			if (fade_seconds_ <= 0.0f) {
				scene_ = std::move(next_scene_);
				RenderingPath = scene_.get();
			}
			else {
				is_transition = true;
			}
		}
		else {
			if (GetActivePath() == next_scene_.get()) {
				scene_ = std::move(next_scene_);
				RenderingPath = scene_.get();
			}
		}
	}
}

