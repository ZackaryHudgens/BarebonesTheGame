#include "FPSDisplay.hpp"

#include <sstream>

#include <Environment.hpp>

using Barebones::FPSDisplay;

/******************************************************************************/
FPSDisplay::FPSDisplay()
  : TextComponent()
  , mLastUpdateTime(0.0)
  , mFrameCount(0)
{
  LoadFont("resources/Roboto-Regular.ttf");
  SetFont("Roboto", "Regular");
  SetSize(24);
  SetText("nothin' yet");
  SetColor(glm::vec4(1.0,
                     0.0,
                     1.0,
                     1.0));
  SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);
}

/******************************************************************************/
void FPSDisplay::Update()
{
  ++mFrameCount;

  double time = env.GetTime();
  double dt = time - mLastUpdateTime;
  if(dt >= 1.0)
  {
    std::stringstream ss;
    ss << "FPS: " << (double)mFrameCount / dt;
    SetText(ss.str());

    mLastUpdateTime = time;
    mFrameCount = 0;
  }
}
