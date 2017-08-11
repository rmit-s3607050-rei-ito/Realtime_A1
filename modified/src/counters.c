#include "counters.h"

void
initCounters(Counters *ctrs)
{
  ctrs->frameCount = 0;
  ctrs->frameTime = 0.0;
  ctrs->lastTime = 0.0;
  ctrs->interval = 1000.0; // 1 s
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
  /* Reset the number of triangles when tesselating
   * Otherwise calling updateTriangleCount() will continually add onto the total
   */
  ctrs->triangles = 0;
}

void
updateTriangleCount(int numTriangles, Counters *ctrs)
{
  /* Updates called when initializing:
   * - Player (Sphere)
   * - Level (Grid)
   * - Cars (Cubes)
   * - Logs (Cylinders)
   * Each call will add onto the total triangles, which are then used to
   * calculate triangles per second
   */
  ctrs->triangles += numTriangles;
}
