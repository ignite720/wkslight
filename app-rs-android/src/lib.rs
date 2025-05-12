use log::info;

#[link(name = "app_core")]
unsafe extern "C" {
    fn app_core_startup(argc: core::ffi::c_int, argv: *const *const core::ffi::c_char) -> core::ffi::c_int;
}

#[no_mangle]
fn android_main(_app: android_activity::AndroidApp) {
    android_logger::init_once(android_logger::Config::default().with_max_level(log::Level::Info));

    info!("hi");
    println!("hello");

    let args = vec![std::ffi::CString::new("wkslight").unwrap()];
    let mut argv: Vec<_> = args.iter().map(|s| s.as_ptr()).collect();
    argv.push(core::ptr::null());

    let argc = (argv.len() - 1) as i32;

    unsafe {
        let ret = app_core_startup(argc, argv.as_ptr());
        info!("RUST: {ret}");
    }
    info!("world");
}