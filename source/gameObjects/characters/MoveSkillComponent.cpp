#include "MoveSkillComponent.hpp"

#include <algorithm>

#include <SpriteComponent.hpp>

#include "CharacterBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

using Barebones::MoveSkillComponent;

/******************************************************************************/
MoveSkillComponent::MoveSkillComponent()
  : CharacterSkillComponent()
{
  SetName("Move");
  SetDescription("Moves the character.");
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::MeshComponent> MoveSkillComponent::GetIcon()
{
  auto icon = std::make_unique<UrsineEngine::SpriteComponent>();

  // Create the texture.
  UrsineEngine::Texture sprite;
  sprite.CreateTextureFromFile("resources/sprites/bear.jpeg");
  icon->SetTexture(sprite);

  // Create the shader.
  std::string vertexFile = "resources/shaders/UIShader.vert";
  std::string fragmentFile = "resources/shaders/SkillActionShader.frag";
  UrsineEngine::Shader shader(vertexFile,
                              fragmentFile);

  // Initialize the glow color.
  shader.Activate();
  shader.SetVec4("glowColor",
                 glm::vec4(1.0,
                           1.0,
                           1.0,
                           1.0));
  icon->AddShader("defaultShader",
                  shader);
  icon->SetCurrentShader("defaultShader");

  // Display the icon in screen space.
  icon->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

  return icon;
}

/******************************************************************************/
bool MoveSkillComponent::IsTileValid(UrsineEngine::GameObject& aBoard,
                                     const TileLocation& aLocation)
{
  bool success = false;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto behaviorComp = parent->GetFirstComponentOfType<CharacterBehaviorComponent>();
    auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
    if(behaviorComp != nullptr)
    {
      auto currentLocation = boardLayoutComponent->GetLocationOfCharacter(parent->GetName());
      auto movements = behaviorComp->GetMovements(aBoard,
                                                  currentLocation);
      auto foundLocation = std::find(movements.begin(),
                                     movements.end(),
                                     aLocation);
      if(foundLocation != movements.end())
      {
        success = true;
      }
    }
  }

  return success;
}

/******************************************************************************/
void MoveSkillComponent::ProtectedSelect()
{
  auto character = GetParent();
  if(character != nullptr)
  {
    auto board = character->GetParent();
    if(board != nullptr)
    {
      // Highlight each tile that's valid for movement.
      auto boardLayoutComponent = board->GetFirstComponentOfType<BoardLayoutComponent>();
      auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(boardLayoutComponent != nullptr &&
         characterBehaviorComponent != nullptr)
      {
        auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(character->GetName());
        auto locations = characterBehaviorComponent->GetMovements(*board,
                                                                  characterLocation);

        for(const auto& location : locations)
        {
          auto tile = boardLayoutComponent->GetTileAtLocation(location);
          if(tile != nullptr)
          {
            auto tileBehaviorComponent = tile->GetFirstComponentOfType<TileBehaviorComponent>();
            if(tileBehaviorComponent != nullptr)
            {
              tileBehaviorComponent->SetHighlightColor(glm::vec3(1.0,
                                                                 1.0,
                                                                 0.0));
              tileBehaviorComponent->SetHighlighted(true);

              // Keep track of highlighted tiles to un-highlight them later.
              mHighlightedTiles.emplace_back(tileBehaviorComponent);
            }
          }
        }
      }
    }
  }
}

/******************************************************************************/
void MoveSkillComponent::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                          const TileLocation& aLocation)
{
  // Move this character to the given location on the board if it's valid.
  if(IsTileValid(aBoard,
                 aLocation))
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
      if(boardLayoutComponent != nullptr)
      {
        auto initialLocation = boardLayoutComponent->GetLocationOfCharacter(parent->GetName());
        boardLayoutComponent->MoveCharacter(initialLocation,
                                            aLocation);

        // Un-highlight each previously highlighted tile.
        for(auto& tile : mHighlightedTiles)
        {
          tile->SetHighlighted(false);
        }
        mHighlightedTiles.clear();
      }
    }
  }
}
