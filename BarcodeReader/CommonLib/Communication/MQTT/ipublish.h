#ifndef IPUBLISH_H
#define IPUBLISH_H

#include "publisher.h"

class IPublish
{
public:
    explicit IPublish(const QString &name);

    /// QMqttClient的初始化
    /// client 需要绑定的QMqttClient
    /// prefix topic的前缀
    /// topic
    bool LinkToPublishClient(MqttClient *client, const QString &prefix, const QString &topic);

    /// 通过QMqttClient发布信息
    /// cmd 发送信息的命令
    /// result 当前指令的执行结果
    /// ba 当前指令的具体内容
    void Publish(const QString &cmd, bool result = true, const QByteArray &ba = QByteArray(), const QByteArray &errMsg = QByteArray());

    bool IsClientConnected();

    QString Topic();

    QString Name();

    Publisher *GetPublisher();

    /// 需要周期性发送信息时重写,会在LinkClient()方法内调用
    virtual void SetPeriodPublish() {};

    /// 需要软件启动发送信息时重写，会在LinkClient()方法内调用
    virtual void StartPublish() {};

protected:
    /// 在LinkClient()方法内调用
    virtual void initialize() {};

protected:
    Publisher m_Publisher;
    QString m_Prefix;
    QString m_Topic;
    QString m_Name;
};

#endif // IPUBLISH_H
