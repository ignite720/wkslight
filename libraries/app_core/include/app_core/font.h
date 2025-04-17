#pragma once

#include "app_core/app_core_sdl.h"

class Font {
    friend class ResourceBundle;
private:
    explicit Font(const char *path, int pt_size);
public:
    ~Font();

public:
    bool text_size(const char *text, int *w, int *h);
    SDL_Surface * render_text(const char *text, const SDL_Color &fg_color, Uint32 wrap_length);

private:
    bool load_from_file(const char *path, int pt_size);
    void drop();
    
private:
    TTF_Font *m_ttf_font = nullptr;
};