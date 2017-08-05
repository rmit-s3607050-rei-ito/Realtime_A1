#include "gl.h"
#include "util.h"
#include "state.h"
#include "player.h"
#include "level.h"
#include "counters.h"
#include "OSD.h"

Globals globals;

static void cleanup() {
  destroyPlayer(&globals.player);
  destroyLevel(&globals.level);
}

void postRedisplay()
{
  globals.wantRedisplay = 1;
}

void quit(int code)
{
  SDL_DestroyWindow(globals.window);
  SDL_Quit();
  exit(code);
}

static void
reshape(int width, int height)
{
  glViewport(0,0, width, height);
  globals.camera.width = width;
  globals.camera.height = height;
  applyProjectionMatrix(&globals.camera);
}

static void updateKey(SDL_KeyboardEvent *e, bool state)
{
  switch (e->keysym.sym)
  {
    case SDLK_w:
      globals.controls.up = state;
      break;
    case SDLK_s:
      globals.controls.down = state;
      break;
    case SDLK_a:
      globals.controls.left = state;
      break;
    case SDLK_d:
      globals.controls.right = state;
      break;
    case SDLK_SPACE:
      globals.controls.jump = state;
      break;
    case SDLK_LEFT:
      globals.controls.turnLeft = state;
      break;
    case SDLK_RIGHT:
      globals.controls.turnRight = state;
      break;
    default:
      break;
  }
}

static void mouseMotion(int x, int y)
{
  int dX = x - globals.camera.lastX;
  int dY = y - globals.camera.lastY;

  if (globals.controls.lmb) {
    globals.camera.xRot += dX * 0.1;
    globals.camera.yRot += dY * 0.1;
    globals.camera.yRot = clamp(globals.camera.yRot, 0, 90);
  }

  if (globals.controls.rmb) {
    globals.camera.zoom += dY * 0.01;
    globals.camera.zoom = max(globals.camera.zoom, 0.5);
  }

  globals.camera.lastX = x;
  globals.camera.lastY = y;
}

static void mouseButton(SDL_MouseButtonEvent *e, int state, int x, int y)
{
  if (state == true) {
    globals.camera.lastX = x;
    globals.camera.lastY = y;
  }

  if (e->button == SDL_BUTTON_LEFT) {
    globals.controls.lmb = state;
  } else if (e->button == SDL_BUTTON_RIGHT) {
    globals.controls.rmb = state;
  }
}

// key down events
void keyDown(SDL_KeyboardEvent *e)
{
  switch (e->keysym.sym)
  {
    case SDLK_ESCAPE:
      cleanup();
      quit(0);
      break;

    case SDLK_h:
      globals.halt = !globals.halt;
      if (globals.halt)
        printf("Stopping time\n");
      else
        printf("Resuming time\n");
      break;

    case SDLK_l:
      globals.drawingFlags.lighting = !globals.drawingFlags.lighting;
      printf("Toggling lighting\n");
      break;

    case SDLK_t:
      globals.drawingFlags.textures = !globals.drawingFlags.textures;
      printf("Toggling textures\n");
      break;

    case SDLK_n:
      globals.drawingFlags.normals = !globals.drawingFlags.normals;
      printf("Toggling normals\n");
      break;

    case SDLK_o:
      globals.drawingFlags.axes = !globals.drawingFlags.axes;
      printf("Toggling axes\n");
      break;

    case SDLK_m:
      globals.drawingFlags.rm++;
      if (globals.drawingFlags.rm >= nrms)
        globals.drawingFlags.rm = im;
      printf("Changing RM\n");
      break;

    case SDLK_p:
      globals.drawingFlags.wireframe = !globals.drawingFlags.wireframe;
      if (globals.drawingFlags.wireframe)
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        printf("Using wireframe rendering\n");
      }
      else
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        printf("Using filled rendering\n");
      }
      break;

    case SDLK_EQUALS:
      globals.drawingFlags.tess[0] =
        clamp(globals.drawingFlags.tess[0] * 2, 8, 1024);
      globals.drawingFlags.tess[1] =
        clamp(globals.drawingFlags.tess[1] * 2, 8, 1024);
      generatePlayerGeometry(&globals.player, globals.drawingFlags.tess);
      generateLevelGeometry(&globals.level, globals.drawingFlags.tess);
      printf("Tesselation: %zu %zu\n",
      globals.drawingFlags.tess[0], globals.drawingFlags.tess[1]);
      break;

    case SDLK_MINUS:
      globals.drawingFlags.tess[0] =
        clamp(globals.drawingFlags.tess[0] / 2, 8, 1024);
      globals.drawingFlags.tess[1] =
        clamp(globals.drawingFlags.tess[1] / 2, 8, 1024);
      generatePlayerGeometry(&globals.player, globals.drawingFlags.tess);
      generateLevelGeometry(&globals.level, globals.drawingFlags.tess);
      printf("Tesselation: %zu %zu\n",
      globals.drawingFlags.tess[0], globals.drawingFlags.tess[1]);
      break;
    default:
      updateKey(e, true);
      break;
  }
}

