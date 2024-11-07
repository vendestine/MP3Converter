#include "appsettingsmanager.h"
#include <QStandardPaths>

void AppSettingsManager::writeRecords() {
    // 开始一个设置组，所有设置项将被归入 "app_settings" 组
    settings->beginGroup("app_settings");

    // writeSetting，将各个设置项的值写入到 QSettings 中
    writeSetting("app_themes", themesStr);
    writeSetting("app_languages", languagesStr);
    writeSetting("app_destinition", destinitionStr);
    writeSetting("app_bitrate", bitRateStr);
    writeSetting("app_samperate", sampleRateStr);
    writeSetting("app_finishsound", finishSoundStr);

    // 结束设置组，标记所有设置项已被写入
    settings->endGroup();

    // 确保所有更改都被同步到存储中，以便持久保存设置
    settings->sync();
}

void AppSettingsManager::readRecords() {
    // 获取用户的音乐目录路径，这个路径通常用于存放音乐文件。
    QString musicPath = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);

    // 构造默认目标路径，使用音乐目录加上子目录和文件名。
    QString defaultPath = musicPath + "/com.hg.mp3converter";

    // 开始一个设置组，所有设置都会归入 "app_settings" 组。
    settings->beginGroup("app_settings");

    // 从设置中读取各项数据。如果指定键不存在，则使用默认值。
    themesStr = settings->value("app_themes", "default-yellow").toString();   // 读取主题设置，默认值为 "default-yellow"
    languagesStr = settings->value("app_languages", "English").toString();    // 读取语言设置，默认值为 "English"
    destinitionStr = settings->value("app_destinition", defaultPath).toString(); // 读取目标路径设置，默认值为 defaultPath
    bitRateStr = settings->value("app_bitrate", "192k").toString();            // 读取比特率设置，默认值为 "192k"
    sampleRateStr = settings->value("app_samperate", "44100").toString();      // 读取采样率设置，默认值为 "44100"
    finishSoundStr = settings->value("app_finishsound", "YES").toString();     // 读取完成声音设置，默认值为 "YES"

    // 结束设置组，标记所有设置项已被读取。
    settings->endGroup();
}

void AppSettingsManager::setAppDefaultSettings() {
    // 获取用户的音乐目录路径，这个路径通常用于存放音乐文件。
    QString musicPath = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);

    // 构造默认目标路径，使用音乐目录加上子目录和文件名。
    QString defaultPath = musicPath + "/com.hg.mp3converter";

    // 开始一个settings组，所有设置都会归入 "app_settings" group
    settings->beginGroup("app_settings");
    // 设置key和value, 写入QSettings对象
    writeSetting("app_themes", "default-yellow");
    writeSetting("app_languages", "English");
    writeSetting("app_destinition", defaultPath);
    writeSetting("app_bitrate", "192k");
    writeSetting("app_samperate", "44100");
    writeSetting("app_finishsound", "YES");

    // 结束设置组，标记所有设置项已被写入
    settings->endGroup();

    // 确保缓存中的所有更改都同步到磁盘，以便持久保存设置
    settings->sync();
}
