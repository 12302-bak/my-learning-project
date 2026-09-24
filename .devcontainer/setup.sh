#!/bin/bash
set -e

# 备份并替换 sources.list
sudo cp /etc/apt/sources.list /etc/apt/sources.list.bak
cat > /tmp/sources.list << 'EOF'
# $(lsb_release -cs)
# https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/
# https://developer.aliyun.com/mirror/ubuntu
# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-updates main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-updates main restricted universe multiverse
# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-backports main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-backports main restricted universe multiverse

# 以下安全更新软件源为官方源配置
deb http://security.ubuntu.com/ubuntu/ noble-security main restricted universe multiverse
# deb-src http://security.ubuntu.com/ubuntu/ noble-security main restricted universe multiverse

# 预发布软件源，不建议启用
# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-proposed main restricted universe multiverse
# # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-proposed main restricted universe multiverse

EOF

sudo mv /tmp/sources.list /etc/apt/sources.list
sudo apt update
sudo apt install -y gdb cmake file xxd gdbserver ninja-build

# 安装时区数据 
sudo apt install -y tzdata && echo "Asia/Shanghai" | sudo tee /etc/timezone

# 安装 gcc-multilib 包，它包含了在 64 位机器上生成 32 位程序。
# gcc-multilib 对于交叉编译很有用，也就是说，编译一个程序以在不同的处理器架构上运行。
# 例如，如果你正在运行 64 位 Ubuntu，并且想要编译一个程序以在 32 位 Ubuntu(或 ARM 等) 上运行，你就需要 gcc-multilib
sudo apt install -y gcc-multilib

# 安装 glibc (2.39)源码
sudo apt install -y glibc-source && cd /usr/src/glibc/ && sudo tar -xf glibc-*.tar.xz

# 安装 clangd (22.1.6)，外部下载的压缩包挂载到 /mnt 目录下
# sudo unzip -qo /mnt/clangd-linux-22.1.6.zip -d /opt/ && sudo ln -s /opt/clangd_22.1.6/bin/clangd /usr/bin/clangd

echo '✅ APT source updated and tools installed!'