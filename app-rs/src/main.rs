#[cfg_attr(not(target_os = "android"), link(name = "app_core"))]
unsafe extern "C" {
    fn app_core_startup(argc: core::ffi::c_int, argv: *const *const core::ffi::c_char) -> core::ffi::c_int;
}

fn main() {
    let args: Vec<String> = std::env::args().collect();
    println!("RUST: args={:?}", args);

    let argc = args.len() as core::ffi::c_int;
    let c_args: Vec<_> = args
        .iter()
        .map(|s| std::ffi::CString::new(s.as_str()).unwrap())
        .collect();
    let mut argv: Vec<_> = c_args.iter().map(|s| s.as_ptr()).collect();
    argv.push(core::ptr::null());

    unsafe {
        let ret = app_core_startup(argc, argv.as_ptr());
        println!("RUST: ret={}", ret);
    }
}