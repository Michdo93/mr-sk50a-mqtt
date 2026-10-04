# Wiring

## Functional wiring

The intended signal path is:

```text
230 V AC
   │
   ▼
MR-SK50A
(sound + light sensor)
   │
   │ switched mains output
   ▼
isolated AC detector
   │
   │ SELV / isolated logic
   ▼
ESP32 GPIO
   │
   ▼
Wi-Fi / MQTT
   │
   ▼
openHAB
```

## Important

The exact MR-SK50A terminal arrangement varies between versions. Many versions expose separate mains input and switched-load connections.

**Do not wire the device based only on a generic four-wire diagram. Read the markings on your physical MR-SK50A first.**

If the terminal markings are unclear, take a photo of the actual device and verify them before applying mains voltage.

## ESP32 side

Only the detector's documented low-voltage output is connected to the ESP32.

Example:

```text
AC detector LOW-VOLTAGE OUTPUT ───> ESP32 GPIO 27
AC detector LOW-VOLTAGE GND    ───> ESP32 GND
```

The above is only valid if the selected detector explicitly specifies a common low-voltage ground and an ESP32-compatible output.

If the detector has a relay contact or another interface instead, wire it according to that module's datasheet.

## Voltage conversion / isolation

There is no software-based “voltage conversion”.

The electrical conversion happens inside the isolated AC detector.

Conceptually:

```text
230 V AC
   │
   │ galvanically isolated sensing
   ▼
low-voltage logic signal
   │
   ▼
ESP32 3.3 V GPIO
```

The exact low-voltage level depends on the selected detector module.

**Never connect the 230 V output of the MR-SK50A directly to an ESP32 GPIO.**

## No lamp is required

The project does not use a lamp.

The AC detector acts as the load/sensing device connected to the MR-SK50A output.

Before installation, verify that the detector input is an acceptable load for the MR-SK50A. Do not assume this from the detector's small physical size alone.
