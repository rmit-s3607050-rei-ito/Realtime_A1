#include "util.h"
#include "gl.h"

#define MAX_LIGHTS 8

typedef struct
{
  float x, y, z, a;
} LightPos;

void initLightPos();
void renderLights(int nLights);
void enableLights(int nLights);
