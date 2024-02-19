#pragma once

#define RGBLED_debug false

#if RGBLED_debug
#warning "RGBLED: Debugging messages are enabled."
#define RGBLED_DEBUG(...) Serial.print(__VA_ARGS__);
#define RGBLED_DEBUGLN(...) Serial.println(__VA_ARGS__);
#else
#define RGBLED_DEBUG(...)
#define RGBLED_DEBUGLN(...)
#endif
