#include "app_core_web.h"

static EM_BOOL s_onopen(int event_type, const EmscriptenWebSocketOpenEvent *websocket_event, void *user_data) {
    PRINT_FUNCTION_NAME();

    return EM_TRUE;
}

static EM_BOOL s_onclose(int event_type, const EmscriptenWebSocketCloseEvent *websocket_event, void *user_data) {
    PRINT_FUNCTION_NAME();

    return EM_TRUE;
}

static EM_BOOL s_onerror(int event_type, const EmscriptenWebSocketErrorEvent *websocket_event, void *user_data) {
    PRINT_FUNCTION_NAME();

    return EM_TRUE;
}

static EM_BOOL s_onmessage(int event_type, const EmscriptenWebSocketMessageEvent *websocket_event, void *user_data) {
    PRINT_FUNCTION_NAME();
    
    if (websocket_event->isText) {
        auto message = String { websocket_event->data, websocket_event->data + websocket_event->numBytes };
        printf("message: %s\n", message.c_str());
    }
    
    return EM_TRUE;
}

Net::Net(AppCore *app_core)
    : WebObject(app_core) {
    assert(emscripten_websocket_is_supported());
}

Net::~Net() {
    this->close();
}

void Net::connect_to(const char *url) {
    this->close();

    auto create_attrs = EmscriptenWebSocketCreateAttributes { url, nullptr, EM_TRUE };
    m_socket = emscripten_websocket_new(&create_attrs);

    emscripten_websocket_set_onopen_callback(m_socket, nullptr, s_onopen);
    emscripten_websocket_set_onclose_callback(m_socket, nullptr, s_onclose);
    emscripten_websocket_set_onerror_callback(m_socket, nullptr, s_onerror);
    emscripten_websocket_set_onmessage_callback(m_socket, nullptr, s_onmessage);
}

void Net::close() {
    if (m_socket > 0) {
        emscripten_websocket_close(m_socket, 100, "reason");
        emscripten_websocket_delete(m_socket);
        m_socket = 0;
    }
}

void Net::send_text(const String &value) {
    emscripten_websocket_send_utf8_text(m_socket, value.c_str());
}

void Net::send_binary(const void *data, size_t size) {
    emscripten_websocket_send_binary(m_socket, const_cast<void *>(data), size);
}