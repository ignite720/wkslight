#pragma once

class Font final {
public:
    explicit Font(const char *path, int pt_size);
    ~Font();

public:
    TTF_Font * get_raw_handle() const { return m_ttf_font; }

private:
    bool load_from_file(const char *path, int pt_size);
    void drop();
    
private:
    TTF_Font *m_ttf_font = nullptr;
};