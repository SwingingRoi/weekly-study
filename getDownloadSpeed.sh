#!/bin/bash

# 监控的网络接口名称，例如 eth0, wlan0 等
INTERFACE=$1
SLEEPTIME=0.1
# 获取初始接收字节数（注意这里使用 -f 10 来获取正确的接收字节数）
initial_bytes=$(cat /proc/net/dev | grep "$INTERFACE" | tr -s ' ' | cut -d ' ' -f 10)
initial_bytes=$(echo $initial_bytes | sed 's/,//g')  # 移除可能的逗号（如果字节数很大）
initial_bytes=$((10#$initial_bytes))  # 确保转换为十进制整数

# 等待一秒
sleep $SLEEPTIME

# 获取下一次接收字节数
final_bytes=$(cat /proc/net/dev | grep "$INTERFACE" | tr -s ' ' | cut -d ' ' -f 10)
final_bytes=$(echo $final_bytes | sed 's/,//g')  # 移除可能的逗号
final_bytes=$((10#$final_bytes))  # 确保转换为十进制整数

# 计算下载的字节数
bytes_downloaded=$((final_bytes - initial_bytes))
bytes_downloaded=$(echo "$bytes_downloaded / $SLEEPTIME" | bc)  # 因为 sleep 的是小数秒，这里用 bc 计算
更准确

# 转换为 MB/s
mb_per_sec=$(echo "scale=2; $bytes_downloaded / 1024 / 1024" | bc)

echo "$mb_per_sec"
