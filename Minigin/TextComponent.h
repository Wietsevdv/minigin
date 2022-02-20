#pragma once
#include "Component.h"

namespace dae
{
	class Font;
	class Texture2D;
    class TextComponent final : public Component
    {
    public:
		const std::string& Name() const override { return m_Name; }

		virtual void Update(float deltaTime) override;

		void SetText(const std::string& text);
		void SetColor(Uint8 r, Uint8 g, Uint8 b);
		void SetPosition(float x, float y);
		const glm::vec3& GetPosition() const { return m_Transform.GetPosition(); }
		const Texture2D& GetTexture() const { return *m_TextTexture.get(); }

		explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		const std::string m_Name = "TextComponent";

		bool m_NeedsUpdate;
		std::string m_Text;
		SDL_Color m_Color;
		Transform m_Transform;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
    };
}