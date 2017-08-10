#include "bench.h"

BenchParams bench;

void initBench(int tess, bool iMode, bool rMode, bool light, int nLights,
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

  sprintf(str, "%d|IM:", bench.tessellation);
  strcat(name, str);

  if (bench.iMode)
    strcat(name, "va|RM:");
  else
    strcat(name, "vbo|RM:");

  if (bench.rMode)
    strcat(name, "wired|L:");
  else
    strcat(name, "filled|L:");

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
