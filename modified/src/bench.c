#include "bench.h"

BenchParams bench;

void initBench(renderMode rMode, bool wf, bool light, int nLights,
               bool normals)
{
  // Store initial benchmarking values
  bench.rMode = rMode;
  bench.wf = wf;
  bench.lighting = light;
  bench.normals = normals;
  bench.nLights = nLights;
  /* Create file using specific naming conventions
   * E.g.
   * RM:va|WF:off|L:on|LC:1|N:off
   * ##### Format #####
   * Variables = Tesselation|RenderMode|Wireframe|Lighting|LightingCount|normals
   * Values = [Count]|[IM/VA/VBO]|[On/Off]|[On/Off]|1 to 8|[On/Off]
   */
  char file[STR_LEN] = "benches/";
  strcat(file, fileName(bench));
  bench.file = fopen(file, "w");
}

void saveBench(float tps, float ft, float fr)
{
  // Check if there are no errors with the file location/name, if not save data
  if (bench.file == NULL)
    printf("Error opening file!\n");

  /* ##### Data format #####
   * E.g. (As can be seen on the OSD)
   * 2083.916016|0.479866|403.596375
   * TrianglesPerSecond|FrameTime|FrameRate
   */
  fprintf(bench.file, "%10.2f|%8.2f|%7.2f\n", tps, ft, fr);
}

char *fileName(BenchParams bench)
{ // Save file name using various checks for the file name
  // [1]. Start with render mode
  static char name[STR_LEN] = "RM:";
  char str[STR_LEN];

  // [2]. Append render mode value, then attach WireFrame key
  if (bench.rMode == VA)
    strcat(name, "va|WF:");
  else if (bench.rMode == VBO)
    strcat(name, "vbo|WF:");
  else
    strcat(name, "im|WF:");

  // [3]. Append whether WireFrame on or off (wireframe or filled objects)
  if (bench.wf)
    strcat(name, "on|L:");
  else
    strcat(name, "off|L:");

  /* [4]. Append whether lighting on or off, if on append number of lights.
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
