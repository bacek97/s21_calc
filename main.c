#define NKC_IMPLEMENTATION
#include "./nuklear+/nuklear_cross.h"
//#include "./nuklear+/nuklear.h"
//#include "GL/glxew.h"
#include <stdio.h>

enum radioOptions {
  EASY,
  HARD
};

struct my_nkc_app {
  struct nkc *nkcHandle;

  /* some user data */
  float value;
  enum radioOptions op;
};

void mainLoop(void *loopArg) {
  struct my_nkc_app *myapp = (struct my_nkc_app *) loopArg;
  struct nk_context *ctx = nkc_get_ctx(myapp->nkcHandle);

  union nkc_event e = nkc_poll_events(myapp->nkcHandle);
  if ((e.type == NKC_EWINDOW) && (e.window.param == NKC_EQUIT)) {
    nkc_stop_main_loop(myapp->nkcHandle);
  }
  struct nk_vec2 mpos = myapp->nkcHandle->ctx->input.mouse.pos;
  if (mpos.x && mpos.y){
    printf("%f\n",mpos.x);
  }

  /* Nuklear GUI code */

  if (nk_begin(ctx, "Calculator", nk_rect(10, 10, 180, 250),
               NK_WINDOW_DYNAMIC|NK_WINDOW_BORDER | NK_WINDOW_MOVABLE |NK_WINDOW_SCALABLE)) {
    static int set = 0, prev = 0, op = 0;
    static const char numbers[] = "789456123";
    static const char ops[] = "+-*/";
    static double a = 0, b = 0;
    static double *current = &a;

    size_t i = 0;
    int solve = 0;
    {
      int len;
      char buffer[256];
      nk_layout_row_dynamic(ctx, 35, 1);
      len = snprintf(buffer, 256, "%.2f", *current);
      nk_edit_string(ctx, NK_EDIT_SIMPLE, buffer, &len, 255, nk_filter_float);
      buffer[len] = 0;
      *current = atof(buffer);
    }

    nk_layout_row_dynamic(ctx, 35, 4);

    for (i = 0; i < 16; ++i) {
      if (i >= 12 && i < 15) {
        if (i > 12) continue;
        if (nk_button_label(ctx, "C")) {
          a = b = op = 0;
          current = &a;
          set = 0;
        }
        if (nk_button_label(ctx, "0")) {
          *current = *current * 10.0f;
          set = 0;
        }
        if (nk_button_label(ctx, "=")) {
          solve = 1;
          prev = op;
          op = 0;
        }
      } else if (((i + 1) % 4)) {
        if (nk_button_text(ctx, &numbers[(i / 4) * 3 + i % 4], 1)) {
          *current = *current * 10.0f + numbers[(i / 4) * 3 + i % 4] - '0';
          set = 0;
        }
      } else if (nk_button_text(ctx, &ops[i / 4], 1)) {
        if (!set) {
          if (current != &b) {
            current = &b;
          } else {
            prev = op;
            solve = 1;
          }
        }
        op = ops[i / 4];
        set = 1;
      }
    }
    if (solve) {
      if (prev == '+') a = a + b;
      if (prev == '-') a = a - b;
      if (prev == '*') a = a * b;
      if (prev == '/') a = a / b;
      current = &a;
      if (set) current = &b;
      b = 0;
      set = 0;
    }
  }
  nk_end(ctx);


  nk_end(ctx);
  if (nk_begin(ctx,
               "Mywidget",
               nk_rect(0, 0, 300, 300),
               NK_WINDOW_SCALABLE | NK_WINDOW_BORDER | NK_WINDOW_MINIMIZABLE
                   | NK_WINDOW_MOVABLE)) {

  }
  nk_end(ctx);
  /* End Nuklear GUI */

  nkc_render(myapp->nkcHandle, nk_rgb(40, 40, 40));
}

int main() {
  struct my_nkc_app myapp;
  struct nkc nkcx; /* Allocate memory for Nuklear+ handle */
  myapp.nkcHandle = &nkcx;
  /* init some user data */
  myapp.value = 0.4;
  myapp.op = HARD;

  if (nkc_init(myapp.nkcHandle,
               "Calculator",
               1280,
               720,
               NKC_WIN_MAXIMIZED)) {
    printf("Successfull init. Starting 'infinite' main loop...\n");
    nkc_set_main_loop(myapp.nkcHandle, mainLoop, (void *) &myapp);
  } else {
    printf("Can't init NKC\n");
  }
  nkc_shutdown(myapp.nkcHandle);
  return 0;
}