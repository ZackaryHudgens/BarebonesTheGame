#include "SpellMenuLayoutComponent.hpp"

#include <GameObject.hpp>
#include <SpriteComponent.hpp>

using Barebones::SpellMenuLayoutComponent;

/******************************************************************************/
SpellMenuLayoutComponent::SpellMenuLayoutComponent()
  : MenuLayoutComponent()
{
}

/******************************************************************************/
void SpellMenuLayoutComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a sprite and add it to the parent.
    auto spellbookSprite = std::make_unique<UrsineEngine::SpriteComponent>();
    spellbookSprite->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    UrsineEngine::Texture texture;
    texture.CreateTextureFromFile("resources/sprites/spellbook.png");
    spellbookSprite->SetTexture(texture);

    std::string vertexFile = "resources/shaders/UIShader.vert";
    std::string fragmentFile = "resources/shaders/UIShader.frag";
    UrsineEngine::Shader shader(vertexFile, fragmentFile);
    spellbookSprite->AddShader("default", shader);
    spellbookSprite->SetCurrentShader("default");

    parent->AddComponent(std::move(spellbookSprite));
  }
}
