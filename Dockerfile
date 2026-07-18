FROM ubuntu:20.04

# Avoid prompts during apt install
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    gcc-multilib \
    gdb \
    qemu-system-x86 \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/xv6
