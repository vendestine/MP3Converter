#include "mainwindow.h"

#include <QApplication>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include "appsettingsmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置组织和应用信息
    QCoreApplication::setOrganizationName("WenzheCode");
    QCoreApplication::setOrganizationDomain("com.wenzhecode.mp3converter");
    QCoreApplication::setApplicationName("Mp3Converter");

    // 获取应用程序数据存储路径
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir configDir(dataPath + "/conf");

    // 确保配置目录存在
    if (!configDir.exists())
    {
        if (!configDir.mkpath(".")) // 创建 conf 目录
        {
            qCritical() << "Failed to create configuration directory:" << configDir.path();
            return -1;
        }
    }

    QString iniFilePath = configDir.filePath("system_settings.ini");
    QFileInfo iniFileInfo(iniFilePath);

    // 检查配置文件是否存在，如果不存在则设置默认选项，然后写入settings文件
    if (!iniFileInfo.exists())
    {
        qDebug() << "First Load default System INI:" << iniFilePath;
        AppSettingsManager::getInstance().setAppDefaultSettings();
    }

    MainWindow w;
    w.show();
    return a.exec();
}
