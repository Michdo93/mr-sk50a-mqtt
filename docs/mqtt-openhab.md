# MQTT and openHAB

## MQTT topics

The ESP32 publishes:

```text
mr-sk50a/event
mr-sk50a/state
mr-sk50a/status
```

### Event

When the MR-SK50A output becomes active:

```text
mr-sk50a/event = ON
```

This is a momentary event.

### State

While the MR-SK50A output is active:

```text
mr-sk50a/state = ON
```

After the MR-SK50A switches its output off:

```text
mr-sk50a/state = OFF
```

### Status

The ESP32 publishes a retained:

```text
mr-sk50a/status = online
```

## openHAB

The example configuration uses an MQTT Thing and Channels for:

- event
- state
- device status

Import or adapt:

```text
openhab/mr_sk50a.things
openhab/mr_sk50a.items
```

The MQTT broker itself is expected to be configured separately in openHAB.
