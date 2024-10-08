#pragma once

#include <core/input/drivers/buttons.h>
#include <core/input/drivers/keyboard.h>
#include <core/utils/bit_capacity.hpp>
#include <core/window.h>

namespace input
{
  class WinKeyboard: public IKeyboard
  {
    public:
      virtual
      auto setButtonState(const int key, const bool pressed) -> bool;

      virtual
      auto isButtonPressed(const int key) const -> bool;

    private:
      utils::BitCapacity<BKEY_KEYBOARD_COUNT> m_Buttons;
  };

  class WinKeyboardDriver: public IKeyboardDriver, wnd::IWndProcHandler
  {
    public:
      WinKeyboardDriver();
      virtual
      ~WinKeyboardDriver();

      virtual
      void handleWndEvent(void* hwnd,
                          unsigned int msg,
                          unsigned long long wParam,
                          long long lParam) override;

      virtual
      void setListener(IKeyboardListener* listener) override { m_Listener = listener; }

    private:
      IKeyboardListener* m_Listener = nullptr;
      WinKeyboard m_Kb;
  };
}
