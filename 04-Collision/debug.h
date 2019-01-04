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


#define LBORDER_1 0
#define RBORDER_1 850
#define LBORDER_2 60
#define RBORDER_2 2500
#define LBOSSBORDER 4154
#define RBORDER_2 5069
#define yWATER 500
#define xBOSS 5500

//ITEM TAG 
#define HEART_TAG 100
#define BALL_TAG 101
#define DOUBLE_TAG 102
#define INVI_TAG 103
#define BLUEBLAG_TAG 104
#define REDBAG_TAG 105
#define WHITEBAG_TAG 106
#define WHIP_TAG 107
#define ROAST_TAG  108
#define ROSARY_TAG  109
#define SHEART_TAG 110
#define STOPWATCH_TAG 111
#define TRIPLE_TAG  112
#define KNIFE_TAG  113
#define AXE_TAG  114
#define HOLYWATER_TAG 115
#define CROSS_TAG 116















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
#define DOOR_TYPE 20
