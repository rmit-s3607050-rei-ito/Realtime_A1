#include "counters.h"

void
initCounters(Counters *ctrs)
{
  ctrs->frameCount = 0;
  ctrs->frameTime = 0.0;
  ctrs->lastTime = 0.0;
  ctrs->interval = 1000.0; // 1 s
  // Initial triangle count calculated based on default 8 tesselation
  ctrs->triangles = 0;
}

void
updateCounters(Counters *ctrs, float t)
{
  float dt = (t - ctrs->lastTime);
  if (dt > ctrs->interval) {
    ctrs->frameTime = dt / ctrs->frameCount;
    ctrs->lastTime = t;
    ctrs->frameCount = 0;
    ctrs->triangleTime = dt / ctrs->triangles;
  }
}

void
resetTriangleCount(Counters *ctrs)
{
  // Reset when tesselating
  ctrs->triangles = 0;
}

void
updateTriangleCount(int numTriangles, Counters *ctrs)
{
  ctrs->triangles += numTriangles;
}
