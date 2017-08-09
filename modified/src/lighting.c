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
  //for (int i = 0; i <= nLights; i++)
  //  glLightfv(GL_LIGHT0+i, GL_POSITION, (float *)&lightPos[i]);
  //printf("%d\n", nLights);

  glLightfv(GL_LIGHT0, GL_POSITION, (float *)&lightPos[0]);
  //glLightfv(GL_LIGHT1, GL_POSITION, (float *)&lightPos[1]);
  //glLightfv(GL_LIGHT2, GL_POSITION, (float *)&lightPos[2]);
  //glLightfv(GL_LIGHT3, GL_POSITION, (float *)&lightPos[3]);
  //glLightfv(GL_LIGHT4, GL_POSITION, (float *)&lightPos[4]);
  //glLightfv(GL_LIGHT5, GL_POSITION, (float *)&lightPos[5]);
  //glLightfv(GL_LIGHT6, GL_POSITION, (float *)&lightPos[6]);
  //glLightfv(GL_LIGHT7, GL_POSITION, (float *)&lightPos[7]);

  //switch (nLights)
  //{
  //  case 8:
  //    glLightfv(GL_LIGHT7, GL_POSITION, (float *)&lightPos[7]);
  //  case 7:
  //    glLightfv(GL_LIGHT6, GL_POSITION, (float *)&lightPos[6]);
  //  case 6:
  //    glLightfv(GL_LIGHT5, GL_POSITION, (float *)&lightPos[5]);
  //  case 5:
  //    glLightfv(GL_LIGHT4, GL_POSITION, (float *)&lightPos[4]);
  //  case 4:
  //    glLightfv(GL_LIGHT3, GL_POSITION, (float *)&lightPos[3]);
  //  case 3:
  //    glLightfv(GL_LIGHT2, GL_POSITION, (float *)&lightPos[2]);
  //  case 2:
  //    glLightfv(GL_LIGHT1, GL_POSITION, (float *)&lightPos[1]);
  //  case 1:
  //    glLightfv(GL_LIGHT0, GL_POSITION, (float *)&lightPos[0]);
  //    break;
  //  default:
  //    break;
  //}
}

void enableLights(int nLights)
{
  //switch (nLights)
  //{
  //  case 8:
  //    glEnable(GL_LIGHT7);
  //  case 7:
  //    glEnable(GL_LIGHT6);
  //  case 6:
  //    glEnable(GL_LIGHT5);
  //  case 5:
  //    glEnable(GL_LIGHT4);
  //  case 4:
  //    glEnable(GL_LIGHT3);
  //  case 3:
  //    glEnable(GL_LIGHT2);
  //  case 2:
  //    glEnable(GL_LIGHT1);
  //  case 1:
  //    glEnable(GL_LIGHT0);
  //    break;
  //  default:
  //    break;
  //}

  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  //glEnable(GL_LIGHT2);
  //glEnable(GL_LIGHT3);
  //glEnable(GL_LIGHT4);
  //glEnable(GL_LIGHT5);
  //glEnable(GL_LIGHT6);
  //glEnable(GL_LIGHT7);
}
