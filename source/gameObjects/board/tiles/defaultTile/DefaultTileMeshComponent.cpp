#include "DefaultTileMeshComponent.hpp"

using Barebones::DefaultTileMeshComponent;

/******************************************************************************/
DefaultTileMeshComponent::DefaultTileMeshComponent()
  : TileMeshComponent()
{
}

/******************************************************************************/
void DefaultTileMeshComponent::LoadVertices()
{
  double xVal = mWidth / 2.0;
  double yVal = mHeight / 2.0;
  double zVal = mLength / 2.0;

  // Clear out any vertices that already exist.
  GetVertices().clear();

  // Create the 3D vertices for this tile.
  UrsineEngine::MeshVertex vertex;

  // Vertices for each face are defined in the following order:
  // 1) bottom left
  // 2) bottom right
  // 3) top right
  // 4) top left

  // Front face
  vertex.mPosition  = glm::vec3(-xVal, -yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, zVal);
  vertex.mTexCoords = glm::vec2(1.0, 0.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, zVal);
  vertex.mTexCoords = glm::vec2(1.0, 1.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.0, 1.0);
  AddVertex(vertex);

  AddIndex(0);
  AddIndex(1);
  AddIndex(3);
  AddIndex(1);
  AddIndex(2);
  AddIndex(3);

  // Top face
  vertex.mPosition  = glm::vec3(-xVal, yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, zVal);
  vertex.mTexCoords = glm::vec2(1.0, 0.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, -zVal);
  vertex.mTexCoords = glm::vec2(1.0, 1.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.0, 1.0);
  AddVertex(vertex);

  AddIndex(4);
  AddIndex(5);
  AddIndex(7);
  AddIndex(5);
  AddIndex(6);
  AddIndex(7);

  // Back face
  vertex.mPosition  = glm::vec3(-xVal, -yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, -zVal);
  vertex.mTexCoords = glm::vec2(1.0, 0.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, -zVal);
  vertex.mTexCoords = glm::vec2(1.0, 1.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.0, 1.0);
  AddVertex(vertex);

  AddIndex(8);
  AddIndex(9);
  AddIndex(11);
  AddIndex(9);
  AddIndex(10);
  AddIndex(11);

  // Left face
  vertex.mPosition  = glm::vec3(-xVal, -yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, -yVal, zVal);
  vertex.mTexCoords = glm::vec2(1.0, 0.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, zVal);
  vertex.mTexCoords = glm::vec2(1.0, 1.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.0, 1.0);
  AddVertex(vertex);

  AddIndex(12);
  AddIndex(13);
  AddIndex(15);
  AddIndex(13);
  AddIndex(14);
  AddIndex(15);

  // Bottom face
  vertex.mPosition  = glm::vec3(-xVal, -yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, -zVal);
  vertex.mTexCoords = glm::vec2(1.0, 0.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, zVal);
  vertex.mTexCoords = glm::vec2(1.0, 1.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, -yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.0, 1.0);
  AddVertex(vertex);

  AddIndex(16);
  AddIndex(17);
  AddIndex(19);
  AddIndex(17);
  AddIndex(18);
  AddIndex(19);

  // Right face
  vertex.mPosition  = glm::vec3(xVal, -yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, zVal);
  vertex.mTexCoords = glm::vec2(1.0, 0.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, zVal);
  vertex.mTexCoords = glm::vec2(1.0, 1.0);
  AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.0, 1.0);
  AddVertex(vertex);

  AddIndex(20);
  AddIndex(21);
  AddIndex(23);
  AddIndex(21);
  AddIndex(22);
  AddIndex(23);
}

/******************************************************************************/
void DefaultTileMeshComponent::LoadTextures()
{
}

/******************************************************************************/
void DefaultTileMeshComponent::LoadShaders()
{
  std::string vertexFile = "resources/shaders/TileShader.vert";
  std::string fragmentFile = "resources/shaders/TileShader.frag";
  UrsineEngine::Shader textureShader(vertexFile, fragmentFile);
  AddShader("textureShader", textureShader);
  SetCurrentShader("textureShader");
}
