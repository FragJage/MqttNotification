#include<iostream>
#include<QHostInfo>
#include<QJsonDocument>
#include<QJsonObject>
#include<QString>

#ifdef WIN32
#include <WinSock2.h>		// To stop windows.h including winsock.h
#endif

#include "MqttNotification.h"

using namespace std;

MqttNotification::MqttNotification(QSystemTrayIcon* systemTrayIcon) : MqttDaemon("Notification", "MqttNotification")
{
    m_SystemTrayIcon = systemTrayIcon;
    m_bPause = false;
    m_Name = "";
}

MqttNotification::~MqttNotification()
{
}

void MqttNotification::DaemonConfigure(SimpleIni& iniFile)
{
    LOG_ENTER;
	for (SimpleIni::SectionIterator itSection = iniFile.beginSection(); itSection != iniFile.endSection(); ++itSection)
	{
        if ((*itSection) == "notification")
        {
            m_Name = iniFile.GetValue("notification", "name", "");
        }
	}
	LOG_EXIT_OK;
}

void MqttNotification::on_message(const string& topic, const string& message)
{
	LOG_VERBOSE(m_Log) << "Mqtt receive " << topic << " : " << message;

	string mainTopic = GetMainTopic();
	if (topic.substr(0, mainTopic.length()) != mainTopic)
	{
		LOG_WARNING(m_Log) << "Not for me (" << mainTopic << ")";
		return;
	}

    if(m_bPause)
    {
        LOG_VERBOSE(m_Log) << "Daemon in pause.";
        return;
    }

    QString body;
    QString title = "MqttNotification";

    QString qstr = QString::fromStdString(message);
    QJsonDocument jsonDoc(QJsonDocument::fromJson(qstr.toUtf8()));
    QJsonObject jsonObj = jsonDoc.object();
    if (jsonObj.contains("body") && jsonObj["body"].isString())
            body = jsonObj["body"].toString();
    if (jsonObj.contains("title") && jsonObj["title"].isString())
            title = jsonObj["title"].toString();

    if(body=="") body = qstr;

    //m_SystemTrayIcon->showMessage(title, body, QSystemTrayIcon::Information);
    lock_guard<mutex> lock(m_MqttQueueAccess);
    m_MqttQueue.emplace(title, body);
    m_MqttQueueCond.notify_one();
}

int MqttNotification::DaemonLoop(int argc, char* argv[])
{
	LOG_ENTER;

    if(m_Name=="")
    {
        QString hostname = QHostInfo::localHostName();
        m_Name = hostname.toStdString();
    }

    Subscribe(GetMainTopic() + "command/ALL");
    LOG_VERBOSE(m_Log) << "Subscript to : " << GetMainTopic() + "command/ALL";
    Subscribe(GetMainTopic() + "command/" + m_Name);
    LOG_VERBOSE(m_Log) << "Subscript to : " << GetMainTopic() + "command/" + m_Name;

	bool bStop = false;
	while(!bStop)
    {
        int cond = Service::Get()->Wait({ m_MqttQueueCond });
		if (cond == Service::STATUS_CHANGED)
		{
			switch (Service::Get()->GetStatus())
			{
                case Service::StatusKind::PAUSE:
                    m_bPause = true;
                    break;
                case Service::StatusKind::START:
                    m_bPause = false;
                    cond = 1;
                    break;
                case Service::StatusKind::STOP:
                    bStop = true;
                    break;
			}
		}
        if((!m_bPause)&&(cond == 1))
        {
            lock_guard<mutex> lock(m_MqttQueueAccess);
            while (!m_MqttQueue.empty())
            {
                MqttQueue& mqttQueue = m_MqttQueue.front();
                m_SystemTrayIcon->showMessage(mqttQueue.Title, mqttQueue.Body, QSystemTrayIcon::Information);
                m_MqttQueue.pop();
            }
        }
    }

	LOG_EXIT_OK;
    return 0;
}