// Key up events
void keyUp(SDL_KeyboardEvent *e)
{
  updateKey(e, false);
}

void eventDispatcher()
{
  SDL_Event e;

  // Handle events
  while (SDL_PollEvent(&e))
  {
    switch (e.type)
    {
      case SDL_QUIT:
        if (globals.debug)
          printf("Quit\n");
        quit(0);
        break;
      case SDL_MOUSEMOTION:
        mouseMotion(e.button.x, e.button.y);
        break;
      case SDL_MOUSEBUTTONDOWN:
        mouseButton(&e.button, true, e.button.x, e.button.y);
        break;
      case SDL_MOUSEBUTTONUP:
        mouseButton(&e.button, false, e.button.x, e.button.y);
        break;
      case SDL_KEYDOWN:
        keyDown(&e.key);
        break;
      case SDL_KEYUP:
        keyUp(&e.key);
        break;
      case SDL_WINDOWEVENT:
        if (globals.debug)
          printf("Window event %d\n", e.window.event);
        switch (e.window.event)
        {
          case SDL_WINDOWEVENT_SHOWN:
            if (globals.debug)
              SDL_Log("Window %d shown", e.window.windowID);
            break;
          case SDL_WINDOWEVENT_SIZE_CHANGED:
            if (globals.debug)
              printf("SDL_WINDOWEVENT_SIZE_CHANGED\n");
            break;
          case SDL_WINDOWEVENT_RESIZED:
            if (globals.debug)
              printf("SDL_WINDOWEVENT_RESIZED.\n");
            if (e.window.windowID == SDL_GetWindowID(globals.window))
            {
              SDL_SetWindowSize(globals.window, e.window.data1, e.window.data2);
              reshape(e.window.data1, e.window.data2);
              postRedisplay();
            }
            break;
          case SDL_WINDOWEVENT_CLOSE:
            if (globals.debug)
              printf("Window close event\n");
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
  }

  postRedisplay();
}

static void
render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  applyViewMatrix(&globals.camera);

  static float lightPos[] = { 1, 1, 1, 0 };
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  renderPlayer(&globals.player, &globals.drawingFlags);
  renderLevel(&globals.level, &globals.drawingFlags);

  displayOSD(&globals.counters, &globals.drawingFlags);

  SDL_GL_SwapWindow(globals.window);

  //glutSwapBuffers();

  globals.counters.frameCount++;
}

static void
update()
{
  static int tLast = -1;

  if (tLast < 0)
    tLast = SDL_GetTicks();

  int t = SDL_GetTicks();
  int dtMs = t - tLast;
  float dt = (float)dtMs / 1000.0f;
  tLast = t;

  if (!globals.halt) {
    updatePlayer(&globals.player, dt, &globals.controls);
    updateLevel(&globals.level, dt);
    updateCounters(&globals.counters, t);
    globals.camera.pos = globals.player.pos;

    postRedisplay();
  };
}

static void
init()
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);

  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_FLAT);
  glColor3f(1.0, 1.0, 1.0);

  globals.drawingFlags.tess[0] = 8;
  globals.drawingFlags.tess[1] = 8;
  globals.drawingFlags.wireframe = false;
  globals.drawingFlags.textures = true;
  globals.drawingFlags.lighting = true;
  globals.drawingFlags.rm = im;
  initPlayer(&globals.player, &globals.drawingFlags);
  initLevel(&globals.level, &globals.drawingFlags);
  initCamera(&globals.camera);
  initCounters(&globals.counters);
  globals.camera.pos = globals.player.pos;
  globals.camera.width = 800;
  globals.camera.height = 600;

  globals.wantRedisplay = 1;
  globals.debug = true;
}

void mainLoop()
{
  while (1) {
    eventDispatcher();
    if (globals.wantRedisplay) {
      render();
      globals.wantRedisplay = 0;
    }
    update();
  }
}

int initGraphics()
{
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  globals.window =
    SDL_CreateWindow("Frogger Using SDL2",
         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
         800, 800, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (!globals.window) {
    fprintf(stderr, "%s:%d: create window failed: %s\n",
      __FILE__, __LINE__, SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_GLContext mainGLContext = SDL_GL_CreateContext(globals.window);
  if (mainGLContext == 0) {
    fprintf(stderr, "%s:%d: create context failed: %s\n",
      __FILE__, __LINE__, SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

void sys_shutdown()
{
  SDL_Quit();
}

int
main(int argc, char **argv)
{
  glutInit(&argc, argv);

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "%s:%d: unable to init SDL: %s\n",
      __FILE__, __LINE__, SDL_GetError());
    exit(EXIT_FAILURE);
  }

  if (!initGraphics()) {
      SDL_Quit();
      return EXIT_FAILURE;
  }

  init();

  int w, h;
  SDL_GetWindowSize(globals.window, &w, &h);
  reshape(w, h);

  atexit(sys_shutdown);

  mainLoop();

  return EXIT_SUCCESS;
}
