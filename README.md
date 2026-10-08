# NES2USB

An Atmega32U4 based USB Adapter for NES controllers. Physical prototypes are built using the Sparkfun Pro Micro based generic boards commonly available on Amazon and AliExpress, etc.

## License

MIT License. See LICENSE for details.

## How To Build

For the build that is used here, the following boards from Amazon were used: [Arduino Pro Micro generic](https://www.amazon.com/dp/B09J2FLLD7)

These are based on the Sparkfun Pro Micro but with a USB-C port instead of MicroUSB. The USB-C port was preferred for our builds as we have tons of these cables lying around and it was easier to shape our 3D printed housings (not part of this repository).

*NOTE: The links here are examples of what to get, these are not direct recommendations. Make your own choice based on your needs and budget.*

### Wiring

![NES Controller Pinout](/doc/NES-controller-pinout.gif)

**Pinout**
* Pin 1: Ground
* Pin 2: Clock
* Pin 3: Latch
* Pin 4: Data
* Pin 5: VCC +5v


### Wiring to the Arduino

The boards linked above are by default set to 5v. This is what we want as the NES controller uses +5v for operation.

![NES to Arduino Wiring Guide](/doc/pro-micro-wiring.gif)

**Wiring**

*NES Port -> Arduino Pin*

* Latch -> Pin 2
* Clock -> Pin 3
* Data 0 -> Pin 4
* Ground -> GND
* VCC -> VCC

*OPTIONAL: RXI pin is used for LED+ as it's right next to a ground pin for a pin header that we use here to indicate power if you build this into a case. This is entirely optional.*
