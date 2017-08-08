/*
 * Draw a grid using:
 *   immediate mode and coordinates recalculated each frame
 *   immediate mode and coordinates stored in an array
 *   immediate mode and coordinates and indices (elements) stored in an array
 *   vertex arrays
 *   vertex buffer objects
 *
 * $Id: grid-fw.c,v 1.3 2017/07/24 11:37:53 gl Exp gl $
 */

#define GL_GLEXT_PROTOTYPES

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define BUFFER_OFFSET(i) ((void*)(i))

typedef struct { float x, y, z; } vec3f;
typedef struct { vec3f r, n; } Vertex;

Vertex *vertices;
unsigned *indices;
unsigned n_vertices, n_indices;
unsigned vbo, ibo;
unsigned rows = 3, cols = 3;

typedef enum { IM = 0, SA, SAI, VA, VBO, nM } drawMode;

drawMode mode = IM;

// ########## Vertex Array related functions ##########
#define DEBUG_ENABLE_DISABLE_VAS_AND_VBOS
void enableVAs()
{
   glEnableClientState(GL_VERTEX_ARRAY);

   #ifdef DEBUG_ENABLE_DISABLE_VAS_AND_VBOS
      printf("\n[ENABLED]: Vertex Arrays");
   #endif
}

void disableVAs()
{
   glDisableClientState(GL_VERTEX_ARRAY);

   #ifdef DEBUG_ENABLE_DISABLE_VAS_AND_VBOS
      printf("\n[DISABLED]: Vertex Arrays");
   #endif
}

// ########## Vertex Buffer Objects related functions ##########
void buildVBOs()
{
   // Usage: Generate buffer VBOS for:
   // [1]. verticies
   glGenBuffers(1, &vbo);
   // [2]. indices
   glGenBuffers(1, &ibo);

   #ifdef DEBUG_ENABLE_DISABLE_VAS_AND_VBOS
      printf("\nGenerated buffers for vertex/index buffer objects\n");
   #endif
}

void bindVBOs()
{
   // Bind buffers then add data into the buffer for both verticies and indices
   // [1]. Verticies
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, n_vertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);
   // [2]. indices
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_indices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void unbindVBOs()
{
   // Unbind buffers of VBOs when switching rendering mode (empty them)
   int buffer;

   // [1]. Array Buffers (Verticies)
   glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &buffer);
   if (buffer != 0)
      glBindBuffer(GL_ARRAY_BUFFER, 0);

   // [2]. Element Array Buffers (Indices)
   glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &buffer);
   if (buffer != 0)
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void enableVBOs()
{
   bindVBOs();

   #ifdef DEBUG_ENABLE_DISABLE_VAS_AND_VBOS
      printf("\n[ENABLED]: Vertex Buffer Objects");
   #endif
}

void disableVBOs()
{
   unbindVBOs();

   #ifdef DEBUG_ENABLE_DISABLE_VAS_AND_VBOS
      printf("\n[DISABLED]: Vertex Buffer Objects");
   #endif
}

drawMode changeMode(drawMode &nextMode)
{
   // Increment to next mode, loop once end reached (nM == num modes?)
   nextMode = (drawMode) ((mode + 1) % nM);
   return nextMode;
}

void drawAxes(float length)
{
  glPushAttrib(GL_CURRENT_BIT);
  glBegin(GL_LINES);

  /* x axis */
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(length, 0.0, 0.0);

  /* y axis */
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, length, 0.0);

  /* z axis */
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, length);

  glEnd();
  glPopAttrib();
}

