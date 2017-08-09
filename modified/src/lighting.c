#include "lighting.h"

LightPos lightPos[MAX_LIGHTS];

void initLightPos()
{
  lightPos[0] = { 1, 1, 1, 0};
  lightPos[1] = { -1, 1, 1, 0 };
  lightPos[2] = { -1, -1, 1, 0 };
  lightPos[3] = { 1, -1, 1, 0 };
  lightPos[4] = { -1, -1, -1, 0 };
  lightPos[5] = { -1, 1, -1, 0 };
  lightPos[6] = { 1, 1, -1, 0 };
  lightPos[7] = { 1, -1, -1 ,0 };
}

void renderLights(int nLights)
{
  for (int i = 0; i <= nLights; i++)
    glLightfv(GL_LIGHT0+i, GL_POSITION, lightPos[i]);
}

void enableLights(int nLights)
{
  for (int i = 0; i <= nLights; i++)
    glEnable(GL_LIGHT0+i);
}
