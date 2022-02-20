#include "TurnDisplayComponent.hpp"

#include <sstream>

#include <Environment.hpp>
#include <MeshComponent.hpp>
#include <TextComponent.hpp>

#include "BoardTurnManagerComponent.hpp"

using Barebones::TurnDisplayComponent;

/******************************************************************************/
TurnDisplayComponent::TurnDisplayComponent()
  : Component()
  , mDisplayTime(2.0)
  , mInitialDisplayTime(0.0)
  , mDisplayingText(false)
{
  PlayerTurnBegan.Connect(*this, [this](PlayerBehaviorComponent& aPlayer)
  {
    this->HandlePlayerTurnBegan(aPlayer);
  });
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
                                 -0.1);
    background->AddVertex(vertex);
    vertex.mPosition = glm::vec3(overlayWidth,
                                 0.0,
                                 -0.1);
    background->AddVertex(vertex);
    vertex.mPosition = glm::vec3(overlayWidth,
                                 overlayHeight,
                                 -0.1);
    background->AddVertex(vertex);
    vertex.mPosition = glm::vec3(0.0,
                                 overlayHeight,
                                 -0.1);
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
                    0.6f);
    background->AddShader("defaultShader",
                          shader);
    background->SetCurrentShader("defaultShader");

    auto backgroundObject = std::make_unique<UrsineEngine::GameObject>("turnDisplayBackground");
    backgroundObject->AddComponent(std::move(background));
    parent->AddChild(std::move(backgroundObject));
  }
}

/******************************************************************************/
void TurnDisplayComponent::Update()
{
  if(mDisplayingText)
  {
    double totalTime = env.GetTime() - mInitialDisplayTime;
    if(totalTime >= mDisplayTime)
    {
      mDisplayingText = false;

      auto parent = GetParent();
      if(parent != nullptr)
      {
        parent->ScheduleForDeletion();
      }
    }
  }
}

/******************************************************************************/
void TurnDisplayComponent::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto playerName = parent->GetChild("playerName");
    if(playerName != nullptr)
    {
      auto playerNameText = playerName->GetFirstComponentOfType<UrsineEngine::TextComponent>();
      if(playerNameText != nullptr)
      {
        std::stringstream ss;
        ss << aPlayer.GetName() << "'s Turn";
        playerNameText->SetText(ss.str());

        mDisplayingText = true;
        mInitialDisplayTime = env.GetTime();
      }
    }
  }
}
