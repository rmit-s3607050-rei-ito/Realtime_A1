#include "util.h"

#define STR_LEN 255;

typedef struct
{
  File *file;
  int tessalation;
  bool iMode;
  bool rMode;
  bool lighting;
  bool normals;
  int nLights;
} BenchParams;

void initBench();
void startBench();
void saveBench(float fpr, float ft, float tps, BenchParams params);
