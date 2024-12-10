#[cfg_attr(not(target_os = "android"), link(name = "app_core"))]
extern {
    fn app_core_startup() -> core::ffi::c_int;
}

fn main() {
    unsafe {
        let ret = app_core_startup();
        println!("RUST: {}", ret);
    }
}