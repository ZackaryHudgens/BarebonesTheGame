#include "DefaultTileComponent.hpp"

using Barebones::DefaultTileComponent;

/******************************************************************************/
DefaultTileComponent::DefaultTileComponent()
  : TileBehaviorComponent()
{
}

/******************************************************************************/
void DefaultTileComponent::SetupVertexInfo(UrsineEngine::MeshComponent& aMesh)
{
  double xVal = mWidth / 2.0;
  double yVal = mHeight / 2.0;
  double zVal = mLength / 2.0;

  // Clear out any vertices that already exist on the mesh.
  aMesh.GetVertices().clear();

  // Create the 3D vertices for this cube.
  UrsineEngine::MeshVertex vertex;

  // Vertices for each face are defined in the following order:
  // 1) bottom left
  // 2) bottom right
  // 3) top right
  // 4) top left

  // Front face
  vertex.mPosition  = glm::vec3(-xVal, -yVal, zVal);
  vertex.mColor     = glm::vec3(1.0, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, zVal);
  vertex.mColor     = glm::vec3(0.0, 1.0, 0.0);
  vertex.mTexCoords = glm::vec2(1.0, 0.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, zVal);
  vertex.mColor     = glm::vec3(0.0, 0.0, 1.0);
  vertex.mTexCoords = glm::vec2(1.0, 1.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, zVal);
  vertex.mColor     = glm::vec3(1.0, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 1.0);
  aMesh.AddVertex(vertex);

  aMesh.AddIndex(0);
  aMesh.AddIndex(1);
  aMesh.AddIndex(3);
  aMesh.AddIndex(1);
  aMesh.AddIndex(2);
  aMesh.AddIndex(3);

  // Top face
  vertex.mPosition  = glm::vec3(-xVal, yVal, zVal);
  vertex.mColor     = glm::vec3(1.0, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, zVal);
  vertex.mColor     = glm::vec3(0.0, 1.0, 0.0);
  vertex.mTexCoords = glm::vec2(1.0, 0.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, -zVal);
  vertex.mColor     = glm::vec3(0.0, 0.0, 1.0);
  vertex.mTexCoords = glm::vec2(1.0, 1.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, -zVal);
  vertex.mColor     = glm::vec3(1.0, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 1.0);
  aMesh.AddVertex(vertex);

  aMesh.AddIndex(4);
  aMesh.AddIndex(5);
  aMesh.AddIndex(7);
  aMesh.AddIndex(5);
  aMesh.AddIndex(6);
  aMesh.AddIndex(7);

  // Back face
  vertex.mPosition  = glm::vec3(-xVal, -yVal, -zVal);
  vertex.mColor     = glm::vec3(1.0, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, -zVal);
  vertex.mColor     = glm::vec3(0.0, 1.0, 0.0);
  vertex.mTexCoords = glm::vec2(1.0, 0.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, -zVal);
  vertex.mColor     = glm::vec3(0.0, 0.0, 1.0);
  vertex.mTexCoords = glm::vec2(1.0, 1.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, -zVal);
  vertex.mColor     = glm::vec3(1.0, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 1.0);
  aMesh.AddVertex(vertex);

  aMesh.AddIndex(8);
  aMesh.AddIndex(9);
  aMesh.AddIndex(11);
  aMesh.AddIndex(9);
  aMesh.AddIndex(10);
  aMesh.AddIndex(11);

  // Left face
  vertex.mPosition  = glm::vec3(-xVal, -yVal, -zVal);
  vertex.mColor     = glm::vec3(1.0, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, -yVal, zVal);
  vertex.mColor     = glm::vec3(0.0, 1.0, 0.0);
  vertex.mTexCoords = glm::vec2(1.0, 0.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, zVal);
  vertex.mColor     = glm::vec3(0.0, 0.0, 1.0);
  vertex.mTexCoords = glm::vec2(1.0, 1.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, -zVal);
  vertex.mColor     = glm::vec3(1.0, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 1.0);
  aMesh.AddVertex(vertex);

  aMesh.AddIndex(12);
  aMesh.AddIndex(13);
  aMesh.AddIndex(15);
  aMesh.AddIndex(13);
  aMesh.AddIndex(14);
  aMesh.AddIndex(15);

  // Bottom face
  vertex.mPosition  = glm::vec3(-xVal, -yVal, -zVal);
  vertex.mColor     = glm::vec3(1.0, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, -zVal);
  vertex.mColor     = glm::vec3(0.0, 1.0, 0.0);
  vertex.mTexCoords = glm::vec2(1.0, 0.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, zVal);
  vertex.mColor     = glm::vec3(0.0, 0.0, 1.0);
  vertex.mTexCoords = glm::vec2(1.0, 1.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, -yVal, zVal);
  vertex.mColor     = glm::vec3(1.0, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 1.0);
  aMesh.AddVertex(vertex);

  aMesh.AddIndex(16);
  aMesh.AddIndex(17);
  aMesh.AddIndex(19);
  aMesh.AddIndex(17);
  aMesh.AddIndex(18);
  aMesh.AddIndex(19);

  // Right face
  vertex.mPosition  = glm::vec3(xVal, -yVal, -zVal);
  vertex.mColor     = glm::vec3(1.0, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, zVal);
  vertex.mColor     = glm::vec3(0.0, 1.0, 0.0);
  vertex.mTexCoords = glm::vec2(1.0, 0.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, zVal);
  vertex.mColor     = glm::vec3(0.0, 0.0, 1.0);
  vertex.mTexCoords = glm::vec2(1.0, 1.0);
  aMesh.AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, -zVal);
  vertex.mColor     = glm::vec3(1.0, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 1.0);
  aMesh.AddVertex(vertex);

  aMesh.AddIndex(20);
  aMesh.AddIndex(21);
  aMesh.AddIndex(23);
  aMesh.AddIndex(21);
  aMesh.AddIndex(22);
  aMesh.AddIndex(23);
}

/******************************************************************************/
void DefaultTileComponent::SetupTextureInfo(UrsineEngine::MeshComponent& aMesh)
{
  UrsineEngine::Texture defaultTexture;
  defaultTexture.CreateTextureFromFile("resources/textures/defaultTile.");
  aMesh.AddTexture(defaultTexture);
}

/******************************************************************************/
void DefaultTileComponent::SetupShaderInfo(UrsineEngine::MeshComponent& aMesh)
{
  std::string vertexFile = "resources/shaders/TileShader.vert";
  std::string fragmentFile = "resources/shaders/TileShader.frag";
  UrsineEngine::Shader textureShader(vertexFile, fragmentFile);
  aMesh.AddShader("textureShader", textureShader);
  aMesh.SetCurrentShader("textureShader");
}
