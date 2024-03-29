#[cfg(target_os = "android")]
#[no_mangle]
fn android_main(_app: android_activity::AndroidApp) {
    use log::info;
    use ndk::trace;

    android_logger::init_once(android_logger::Config::default().with_min_level(log::Level::Info));

    let _trace;
    if trace::is_trace_enabled() {
        _trace = trace::Section::new("ndk-rs example main").unwrap();
    }

    info!("hello world");
    println!("hello world");
}