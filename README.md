# C Programming Learning Journey

Welcome to this C programming repository. This project is dedicated to mastering the core concepts of C, configuring an efficient development environment, and documenting practical code examples.

---

## 🛠️ Environment Configuration

This repository is optimized for **VS Code** running inside a **Linux / Dev Container** environment.

*   **Language Server**: `clangd` (v22.1.6+) for lightning-fast autocomplete and code navigation.
*   **Build System**: `CMake` & `GNU Make` for cross-platform compilation.
*   **Debugging Engine**: Microsoft `C/C++` core extension (`cppdbg`).

### Setup Prerequisites
No manual setup is required. The entire development environment, including compilers, toolchains, and configurations, is fully automated. When the Dev Container is created, it seamlessly triggers the internal `.devcontainer/setup.sh` script to complete the environment initialization before you even type your first line of code.

---

## 🚀 How to Build and Run

This repository utilizes custom VS Code automation tasks to achieve a seamless **"One-Click F5"** build and debug workflow without relying on external UI extensions.

1.  **Select the Active File**: 
    Switch your editor tab to the specific `.c` file you want to execute (e.g., `syntax.c` or `main.c`).
2.  **Trigger One-Key Debug**:
    Simply press **`F5`** on your keyboard. 
3.  **Under the Hood (Custom Task Automation)**:
    Once **`F5`** is pressed, the custom debugging configuration automatically triggers its `preLaunchTask` dependency chain defined in `.vscode/tasks.json`:
    *   **Configure**: Runs your tailored CMake configuration command if necessary.
    *   **Compile**: Automatically builds the corresponding binary target for the active file.
    *   **Debug**: Instantly launches the `cppdbg` core engine, allowing you to trace code and hit breakpoints immediately.