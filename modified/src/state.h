#pragma once

#include "player.h"
#include "level.h"
#include "controls.h"
#include "mesh.h"
#include "camera.h"
#include "counters.h"

/*
 * All of the global state for our main functions is declared here
 */
typedef struct {
  Player player;
  Level level;
  Controls controls;
  Camera camera;
  DrawingFlags drawingFlags;
  Counters counters;
  bool halt;
  int wantRedisplay;
  SDL_Window *window;
  bool debug;
  bool bench;
  bool OSD;
  int timePast;
  int nLights;
} Globals;
