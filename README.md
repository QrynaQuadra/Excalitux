# ⚔️ ExcaliTux Suite v1.0 (Pure C & Raylib)

> **The missing Control Center for Casper Excalibur G870 laptops on Linux.**

ExcaliTux is a lightweight, high-performance, Cyberpunk-themed hardware control suite written in **Pure C** using the **Raylib** GUI framework. It bridges the gap for Linux users on Casper Excalibur hardware, providing GPU switching, performance profile management, and RGB keyboard lighting control.

---

## ✨ Features

* 🚀 **GPU Mode Switching:** Seamlessly switch between Intel (Power Saving), NVIDIA (Performance), and On-Demand (Hybrid) modes via `prime-select`.
* ⚡ **Performance Profiles:** Adjust power consumption on the fly (Office / Gaming / Turbo) integrated with `powerprofilesctl`.
* 🔴 **RGB Control:** Custom keyboard LED lighting controls using `OpenRGB`.
* 🌡️ **Live Thermal Monitoring:** Real-time CPU temperature gauge directly reading from Linux system thermal zones.
* 🎨 **Cyberpunk UI:** Ultra-fast, lightweight 60 FPS graphical interface built with Raylib.

---

## 🛠️ Prerequisites & Dependencies

To build and run ExcaliTux, ensure you have the following installed on your Linux distribution:

`sudo apt update && sudo apt install build-essential libraylib-dev openrgb power-profiles-daemon`

---

## ⚙️ Building & Running

1. **Clone the repository:**
   `git clone [https://github.com/QrynaQuadra/Excalitux.git](https://github.com/QrynaQuadra/Excalitux.git)`
   `cd Excalitux`

2. **Compile with GCC & Raylib:**
   `gcc main.c -o excalitux -lraylib -lGL -lm -lpthread -ldl -lrt -lX11`

3. **Run the suite:**
   `./excalitux`

---

## 🤝 Contributing (Pull Requests are Welcome!)

This project was started to solve a real Linux compatibility problem for Excalibur users. **We need your help to make it even better!**

### 🎯 Roadmap & Help Needed:
- [ ] Fan Speed Control (ACPI/Kernel module integration).
- [ ] Refactoring `system()` calls to native C execution (`execvp` / POSIX APIs) for better security & performance.
- [ ] Dynamic OpenRGB profile parsing.
- [ ] Native `.desktop` entry & Installer script (`make install`).

If you have an Excalibur laptop or want to contribute to Linux hardware tooling in C, feel free to **Fork**, **Open Issues**, and submit **Pull Requests**!

---

## 📜 License

Distributed under the MIT License. Feel free to modify, distribute, and contribute.
