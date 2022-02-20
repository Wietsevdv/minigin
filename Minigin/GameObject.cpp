#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include <memory>
#include "string"

void dae::GameObject::Update(float deltaTime)
{
	for (auto& component : m_Components)
	{
		component->Update(deltaTime);
	}

	for (auto& component : m_Components)
	{
		if (component->GetMarkedForDelete())
			m_Components.remove(component);
	}

	for (auto& child : m_Children)
	{
		if (child->GetMarkedForRemove())
			m_Children.remove(child);
	}

	if (m_HasFps)
	{
		int fps = this->GetComponent<FpsComponent>()->GetFps();
		std::string fpsText = std::to_string(fps) + " FPS";

		this->GetComponent<TextComponent>()->SetText(fpsText);
	}
}

void dae::GameObject::Render() const
{
	if (m_HasTexture)
	{
		const auto& pos = this->GetComponent<TextureComponent>()->GetPosition();
		const auto& texture = this->GetComponent<TextureComponent>()->GetTexture();

		this->GetComponent<RenderComponent>()->Render(texture, pos);
	}

	if (m_HasText)
	{
		const auto& pos = this->GetComponent<TextComponent>()->GetPosition();
		const auto& texture = this->GetComponent<TextComponent>()->GetTexture();
		
		this->GetComponent<RenderComponent>()->Render(texture, pos);
	}
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(int index) const
{
	std::shared_ptr<dae::GameObject> toReturn;
	int indexToReach = 0;
	for (const auto& child : m_Children)
	{
		if (index == indexToReach)
		{
			toReturn = child;
			break;
		}

		++indexToReach;
	}
	return toReturn;
}

void dae::GameObject::RemoveChild(int index)
{
	std::shared_ptr<dae::GameObject> toReturn;
	int indexToReach = 0;
	for (const auto& child : m_Children)
	{
		if (index == indexToReach)
		{
			child->SetMarkedForRemove(true);
			break;
		}

		++indexToReach;
	}
}