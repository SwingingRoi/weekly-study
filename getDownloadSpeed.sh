#!/bin/bash

# 监控的网络接口名称，例如 eth0, wlan0 等
INTERFACE="eth1"

# 获取初始接收字节数
initial_bytes=$(cat /proc/net/dev | grep "$INTERFACE" | tr -s ' ' | cut -d ' ' -f 3)

# 等待一秒
sleep 1

# 获取下一次接收字节数
final_bytes=$(cat /proc/net/dev | grep "$INTERFACE" | tr -s ' ' | cut -d ' ' -f 3)

# 计算下载的字节数
bytes_downloaded=$((final_bytes - initial_bytes))

# 转换为 MB/s
mb_per_sec=$(echo "scale=2; $bytes_downloaded / 1024 / 1024" | bc)

echo "$mb_per_sec"

