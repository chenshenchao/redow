# redow

[English](Readme.md) | 简体中文

# 简介

又一个 Redis 的 Windows 服务安装包。

[下载](https://github.com/chenshenchao/redow/releases)

安装后通过 Redow 服务管理开关 Redis(7.0.14) 服务器。

# 编译

安装 [Msys2](https://www.msys2.org/)。

```bash
# Msys2 更新
pacman -Syu

# Msys2 安装编译工具
pacman -Sy gcc make pkg-config
```

需要把 Msys2 安装目录和其目录下 usr/bin 两个路径添加到环境变量 PATH 里面。

注：报找不到结构 Dl_info 错误时，MSYS2 目录下 /usr/include/dlfcn.h 修改源码，注释掉 宏判定 #if __GNU_VISIBLE #endif。
