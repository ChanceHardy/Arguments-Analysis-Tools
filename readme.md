🛠️ AAT-CLI-Tools (C++ 命令行参数解析库)
同济大学《高级语言程序设计》专项练习 (2024.12)
Tongji University - CLI Argument Parsing Library & Tools
本项目核心是一个纯手搓的 C++ 命令行参数解析库 (class_aat)。它能够优雅地处理 argc 和 argv，支持复杂的参数校验和自动化的帮助信息生成。
📖 项目简介 | About
在没有使用 AI 工具的情况下，我从底层实现了这个名为 AAT (Args Analyse Tools) 的类库。它不仅能解析基础字符串，还能进行范围检查、集合限制以及自动化的 ASCII 表格输出。
包含组件：
class_aat (核心库)
支持 bool, int, double, string 以及 IP 地址 类型的自动解析。
内置 自动排版功能：一键生成对齐的参数状态表格。
my_ping (模拟工具)
基于 AAT 库实现的命令行 Ping 工具模拟，演示了如何解析 IP 地址和可选参数。
my_convert (模拟工具)
演示了两种命令行风格（固定位置参数 vs 命名参数）的文件格式转换器模拟。
✨ 技术亮点 | Features
严格校验：支持数值范围校验 (min/max) 和字符串集合约束 (wtol/ltow)。
容错处理：支持“报错并退出”或“使用缺省默认值”两种解析逻辑。
工程化实践：展示了如何使用静态链接库 (.lib) 在多项目间共享代码。
🛠️ 技术栈 | Tech Stack
编程语言: C++ / C
开发工具: Visual Studio 2022
核心组件: 手写 args_analyse_tools 类 (无第三方依赖)
