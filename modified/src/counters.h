#pragma once

/*
 * performance counters
 */

typedef struct {
  int frameCount;
  float frameTime;
  float interval;
  float lastTime;
  float triangleTime;
  int triangles;
} Counters;

void updateCounters(Counters *ctrs, float t);
void initCounters(Counters *ctrs);
void resetTriangleCount();
void updateTriangleCount(int numTriangles, Counters *ctrs);
