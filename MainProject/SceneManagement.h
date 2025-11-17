#pragma once

#include "HEToolKit\HEToolKit.h"
#include <memory>

enum class NextScene : int {
	MainScene,
	StartScene = MainScene
};

class SceneManagement : public HE::Application
{
public:
	SceneManagement()
		: fade_seconds_(0.0f), fade_color_(), is_transition(false), scene_loader_(this) {}
	virtual ~SceneManagement() = default;

	void Initialize() override;

	void SetNextScene(const NextScene nextScene, float fadeSeconds = 0, HE::Color fadeColor = HE::Color(0, 0, 0, 255));
	void TransitionScene();

	inline HE::RenderPath* GetRenderPath() const { return scene_.get(); }
	inline void OnCaptureChanged() { timer.record(); }

private:
	std::unique_ptr<HE::Scene> CreateScene(const NextScene nextScene);

	std::unique_ptr<HE::Scene> scene_;
	std::unique_ptr<HE::Scene> next_scene_;

	float     fade_seconds_;
	HE::Color fade_color_;
	bool      is_transition;

	class SceneLoader : public HE::RenderPath {
	public:
		SceneLoader(SceneManagement* scene_manager)
			: scene_manager_(scene_manager), scene_(nullptr), is_initializing_(false) {}
		virtual ~SceneLoader() { wi::jobsystem::Wait(job_context_); };

		void Load(const NextScene load_scene)
		{
			scene_ = scene_manager_->CreateScene(load_scene);
			RenderingPath = scene_.get();
			scene_->Load();
			scene_manager_->ActivatePath(this);
		}

		void PostUpdate()
		{
			if (!wi::initializer::IsInitializeFinished())
				return;

			if (is_initializing_) {
				if (!wi::jobsystem::IsBusy(job_context_)) {
					scene_manager_->next_scene_ = std::move(scene_);
				}
			}
			else {
				//wi::jobsystem::Execute(job_context_, [&](wi::jobsystem::JobArgs args)
				//	{
						scene_->init(scene_manager_->canvas);
						scene_->Initialize();
					//}
				//);
				is_initializing_ = true;
			}
		}

	private:
		friend class SceneManagement;
		SceneManagement*           scene_manager_;
		std::unique_ptr<HE::Scene> scene_;
		bool                       is_initializing_;
		wi::jobsystem::context     job_context_;
	} scene_loader_;
};

extern SceneManagement SceneManager;
