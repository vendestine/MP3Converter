#ifndef APPSETTINGSMANAGER_H
#define APPSETTINGSMANAGER_H

#include <QApplication>
#include <QSettings>
#include <QObject>
#include <QMutex>
#include <QStandardPaths>

class AppSettingsManager : public QObject {
    Q_OBJECT

public:
    // 单例模式
    static AppSettingsManager& getInstance() {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        static AppSettingsManager instance;
        return instance;
    }

    // appsettings所有属性的getter and setter 函数
    void setThememsString(const QString& str) { themesStr = str; }
    void setLanguageString(const QString& str) { languagesStr = str; }
    void setDestinitionString(const QString& str) { destinitionStr = str; }
    void setBitrateString(const QString& str) { bitRateStr = str; }
    void setSamplerateString(const QString& str) { sampleRateStr = str; }
    void setFinishSoundStr(const QString& str) { finishSoundStr = str; }

    QString getThememsString() const { return themesStr; }
    QString getLanguageString() const { return languagesStr; }
    QString getDestinitionString() const { return destinitionStr; }
    QString getBitrateString() const { return bitRateStr; }
    QString getSamplerateString() const { return sampleRateStr; }
    QString getFinishSoundStr() const { return finishSoundStr; }


    void setAppDefaultSettings();  // 设置app settings为default settings，然后写入settings文件
    void writeRecords();           // 写settings文件
    void readRecords();            // 读settings文件

private:
    AppSettingsManager() : QObject(qApp)
    {
        // 创建一个settings对象，和指定的file绑定
        settings = new QSettings(getAppSettingsIniPath(), QSettings::IniFormat, this);
    }

    // 返回配置文件的file path
    QString getAppSettingsIniPath() const {
        return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/conf/system_settings.ini";
    }

    // 将key和value写入QSettings对象
    void writeSetting(const QString& key, const QString& value) {
        settings->setValue(key, value);
    }

private:
    // settings属性
    QSettings* settings = nullptr;
    QString themesStr {};
    QString languagesStr {};
    QString destinitionStr {};
    QString bitRateStr {};
    QString sampleRateStr {};
    QString finishSoundStr {};
};

#endif // APPSETTINGSMANAGER_H
