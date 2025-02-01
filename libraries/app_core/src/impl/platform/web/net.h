#pragma once

class Net : public WebObject {
public:
    Net(AppCore *app_core);
    ~Net();

public:
    void connect_to(const char *url);
    void close();

    void send_text(const String &value);
    void send_binary(const void *data, size_t size);
    
private:
    EMSCRIPTEN_WEBSOCKET_T m_socket = 0;
};