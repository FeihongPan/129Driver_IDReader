/***********************************************************************
* Copyright (C) 2024, iStar.
*
* File Name:        ifileoperator.h
* Description:      文件处理接口类，提供文件读写操作
* Version:          V1.0.0
* Author:           Feihong Pan
* Date:             2024-2-21
* Modify Record：
*       V1.0.1     2024-2-21     Feihong     增加异步方式写文件
***********************************************************************/

#ifndef IFILEOPERATOR_H
#define IFILEOPERATOR_H

#include "Tools_global.h"
#include "FileSystem/filesystem.h"

#include <QString>

class TOOLS_EXPORT IFileOperator
{
public:
    IFileOperator(QString name);

    /// 设置通过该基类执行文件读写操作时是否需要CRC校验
    void SetCRCVerifyUsed(bool used);

    /// folderPath文件夹路径
    /// folderPath_Backup备份文件夹路径
    /// fileName 仅针对该类只操作一个文件的场景下使用
    /// cmdPath mqtt指令保存的文件路径
    void SetPath(const QString &folderPath, const QString &folderPath_Backup, const QString &fileName, const QString &cmdPath);

    /// 将文件写入SetPath()方法设置的folderPath文件夹下，文件名为fileName
    bool WriteToFile(const QByteArray &msg);

    /// 将文件写入文件夹下，文件名为SetPath()方法设置的fileName
    bool WriteToFile(const QString &filePath, const QByteArray &msg);

    /// folderPath文件夹路径
    /// fileName 文件名
    /// msg 文件信息
    bool WriteToFile(const QString &folderPath, const QString &fileName, const QByteArray &msg);

    /// <summary>
    /// 异步方式写文件
    /// </summary>
    /// <param name="ba">待写入的数据</param>
    void AsyncWriteToFile(const QByteArray &ba);

    /// <summary>
    /// 异步方式写文件
    /// </summary>
    /// <param name="strFilePath">文件地址</param>
    /// <param name="ba">待写入的数据</param>
    void AsyncWriteToFile(const QString &strFilePath, const QByteArray &ba);

    /// <summary>
    /// 异步方式写文件
    /// </summary>
    /// <param name="strFolderPath">文件夹地址</param>
    /// <param name="strFileName">文件名</param>
    /// <param name="ba">待写入的数据</param>
    void AsyncWriteToFile(const QString &strFolderPath, const QString &strFileName, const QByteArray &ba);

    /// 读取在SetPath()方法设置的folderPath文件夹下，文件名为fileName的文件
    bool ReadFromFile(QByteArray &msg);

    /// 读取在filePath文件夹下，SetPath()方法设置的文件名为fileName的文件
    bool ReadFromFile(const QString &filePath, QByteArray &msg);

    /// folderPath文件夹路径
    /// fileName 文件名
    /// msg 文件信息
    bool ReadFromFile(const QString &folderPath, const QString &fileName, QByteArray &msg);

    bool IsFolderEmpty();

    void SetFolderPath(const QString &folderPath);

    void SetFileName(const QString &fileName);

    void SetFolderPath_CmdSample(const QString &folderPath);

    bool Backup();

    QString FileOperatorName();

    virtual void SaveCommandInfo() {};

protected:
    bool writeCmdSampleToFile(const QString &name, const QByteArray &msg);

private:
    bool writeToFile(const QByteArray &msg);
    bool writeToFile_CRC(const QByteArray &msg);

    bool readFromFile(QByteArray &msg);
    bool readFromFile_CRC(QByteArray &msg);

protected:
    QString m_Name;
    QString m_FolderPath;
    QString m_FileName;
    QString m_FolderPath_CmdSample;
    QString m_FolderPath_Backup;
    bool m_bCRCVerifyUsed = false;
};

#endif // IFILEOPERATOR_H
