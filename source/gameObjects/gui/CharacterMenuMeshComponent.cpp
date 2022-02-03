#include "CharacterMenuMeshComponent.hpp"

using Barebones::CharacterMenuMeshComponent;

/******************************************************************************/
CharacterMenuMeshComponent::CharacterMenuMeshComponent()
  : MeshComponent()
  , mWidth(1200)
  , mHeight(70)
{
  // Since this is a 2D quad, the vertex draw order will
  // never change.
  AddIndex(0);
  AddIndex(1);
  AddIndex(3);
  AddIndex(1);
  AddIndex(2);
  AddIndex(3);
}

/******************************************************************************/
void CharacterMenuMeshComponent::Initialize()
{
  SetupVertices();
  SetupTextures();
  SetupShaders();

  SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);
}

/******************************************************************************/
void CharacterMenuMeshComponent::SetWidth(int aWidth)
{
  mWidth = aWidth;
  SetupVertices();
}

/******************************************************************************/
void CharacterMenuMeshComponent::SetHeight(int aHeight)
{
  mHeight = aHeight;
  SetupVertices();
}

/******************************************************************************/
void CharacterMenuMeshComponent::SetupVertices()
{
  // Clear out any vertices that already exist.
  GetVertices().clear();

  UrsineEngine::MeshVertex vertex;

  // Bottom left
  vertex.mPosition  = glm::vec3(0.0,
                                0.0,
                                0.0);
  vertex.mTexCoords = glm::vec2(0.0,
                                0.0);
  AddVertex(vertex);

  // Bottom right
  vertex.mPosition  = glm::vec3((double)mWidth,
                                0.0,
                                0.0);
  vertex.mTexCoords = glm::vec2(1.0,
                                0.0);
  AddVertex(vertex);

  // Top right
  vertex.mPosition  = glm::vec3((double)mWidth,
                                (double)mHeight,
                                0.0);
  vertex.mTexCoords = glm::vec2(1.0,
                                1.0);
  AddVertex(vertex);

  // Top left
  vertex.mPosition  = glm::vec3(0.0,
                                (double)mHeight,
                                0.0);
  vertex.mTexCoords = glm::vec2(0.0,
                                1.0);
  AddVertex(vertex);
}

/******************************************************************************/
void CharacterMenuMeshComponent::SetupTextures()
{
  // Clear out any previous textures.
  GetTextures().clear();

  UrsineEngine::Texture spritesheet;
  spritesheet.CreateTextureFromFile("resources/sprites/menuBox.png");
  AddTexture(spritesheet);
}

/******************************************************************************/
void CharacterMenuMeshComponent::SetupShaders()
{
  std::string vertexFile = "resources/shaders/UIShader.vert";
  std::string fragmentFile = "resources/shaders/UIShader.frag";
  UrsineEngine::Shader defaultShader(vertexFile,
                                     fragmentFile);

  AddShader("defaultShader", defaultShader);
  SetCurrentShader("defaultShader");
}
