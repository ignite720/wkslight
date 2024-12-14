#pragma once

struct Font {
    explicit Font(const char *path, int pt_size);
    ~Font();

private:
    bool load_from_file(const char *path, int pt_size);
    void drop();
    
private:
    TTF_Font *m_ttf_font = nullptr;
};