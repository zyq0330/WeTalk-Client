#WeTalk-Server
WeTalk即使通讯系统的客户端
##技术栈
-- Qt 6.11.0（MinGw 64-bit）
-- c++17
-- QTcpSocket（网络通信）
-- 自定义二进制协议（与服务端一致）
## 功能列表
-- 用户登录
-- 用户注册
-- 一对一聊天转发
-- 心跳保活（15秒发送心跳）
-- 未读消息“未读”提示
-- 聊天消息自动滚动
-- 记录气泡样式（自己/对方区分）
##项目目录结构
WeTalk-Client/
|----src/# 源文件
|----include/#头文件
|----WeTalk-Client.pro #Qt项目文件
|----REAMDE.md
|----.gitignore
##编译运行步骤
###环境要求
-Windows 10/11
-Qt 6.11.0(MinGw 64-bit)
-CMake >=3.10
-Qt Creator或MinGw命令行
###使用Qt Creator
1.打开WeTalk-Client.pro
2.选择DeskTop Qt 6.111.0 MinGW 64-bit 套件
3.点击构建->运行
###使用命令行
确保qmake和mingw32-make在PATH中
qmake WeTalk-Client.pro
mingw32-make
./debug/WeTalk-Client.exe

连接配置 
客户端默认链接127.0.0.1：8888 如需修改，在MainWindow：：on_btn_login_clicked()中更改ip端口





作者:zyq0330