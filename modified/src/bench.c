#include "bench.h"

BenchParams bench;

void initBench(int tess, bool iMode, bool rMode, bool light, bool normals,
  int nLights)
{
  bench.tessalation = tess;
  bench.iMode = iMode;
  bench.rMode = rMode;
  bench.lighting = light;
  bench.normals = normals;
  bench.nLights = nLights;
  bench.file = fopen(fileName(), "w");
}

void startBench()
{

}

void saveBench(float fpr, float ft, float tps)
{
  if (bench.file == NULL)
    printf("Error opening file!\n");


}

char[] fileName()
{
  char name[STR_LEN] = "T:";
  char str[STR_LEN];

  sprintf(str, "%d|IM:", bench.tesselation);
  strcat(name, str);

  if (bench.iMode)
    strcat(name, "va|RM:");
  else
    strcat(name, "vbo|RM:");

  if (bench.rMode)
    strcat(fileName, "filled|L:");
  else
    strcat(fileName, "wired|L:");

  if (bench.lighting)
    strcat(name, "on|LC:");
    sprintf(str, "%d|N:", bench.nLights);
    strcat(name, str);
    if (bench.normals)
      strcat(name, "on");
    else
      strcat(name, "off");
  else
    strcat(name, "off");

  return name;
}
