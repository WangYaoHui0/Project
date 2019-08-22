#pragma once

#include <iostream>
#include <pthread.h>
#include "ProtocolUtil.hpp"
#include "UserManager.hpp"
#include "Message.hpp"
#include "Log.hpp"
#include "DataPool.hpp"

class ChatServer;

class Param
{
    public:
        ChatServer *sp;
        int sock;
        std::string ip;
        int port;
    public:
        Param(ChatServer *sp_, int &sock_, const std::string &ip_, const int &port_)
            : sp(sp_), sock(sock_), ip(ip_), port(port_)
        {}
        ~Param()
        {}
};

class ChatServer
{
    private:
        int tcp_listen_sock;
        int tcp_port;

        int udp_work_sock;
        int udp_port;

        // 用户管理，um中：id，用户，在线用户
        UserManager um;
        // Datapool：数据池 
        DataPool pool;
    public:
        ChatServer(int tcp_port_ = 8080, int udp_port_ = 8888)
            : tcp_listen_sock(-1)
            , tcp_port(tcp_port_)
            , udp_work_sock(-1)
            , udp_port(udp_port_)
        {}

        // 初始化
        void InitServer()
        {
            tcp_listen_sock = SocketApi::Socket(SOCK_STREAM);
            udp_work_sock = SocketApi::Socket(SOCK_DGRAM);
            SocketApi::Bind(tcp_listen_sock, tcp_port);
            SocketApi::Bind(udp_work_sock, udp_port);

            SocketApi::Listen(tcp_listen_sock);
        }

        // 用户注册
        unsigned int RegisterUser(const std::string &name, const std::string &school, const std::string &passwd)
        {
            return um.Insert(name, school, passwd);
        }

        // 用户登录
        unsigned int LoginUser(const unsigned int &id, const std::string &passwd, const std::string &ip, int port)
        {
           return um.Check(id, passwd);
        }
        //UDP
        void Product()
        {
            std::string message;
            struct sockaddr_in peer;
            Util::RecvMessage(udp_work_sock, message, peer);    // 读取消息
            std::cout << "debug: recv message: " << message << std::endl;
            if(!message.empty())
            {
                Message m;
                m.ToRecvValue(message);     // 消息不为空，拿到消息，反序列化
                if(m.Type() == LOGIN_TYPE)
                {
                    um.AddOnlineUser(m.Id(), peer);     // 将用户添加到在线用户列表中
                    std::string name_, school_;
                    um.GetUserInfo(m.Id(), name_, school_);     // 获取用户信息
                    Message new_msg(name_, school_, m.Text(), m.Id(), m.Type());
                    new_msg.ToSendString(message);
                }
                pool.PutMessage(message); // 将消息放到消息池里
            }
        }
        void Consume()
        {
            std::string message;
            pool.GetMessage(message);   // 从消息池中拿消息
            std::cout << "debug: send message: " << message << std::endl;
            auto online = um.OnlineUser();  // 拿到在线用户列表
            for(auto it = online.begin(); it != online.end(); it++)
            {
                Util::SendMessage(udp_work_sock, message, it->second);  // 遍历在线用户列表，将消息发给每一位在线用户
            }
        }
        static void *HandlerRequest(void *arg)
        {
            Param *p = (Param*)arg;
            int sock = p->sock;
            ChatServer *sp = p->sp;
            std::string ip = p->ip;
            int port = p->port;

            delete p;
            pthread_detach(pthread_self());

            Request rq;
            Util::RecvRequest(sock, rq);
            Json::Value root;

            LOG(rq.text, NORMAL);   // 打印收到的消息正文
            
            Util::UnSeralizer(rq.text, root);
            if(rq.method == "REGISTER")
            {
                std::string name = root["name"].asString();
                std::string school = root["school"].asString();
                std::string passwd = root["passwd"].asString();
                unsigned int id = sp->RegisterUser(name, school, passwd);
                //std::cout << id << std::endl;
                //std::cout << name << std::endl;
                //std::cout << passwd << std::endl;
                //std::cout << school << std::endl;
                send(sock, &id, sizeof(id), 0);
            }
            else if(rq.method == "LOGIN")
            {
                unsigned int id = root["id"].asInt();
                std::string passwd = root["passwd"].asString();

                //std::cout << id << std::endl;
                unsigned int result = sp->LoginUser(id, passwd, ip, port);

                //std::cout << result << std::endl;
                send(sock, &result, sizeof(result), 0);
            }
            else
            {}

            close(sock);
        }
        void Start()
        {
            std::string ip;
            int port;
            for(;;)
            {
                int sock = SocketApi::Accept(tcp_listen_sock, ip, port);
                if(sock > 0)
                {
                    std::cout << "get a new client " << ip << " : " << port << std::endl;
                    Param *p = new Param(this, sock, ip, port);
                    pthread_t tid;
                    pthread_create(&tid, NULL, HandlerRequest, p);
                }
            }
        }

        ~ChatServer()
        {}
};

















