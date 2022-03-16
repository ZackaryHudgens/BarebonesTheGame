#include "TurnDisplayComponent.hpp"

#include <sstream>

#include <Environment.hpp>
#include <MeshComponent.hpp>
#include <TextComponent.hpp>

#include "Signals.hpp"

#include "BoardTurnManagerComponent.hpp"

#include "PlayerBehaviorComponent.hpp"

using Barebones::TurnDisplayComponent;

/******************************************************************************/
TurnDisplayComponent::TurnDisplayComponent()
  : Component()
  , mNameText(nullptr)
  , mBackground(nullptr)
  , mDisplayTime(1.0)
  , mInitialDisplayTime(0.0)
  , mDisplaying(false)
{
}

/******************************************************************************/
void TurnDisplayComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

    // Add the player name text.
    auto playerName = std::make_unique<UrsineEngine::TextComponent>();
    playerName->SetFont("Alagard", "Medium");
    playerName->SetSize(48);
    playerName->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    auto nameObject = std::make_unique<UrsineEngine::GameObject>("playerName");
    nameObject->AddComponent(std::move(playerName));
    parent->AddChild(std::move(nameObject));

    mNameText = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::TextComponent>();

    // Add the transparent black background.
    auto background = std::make_unique<UrsineEngine::MeshComponent>();
    background->SetHasTransparency(true);
    background->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    UrsineEngine::MeshVertex vertex;
    vertex.mColor = glm::vec3(0.0,
                              0.0,
                              0.0);

    vertex.mPosition = glm::vec3(0.0,
                                 0.0,
                                 0.0);
    background->AddVertex(vertex);
    vertex.mPosition = glm::vec3(overlayWidth,
                                 0.0,
                                 0.0);
    background->AddVertex(vertex);
    vertex.mPosition = glm::vec3(overlayWidth,
                                 overlayHeight,
                                 0.0);
    background->AddVertex(vertex);
    vertex.mPosition = glm::vec3(0.0,
                                 overlayHeight,
                                 0.0);
    background->AddVertex(vertex);

    background->AddIndex(0);
    background->AddIndex(1);
    background->AddIndex(3);
    background->AddIndex(3);
    background->AddIndex(1);
    background->AddIndex(2);

    std::string uiVert = "resources/shaders/UIShader.vert";
    std::string uiFrag = "resources/shaders/UIShader.frag";
    UrsineEngine::Shader shader(uiVert,
                                uiFrag);
    shader.Activate();
    shader.SetFloat("opacity",
                    0.0f);
    background->AddShader("defaultShader",
                          shader);
    background->SetCurrentShader("defaultShader");

    auto backgroundObject = std::make_unique<UrsineEngine::GameObject>("turnDisplayBackground");
    backgroundObject->AddComponent(std::move(background));
    backgroundObject->SetPosition(glm::vec3(0.0, 0.0, -0.1));
    parent->AddChild(std::move(backgroundObject));

    mBackground = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
  }
}

/******************************************************************************/
void TurnDisplayComponent::Update()
{
  if(mDisplaying)
  {
    double totalTime = env.GetTime() - mInitialDisplayTime;
    if(totalTime >= mDisplayTime)
    {
      mDisplaying = false;

      if(mBackground != nullptr &&
         mNameText != nullptr)
      {
        auto shader = mBackground->GetCurrentShader();
        if(shader != nullptr)
        {
          shader->Activate();
          shader->SetFloat("opacity",
                           0.0f);
        }
        mNameText->SetText("");
      }

      auto parent = GetParent();
      if(parent != nullptr)
      {
        parent->ScheduleForDeletion();
        TurnDisplayFinished.Notify(*this);
      }
    }
  }
}

/******************************************************************************/
void TurnDisplayComponent::DisplayMessageForPlayer(UrsineEngine::GameObject& aPlayer)
{
  auto playerBehaviorComponent = aPlayer.GetFirstComponentOfType<PlayerBehaviorComponent>();
  if(playerBehaviorComponent != nullptr &&
     mNameText != nullptr)
  {
    std::stringstream ss;
    ss << playerBehaviorComponent->GetName() << "'s Turn";
    mNameText->SetText(ss.str());

    mBackground->GetCurrentShader()->Activate();
    mBackground->GetCurrentShader()->SetFloat("opacity",
                                              0.6f);

    mDisplaying = true;
    mInitialDisplayTime = env.GetTime();
  }
}