void drawGrid2D(int rows, int cols) // RED color
{
  glPushAttrib(GL_CURRENT_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(1.0, 0.0, 0.0);

  /* Grid */
  float dy = 2.0f / (float) rows;
  float dx = 2.0f / (float) cols;
  for (int i = 0; i < cols; i++) {
    float x = -1.0 + i * dx;
    glBegin(GL_TRIANGLE_STRIP);
    for (int j = 0; j <= rows; j++) {
      float y = -1.0 + j * dy;
      glVertex3f(x, y, 0.0);
      glVertex3f(x + dx, y, 0.0);
    }
    glEnd();
  }

  glPopAttrib();
}

void computeAndStoreGrid2D(int rows, int cols)
{
  n_vertices = (rows + 1) * (cols + 1);
  n_indices = (rows + 1) * (cols - 1) * 2 + (rows + 1) * 2;
  // or more simply: n_indices = n_vertices * 2;
  vertices = (Vertex *)malloc(n_vertices * sizeof(Vertex));
  indices = (unsigned *)malloc(n_indices * sizeof(unsigned));

  /* Grid */

  /* Vertices */
  float dy = 2.0f / (float) rows;
  float dx = 2.0f / (float) cols;
  Vertex *vtx = vertices;
  for (int i = 0; i <= cols; i++) {
    float x = -1.0 + i * dx;
    for (int j = 0; j <= rows; j++) {
      float y = -1.0 + j * dy;
      vtx->r = (vec3f) { x, y, 0.0 };
      vtx++;
    }
  }

  /* Indices */
  unsigned *idx = indices;
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j <= rows; j++) {
      *idx++ = i * (rows + 1) + j;
      *idx++ = (i + 1) * (rows + 1) + j;
    }
  }

#define DEBUG_STORE_VERTICES
#ifdef DEBUG_STORE_VERTICES
  printf("########## VERTICIES ##########\n");
  for (int i = 0; i <= cols; i++) {
    for (int j = 0; j <= rows; j++) {
      int idx = i * (rows + 1) + j;
      printf("(%5.2f,%5.2f)", vertices[idx].r.x, vertices[idx].r.y);
    }
    printf("\n");
  }
  printf("\n########## INDICIES ##########\n");
  for (int i = 0; i < n_indices; i++) {
    printf("%d ", indices[i]);
  }
  printf("\n\n########## FORMAT ##########\n");
  printf("[i, j]: idx = (x, y)\n");
#endif
}

void drawGrid2DStoredVertices(int rows, int cols) // GREEN color
{
   glPushAttrib(GL_CURRENT_BIT);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glColor3f(0.0, 1.0, 0.0);

   /* Grid */
   printf("\n########## [1]: 2D-STORED_VERTICIES ##########\n");
   #define DEBUG_DRAW_GRID_ARRAY
   #ifdef DEBUG_DRAW_GRID_ARRAY
      printf("----- DEBUG INFORMATION -----\n");
   #endif
   for (int i = 0; i < cols; i++) {
      glBegin(GL_TRIANGLE_STRIP);
      for (int j = 0; j <= rows; j++) {
         int idx = i * (rows + 1) + j;
         #ifdef DEBUG_DRAW_GRID_ARRAY
               printf("[%d, %d]: %2d = (%5.2f, %5.2f)\n", i, j, idx,
               vertices[idx].r.x, vertices[idx].r.y);
         #endif
               glVertex3fv(&vertices[idx].r.x);
               idx += rows + 1;
         #ifdef DEBUG_DRAW_GRID_ARRAY
               printf("[%d, %d]: %2d = (%5.2f, %5.2f)\n", i, j, idx,
               vertices[idx].r.x, vertices[idx].r.y);
         #endif
               glVertex3fv(&vertices[idx].r.x);
    }
    glEnd();
  }

  glPopAttrib();
}

void drawGrid2DStoredVerticesAndIndices(int rows, int cols) // BLUE color
{
  glPushAttrib(GL_CURRENT_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0.0, 0.0, 1.0);

  /* Grid */
  printf("\n########## [2]: 2D-STORED_VERTICIES_AND_INDICIES ##########\n");
  #define DEBUG_DRAW_GRID_2D_VERTICIES_AND_INDICIES
  #ifdef DEBUG_DRAW_GRID_2D_VERTICIES_AND_INDICIES
     printf("----- DEBUG INFORMATION -----\n");
  #endif
  int idx = 0;
  int next = 1;
  for (int i = 0; i < cols; i++) {
    glBegin(GL_TRIANGLE_STRIP);
    for (int j = 0; j <= rows; j++) {
      // Add code to use array of indices aka "element array"
      glVertex3fv(&vertices[indices[idx]].r.x);
      glVertex3fv(&vertices[indices[next]].r.x);
      // Also add debugging code similar to drawGrid2DStoredVertices
      #ifdef DEBUG_DRAW_GRID_2D_VERTICIES_AND_INDICIES
         printf("[%d, %d]: %2d = (%5.2f, %5.2f)\n", i, j, indices[idx],
               vertices[indices[idx]].r.x, vertices[indices[idx]].r.y);
         printf("[%d, %d]: %2d = (%5.2f, %5.2f)\n", i, j, indices[next],
               vertices[indices[next]].r.x, vertices[indices[next]].r.y);
      #endif
      // Move to next pair of verticies
      idx += 2;
      next += 2;
    }
    glEnd();
  }

  glPopAttrib();
}

