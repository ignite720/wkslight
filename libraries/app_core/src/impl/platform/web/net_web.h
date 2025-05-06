#pragma once

#include "app_core/net.h"

class NetWeb : public Net {
public:
    NetWeb(AppCore &app_core);

public:
    virtual void connect(const char *url) override;
    virtual void close() override;

    virtual void send_text(const std::string &value) override;
    virtual void send_binary(const void *data, size_t size) override;
    
public:
    virtual void on_open() override;
    virtual void on_close() override;
    virtual void on_error() override;
    virtual void on_message(const uint8_t *data, uint32_t size, bool is_text) override;

private:
    EMSCRIPTEN_WEBSOCKET_T m_socket = 0;
};