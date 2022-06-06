#include "HealthBarMeshComponent.hpp"

#include <GameObject.hpp>

#include "Colors.hpp"
#include "Signals.hpp"

using Barebones::HealthBarMeshComponent;

/******************************************************************************/
HealthBarMeshComponent::HealthBarMeshComponent()
  : MeshComponent()
  , mCharacter(nullptr)
  , mCurrentFillValue(1.0)
  , mTargetFillValue(1.0)
  , mSpeed(0.1)
  , mMoving(false)
  , mBackgroundWidth(0.7)
  , mBackgroundHeight(0.1)
  , mVerticalPadding(0.03)
  , mHorizontalPadding(0.03)
{
  CharacterHealthChanged.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterHealthChanged(aCharacter);
  });
}

/******************************************************************************/
void HealthBarMeshComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    SetRenderOption(GL_DEPTH_TEST, false);

    std::string vertexFile = "resources/shaders/UntexturedMeshShader.vert";
    std::string fragmentFile = "resources/shaders/UntexturedMeshShader.frag";
    UrsineEngine::Shader defaultShader(vertexFile, fragmentFile);
    AddShader("default", defaultShader);
    SetCurrentShader("default");

    // Create vertices for the background.
    double leftEdge = -mBackgroundWidth / 2.0;
    double rightEdge = mBackgroundWidth / 2.0;
    double topEdge = mBackgroundHeight / 2.0;
    double bottomEdge = -mBackgroundHeight / 2.0;

    UrsineEngine::MeshVertex vertex;
    vertex.mPosition = glm::vec3(leftEdge, bottomEdge, 0.0);
    vertex.mColor = BACKGROUND_COLOR;
    AddVertex(vertex);
    vertex.mPosition = glm::vec3(rightEdge, bottomEdge, 0.0);
    AddVertex(vertex);
    vertex.mPosition = glm::vec3(rightEdge, topEdge, 0.0);
    AddVertex(vertex);
    vertex.mPosition = glm::vec3(leftEdge, topEdge, 0.0);
    AddVertex(vertex);

    AddIndex(0);
    AddIndex(1);
    AddIndex(3);
    AddIndex(3);
    AddIndex(1);
    AddIndex(2);

    // Create vertices for the foreground.
    leftEdge += mHorizontalPadding;
    rightEdge -= mHorizontalPadding;
    bottomEdge += mVerticalPadding;
    topEdge -= mVerticalPadding;

    vertex.mPosition = glm::vec3(leftEdge, bottomEdge, 0.0);
    vertex.mColor = FOREGROUND_COLOR;
    AddVertex(vertex);
    vertex.mPosition = glm::vec3(rightEdge, bottomEdge, 0.0);
    AddVertex(vertex);
    vertex.mPosition = glm::vec3(rightEdge, topEdge, 0.0);
    AddVertex(vertex);
    vertex.mPosition = glm::vec3(leftEdge, topEdge, 0.0);
    AddVertex(vertex);

    AddIndex(4);
    AddIndex(5);
    AddIndex(7);
    AddIndex(7);
    AddIndex(5);
    AddIndex(6);
  }
}

/******************************************************************************/
void HealthBarMeshComponent::Update(double aTime)
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

    GetVertices().clear();

    // Create vertices for the background.
    double leftEdge = -mBackgroundWidth / 2.0;
    double rightEdge = mBackgroundWidth / 2.0;
    double topEdge = mBackgroundHeight / 2.0;
    double bottomEdge = -mBackgroundHeight / 2.0;

    UrsineEngine::MeshVertex vertex;
    vertex.mPosition = glm::vec3(leftEdge, bottomEdge, 0.0);
    vertex.mColor = BACKGROUND_COLOR;
    AddVertex(vertex);
    vertex.mPosition = glm::vec3(rightEdge, bottomEdge, 0.0);
    AddVertex(vertex);
    vertex.mPosition = glm::vec3(rightEdge, topEdge, 0.0);
    AddVertex(vertex);
    vertex.mPosition = glm::vec3(leftEdge, topEdge, 0.0);
    AddVertex(vertex);

    // Create vertices for the foreground.
    leftEdge += mHorizontalPadding;
    rightEdge -= mHorizontalPadding;
    bottomEdge += mVerticalPadding;
    topEdge -= mVerticalPadding;

    auto healthBarWidth = mBackgroundWidth - (mHorizontalPadding * 2);
    auto fillAmount = healthBarWidth * mCurrentFillValue;
    rightEdge -= (healthBarWidth - fillAmount);

    rightEdge = std::max(leftEdge, rightEdge);
    rightEdge = std::min((healthBarWidth / 2.0), rightEdge);

    vertex.mPosition = glm::vec3(leftEdge, bottomEdge, 0.0);
    vertex.mColor = FOREGROUND_COLOR;
    AddVertex(vertex);
    vertex.mPosition = glm::vec3(rightEdge, bottomEdge, 0.0);
    AddVertex(vertex);
    vertex.mPosition = glm::vec3(rightEdge, topEdge, 0.0);
    AddVertex(vertex);
    vertex.mPosition = glm::vec3(leftEdge, topEdge, 0.0);
    AddVertex(vertex);
  }
}

/******************************************************************************/
void HealthBarMeshComponent::SetCharacter(CharacterBehaviorComponent& aCharacter)
{
  mCharacter = &aCharacter;
}

/******************************************************************************/
void HealthBarMeshComponent::HandleCharacterHealthChanged(CharacterBehaviorComponent& aCharacter)
{
  if(&aCharacter == mCharacter)
  {
    double maxHealth = aCharacter.GetMaximumHealth();
    double currentHealth = aCharacter.GetCurrentHealth();

    mTargetFillValue = currentHealth / maxHealth;
    mMoving = true;
  }
}
