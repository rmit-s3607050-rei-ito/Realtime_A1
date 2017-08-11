#pragma once

#include "counters.h"
#include "util.h"

/*
 * Flags used to specify debug lines, wireframe rendering, tesselation, etc
 */
typedef enum { im = 0, VA, VBO, nrms } renderMode;
typedef struct {
  bool normals, wireframe, lighting, textures, axes;
  size_t tess[2];
  renderMode rm;
} DrawingFlags;

/*
 * Everything needed by a vertex, you could also have tangents and binormals, but they aren't used in this app
 */
typedef struct {
  Vec3f pos, normal;
  Vec2f tc;
} Vertex;

/*
 * An indexed mesh which can be used for instanced rendering
 */
typedef struct {
  Vertex* verts;
  unsigned int* indices;
  size_t numVerts, numIndices;
  unsigned vbo, ibo;
} Mesh;

/*
 * VBO related variables and functions
 */
#define BUFFER_OFFSET(i) ((void*)(i))
void initVBOs();
void bindVBOs();

Mesh* createMesh(size_t numVerts, size_t numIndices);
void destroyMesh(Mesh* mesh);
void renderMesh(Mesh* mesh, DrawingFlags* flags);

Mesh* createCube(Counters *ctrs);
Mesh* createPlane(float width, float height, size_t rows, size_t cols, Counters *ctrs);
Mesh* createSphere(size_t segments, size_t slices, Counters *ctrs);
Mesh* createCylinder(size_t segments, size_t slices, float radius, Counters *ctrs);

void drawLine(Vec3f color, Vec3f a, Vec3f b);
void drawParabola(Vec3f color, Vec3f vel, float g, DrawingFlags* flags);
