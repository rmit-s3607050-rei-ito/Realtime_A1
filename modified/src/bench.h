#include "util.h"
#include "gl.h"
#include "controls.h"
#include "player.h"

#define STR_LEN 255

typedef struct
{
  FILE *file;
  int tessellation;
  bool iMode;
  bool rMode;
  bool lighting;
  bool normals;
  int nLights;
} BenchParams;

void initBench(int tess, bool iMode, bool rMode, bool light, int nLights,
  bool normals);
void saveBench(float fr, float ft, float tps);
char *fileName(BenchParams bench);
