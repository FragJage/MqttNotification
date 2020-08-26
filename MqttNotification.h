#ifndef MQTTNOTIFICATION_H
#define MQTTNOTIFICATION_H

#include <QSystemTrayIcon>
#include <mutex>
#include <queue>
#include "MqttDaemon.h"

struct MqttQueue
{
    MqttQueue(QString title,QString body) : Title(title), Body(body) {};
    QString Title;
    QString Body;
};

class MqttNotification : public MqttDaemon
{
    public:
        MqttNotification(QSystemTrayIcon* systemTrayIcon);
        ~MqttNotification();

		int DaemonLoop(int argc, char* argv[]);
        void on_message(const std::string& topic, const std::string& message);

    private:
		void DaemonConfigure(SimpleIni& iniFile);
		void MessageForService(const std::string& msg);
		void MessageForDevice(const std::string& device, const std::string& msg);
        std::string m_Name;
        bool m_bPause;
        QSystemTrayIcon* m_SystemTrayIcon;
        std::mutex m_MqttQueueAccess;
        ServiceConditionVariable m_MqttQueueCond;
        std::queue<MqttQueue> m_MqttQueue;
};
#endif // MQTTNOTIFICATION_H
