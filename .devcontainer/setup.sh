#!/bin/bash
set -e

# 备份并替换 sources.list
sudo cp /etc/apt/sources.list /etc/apt/sources.list.bak
cat > /tmp/sources.list << 'EOF'
# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-updates main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-backports main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-backports main restricted universe multiverse

# 以下安全更新软件源包含了官方源与镜像站配置，如有需要可自行修改注释切换
deb http://security.ubuntu.com/ubuntu/ noble-security main restricted universe multiverse
# deb-src http://security.ubuntu.com/ubuntu/ noble-security main restricted universe multiverse

# 预发布软件源，不建议启用
# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-proposed main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-proposed main restricted universe multiverse
EOF

sudo mv /tmp/sources.list /etc/apt/sources.list
sudo apt update
sudo apt install -y gdb cmake file xxd gdbserver

# 安装时区数据 
sudo apt install -y tzdata && echo "Asia/Shanghai" | sudo tee /etc/timezone

# 安装 gcc-multilib 包，它包含了在 64 位机器上生成 32 位程序所需的 32 位库和头文件
sudo apt install -y gcc-multilib

# 安装 glibc (2.39)源码
sudo apt install -y glibc-source && cd /usr/src/glibc/ && sudo tar -xf glibc-*.tar.xz

echo '✅ APT source updated and tools installed!'