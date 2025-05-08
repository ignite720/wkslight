#pragma once

class Font2 {
    friend class ResourceBundle;
private:
    explicit Font2(const char *path, int pt_size);
public:
    ~Font2();

public:
    TTF_Font * ttf_font_as_mut_ptr() { return m_ttf_font; }

    bool text_size(const char *text, int *w, int *h);
    SDL_Surface * render_text(const char *text, const SDL_Color &fg_color, Uint32 wrap_length);

private:
    bool load_from_file(const char *path, int pt_size);
    void drop();
    
private:
    TTF_Font *m_ttf_font = nullptr;
};