#include "lighting.h"

// Colors used for ambient and diffuse lighting
GLfloat lightDefault[] = { 0.25, 0.25, 0.25, 0.0 };

// Lighting position based on cube verticies (as required in assignment specifications)
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
  // Loop through number of lights to render and apply positioning and ambient/diffuse
  for (int i = 0; i < nLights; i++)
  {
    glLightfv(GL_LIGHT0+i, GL_POSITION, (float *)&lightPos[i]);
    glLightfv(GL_LIGHT0+i, GL_AMBIENT, lightDefault);
    glLightfv(GL_LIGHT0+i, GL_DIFFUSE, lightDefault);
  }
}

// Add extra light sources (max 8)
void enableLights(int nLights)
{
  for (int i = 0; i < nLights; i++)
  {
    glEnable(GL_LIGHT0+i);
  }
}

// Reduce number of light sources by one (min 1)
void disableLights(int nLights)
{
  for (int i = MAX_LIGHTS; nLights <= i; i--)
  {
    glDisable(GL_LIGHT0+i);
  }
}
