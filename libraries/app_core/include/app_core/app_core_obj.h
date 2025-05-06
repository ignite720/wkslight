#pragma once

class AppCoreObj {
public:
    AppCoreObj(AppCore &app_core) : m_app_core(app_core) {}
    virtual ~AppCoreObj() = default;

public:
    const AppCore * app_core_as_ptr() const { return &m_app_core; }
    AppCore * app_core_as_mut_ptr() { return &m_app_core; }

private:
    AppCore &m_app_core;
};