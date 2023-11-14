#!/usr/bin/env python3
# coding=utf-8

import subprocess
import socket
import threading

def client_handler(client_socket):
    # 使用Popen启动长期运行的程序，并获取其输出
    process = subprocess.Popen(
        "rosrun main_bt all_bt",
        shell=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True
   )

    # 循环读取输出
    while True:
        output = process.stdout.readline()
        if output == '' and process.poll() is not None:
            break
        if output:
            print(output.strip())
            # 将输出发送到客户端
            client_socket.sendall(output.encode('utf-8'))
    rc = process.poll()

    # 关闭客户端连接
    client_socket.close()

# 创建一个Socket服务器
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = '0.0.0.0'  # 允许所有IP连接
port = 5000  # 选择一个合适的端口号

# 绑定服务器到指定的地址和端口
server_socket.bind((host, port))

# 开始监听来自客户端的连接
server_socket.listen(5)

print(f"等待客户端连接在 {host}:{port}")

while True:
    # 等待客户端连接
    client_socket, client_address = server_socket.accept()
    print(f"接受来自 {client_address} 的连接")

    # 创建一个线程来处理新的客户端
    client_thread = threading.Thread(target=client_handler, args=(client_socket,))
    client_thread.start()

