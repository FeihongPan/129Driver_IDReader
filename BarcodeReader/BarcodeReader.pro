TEMPLATE = subdirs

SUBDIRS += \
    Tools \
    CommonLib \
    MainProject

Tools.subdir = $$_PRO_FILE_PWD_/Tools
CommonLib.subdir = $$_PRO_FILE_PWD_/CommonLib
MainProject.subdir = $$_PRO_FILE_PWD_/MainProject

CommonLib.depends = Tools
MainProject.depends = Tools CommonLib
