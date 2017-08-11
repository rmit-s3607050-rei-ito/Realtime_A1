#include "util.h"
#include "gl.h"
#include "mesh.h"

#define STR_LEN 255

typedef struct
{
  FILE *file;
  renderMode rMode;
  bool wf;
  bool lighting;
  bool normals;
  int nLights;
} BenchParams;

void initBench(renderMode rMode, bool wf, bool light, int nLights,
  bool normals);
void saveBench(float tps, float ft, float fr);
char *fileName(BenchParams bench);