void drawGrid2DVAs(int rows, int cols) // YELLOW color
{
   glPushAttrib(GL_CURRENT_BIT);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glColor3f(1.0, 1.0, 0.0);

   // PARAMS: (NumCoordsPerVertex, TypeOfEachCoord, ByteOffSet, PointerLocation)
   glVertexPointer(3, GL_FLOAT, sizeof(Vertex), vertices);
   int num = (rows + 1) * 2;
   /* Grid */
   printf("\n########## [3]: 2D-VERTEX_ARRAYS ##########\n");
   for (int i = 0; i < cols; i++) {
      // Code to draw a column using a triangle strip
      // PARAMS: (TypeToRender, NumElements, TypeOfIndicies, LocationOfIndicies)
      glDrawElements(GL_TRIANGLE_STRIP, num, GL_UNSIGNED_INT, &indices[i * num]);
   }

   glPopAttrib();
}

void drawGrid2DVBOs(int rows, int cols)
{
   glPushAttrib(GL_CURRENT_BIT);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glColor3f(0.0, 1.0, 1.0);

   // 1. Bind vertex VBO
   glBindBuffer(GL_ARRAY_BUFFER, vbo);

   // 2. Set vertex pointer using BUFFER_OFFSET defined variable
   // PARAMS: (NumCoordsPerVertex, TypeOfEachCoord, ByteOffSet, PointerLocation)
   #define BUFFER_OFFSET(i) ((void*)(i))
   glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));

   // 3. Bind index VBO
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

   // 4. Render
   int num = (rows + 1) * 2;
   /* Grid */
   printf("\n########## [4]: 2D-VERTEX_BUFFER_OBJECTS ##########\n");
   for (int i = 0; i < cols; i++) {
     // Code to draw a column using a triangle strip
     // PARAMS: (TypeToRender, NumElements, TypeOfIndicies, LocationOfIndicies)
     glDrawElements(GL_TRIANGLE_STRIP, num, GL_UNSIGNED_INT,
                    BUFFER_OFFSET(i * num * sizeof(unsigned int)));
   }

   glPopAttrib();
}

void init()
{
  computeAndStoreGrid2D(rows, cols);
  buildVBOs();
}

void display(void)
{
  int err;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

  glLoadIdentity();

  // Draw axes
  drawAxes(5.0);

  // Draw grid
  switch (mode) {
  case IM:
    drawGrid2D(rows, cols);
    break;
  case SA:
    drawGrid2DStoredVertices(rows, cols);
    break;
  case SAI:
    drawGrid2DStoredVerticesAndIndices(rows, cols);
    break;
  case VA:
    drawGrid2DVAs(rows, cols);
    break;
  case VBO:
    drawGrid2DVBOs(rows, cols);
    break;
  case nM:
    break;
  }

  glPopMatrix();

  glutSwapBuffers();

  if ((err = glGetError()) != GL_NO_ERROR)
    printf("display: %s\n", gluErrorString(err));
}

void key(unsigned char k, int x, int y)
{
   switch (k)
   {

   case 27:  /* Escape */
      exit(0);
      break;

   case 'm':
      if (mode == VA)
         disableVAs();
      if (mode == VBO)
         disableVBOs();

      changeMode(mode);

      if (mode >= nM)
         mode = IM;
      if (mode == VA)
         enableVAs();
      if (mode == VBO)
         enableVBOs();
         break;
   default:
      return;
   }

   glutPostRedisplay();
}

void update()
{
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

/*
 * Main Loop Open window with initial window size, title bar, RGBA display
 * mode, and handle input events.
 */
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(500, 500);
  glutCreateWindow(argv[0]);
  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(key);
  glutIdleFunc(update);
  glutMainLoop();

  return 0;
}
