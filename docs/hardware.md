# Hardware

## MR-SK50A

The MR-SK50A is the actual acoustic trigger in this project.

Typical product-family specifications:

- 180–265 V AC
- 50/60 Hz
- up to approximately 40 W load
- acoustic detection around 50–70 dB
- roughly 6 m detection range
- light threshold around 10 lux
- approximately 40–50 s delay
- IP22

The exact variant must be checked before installation.

## ESP32

Any ESP32 board with a 3.3 V GPIO can be used if it has:

- Wi-Fi
- one available digital GPIO
- USB power

The example firmware uses GPIO 27.

## AC detector

Use a **galvanically isolated AC presence detector** with:

- an input explicitly rated for the intended mains voltage;
- sufficient isolation rating;
- a documented low-voltage output;
- an output compatible with the chosen ESP32 input;
- an input/load suitable for connection to the MR-SK50A switched output.

Do not assume that all modules sold as “AC detection modules” have the same pinout or output voltage.

A ZMPT101B-style analog voltage transformer module is not the default choice for this project because this application only needs a reliable binary “mains present” signal.

## Power supply

Power the ESP32 separately through USB or another suitable SELV supply.

The ESP32 power supply must not be derived from an improvised mains circuit.
