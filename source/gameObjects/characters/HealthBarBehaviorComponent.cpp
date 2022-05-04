#include "HealthBarBehaviorComponent.hpp"

#include <GameObject.hpp>

#include "Colors.hpp"
#include "Signals.hpp"

using Barebones::HealthBarBehaviorComponent;

/******************************************************************************/
HealthBarBehaviorComponent::HealthBarBehaviorComponent()
  : Component()
  , mBackgroundMesh(nullptr)
  , mForegroundMesh(nullptr)
  , mCharacter(nullptr)
  , mCurrentFillValue(1.0)
  , mTargetFillValue(1.0)
  , mSpeed(0.1)
  , mMoving(false)
  , mBackgroundWidth(0.7)
  , mBackgroundHeight(0.1)
  , mVerticalPadding(0.02)
  , mHorizontalPadding(0.03)
{
  CharacterHealthChanged.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterHealthChanged(aCharacter);
  });
}

/******************************************************************************/
void HealthBarBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create the health bar background mesh.
    auto backgroundMesh = std::make_unique<UrsineEngine::MeshComponent>();
    backgroundMesh->SetRenderOption(GL_DEPTH_TEST, false);

    std::string vertexFile = "resources/shaders/UntexturedMeshShader.vert";
    std::string fragmentFile = "resources/shaders/UntexturedMeshShader.frag";
    UrsineEngine::Shader defaultShader(vertexFile, fragmentFile);
    backgroundMesh->AddShader("default", defaultShader);
    backgroundMesh->SetCurrentShader("default");

    double width = mBackgroundWidth / 2.0;
    double height = mBackgroundHeight / 2.0;

    UrsineEngine::MeshVertex vertex;
    vertex.mPosition = glm::vec3(-width, -height, 0.0);
    vertex.mColor = BACKGROUND_COLOR;
    backgroundMesh->AddVertex(vertex);
    vertex.mPosition = glm::vec3(width, -height, 0.0);
    backgroundMesh->AddVertex(vertex);
    vertex.mPosition = glm::vec3(width, height, 0.0);
    backgroundMesh->AddVertex(vertex);
    vertex.mPosition = glm::vec3(-width, height, 0.0);
    backgroundMesh->AddVertex(vertex);

    backgroundMesh->AddIndex(0);
    backgroundMesh->AddIndex(1);
    backgroundMesh->AddIndex(3);
    backgroundMesh->AddIndex(3);
    backgroundMesh->AddIndex(1);
    backgroundMesh->AddIndex(2);

    parent->AddComponent(std::move(backgroundMesh));
    mBackgroundMesh = parent->GetComponentsOfType<UrsineEngine::MeshComponent>().back();

    // Create the health bar foreground mesh.
    auto foregroundMesh = std::make_unique<UrsineEngine::MeshComponent>();
    foregroundMesh->SetRenderOption(GL_DEPTH_TEST, false);

    vertexFile = "resources/shaders/HealthBarFillShader.vert";
    fragmentFile = "resources/shaders/HealthBarFillShader.frag";
    UrsineEngine::Shader healthBarShader(vertexFile, fragmentFile);
    healthBarShader.Activate();
    healthBarShader.SetFloat("fillValue", 1.0);
    healthBarShader.SetFloat("leftEdge", (-width + mHorizontalPadding));
    foregroundMesh->AddShader("default", healthBarShader);
    foregroundMesh->SetCurrentShader("default");

    width -= (mHorizontalPadding * 2);
    height -= (mVerticalPadding * 2);

    vertex.mPosition = glm::vec3(-width, -height, 0.0);
    vertex.mColor = FOREGROUND_COLOR;
    foregroundMesh->AddVertex(vertex);
    vertex.mPosition = glm::vec3(width, -height, 0.0);
    foregroundMesh->AddVertex(vertex);
    vertex.mPosition = glm::vec3(width, height, 0.0);
    foregroundMesh->AddVertex(vertex);
    vertex.mPosition = glm::vec3(-width, height, 0.0);
    foregroundMesh->AddVertex(vertex);

    foregroundMesh->AddIndex(0);
    foregroundMesh->AddIndex(1);
    foregroundMesh->AddIndex(3);
    foregroundMesh->AddIndex(3);
    foregroundMesh->AddIndex(1);
    foregroundMesh->AddIndex(2);

    parent->AddComponent(std::move(foregroundMesh));
    mForegroundMesh = parent->GetComponentsOfType<UrsineEngine::MeshComponent>().back();
  }
}

/******************************************************************************/
void HealthBarBehaviorComponent::Update(double aTime)
{
  if(mMoving)
  {
    mCurrentFillValue = glm::mix(mCurrentFillValue,
                                 mTargetFillValue,
                                 mSpeed);
    if(std::abs(mTargetFillValue - mCurrentFillValue) <= 0.005)
    {
      mCurrentFillValue = mTargetFillValue;
      mMoving = false;
    }

    if(mForegroundMesh != nullptr)
    {
      auto shader = mForegroundMesh->GetCurrentShader();
      if(shader != nullptr)
      {
        shader->Activate();
        shader->SetFloat("fillValue", mCurrentFillValue);
      }
    }
  }
}

/******************************************************************************/
void HealthBarBehaviorComponent::SetCharacter(CharacterBehaviorComponent& aCharacter)
{
  mCharacter = &aCharacter;
}

/******************************************************************************/
void HealthBarBehaviorComponent::HandleCharacterHealthChanged(CharacterBehaviorComponent& aCharacter)
{
  if(&aCharacter == mCharacter)
  {
    double maxHealth = aCharacter.GetMaximumHealth();
    double currentHealth = aCharacter.GetCurrentHealth();

    mTargetFillValue = currentHealth / maxHealth;
    mMoving = true;
  }
}
