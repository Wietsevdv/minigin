#pragma once
#include "Transform.h"
#include "Component.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FpsComponent.h"
#include <list>
#include <typeinfo>

namespace dae
{
	class TextureComponent;
}

namespace dae
{
	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject() = default;

		void Update(float deltaTime);
		void Render() const;

		void SetMarkedForRemove(bool state) { m_MarkedForRemove = state; }
		bool GetMarkedForRemove() const { return m_MarkedForRemove; }

		template <typename T> void AddComponent()
		{
			// make an instance of the component.
			auto component = std::make_shared<T>();

			// add the instance to the vector
			m_Components.push_back(component);

			// this could probably be done prettier using 'T', but I haven't figured out how yet
			if (m_Components.back()->Name() == "TextureComponent")
				m_HasTexture = true;
			if (m_Components.back()->Name() == "FpsComponent")
				m_HasFps = true;
		};

		template <typename T> void AddComponent(const std::string& text, const std::shared_ptr<Font>& font)
		{
			// make an instance of the component.
			auto textComponent = std::make_shared<TextComponent>(text, font);

			// add the instance to the vector
			m_Components.push_back(textComponent);

			m_HasText = true;
		};

		template <typename T> T* GetComponent() const
		{
			//------this function doesn't work, template specialization below--------

			//T* toReturn{};
			//size_t nrOfComponents = m_Components.size();
			//for (size_t i{}; i < nrOfComponents; ++i)
			//{
			//	const type_info& ti1 = typeid(T);
			//	const type_info& ti2 = typeid(T);
			//	if (ti1 == ti2)
			//	{
			//		toReturn = dynamic_cast<T*>(m_Components[i].get());
			//		break;
			//	}
			//}
			//return toReturn;
		};

		template <typename T> void RemoveComponent()
		{
		};

		void SetParent(std::shared_ptr<GameObject> parent) { m_Parent = parent; }
		std::shared_ptr<GameObject> GetParent() const { return m_Parent; }

		size_t GetChildCount() const { return m_ChildCount; }
		std::shared_ptr<GameObject> GetChildAt(int index) const;
		void RemoveChild(int index);
		void AddChild(std::shared_ptr<GameObject> child) { m_Children.push_back(child); }

	private:
		std::shared_ptr<GameObject> m_Parent;
		std::list<std::shared_ptr<GameObject>> m_Children;
		size_t m_ChildCount = 0;

		std::list<std::shared_ptr<dae::Component>> m_Components{};
		
		bool m_HasTexture{false}, m_HasText{false}, m_HasFps{false};
		bool m_MarkedForRemove{ false };
	};
}

template<>
inline dae::TextureComponent* dae::GameObject::GetComponent<dae::TextureComponent>() const
{
	dae::TextureComponent* toReturn{};

	for (const auto& component : m_Components)
	{
		if (component.get()->Name() == "TextureComponent")
		{
			toReturn = dynamic_cast<dae::TextureComponent*>(component.get());
			break;
		}
	}

	return toReturn;
}

template<>
inline dae::RenderComponent* dae::GameObject::GetComponent<dae::RenderComponent>() const
{
	dae::RenderComponent* toReturn{};

	for (const auto& component : m_Components)
	{
		if (component.get()->Name() == "RenderComponent")
		{
			toReturn = dynamic_cast<dae::RenderComponent*>(component.get());
			break;
		}
	}

	return toReturn;
}

template<>
inline dae::TextComponent* dae::GameObject::GetComponent<dae::TextComponent>() const
{
	dae::TextComponent* toReturn{};

	for (const auto& component : m_Components)
	{
		if (component.get()->Name() == "TextComponent")
		{
			toReturn = dynamic_cast<dae::TextComponent*>(component.get());
			break;
		}
	}

	return toReturn;
}

template<>
inline dae::FpsComponent* dae::GameObject::GetComponent<dae::FpsComponent>() const
{
	dae::FpsComponent* toReturn{};

	for (const auto& component : m_Components)
	{
		if (component.get()->Name() == "FpsComponent")
		{
			toReturn = dynamic_cast<dae::FpsComponent*>(component.get());
			break;
		}
	}

	return toReturn;
}

template<>
inline void dae::GameObject::RemoveComponent<dae::TextureComponent>()
{
	for (const auto& component : m_Components)
	{
		if (component.get()->Name() == "TextureComponent")
			m_Components.remove(component);
	}
}

template<>
inline void dae::GameObject::RemoveComponent<dae::RenderComponent>()
{
	for (const auto& component : m_Components)
	{
		if (component.get()->Name() == "RenderComponent")
			m_Components.remove(component);
	}
}

template<>
inline void dae::GameObject::RemoveComponent<dae::TextComponent>()
{
	for (const auto& component : m_Components)
	{
		if (component.get()->Name() == "TextComponent")
			m_Components.remove(component);
	}
}

template<>
inline void dae::GameObject::RemoveComponent<dae::FpsComponent>()
{
	for (const auto& component : m_Components)
	{
		if (component.get()->Name() == "FpsComponent")
			m_Components.remove(component);
	}
}