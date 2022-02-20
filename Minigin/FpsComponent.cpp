#include "MiniginPCH.h"
#include "FpsComponent.h"

int dae::FpsComponent::m_Frames = 0;
float dae::FpsComponent::m_TimePassed = 0;
float dae::FpsComponent::m_Fps = 0;

void dae::FpsComponent::Update(float deltaTime)
{
	++m_Frames;
	m_TimePassed += deltaTime;

	if (m_TimePassed > 0.05f && m_Frames > 5) // the two magical nr here are used to slow down "showing" of the fps. Otherwise it would change constantly making it unreadable
	{
		m_Fps = m_Frames / m_TimePassed;
		m_TimePassed = 0;
		m_Frames = 0;
	}
}