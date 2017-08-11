#pragma once

#include "counters.h"
#include "util.h"
#include "mesh.h"
#include "material.h"

/*
 * An object we can use to store the size, position and velocity of
 * both the logs and cars in our game
 */
typedef struct {
  Vec3f pos, vel, size;
  Vec2f rot;
} Entity;

/*
 * Keeps track of a list of cars which should be arranged into lanes
 * Also has all of the information we need to render our cars
 */
typedef struct {
  size_t numLanes;
  float laneWidth, laneHeight;
  Vec3f pos;
  Entity* enemies;
  Mesh* enemyMesh;
  Material enemyMaterial;
} Road;

/*
 * Same as above but for our logs
 */
typedef struct {
  size_t numLanes;
  float laneWidth, laneHeight;
  Vec3f pos;
  Entity* logs;
  Mesh* logMesh;
  Material logMaterial;
  unsigned int logTexture;
} River;

/*
 * Bundles up of the state for our game, including a mesh and material
 * for our play area
 */
typedef struct {
  int width, height;
  Mesh* terrainMesh;
  Material terrainMaterial;
  Road road;
  River river;
} Level;

void generateLevelGeometry(Level* level, size_t segments[], Counters *ctrs);
void initLevel(Level* level, DrawingFlags* flags, Counters *ctrs);
void destroyLevel(Level* level);
void updateLevel(Level* level, float dt);
void renderLevel(Level* level, DrawingFlags* flags);
