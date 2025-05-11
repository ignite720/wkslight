#pragma once

#include "app_core/app_core_obj.h"

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

class Net : public AppCoreObj {
public:
    Net(AppCore &app_core);
    ~Net();

public:
    virtual void connect(const char *url);
    virtual void close();

    virtual void send_text(const std::string &value);
    virtual void send_binary(const void *data, size_t size);
    
public:
    virtual void on_open();
    virtual void on_close();
    virtual void on_error();
    virtual void on_message(const uint8_t *data, uint32_t size, bool is_text);
};