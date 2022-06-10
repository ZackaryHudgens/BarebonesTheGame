#ifndef MENUACTION_HPP
#define MENUACTION_HPP

#include <functional>
#include <string>

namespace Barebones
{
  class MenuAction
  {
    public:

      /**
       * Constructor.
       *
       * @param aName The name for this action.
       * @param aDescription An optional description of this action.
       */
      MenuAction(const std::string& aName, const std::string& aDescription = "");

      /**
       * Executes this action.
       */
      void Execute();

      /**
       * Sets the function to call when this action is executed.
       *
       * @param aFunction The function to call.
       */
      void SetFunction(const std::function<void()>& aFunction) { mFunction = aFunction; }

      /**
       * Returns the name of this action.
       *
       * @return The name of this action.
       */
      std::string GetName() const { return mName; }

      /**
       * Returns the description of this action.
       *
       * @return The description of this action.
       */
      std::string GetDescription() const { return mDescription; }

      /**
       * Enables/disables this action.
       *
       * @param aEnabled Whether to enable or disable this action.
       */
      void SetEnabled(bool aEnabled);

      /**
       * Returns whether this action is enabled.
       *
       * @return Whether this action is enabled.
       */
      bool IsEnabled() const { return mEnabled; }

    private:
      std::string mName;
      std::string mDescription;

      std::function<void()> mFunction;

      bool mEnabled;
  };
}

#endif
