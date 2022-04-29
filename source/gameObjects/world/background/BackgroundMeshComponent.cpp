#include "BackgroundMeshComponent.hpp"

#include <Environment.hpp>

using Barebones::BackgroundMeshComponent;

/******************************************************************************/
BackgroundMeshComponent::BackgroundMeshComponent()
  : MeshComponent()
  , mHorizontalRepetition(3.0)
  , mVerticalRepetition(3.0)
  , mHorizontalScrollSpeed(-0.005)
  , mVerticalScrollSpeed(0.005)
{
}

/******************************************************************************/
void BackgroundMeshComponent::Update(double aTime)
{
  auto vertices = GetVertices();

  // If the first vertex has fully scrolled, then the whole background has
  // fully scrolled and needs to be reset.
  if(!vertices.empty())
  {
    auto firstTexCoords = vertices.front().mTexCoords;
    if(std::abs(firstTexCoords.x) >= mHorizontalRepetition &&
       std::abs(firstTexCoords.y) >= mVerticalRepetition)
    {
      // Reset the vertices.
      vertices[0].mTexCoords.x = 0.0;
      vertices[0].mTexCoords.y = 0.0;
      vertices[1].mTexCoords.x = mHorizontalRepetition;
      vertices[1].mTexCoords.y = 0.0;
      vertices[2].mTexCoords.x = mHorizontalRepetition;
      vertices[2].mTexCoords.y = mVerticalRepetition;
      vertices[3].mTexCoords.x = 0.0;
      vertices[3].mTexCoords.y = mVerticalRepetition;
    }
    else
    {
      for(auto& vertex : vertices)
      {
        vertex.mTexCoords.x += mHorizontalScrollSpeed;
        vertex.mTexCoords.y += mVerticalScrollSpeed;
      }
    }
  }

  GetVertices().clear();
  for(auto& vertex : vertices)
  {
    AddVertex(vertex);
  }
}

/******************************************************************************/
void BackgroundMeshComponent::Initialize()
{
  // Set the texture.
  UrsineEngine::Texture texture;
  texture.CreateTextureFromFile("resources/sprites/tempBG.png");
  AddTexture(texture);

  // Set the indices.
  AddIndex(0);
  AddIndex(1);
  AddIndex(3);
  AddIndex(3);
  AddIndex(1);
  AddIndex(2);

  // Add the vertices. Use the overlay dimensions to stretch the background
  // across the entire overlay.
  auto width = env.GetGraphicsOptions().mOverlayWidth;
  auto height = env.GetGraphicsOptions().mOverlayHeight;

  UrsineEngine::MeshVertex vertex;
  vertex.mPosition = glm::vec3(0.0, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, 0.0);
  AddVertex(vertex);

  vertex.mPosition = glm::vec3(width, 0.0, 0.0);
  vertex.mTexCoords = glm::vec2(mHorizontalRepetition, 0.0);
  AddVertex(vertex);

  vertex.mPosition = glm::vec3(width, height, 0.0);
  vertex.mTexCoords = glm::vec2(mHorizontalRepetition, mVerticalRepetition);
  AddVertex(vertex);

  vertex.mPosition = glm::vec3(0.0, height, 0.0);
  vertex.mTexCoords = glm::vec2(0.0, mVerticalRepetition);
  AddVertex(vertex);

  // Set the shader.
  std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
  std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
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
