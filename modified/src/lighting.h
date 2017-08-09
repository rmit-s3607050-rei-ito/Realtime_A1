#include "util.h"

#define MAX_LIGHTS 8

typedef struct
{
  static float pos[];
} LightPos;

void initLightPos();
void renderLights(int nLights);
void enableLights(int nLights);
