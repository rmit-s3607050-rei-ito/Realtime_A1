#include "bench.h"

BenchParams bench;

void initBench(int tess, renderMode iMode, bool rMode, bool light, int nLights,
               bool normals)
{
  // Store initial benchmarking values
  bench.tessellation = tess;
  bench.iMode = iMode;
  bench.rMode = rMode;
  bench.lighting = light;
  bench.normals = normals;
  bench.nLights = nLights;
  /* Create file using specific naming conventions
   * E.g.
   * T:8|RM:va|WF:off|L:on|LC:1|N:off
   * ##### Format #####
   * Variables = Tesselation|RenderMode|Wireframe|Lighting|LightingCount|normals
   * Values = [Count]|[IM/VA/VBO]|[On/Off]|[On/Off]|1 to 8|[On/Off]
   */
  char file[STR_LEN] = "benches/";
  strcat(file, fileName(bench));
  bench.file = fopen(file, "w");
}

void saveBench(float fr, float ft, float tps)
{
  // Check if there are no errors with the file location/name, if not save data
  if (bench.file == NULL)
    printf("Error opening file!\n");

  /* ##### Data format #####
   * E.g. (As can be seen on the OSD)
   * 2083.916016|0.479866|403.596375
   * FrameRate|FrameTime|TrianglesPerSecond
   */
  fprintf(bench.file, "%11f|%11f|%14f\n", fr, ft, tps);
}

char *fileName(BenchParams bench)
{ // Save file name using various checks for the file name
  // [1]. Start with tesselation
  static char name[STR_LEN] = "T:";
  char str[STR_LEN];

  // [2]. Append tessellation value then attach RenderMode key
  sprintf(str, "%d|RM:", bench.tessellation);
  strcat(name, str);

  // [3]. Append render mode value, then attach WireFrame key
  if (bench.iMode == VA)
    strcat(name, "va|WF:");
  else if (bench.iMode == VBO)
    strcat(name, "vbo|WF:");
  else
    strcat(name, "im|WF:");

  // [4]. Append whether WireFrame on or off (wireframe or filled objects)
  if (bench.rMode)
    strcat(name, "on|L:");
  else
    strcat(name, "off|L:");

  /* [5]. Append whether lighting on or off, if on append number of lights.
   * Then append whether normals are displayed or not
   */
  if (bench.lighting)
  {
    strcat(name, "on|LC:");
    sprintf(str, "%d|N:", bench.nLights);
    strcat(name, str);
    if (bench.normals)
      strcat(name, "on");
    else
      strcat(name, "off");
  }
  else
    strcat(name, "off");

  return name;
}
