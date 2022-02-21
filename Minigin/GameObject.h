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

	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject() = default;

		void Update(float deltaTime);
		void Render() const;

		void SetMarkedForRemove(bool state) { m_MarkedForRemove = state; }
		bool GetMarkedForRemove() const { return m_MarkedForRemove; }

		template <typename T> T* AddComponent()
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

			return dynamic_cast<T*>(m_Components.back().get());
		};

		template <typename T> T* AddComponent(const std::string& text, const std::shared_ptr<Font>& font)
		{
			// make an instance of the component.
			auto textComponent = std::make_shared<TextComponent>(text, font);

			// add the instance to the vector
			m_Components.push_back(textComponent);

			m_HasText = true;

			return dynamic_cast<T*>(m_Components.back().get());
		};

		template <typename T> T* GetComponent() const
		{
			T* toReturn = nullptr;

			for (const auto& component : m_Components)
			{
				toReturn = dynamic_cast<T*>(component.get());

				if (toReturn != nullptr)
					break;
			}

			return toReturn;
		};

		template <typename T> void RemoveComponent()
		{
			T* toRemove = nullptr;

			for (auto& component : m_Components)
			{
				toRemove = dynamic_cast<T*>(component.get());

				if (toRemove != nullptr)
					component.get()->SetMarkedForDelete(true);
			}
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