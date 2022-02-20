#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"

void dae::RenderComponent::Render(const Texture2D& texture, const glm::vec3& pos) const
{
	Renderer::GetInstance().RenderTexture(texture, pos.x, pos.y);
}