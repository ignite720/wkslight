#include "app_core_web.h"

static EM_BOOL s_ws_onopen(int event_type, const EmscriptenWebSocketOpenEvent *websocket_event, void *user_data) {
    auto *net = static_cast<Net *>(user_data);
    net->on_open();
    return EM_TRUE;
}

static EM_BOOL s_ws_onclose(int event_type, const EmscriptenWebSocketCloseEvent *websocket_event, void *user_data) {
    auto *net = static_cast<Net *>(user_data);
    net->on_close();
    return EM_TRUE;
}

static EM_BOOL s_ws_onerror(int event_type, const EmscriptenWebSocketErrorEvent *websocket_event, void *user_data) {
    auto *net = static_cast<Net *>(user_data);
    net->on_error();
    return EM_TRUE;
}

static EM_BOOL s_ws_onmessage(int event_type, const EmscriptenWebSocketMessageEvent *websocket_event, void *user_data) {
    auto *net = static_cast<Net *>(user_data);
    net->on_message(websocket_event->data, websocket_event->numBytes, websocket_event->isText);
    return EM_TRUE;
}

Net::Net(AppCore *app_core)
    : WebObject(app_core) {
    assert(emscripten_websocket_is_supported());
}

Net::~Net() {
    this->close();
}

void Net::connect(const char *url) {
    this->close();

    auto create_attrs = EmscriptenWebSocketCreateAttributes { url, nullptr, EM_TRUE };
    m_socket = emscripten_websocket_new(&create_attrs);

    emscripten_websocket_set_onopen_callback(m_socket, this, __ws_onopen);
    emscripten_websocket_set_onclose_callback(m_socket, this, __ws_onclose);
    emscripten_websocket_set_onerror_callback(m_socket, this, __ws_onerror);
    emscripten_websocket_set_onmessage_callback(m_socket, this, __ws_onmessage);
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

void Net::on_open() {
    PRINT_FUNCTION_NAME();

    this->send_text("hi");
    
    {
        auto pkt = FooNetPacket(0xabcd);
        this->send_binary(&pkt, sizeof(pkt));
    }
    {
        auto pkt = BarNetPacket { 0xabcdefab };
        this->send_binary(&pkt, sizeof(pkt));
    }
}

void Net::on_close() {
    PRINT_FUNCTION_NAME();
}

void Net::on_error() {
    PRINT_FUNCTION_NAME();
}

void Net::on_message(const uint8_t *data, uint32_t size, bool is_text) {
    PRINT_FUNCTION_NAME();

    if (is_text) {
        auto message = String { data, data + size };
        printf("message(text): %s\n", message.c_str());
    } else {
        const auto kind = static_cast<NetPacketKind>(data[0]);
        switch (kind) {
            case NetPacketKind::Foo: {
                const auto *pkt = reinterpret_cast<const FooNetPacket *>(data);
                printf("message(binary): 0x%08x\n", pkt->i);
            } break;
            case NetPacketKind::Bar: {
                auto pkt = BarNetPacket { 0 };
                memcpy(&pkt, data, size);
                printf("message(binary): 0x%08x\n", pkt.j);
            } break;
        }
    }
}