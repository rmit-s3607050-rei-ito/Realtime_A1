#include "util.h"
#include "gl.h"
#include "mesh.h"

#define STR_LEN 255

typedef struct
{
  FILE *file;
  int tessellation;
  renderMode iMode;
  bool rMode;
  bool lighting;
  bool normals;
  int nLights;
} BenchParams;

void initBench(int tess, renderMode iMode, bool rMode, bool light, int nLights,
  bool normals);
void saveBench(float fr, float ft, float tps);
char *fileName(BenchParams bench);
