#pragma once
#include "Component.h"
#include <chrono>

namespace dae
{
    class FpsComponent : public Component
    {
    public:
		const std::string& Name() const override { return m_Name; }

		virtual void Update(float deltaTime) override;
		int GetFps() const { return int(m_Fps); }

		FpsComponent() = default;
		virtual ~FpsComponent() = default;
		FpsComponent(const FpsComponent& other) = delete;
		FpsComponent(FpsComponent&& other) = delete;
		FpsComponent& operator=(const FpsComponent& other) = delete;
		FpsComponent& operator=(FpsComponent&& other) = delete;

	private:
		const std::string m_Name = "FpsComponent";

		static int m_Frames;
		static float m_TimePassed;
		static float m_Fps;
    };
}