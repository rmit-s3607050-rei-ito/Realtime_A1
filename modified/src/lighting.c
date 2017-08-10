#include "lighting.h"

GLfloat lightDefault[] = { 0.25, 0.25, 0.25, 0.0 };

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
  for (int i = 0; i < nLights; i++)
  {
    glLightfv(GL_LIGHT0+i, GL_POSITION, (float *)&lightPos[i]);
    glLightfv(GL_LIGHT0+i, GL_AMBIENT, lightDefault);
    glLightfv(GL_LIGHT0+i, GL_DIFFUSE, lightDefault);
  }
}

void enableLights(int nLights)
{
  for (int i = 0; i < nLights; i++)
  {
    glEnable(GL_LIGHT0+i);
  }
}

void disableLights(int nLights)
{
  for (int i = MAX_LIGHTS; nLights <= i; i--)
  {
    glDisable(GL_LIGHT0+i);
  }
}
