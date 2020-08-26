#include <QApplication>
#include <QSystemTrayIcon>
#include <iostream>
#include <exception>
#include "MqttNotification.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QIcon icon("://new/prefix1/tache_rouge.png");
    QSystemTrayIcon systemTrayIcon(&a);
    systemTrayIcon.setIcon(icon);
    systemTrayIcon.show();

    int res = 0;

    try
    {
        MqttNotification mqttNotification(&systemTrayIcon);
        Service* pService = Service::Create("MqttNotification", "Notifications from mqtt protocol", &mqttNotification);
        res = pService->Start(argc, argv);
        Service::Destroy();
    }
    catch(const std::exception &e)
    {
        std::cout << e.what();
    }

    #if defined(_MSC_VER) && defined(DEBUG)
    cout << "Press any key..." << endl;
    getchar();
    #endif

    return res;
}
