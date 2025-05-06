#include "pch.h"

#if !TARGET_PLATFORM_ANDROID
#include "app_core/net.h"

Net::Net(AppCore &app_core)
    : AppCoreObj(app_core) {
    PRINT_FUNCTION_NAME();
}

Net::~Net() {
    PRINT_FUNCTION_NAME();

    this->close();
}

void Net::connect(const char *url) {
    PRINT_FUNCTION_NAME();

    this->close();
}

void Net::close() {
    PRINT_FUNCTION_NAME();
}

void Net::send_text(const std::string &value) {
    PRINT_FUNCTION_NAME();
}

void Net::send_binary(const void *data, size_t size) {
    PRINT_FUNCTION_NAME();
}

void Net::on_open() {
    PRINT_FUNCTION_NAME();
}

void Net::on_close() {
    PRINT_FUNCTION_NAME();
}

void Net::on_error() {
    PRINT_FUNCTION_NAME();
}

void Net::on_message(const uint8_t *data, uint32_t size, bool is_text) {
    PRINT_FUNCTION_NAME();
}
#endif