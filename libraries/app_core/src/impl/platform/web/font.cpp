#include "app_core_web.h"

#if TARGET_PLATFORM_WEB

Font::Font(const char *path, int pt_size) {
    auto _ret = this->load_from_file(path, pt_size);
}

Font::~Font() {
    this->drop();
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

#endif