# 🛠️ AAT-CLI-Parser (C++ 命令行解析工具库)

**同济大学面向对象程序设计期末大作业 (2024.11)**  
*Tongji University - Command Line Argument Parsing Library*

本项目核心是一个纯手搓的 C++ 命令行参数解析框架 **AAT (Args Analyse Tools)**。它旨在通过面向对象的方式，解决 C/C++ 原生 `argc/argv` 处理繁琐且难以校验的问题。


### 核心组件：
1.  **`class_aat` (核心解析类)**  
    - 支持多种数据类型：`Bool`, `Int`, `Double`, `String` 以及 **IP 地址**。
    - **约束机制**：内置范围校验 (Range Check) 和集合校验 (Set Check)。
    - **自动报表**：内置 `args_analyse_print` 函数，可自动绘制对齐的 ASCII 参数状态表。
2.  **`my_ping` (模拟工具)**  
    - 仿 Windows 系统 `ping` 命令，演示如何解析 IP 地址及可选标志位。
3.  **`my_convert` (模拟工具)**  
    - 演示了“固定位置参数”与“命名可选参数”两种不同的 CLI 设计模式。


## 🛠️ 技术栈 | Tech Stack
-   **编程语言**: C++ / C
-   **开发工具**: Visual Studio 2022
-   **核心库**: 手写 `args_analyse_tools` 框架

