#include "app_core_web.h"

Font::Font(const char *path, int pt_size) {
    auto _ret = this->load_from_file(path, pt_size);
}

Font::~Font() {
    this->drop();
}

bool Font::text_size(const char *text, int *w, int *h) {
    if (TTF_SizeUTF8(m_ttf_font, text, w, h) != 0) {
        printf("%s => Failed to calculate the dimensions of the given text: %s\n", FUNCTION_NAME, TTF_GetError());
        return false;
    }
    return true;
}

SDL_Surface * Font::render_text(const char *text, const SDL_Color &fg_color, Uint32 wrap_length) {
    return TTF_RenderUTF8_Blended_Wrapped(m_ttf_font, text, fg_color, wrap_length);
}

bool Font::load_from_file(const char *path, int pt_size) {
    this->drop();
    
    m_ttf_font = TTF_OpenFont(path, pt_size);
    if (!m_ttf_font) {
        printf("%s => Failed to load Font[%s][%d]: %s\n", FUNCTION_NAME, path, pt_size, TTF_GetError());
        return false;
    }
    
    printf("%s => Font[%s][%d] loaded successfully.\n", FUNCTION_NAME, path, pt_size);
    return true;
}

void Font::drop() {
    if (m_ttf_font) {
        TTF_CloseFont(m_ttf_font);

        m_ttf_font = nullptr;
    }
}