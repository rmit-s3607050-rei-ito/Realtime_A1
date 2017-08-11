#include "bench.h"

BenchParams bench;

void initBench(int tess, renderMode iMode, bool rMode, bool light, int nLights,
  bool normals)
{
  bench.tessellation = tess;
  bench.iMode = iMode;
  bench.rMode = rMode;
  bench.lighting = light;
  bench.normals = normals;
  bench.nLights = nLights;
  char file[STR_LEN] = "benches/";
  strcat(file, fileName(bench));
  bench.file = fopen(file, "w");
}

void saveBench(float fr, float ft, float tps)
{
  if (bench.file == NULL)
    printf("Error opening file!\n");

  fprintf(bench.file, "%f|", fr);
  fprintf(bench.file, "%f|", ft);
  fprintf(bench.file, "%f\n", tps);
}

char *fileName(BenchParams bench)
{
  static char name[STR_LEN] = "T:";
  char str[STR_LEN];

  sprintf(str, "%d|RM:", bench.tessellation);
  strcat(name, str);

  if (bench.iMode == VA)
    strcat(name, "va|WF:");
  else if (bench.iMode == VBO)
    strcat(name, "vbo|WF:");
  else
    strcat(name, "im|WF:");

  if (bench.rMode)
    strcat(name, "on|L:");
  else
    strcat(name, "off|L:");

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
