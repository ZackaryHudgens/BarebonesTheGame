#include "TileFactory.hpp"

#include <MeshComponent.hpp>

#include "DefaultTileBehaviorComponent.hpp"
#include "DesecratedTileBehaviorComponent.hpp"

using Barebones::TileFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> TileFactory::CreateTile(const TileType& aType,
                                                                  const std::string& aName)
{
  auto newTile = std::make_unique<UrsineEngine::GameObject>(aName);

  // The tile mesh is created the same way for each type of tile, so go ahead
  // and set it up now.
  auto tileMesh = std::make_unique<UrsineEngine::MeshComponent>();

  // Create the 3D vertices for this tile.
  UrsineEngine::MeshVertex vertex;

  // Vertices for each face are defined in the following order:
  // 1) bottom left corner
  // 2) bottom right corner
  // 3) top right corner
  // 4) top left corner

  double xVal = 0.5;
  double yVal = 0.5;
  double zVal = 0.5;

  // Front face
  vertex.mPosition  = glm::vec3(-xVal, -yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.33, 0.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.66, 0.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.66, 1.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.33, 1.0);
  tileMesh->AddVertex(vertex);

  tileMesh->AddIndex(0);
  tileMesh->AddIndex(1);
  tileMesh->AddIndex(3);
  tileMesh->AddIndex(1);
  tileMesh->AddIndex(2);
  tileMesh->AddIndex(3);

  // Top face
  vertex.mPosition  = glm::vec3(-xVal, yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.33, 0.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.33, 1.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.0, 1.0);
  tileMesh->AddVertex(vertex);

  tileMesh->AddIndex(4);
  tileMesh->AddIndex(5);
  tileMesh->AddIndex(7);
  tileMesh->AddIndex(5);
  tileMesh->AddIndex(6);
  tileMesh->AddIndex(7);

  // Back face
  vertex.mPosition  = glm::vec3(-xVal, -yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.33, 0.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.66, 0.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.66, 1.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.33, 1.0);
  tileMesh->AddVertex(vertex);

  tileMesh->AddIndex(8);
  tileMesh->AddIndex(9);
  tileMesh->AddIndex(11);
  tileMesh->AddIndex(9);
  tileMesh->AddIndex(10);
  tileMesh->AddIndex(11);

  // Left face
  vertex.mPosition  = glm::vec3(-xVal, -yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.33, 0.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, -yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.66, 0.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.66, 1.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.33, 1.0);
  tileMesh->AddVertex(vertex);

  tileMesh->AddIndex(12);
  tileMesh->AddIndex(13);
  tileMesh->AddIndex(15);
  tileMesh->AddIndex(13);
  tileMesh->AddIndex(14);
  tileMesh->AddIndex(15);

  // Bottom face
  vertex.mPosition  = glm::vec3(-xVal, -yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.66, 0.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, -zVal);
  vertex.mTexCoords = glm::vec2(1.0, 0.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, zVal);
  vertex.mTexCoords = glm::vec2(1.0, 1.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(-xVal, -yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.66, 1.0);
  tileMesh->AddVertex(vertex);

  tileMesh->AddIndex(16);
  tileMesh->AddIndex(17);
  tileMesh->AddIndex(19);
  tileMesh->AddIndex(17);
  tileMesh->AddIndex(18);
  tileMesh->AddIndex(19);

  // Right face
  vertex.mPosition  = glm::vec3(xVal, -yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.33, 0.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, -yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.66, 0.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, zVal);
  vertex.mTexCoords = glm::vec2(0.66, 1.0);
  tileMesh->AddVertex(vertex);
  vertex.mPosition  = glm::vec3(xVal, yVal, -zVal);
  vertex.mTexCoords = glm::vec2(0.33, 1.0);
  tileMesh->AddVertex(vertex);

  tileMesh->AddIndex(20);
  tileMesh->AddIndex(21);
  tileMesh->AddIndex(23);
  tileMesh->AddIndex(21);
  tileMesh->AddIndex(22);
  tileMesh->AddIndex(23);

  switch(aType)
  {
    case TileType::eDEFAULT:
    {
      newTile->AddComponent(std::make_unique<DefaultTileBehaviorComponent>());

      // Set up the shader and add it to the tile mesh.
      std::string vertexFile = "resources/shaders/TileShader.vert";
      std::string fragmentFile = "resources/shaders/TileShader.frag";
      UrsineEngine::Shader tileShader(vertexFile, fragmentFile);

      tileShader.Activate();
      tileShader.SetVec4("highlightColor", glm::vec4(1.0,
                                                     1.0,
                                                     1.0,
                                                     1.0));
      tileShader.SetVec4("hoverColor", glm::vec4(1.0,
                                                 1.0,
                                                 1.0,
                                                 1.0));
      tileShader.SetVec4("fadeInColor", glm::vec4(0.89, 0.93, 0.75, 1.0));

      tileMesh->AddShader("tileShader", tileShader);
      tileMesh->SetCurrentShader("tileShader");

      // Add the texture to the tile mesh.
      UrsineEngine::Texture brickTexture;
      brickTexture.CreateTextureFromFile("resources/sprites/tileTemplate.png");
      tileMesh->AddTexture(brickTexture);

      break;
    }
    case TileType::eDESECRATED:
    {
      newTile->AddComponent(std::make_unique<DesecratedTileBehaviorComponent>());

      // Set up the shader and add it to the tile mesh.
      std::string vertexFile = "resources/shaders/TileShader.vert";
      std::string fragmentFile = "resources/shaders/TileShader.frag";
      UrsineEngine::Shader tileShader(vertexFile, fragmentFile);

      tileShader.Activate();
      tileShader.SetVec4("highlightColor", glm::vec4(1.0,
                                                     1.0,
                                                     1.0,
                                                     1.0));
      tileShader.SetVec4("hoverColor", glm::vec4(1.0,
                                                 1.0,
                                                 1.0,
                                                 1.0));
      tileShader.SetVec4("fadeInColor", glm::vec4(0.89, 0.93, 0.75, 1.0));

      tileMesh->AddShader("tileShader", tileShader);
      tileMesh->SetCurrentShader("tileShader");

      // Add the texture to the tile mesh.
      UrsineEngine::Texture brickTexture;
      brickTexture.CreateTextureFromFile("resources/sprites/desecratedTile.png");
      tileMesh->AddTexture(brickTexture);

      break;
    }
    default:
    {
      break;
    }
  }

  // Finally, add the tile mesh.
  newTile->AddComponent(std::move(tileMesh));

  return std::move(newTile);
}
