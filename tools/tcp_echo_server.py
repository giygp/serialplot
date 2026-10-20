#!/usr/bin/env python3
"""简易 TCP 回环测试服务器：用于验证 serialplot 的 TcpControl 能否连上。

用法:
    python tools/tcp_echo_server.py            # 默认监听 127.0.0.1:8080
    python tools/tcp_echo_server.py 9000       # 监听 127.0.0.1:9000

行为:
    - 打印每个客户端的连接/断开
    - 打印收到的数据(hex + 文本预览), 并原样回发(echo)
    - Ctrl+C 退出
"""
import socket
import sys
import threading

HOST = "127.0.0.1"


def handle_client(conn, addr):
    print(f"[+] 客户端已连接: {addr}")
    try:
        while True:
            data = conn.recv(4096)
            if not data:
                break
            print(f"    收到 {len(data)} 字节: {data.hex(' ')}  |  {data.decode(errors='replace')!r}")
            conn.sendall(data)  # 原样回发
    except ConnectionError:
        pass
    finally:
        conn.close()
        print(f"[-] 客户端已断开: {addr}")


def main():
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 8080
    srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv.bind((HOST, port))
    srv.listen(5)
    print(f"TCP 测试服务器已启动: {HOST}:{port}，等待 serialplot 连接... (Ctrl+C 退出)")
    try:
        while True:
            conn, addr = srv.accept()
            threading.Thread(target=handle_client, args=(conn, addr), daemon=True).start()
    except KeyboardInterrupt:
        print("\n服务器已停止")
    finally:
        srv.close()


if __name__ == "__main__":
    main()
