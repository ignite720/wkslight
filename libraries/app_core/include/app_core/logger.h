#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/dist_sink.h>

#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

inline auto g_logger_sinks = std::make_shared<spdlog::sinks::dist_sink_mt>();
inline auto g_logger = std::make_shared<spdlog::logger>("logger", g_logger_sinks);

inline void g_setup_logger() {
    auto daily_file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("log.txt", 0, 5);
    daily_file_sink->set_level(spdlog::level::trace);
    daily_file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%l] %v");
    g_logger_sinks->add_sink(daily_file_sink);

    auto console_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);
    g_logger_sinks->add_sink(console_sink);

    g_logger->flush_on(spdlog::level::info);
    g_logger->set_level(spdlog::level::trace);
    spdlog::flush_every(std::chrono::seconds(5));
}

#define LOG_TRACE(...)                                          g_logger->trace(__VA_ARGS__)
#define LOG_DEBUG(...)                                          g_logger->debug(__VA_ARGS__)
#define LOG_INFO(...)                                           g_logger->info(__VA_ARGS__)
#define LOG_WARN(...)                                           g_logger->warn(__VA_ARGS__)
#define LOG_ERROR(...)                                          g_logger->error(__VA_ARGS__)
#define LOG_CRITICAL(...)                                       g_logger->critical(__VA_ARGS__)