## 基于muduo网络库实现集群聊天服务器
- 使用`nginx tcp`负载均衡，`redis`实现集群聊天服务器和客户端

编译方法
- 直接使用`autobuild.sh`脚本 运行`./autobuild.sh`

- 手动编译
```
cd build
rm -rf *
cmake ..
make
```
