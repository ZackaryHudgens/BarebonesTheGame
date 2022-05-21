#include "MainMenuLayoutComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>
#include <MeshComponent.hpp>

#include "Colors.hpp"

using Barebones::MainMenuLayoutComponent;

/******************************************************************************/
MainMenuLayoutComponent::MainMenuLayoutComponent()
  : MenuLayoutComponent()
  , mHoveredTextBox(nullptr)
  , mVerticalPadding(50)
{
}

/******************************************************************************/
void MainMenuLayoutComponent::HandleActionAdded()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a mesh for the background.
    auto backgroundMesh = std::make_unique<UrsineEngine::MeshComponent>();
    backgroundMesh->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);
    
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

    backgroundMesh->AddIndex(0);
    backgroundMesh->AddIndex(1);
    backgroundMesh->AddIndex(3);
    backgroundMesh->AddIndex(3);
    backgroundMesh->AddIndex(1);
    backgroundMesh->AddIndex(2);

    UrsineEngine::MeshVertex vertex;
    vertex.mColor = LIGHT_COLOR;
    vertex.mPosition = glm::vec3(0.0, 0.0, 0.0);
    backgroundMesh->AddVertex(vertex);
    vertex.mPosition = glm::vec3(overlayWidth, 0.0, 0.0);
    backgroundMesh->AddVertex(vertex);
    vertex.mPosition = glm::vec3(overlayWidth, overlayHeight, 0.0);
    backgroundMesh->AddVertex(vertex);
    vertex.mPosition = glm::vec3(0.0, overlayHeight, 0.0);
    backgroundMesh->AddVertex(vertex);

    std::string vertexShader = "resources/shaders/UntexturedMeshShader.vert";
    std::string fragmentShader = "resources/shaders/UntexturedMeshShader.frag";
    UrsineEngine::Shader shader(vertexShader, fragmentShader);
    backgroundMesh->AddShader("default", shader);
    backgroundMesh->SetCurrentShader("default");

    parent->AddComponent(std::move(backgroundMesh));

    // Create a new GameObject with a TextBoxComponent, then add it as a child.
    auto newAction = GetActions().back();
    auto actionObject = std::make_unique<UrsineEngine::GameObject>(newAction->GetName());
    actionObject->AddComponent(std::make_unique<TextBoxComponent>());
    parent->AddChild(std::move(actionObject));

    auto newActionTextBox = parent->GetChildren().back()->GetFirstComponentOfType<TextBoxComponent>();

    // Set the font parameters for this text box.
    newActionTextBox->SetFont("Alagard", "Medium");
    newActionTextBox->SetTextSize(48);
    newActionTextBox->SetTextAlignment(TextAlignment::eLEFT);
    newActionTextBox->SetTextColor(glm::vec4(BACKGROUND_COLOR, 1.0));
    newActionTextBox->SetWidth(500);
    newActionTextBox->SetFixedWidth(true);

    newActionTextBox->SetText(newAction->GetName());

    // Position the text box in the center of the screen.
    double xPos = overlayWidth / 2.0;
    double yPos = overlayHeight / 2.0;

    yPos -= (mVerticalPadding * mTextBoxes.size());

    newActionTextBox->GetParent()->SetPosition(glm::vec3(xPos, yPos, 0.1));
    mTextBoxes.emplace_back(newActionTextBox);
  }
}

/******************************************************************************/
void MainMenuLayoutComponent::HandleActionHovered()
{
}

/******************************************************************************/
void MainMenuLayoutComponent::HandleActionExecuted()
{
}
