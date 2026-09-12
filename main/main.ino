// NES controller (4021 shift register) -> USB Gamepad via GamepadAPI
//
// Wiring:
//   1: White  (5V)
//   2: Yellow (clock)
//   3: Orange (latch)
//   4: Red    (data)
//   7: Brown  (ground)

#include "Gamepad.h"
#include "NesController.h"


namespace
{
  constexpr auto PowerLedPin = 0;

  constexpr unsigned long PollInterval = 16; // ~60Hz

  NesController controller;
  Gamepad gamepad;
  
  int lastButtonsValue = -1; // impossible value, guarantees first report
  int lastDirectionIndex = -1;

    /**
   * Array index map
   *
   * 0:  none                  -> centered
   * 1:  down                  -> down
   * 2:  right                 -> right
   * 3:  down+right            -> down-right
   * 4:  up                    -> up
   * 5:  down+up (invalid)     -> down
   * 6:  up+right              -> up-right
   * 7:  down+up+right (inv.)  -> right
   * 8:  left                  -> left
   * 9:  down+left             -> down-left
   * 10: left+right (invalid)  -> right
   * 11: (invalid)             -> down
   * 12: up+left               -> up-left
   * 13: (invalid)             -> left
   * 14: (invalid)             -> up
   * 15: (invalid)             -> centered
   */

  constexpr int8_t DpadFromDirectionIndex[16] = { 0, 5, 3, 4, 1, 5, 2, 3, 7, 6, 3, 5, 8, 7, 1, 0  };

  int directionIndex(const NesButtons &buttons)
  {
    return (buttons.down ? 1 : 0) + (buttons.right ? 2 : 0) + (buttons.up ? 4 : 0) + (buttons.left ? 8 : 0);
  }

  int buttonsValue(const NesButtons &buttons)
  {
    return (buttons.a ? 1 : 0) + (buttons.b ? 2 : 0) + (buttons.select ? 4 : 0) + (buttons.start ? 8 : 0);
  }
}


void pushHidReport(int button, int direction)
{
  // Only push a new HID report when something actually changed.
  if (button != lastButtonsValue || direction != lastDirectionIndex)
  {
    gamepad.buttons(button);
    gamepad.dPad(DpadFromDirectionIndex[direction]);
    gamepad.write();

    lastButtonsValue = button;
    lastDirectionIndex = direction;
  }
}


void enforcePollTiming(unsigned long elapsed)
{
    if (elapsed < PollInterval)
  {
    delay(PollInterval - elapsed);
  }
}


void setup()
{
  controller.begin();
  gamepad.begin();
  digitalWrite(PowerLedPin, HIGH);
}


void loop()
{
  const auto pollStart = millis();

  const auto buttons = controller.read();
  pushHidReport(buttonsValue(buttons), directionIndex(buttons));
  enforcePollTiming(millis() - pollStart);
}
