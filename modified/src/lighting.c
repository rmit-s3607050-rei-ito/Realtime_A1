#include "lighting.h"

LightPos lightPos[MAX_LIGHTS] = {
  { 1, 1, 1, 0 },
  { -1, 1, 1, 0 },
  { -1, -1, 1, 0 },
  { 1, -1, 1, 0 },
  { -1, -1, -1, 0 },
  { -1, 1, -1, 0 },
  { 1, 1, -1, 0 },
  { 1, -1, -1 ,0 },
};

void renderLights(int nLights)
{
  for (int i = 0; i <= nLights; i++)
    glLightfv(GL_LIGHT0+i, GL_POSITION, (float *)&lightPos[i]);
}

void enableLights(int nLights)
{
  for (int i = 0; i <= nLights; i++)
    glEnable(GL_LIGHT0+i);
}
