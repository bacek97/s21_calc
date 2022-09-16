#define NKC_IMPLEMENTATION
#include "./nuklear+/nuklear_cross.h"
//#include "./nuklear+/nuklear.h"
//#include "GL/glxew.h"
//#include <stdio.h>

struct my_nkc_app {
  struct nkc *nkcHandle;
  /*data */
  char input[256];
  size_t input_size;
  size_t current_input_index;
};
void mainLoop(void *loopArg) {

  struct my_nkc_app *global_context = (struct my_nkc_app *) loopArg;
  struct nk_context *ctx = nkc_get_ctx(global_context->nkcHandle);

  union nkc_event e = nkc_poll_events(global_context->nkcHandle);
  if ((e.type == NKC_EWINDOW) && (e.window.param == NKC_EQUIT)) {
    nkc_stop_main_loop(global_context->nkcHandle);
  }

  int x;
  int y;
  glfwGetWindowSize(global_context->nkcHandle->window, &x, &y);

#ifdef NK_GLFW_GL3_MOUSE_GRABBING
  struct nk_vec2 mpos = global_context->nkcHandle->ctx->input.mouse.pos;
  if (mpos.x && mpos.y){
    printf("%f\n",mpos.x);
  }
#endif
  /* Nuklear GUI code */
  char buffer[global_context->input_size];
  memcpy(buffer, global_context->input, global_context->input_size);
  if (nk_begin(ctx, "Calculator", nk_rect(0, 0, x, y),
               /*NK_WINDOW_BORDER |*/ NK_WINDOW_DYNAMIC
  )) {
    float h = nk_window_get_height(ctx);
    float row_h = h / 7;
    nk_layout_row_dynamic(ctx, row_h-15, 1);

    nk_edit_string(ctx,
                   NK_EDIT_READ_ONLY,
                   buffer,
                   &global_context->current_input_index,
                   global_context->input_size,
                   nk_filter_ascii);

    nk_layout_row_dynamic(ctx, row_h, 5);
    int i = 1;
    char c[2] = "";
    for (i; i < 4; ++i) {
      nk_itoa(c, i);
      if (nk_button_label(ctx, c)) {
        strcat(buffer, c);
        global_context->current_input_index++;
      }

    }
    if (nk_button_label(ctx, "(")) {
      strcat(buffer, "(");
      global_context->current_input_index++;
    }
    if (nk_button_label(ctx, ")")) {
      strcat(buffer, ")");
      global_context->current_input_index++;
    }
    for (; i < 7; ++i) {
      nk_itoa(c, i);
      if (nk_button_label(ctx, c)) {
        strcat(buffer, c);
        global_context->current_input_index++;
      }
    }
    if (nk_button_label(ctx, "+")) {
      strcat(buffer, "+");
      global_context->current_input_index++;
    }
    if (nk_button_label(ctx, "-")) {
      strcat(buffer, "-");
      global_context->current_input_index++;
    }
    for (; i < 10; ++i) {
      nk_itoa(c, i);
      if (nk_button_label(ctx, c)) {
        strcat(buffer, c);
        global_context->current_input_index++;
      }
    }
    if (nk_button_label(ctx, "*")) {
      strcat(buffer, "*");
      global_context->current_input_index++;
    }
    if (nk_button_label(ctx, "/")) {
      strcat(buffer, "/");
      global_context->current_input_index++;
    }
    if (nk_button_label(ctx, "0")) {
      strcat(buffer, "0");
      global_context->current_input_index++;
    }
    if (nk_button_label(ctx, ".")) {
      strcat(buffer, ".");
      global_context->current_input_index++;
    }

    if (nk_button_label(ctx, "pow")) {
      strcat(buffer, "pow");
      global_context->current_input_index += 3;
    }
    if (nk_button_label(ctx, "mod")) {
      strcat(buffer, "mod");
      global_context->current_input_index += 3;
    }
    if (nk_button_label(ctx, "cos")) {
      strcat(buffer, "cos");
      global_context->current_input_index += 3;
    }
    if (nk_button_label(ctx, "sin")) {
      strcat(buffer, "sin");
      global_context->current_input_index += 3;
    }
    if (nk_button_label(ctx, "tan")) {
      strcat(buffer, "tan");
      global_context->current_input_index += 3;
    }
    if (nk_button_label(ctx, "acos")) {
      strcat(buffer, "acos");
      global_context->current_input_index += 4;
    }
    if (nk_button_label(ctx, "asin")) {
      strcat(buffer, "asin");
      global_context->current_input_index += 4;
    }
    if (nk_button_label(ctx, "atan")) {
      strcat(buffer, "atan");
      global_context->current_input_index += 4;
    }
    if (nk_button_label(ctx, "sqrt")) {
      strcat(buffer, "sqrt");
      global_context->current_input_index += 4;
    }
    if (nk_button_label(ctx, "ln")) {
      strcat(buffer, "ln");
      global_context->current_input_index += 2;
    }
    if (nk_button_label(ctx, "log")) {
      strcat(buffer, "log");
      global_context->current_input_index += 3;
    }

    if (e.type == NKC_EKEY) {
      switch (e.key.code) {
        default:printf("%d\n",e.key.code);
          break;
        case NKC_KEY_0:
        case NKC_KEY_1:
        case NKC_KEY_2:
        case NKC_KEY_3:
        case NKC_KEY_4:
        case NKC_KEY_5:
        case NKC_KEY_6:
        case NKC_KEY_7:
        case NKC_KEY_8:
        case NKC_KEY_9:
          buffer[global_context->current_input_index++] = e.key.code;
          break;
        case NKC_KEY_DELETE:buffer[0] = 0;
          global_context->current_input_index = 0;
          break;
        case NKC_KEY_E:printf("%c\n", '=');
          break;
        case NKC_KEY_S:printf("%c\n", '-');
          break;
        case NKC_KEY_M:printf("%c\n", '*');
          break;
        case NKC_KEY_A:printf("%c\n", '+');
          break;
        case NKC_KEY_D:printf("%c\n", '/');
          break;
        case NKC_KEY_BACKSPACE:
          buffer[global_context->current_input_index--] = 0;

          break;
      }
    }
    memcpy(global_context->input, buffer, global_context->input_size);
  }
  nk_end(ctx);
/* End Nuklear GUI */

  nkc_render(global_context->nkcHandle, nk_rgb(0, 0, 0));
}

int main() {
  struct my_nkc_app global_context;
  struct nkc nkcx; /* Allocate memory for Nuklear+ handle */
  global_context.nkcHandle = &nkcx;
  /* user data */
  global_context.input_size = 256;
  global_context.current_input_index = 0;
  global_context.input[0] = '\0';
  //memset(global_context.input, ' ', global_context.input_size);
  global_context.input[global_context.input_size - 1] = 0;
  /*user data end*/
  if (nkc_init(global_context.nkcHandle,
               "Calculator",
               1280,
               720,
               NKC_WIN_MAXIMIZED)) {
    nkc_set_main_loop(global_context.nkcHandle,
                      mainLoop,
                      (void *) &global_context);
  } else {
    printf("Can't init NKC\n");
  }
  nkc_shutdown(global_context.nkcHandle);
  return 0;
}