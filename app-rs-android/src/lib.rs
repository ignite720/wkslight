use log::info;

#[link(name = "app_core")]
extern {
    fn app_core_startup() -> core::ffi::c_int;
}

#[no_mangle]
fn android_main(app: android_activity::AndroidApp) {
    android_logger::init_once(android_logger::Config::default().with_min_level(log::Level::Info));

    info!("hi");
    println!("hello");
    unsafe {
        let ret = app_core_startup();
        info!("RUST: {ret}");
    }
    info!("world");
}