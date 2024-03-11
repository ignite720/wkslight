#[link(name = "app_core")]
extern {
    fn app_core();
}

fn main() {
    unsafe { app_core() }
}