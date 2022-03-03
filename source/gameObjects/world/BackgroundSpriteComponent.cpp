#include "BackgroundSpriteComponent.hpp"

#include <Environment.hpp>

using Barebones::BackgroundSpriteComponent;

/******************************************************************************/
BackgroundSpriteComponent::BackgroundSpriteComponent()
  : SpriteComponent()
{
}

/******************************************************************************/
void BackgroundSpriteComponent::Initialize()
{
  // Load the background texture.
  UrsineEngine::Texture texture;
  texture.CreateTextureFromFile("resources/sprites/tempBG.png");
  SetTexture(texture);

  // Set the shader.
  std::string vertexFile = "resources/shaders/BackgroundShader.vert";
  std::string fragmentFile = "resources/shaders/BackgroundShader.frag";
  UrsineEngine::Shader defaultShader(vertexFile,
                                     fragmentFile);
  AddShader("defaultShader",
            defaultShader);
  SetCurrentShader("defaultShader");

  GetParent()->SetScale(glm::vec3(10000.0, 10000.0, 1.0));

  // Disable depth testing for this mesh.
  SetRenderOption(GL_DEPTH_TEST, false);

  // Render this sprite in screen space.
  SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);
}
