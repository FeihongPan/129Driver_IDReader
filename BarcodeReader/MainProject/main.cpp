#include "AppConfig/Manager/appconfigmanager.h"
#include "BarcodeReader/Manage/barcodereadermanager.h"
#include "BarcodeReader/Instance/keyencebarcodereader.h"

#include "Logger/loggermanager.h"
#include "FileSystem/fileoperatormanager.h"
#include "Communication/MQTT/mqttclientmanager.h"
#include "NetworkEquipmentMonitor/Manage/heartbeat.h"

#include <iostream>
#include <QSharedMemory>
#include <QCoreApplication>

#ifdef Q_OS_WIN
#include <WinUser.h>
#include <shellapi.h>
#include <Windows.h>
#include <DbgHelp.h>
#endif

using namespace NS_Log;

#ifdef Q_OS_WIN
BOOL WINAPI ConsoleHandler(DWORD ctrlType)
{
    if(ctrlType == CTRL_CLOSE_EVENT/* || ctrlType == CTRL_C_EVENT*/)
    {
        std::cout << "Console is closing..." << std::endl;

        QTime time;
        time.start();
        while(time.elapsed() < 1000)
        {
            std::cout << "BarcodeReader::Terminating "  << Time()->getInstance()->TimeToString().toStdString() << std::endl;
            QEventLoop loop;
            QTimer::singleShot(1000, &loop, &QEventLoop::quit);
            loop.exec();
        }
        std::cout << "BarcodeReader::Terminate Timeout!" << std::endl;
        return FALSE;
    }
    std::cout << "Unexpected ctrl type triggered: " << ctrlType << std::endl;
    return TRUE;
}

LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
    // 创建 Dump 文件
    HANDLE hDumpFile = CreateFile(reinterpret_cast<const wchar_t *>(("crash_" + Time()->getInstance()->TimeToString("yyyy-MM-dd_hh-mm-ss") + ".dmp").utf16()),
                                  GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(INVALID_HANDLE_VALUE != hDumpFile)
    {
        // Dump 信息
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ExceptionPointers = pException;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ClientPointers = TRUE;

        // 写入 Dump 文件内容
        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
    }

    return EXCEPTION_EXECUTE_HANDLER;
}
#endif


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // check only 1 program can be constructed
    QSharedMemory mem("iStar_BarcodeReader");
    bool b = mem.create(1);
    if(!b)
    {
        std::cout << "An instance has already been running." << std::endl;
        return -1;
    }

#ifdef Q_OS_WIN
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode &= ~ENABLE_INSERT_MODE;
    mode &= ~ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin, mode);

    SetConsoleCtrlHandler(ConsoleHandler, TRUE);

    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
#endif

    // MqttClient
    AppConfigManager::getInstance()->SetPath(m_AppConfig.appDataPath + "AppConfig", m_AppConfig.appDataPath_Backup
            + "AppConfig", "AppConfig.json", m_AppConfig.appDataPath + "CommunicationCommand");
    AppConfigManager::getInstance()->Initialize(); // Read Config Data
    MqttClientManager::getInstance()->AddClient(0, "BarcodeReader");

    // AppConfig
    AppConfig config;
    if(AppConfigManager::getInstance()->IsInitialized())
    {
        config = AppConfigManager::getInstance()->GetAppConfig();
        MqttClientManager::getInstance()->Connect(0, config.serverAdd.IP, config.serverAdd.port);
    }
    LOG()->Initialize_DebugLogger("D:/");
    LOG()->Log_Debug("Server.IP = " + config.serverAdd.IP.toStdString());
    LOG()->Log_Debug("Server.Port = " + std::to_string(config.serverAdd.port));
    LOG()->Log_Debug("Local IP = " + config.LocalIP.toStdString());

    // Publish
    BarcodeReaderManager::getInstance()->LinkToPublishClient(MqttClientManager::getInstance()->GetClient(0), "BRS", "BarcodeReader");

    // HeartBeat
    HeartBeat::getInstance()->LinkHeartBeatToPublishClient(MqttClientManager::getInstance()->GetClient(0), "BarcodeReader");
    HeartBeat::getInstance()->SetPeriodPublish();

    // Subscribe
    BarcodeReaderManager::getInstance()->LinkToSubscribeClient(MqttClientManager::getInstance()->GetClient(0));
    BarcodeReaderManager::getInstance()->Subscribe("BRC_BarcodeReader");

    KeyenceBarcodeReader *reader = new KeyenceBarcodeReader(0);
    reader->Connect("192.168.1.30", 9004);
    BarcodeReaderManager::getInstance()->RegisterBarcodeReader(reader);

    return a.exec();
}
