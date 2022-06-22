#ifndef HINTDISPLAYTAKINGTURNSTATE_HPP
#define HINTDISPLAYTAKINGTURNSTATE_HPP

#include "HintDisplayState.hpp"

#include <GameObject.hpp>
#include <Observer.hpp>

#include "TextBoxComponent.hpp"

#include "Skill.hpp"

namespace Barebones
{
  class HintDisplayTakingTurnState : public HintDisplayState
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The parent GameObject that owns this state.
       */
      HintDisplayTakingTurnState(UrsineEngine::GameObject& aParent);

      /**
       * Gets called by the hint display when it enters this state.
       */
      void OnEnter() override;

      /**
       * Gets called by the hint display when it exits this state.
       */
      void OnExit() override;

    private:

      /**
       * Creates and places the pause icon and text.
       */
      void CreatePauseIconAndText();

      /**
       * Creates and places the select keyboard icon and text.
       */
      void CreateSelectIconAndText();

      /**
       * Creates and places the end turn icon and text.
       */
      void CreateEndTurnIconAndText();

      /**
       * Creates and places the zoom keyboard icon and text.
       */
      void CreateZoomIconAndText();

      /**
       * Creates a GameObject with a SpriteComponent using the given
       * file as a texture.
       *
       * @param aName The name of the new GameObject.
       * @param aFile The file to use as a texture.
       * @return A new GameObject.
       */
      std::unique_ptr<UrsineEngine::GameObject> CreateIconObject(const std::string& aName,
                                                                 const std::string& aFile);

      /**
       * Creates a GameObject with a TextBoxComponent using the given
       * text.
       *
       * @param aName The name of the new GameObject.
       * @param aText The text to display.
       * @return A new GameObject.
       */
      std::unique_ptr<UrsineEngine::GameObject> CreateTextObject(const std::string& aName,
                                                                 const std::string& aText);

      /**
       * A handler function that gets called whenever a skill is selected
       * for use.
       *
       * @param aSkill The skill that was selected.
       */
      void HandleSkillSelected(Skill& aSkill);

      /**
       * A handler function that gets called whenever a skill is executed.
       *
       * @param aSkill The skill that was executed.
       */
      void HandleSkillExecuted(Skill& aSkill);

      /**
       * A handler function that gets called whenever a skill is cancelled.
       *
       * @param aSkill The skill that was cancelled.
       */
      void HandleSkillCancelled(Skill& aSkill);

      std::vector<UrsineEngine::GameObject*> mElements;

      TextBoxComponent* mEndTurnText;

      int mElementPadding;
      double mIconScale;

      UrsineEngine::Observer mObserver;
  };
}

#endif
