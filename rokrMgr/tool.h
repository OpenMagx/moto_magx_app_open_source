#ifndef TOOL_H
#define TOOL_H

#include <ZApplication.h>
#include <qtextcodec.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <ZMessageDlg.h>
#include <ZNoticeDlg.h>

QString ctr(const char *ChineseString);
QString getAppDir();

int showQ(const QString &title, const QString &text, int type = 0);
void showNotify(const QString &title, const QString &text, int type = 0, int time = 1);

//QString createUUID();

#endif

