#pragma once

enum class NetPacketKind : uint8_t {
    Foo,
    Bar,
    Count
};

struct NetPacket {
    explicit NetPacket(NetPacketKind kind_) : kind(kind_) {}

    NetPacketKind kind;
};

struct FooNetPacket : NetPacket {
    explicit FooNetPacket(uint16_t i_) : NetPacket(NetPacketKind::Foo), i(i_) {}

    uint16_t i;
};

struct BarNetPacket : NetPacket {
    explicit BarNetPacket(uint32_t j_) : NetPacket(NetPacketKind::Bar), j(j_) {}

    uint32_t j;
};

class Net : public WebObject {
public:
    Net(AppCore *app_core);
    ~Net();

public:
    void connect(const char *url);
    void close();

    void send_text(const String &value);
    void send_binary(const void *data, size_t size);
    
public:
    void on_open();
    void on_close();
    void on_error();
    void on_message(const uint8_t *data, uint32_t size, bool is_text);

private:
    EMSCRIPTEN_WEBSOCKET_T m_socket = 0;
};