#pragma once

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

void DebugOut(wchar_t *fmt, ...);
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define BRICK_TAG 41
#define BREAKABLEBRICK_TAG 13
#define ENEMY_TAG 500


#define BRICK_TYPE1 12
#define BRICK_TYPE2 -12
#define BREAKABLEBRICK_TYPE1 13
#define BREAKABLEBRICK_TYPE2 14
#define BOTSTAIR -7
#define TOPSTAIR 7
#define LARGECANDLE_TYPE 10
#define CANDLE_TYPE 11
#define ZOMBIE_TYPE 500
#define PANDER_TYPE 501
#define MERMAID_TYPE 502
#define BAT_TYPE 503
