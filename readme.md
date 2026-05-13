# 🛠️ AAT-CLI-Parser (C++ Command Line Argument Parsing Library)

**Tongji University - Object-Oriented Programming Final Project (2024.11)**

## 📖 Introduction | 项目简介
本项目核心是一个纯手搓的 C++ 命令行参数解析框架 **AAT (Args Analyse Tools)**。它旨在通过面向对象的方式，解决 C/C++ 原生 `argc`/`argv` 处理繁琐且难以校验的问题。

The core of this project is a handcrafted C++ command-line argument parsing framework, **AAT (Args Analyse Tools)**. It aims to solve the complex and hard-to-validate nature of native `argc`/`argv` handling in C/C++ through an object-oriented approach.

## 🧩 Core Components | 核心组件
1. **`class_aat` (Core Parsing Class | 核心解析类)**
   - 支持多种数据类型：`Bool`, `Int`, `Double`, `String` 以及 **IP 地址**。
   - Supports multiple data types: `Bool`, `Int`, `Double`, `String`, and **IP Address**.
   - **约束机制**：内置范围校验 (Range Check) 和集合校验 (Set Check)。
   - **Constraint Mechanism**: Built-in Range Check and Set Check.
   - **自动报表**：内置 `args_analyse_print` 函数，可自动绘制对齐的 ASCII 参数状态表。
   - **Auto-Reporting**: Built-in `args_analyse_print` function to automatically generate aligned ASCII parameter status tables.

2. **`my_ping` (Simulation Tool | 模拟工具)**
   - 仿 Windows 系统 `ping` 命令，演示如何解析 IP 地址及可选标志位。
   - A simulated Windows "ping" command demonstrating how to parse IP addresses and optional flags.

3. **`my_convert` (Simulation Tool | 模拟工具)**
   - 演示了“固定位置参数”与“命名可选参数”两种不同的 CLI 设计模式。
   - Demonstrates two different CLI design patterns: "Fixed Position Arguments" and "Named Optional Arguments."

## 🛠️ Tech Stack
- **Programming Language**: C++ / C
- **IDE**: Visual Studio 2022
- **Core Engine**: Handcrafted `args_analyse_tools` framework

