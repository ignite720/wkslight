use log::info;

#[link(name = "app_core")]
extern {
    fn app_core_init();
}

#[no_mangle]
fn android_main(app: android_activity::AndroidApp) {
    android_logger::init_once(android_logger::Config::default().with_min_level(log::Level::Info));

    info!("hello");
    println!("hello world");
    unsafe {
        app_core_init()
    }
    info!("world");
}