#ifndef DIALOG_H
#define DIALOG_H

#include <stdbool.h>
#include "../../engine/vendor/sdl_wrapper/include/context.h"

#define BLACK color(0.0f, 0.0f, 0.0f)
#define WHITE color(1.0f, 1.0f, 1.0f)

#define DIALOG_PADDING 16
#define DIALOG_MARGIN 16
#define DIALOG_HEIGHT 172

static char* msg;
static int current_char;
static bool visible;

void render_dialog(context_T* ctx);
void show_dialog(char* str);
void hide_dialog();

#endif
