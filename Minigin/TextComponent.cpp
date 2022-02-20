#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font)
	: m_NeedsUpdate{true}
	, m_Text{text}
	, m_Color{ 255,255,255 }
	, m_Font{font}
	, m_TextTexture{nullptr}
{
	Update(0.0f); // This update call is necessary to fill in "m_TextTexture". Otherwise this will be a nullptr when render is called
}

void dae::TextComponent::Update(float deltaTime)
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;

		++deltaTime; // "unreferenced formal parameter" error
	}
}

void dae::TextComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	m_Color = { r, g, b };
	m_NeedsUpdate = true;
}