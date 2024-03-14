#[link(name = "app_core")]
extern {
    fn app_core_init();
}

fn main() {
    unsafe { app_core_init() }
}