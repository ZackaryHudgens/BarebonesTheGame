#include "BackgroundSpriteComponent.hpp"

#include <Environment.hpp>

#include <iostream>

using Barebones::BackgroundSpriteComponent;

/******************************************************************************/
BackgroundSpriteComponent::BackgroundSpriteComponent()
  : SpriteComponent()
{
  UrsineEngine::SpriteAnimationFrameChanged.Connect(*this, [this](const std::string& aName,
                                                                  int aFrame,
                                                                  UrsineEngine::SpriteComponent& aComponent)
  {
    this->HandleSpriteAnimationFrameChanged(aName,
                                            aFrame,
                                            aComponent);
  });
}

/******************************************************************************/
void BackgroundSpriteComponent::Initialize()
{
  // Load the background texture.
  UrsineEngine::Texture texture;
  texture.CreateTextureFromFile("resources/sprites/tempBG.png");
  SetTexture(texture);

  GetVertices().clear();
  auto width = env.GetGraphicsOptions().mOverlayWidth;
  auto height = env.GetGraphicsOptions().mOverlayHeight;

  UrsineEngine::MeshVertex vertex;
  vertex.mPosition = glm::vec3(0.0, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  AddVertex(vertex);

  vertex.mPosition = glm::vec3(width, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(1.0, 0.0);
  AddVertex(vertex);

  vertex.mPosition = glm::vec3(width, height, 0.0);
  vertex.mTexCoords = glm::vec2(1.0, 1.0);
  AddVertex(vertex);

  vertex.mPosition = glm::vec3(0.0, height, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 1.0);
  AddVertex(vertex);

  // Set the shader.
  std::string vertexFile = "resources/shaders/BackgroundShader.vert";
  std::string fragmentFile = "resources/shaders/BackgroundShader.frag";
  UrsineEngine::Shader defaultShader(vertexFile,
                                     fragmentFile);
  AddShader("defaultShader",
            defaultShader);
  SetCurrentShader("defaultShader");

  // Disable depth testing for this mesh.
  SetRenderOption(GL_DEPTH_TEST, false);

  // Render this sprite in screen space.
  SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

  // Finally, place it as far back on the z-axis as possible.
  auto newPos = GetParent()->GetPosition();
  GetParent()->SetPosition(glm::vec3(newPos.x,
                                     newPos.y,
                                     -0.9));
}

/******************************************************************************/
void BackgroundSpriteComponent::HandleSpriteAnimationFrameChanged(const std::string& aName,
                                                                  int aFrame,
                                                                  UrsineEngine::SpriteComponent& aComponent)
{
  if(&aComponent == this)
  {
    // Each time the animation frame advances, SpriteComponent recalculates
    // the mesh vertices to keep them on a normalized 0 to 1 scale.
    // For the background sprite, however, the vertices should always stretch
    // across the entire overly.
    GetVertices().clear();
    auto width = env.GetGraphicsOptions().mOverlayWidth;
    auto height = env.GetGraphicsOptions().mOverlayHeight;

    UrsineEngine::MeshVertex vertex;
    vertex.mPosition = glm::vec3(0.0, 0.0, 0.0);
    vertex.mTexCoords = glm::vec2(0.0, 0.0);
    AddVertex(vertex);

    vertex.mPosition = glm::vec3(width, 0.0, 0.0);
    vertex.mTexCoords = glm::vec2(1.0, 0.0);
    AddVertex(vertex);

    vertex.mPosition = glm::vec3(width, height, 0.0);
    vertex.mTexCoords = glm::vec2(1.0, 1.0);
    AddVertex(vertex);

    vertex.mPosition = glm::vec3(0.0, height, 0.0);
    vertex.mTexCoords = glm::vec2(0.0, 1.0);
    AddVertex(vertex);
  }
}
