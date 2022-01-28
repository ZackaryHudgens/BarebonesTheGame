#ifndef FPSDISPLAY_HPP
#define FPSDISPLAY_HPP

#include <TextComponent.hpp>

namespace Barebones
{
  class FPSDisplay : public UrsineEngine::TextComponent
  {
    public:
      FPSDisplay();

      void Update() override;

    private:
      double mLastUpdateTime;
      int mFrameCount;
  };
}

#endif
