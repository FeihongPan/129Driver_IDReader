/***********************************************************************
* Copyright (C) 2024, iStar.
*
* File Name:        filesystem.h
* Description:      文件处理系统类，进行文件读写以及核验等操作
* Version:          V1.0.0
* Author:           Feihong Pan
* Date:             2024-2-21
* Modify Record：
*       V1.0.1     2024-2-21     Feihong     增加异步方式写文件
***********************************************************************/

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Tools_global.h"

#include <QFileInfo>

class TOOLS_EXPORT FileSystem
{
public:
    static bool Write(const QString &folderPath, const QString &fileName, const QByteArray &datas);
    static bool Write(const QString &filePath, const QByteArray &datas);
    static bool Write_CRC(const QString &folderPath, const QString &fileName, const QByteArray &datas);
    static bool Write_CRC(const QString &filePath, QByteArray datas);

    /// <summary>
    /// 异步方式写文件
    /// </summary>
    /// <param name="strFolderPath">文件夹地址</param>
    /// <param name="strFileName">文件名</param>
    /// <param name="ba">待写入的数据</param>
    inline static void AsyncWrite_CRC(const QString &strFolderPath, const QString &strFileName, const QByteArray &ba);

    /// <summary>
    /// 异步方式写文件
    /// </summary>
    /// <param name="strFilePath">文件地址</param>
    /// <param name="ba">待写入的数据</param>
    inline static void AsyncWrite_CRC(const QString &strFilePath, QByteArray ba);

    /// <summary>
    /// 异步方式写文件
    /// </summary>
    /// <param name="strFolderPath">文件夹地址</param>
    /// <param name="strFileName">文件名</param>
    /// <param name="ba">待写入的数据</param>
    inline static void AsyncWrite(const QString &strFolderPath, const QString &strFileName, const QByteArray &ba);

    /// <summary>
    /// 异步方式写文件
    /// </summary>
    /// <param name="strFilePath">文件地址</param>
    /// <param name="ba">待写入的数据</param>
    static void AsyncWrite(const QString &strFilePath, const QByteArray &ba);

    static bool Read(const QString &folderPath, const QString &fileName, QByteArray &datas);
    static bool Read(const QString &filePath, QByteArray &datas);
    static bool Read_CRC(const QString &folderPath, const QString &fileName, QByteArray &datas);
    static bool Read_CRC(const QString &filePath, QByteArray &datas);

    ///names with suffix
    static QStringList GetAllFileNames(const QString &folderPath, const QStringList &filter = {});

    static QStringList GetAllFolderNames(const QString &folderPath, const QStringList &filter = {});

    static bool FileExist(const QString &folderPath, const QString &fileName, const QStringList &filter = {});

    static void ClearDirectory(const QString &path);

    static bool CopyDirectory(const QString &srcPath, const QString &destPath);

    static bool Remove(const QString &filePath);

    static bool Remove(const QString &folderPath, const QString &fileName);

    static bool Rename(const QString &filePath, const QString &newName);

    static bool Copy(const QString &fileName, const QString &newPath);
    static QString Backup(const QString &fileName);
    static bool Move(const QString &fileName, const QString &path);

    static bool FolderEmpty(const QString &dirPath);
    static bool CopyFolder(const QString &sourcePath, const QString &targetPath);
    static QStringList Retrieve(const QString &dirPath, const QString &suffix = QString());

    static bool Validity(const QString &fileName);
    static bool Checksum(QByteArray &datas);
    static uint16_t AddChecksum(QByteArray &datas);
    static void RemoveChecksum(QByteArray &datas);

    inline static QString GetBaseName(const QString &fileName);
    inline static QString GetFileName(const QString &filePath);
};

inline void FileSystem::AsyncWrite_CRC(const QString &strFolderPath, const QString &strFileName, const QByteArray &ba)
{
    FileSystem::AsyncWrite_CRC(strFolderPath + "/" + strFileName, ba);
}

inline void FileSystem::AsyncWrite_CRC(const QString &strFilePath, QByteArray ba)
{
    FileSystem::AddChecksum(ba);
    return FileSystem::AsyncWrite(strFilePath, ba);
}

inline void FileSystem::AsyncWrite(const QString &strFolderPath, const QString &strFileName, const QByteArray &ba)
{
    AsyncWrite(strFolderPath + "/" + strFileName, ba);
}

inline QString FileSystem::GetBaseName(const QString &fileName)
{
    return fileName.split(".")[0];
}

inline QString FileSystem::GetFileName(const QString &filePath)
{
    QFileInfo info(filePath);
    return info.fileName();
}

#endif
