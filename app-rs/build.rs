fn main() {
    println!("cargo:rustc-link-search=native=target/release");
    
    //println!("cargo:rustc-link-lib=app_core_d3d12");
    //println!("cargo:rustc-link-lib=app_core_vulkan");
    //println!("cargo:rustc-link-lib=app_core");
    //println!("cargo:rustc-link-lib=foo");
    //println!("cargo:rustc-link-lib=spdlog");
    //println!("cargo:rustc-link-lib=stdc++");
    
    let rpath_arg = if cfg!(target_os = "linux") {
        "-Wl,-rpath,$ORIGIN"
    } else if cfg!(target_os = "macos") {
        "-Wl,-rpath,@loader_path"
    } else {
        ""
    };

    if !rpath_arg.is_empty() {
        println!("cargo:rustc-link-arg={}", rpath_arg);
    }
}