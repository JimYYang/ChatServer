#pragma once

#include <vector>
#include "user.hpp"
using namespace std;

// 维护好友信息的操作接口方法
class FriendModel
{
public:
    // 添加好友关系
    void insert(int userId, int friendId);

    // 返回用户好友列表
    vector<User> query(int userId);

};