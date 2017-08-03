#include <stdio.h>

#include "mesh.h"
#include "counters.h"
#include "gl.h"

const float milli = 1000.0f;

// On screen display
void
displayOSD(Counters *ctrs, DrawingFlags *dfs)
{
  char buffer[30];
  char *bufp;
  int w, h;
  const int rm = 150, vs = 20;


  glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  /* Set up orthographic coordinate system to match the window,
     i.e. (0,0)-(w,h) */
  w = glutGet(GLUT_WINDOW_WIDTH);
  h = glutGet(GLUT_WINDOW_HEIGHT);
  glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  /* Frame time */
  glColor3f(1.0, 1.0, 0.0);
  glRasterPos2i(w-rm, h-vs);
  snprintf(buffer, sizeof buffer, "ft (ms/f): %5.0f", ctrs->frameTime);
  for (bufp = buffer; *bufp; bufp++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *bufp);

  /* Frame rate */
  glColor3f(1.0, 1.0, 0.0);
  glRasterPos2i(w-rm, h-2*vs);
  snprintf(buffer, sizeof buffer, "fr (f/s):  %5.0f",
	   1.0 / ctrs->frameTime * milli);
  for (bufp = buffer; *bufp; bufp++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *bufp);


  /* Tesselation */
  glColor3f(1.0, 1.0, 0.0);
  glRasterPos2i(w-rm, h-3*vs);
  snprintf(buffer, sizeof buffer, "tess:  %4ld %4ld",
	   dfs->tess[0], dfs->tess[1]);
  for (bufp = buffer; *bufp; bufp++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *bufp);

  glPopMatrix();  /* Pop modelview */

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();  /* Pop projection */

  glMatrixMode(GL_MODELVIEW);

  glPopAttrib();


}
