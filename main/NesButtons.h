#pragma once

// Named button reads, in the order the 4021 shifts them out.
struct NesButtons
{
    static constexpr int Count = 8;

    NesButtons(const bool buttons[Count])
    {
        memcpy(this, buttons, Count);
    }

    bool a { false };
    bool b { false };
    bool select { false };
    bool start { false };
    bool up { false };
    bool down { false };
    bool left { false };
    bool right { false };
};
