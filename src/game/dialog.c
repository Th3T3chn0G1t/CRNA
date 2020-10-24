#include "include/dialog.h"

void render_dialog(context_T* ctx) {
    if(msg && visible) {
        set_color(ctx, BLACK);
        fill_rect(ctx, DIALOG_MARGIN - ctx->offset_x, ctx->image->surface->h - DIALOG_MARGIN - DIALOG_HEIGHT - ctx->offset_y, ctx->image->surface->w - (2 *  DIALOG_MARGIN), DIALOG_HEIGHT);

        set_color(ctx, WHITE);

        char render[strlen(msg)];
        strncpy(render, msg, current_char + 1);
        
        draw_string_bounded(ctx, render, DIALOG_MARGIN - ctx->offset_x + DIALOG_PADDING, ctx->image->surface->h - DIALOG_MARGIN - DIALOG_HEIGHT - ctx->offset_y + DIALOG_PADDING, (ctx->image->surface->w - (2 *  DIALOG_MARGIN)) - (2 * DIALOG_PADDING));

        current_char++;
        if(!msg[current_char])
            current_char--;
    }
}

void show_dialog(char* str) {
    msg = str;
    current_char = 0;
    visible = true;
}

void hide_dialog() {
    visible = false;
}
