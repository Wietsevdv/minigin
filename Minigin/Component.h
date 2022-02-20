#pragma once
#include <string>
#include "Transform.h"

namespace dae
{
	class Component
	{
	public:
		virtual const std::string& Name() const = 0;

		virtual void Update(float deltaTime);
		void SetMarkedForDelete(bool state) { m_MarkedForDelete = state; }
		bool GetMarkedForDelete() const { return m_MarkedForDelete; }

		Component() = default;
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	private:
		const std::string m_Name = "Component";
		bool m_MarkedForDelete = false;
	};
}