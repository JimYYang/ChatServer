#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <unordered_map>
#include <functional>
#include <string>
#include <muduo/net/TcpConnection.h>
#include <mutex>
#include "json.hpp"
#include "userModel.hpp"
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"

using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;
using json = nlohmann::json;

// 表示处理消息的事件回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp Time)>;

// 聊天服务器业务类
class ChatService
{
public:
    // 获取单例对象的接口函数
    static ChatService* instance();
    
    // 处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp Time);
    
    // 处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp Time);
    
    // 一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp Time);

    // 添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp Time);

    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);

    // 处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);

    // 服务器异常 业务重置方法
    void reset();

private:
    // 单例模式 构造函数私有化
    ChatService();
    
    // 存储消息id和其对应的业务处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;
    
    // 存储在线用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    // 定义互斥锁 保证_userConnMap的线程安全
    mutex _connMutex;

    // 数据操作类对象
    UserModel _userModel;
    
    // 离线消息操作对象
    OfflineMsgModel _offlineMsgModel;

    // 好友管理操作对象
    FriendModel _friendModel;
};

#endif