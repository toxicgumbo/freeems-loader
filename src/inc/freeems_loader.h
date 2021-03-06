/* FreeEMS-Loader- the open source s19 loader with special features for FreeEMS
 *
 * Copyright (C) 2008-2011 by Sean Keys <skeys@powerefi.com>
 *
 * This file is part of the FreeEMS-Loader project.
 *
 * FreeEMS-Loader software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS-Loader software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS-Loader software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at info(at)powerefi(dot)com or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS-Loader to load your firmware!
 *
 */

#ifndef FREEEMS_LOADER_H
#define FREEEMS_LOADER_H

#include <QtGui/QWidget>
#include <QtGui>
#include <QTextStream>
#include <QFile>
#include <QCoreApplication>
#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QFileDialog>
#include <QObject>
#include <QMap>
#include <QRegExp>

#include <ui_freeemsLoader.h>
#include <comms.h>
#include <stdio.h>
#include <iostream>

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>

using namespace std;

class FreeEMS_Loader: public QWidget {
	Q_OBJECT

public:
	FreeEMS_Loader(QWidget *parent = 0);
	~FreeEMS_Loader();
	bool showHelp;
	bool fileArg;
	virtual bool notify(QObject *rec, QEvent *ev) {
		qDebug() << "MyApplication::notify";
		try {
			return QApplication::instance()->notify(rec, ev);
		} catch (...) {
			cout << "Unknown Exception: Terminating!";
			exit(0);
		}
		return false;
	}
	bool eventFilter(QObject *, QEvent *);

protected:
	void fillBaud();
	void fillStopBits();
	void fillDataBits();
	void fillParity();
	void redirectCLI();
	void updateGUIState();
	void initGUI();
	void getFileName(QString name);
	void setFlashType();
	bool isUnattended();
	void setLoaderState();

private:
	void saveSettings();
	int restoreSettings();
	QMap<QString, int> deviceMap;
	Ui::FreeEMS_LoaderClass ui;
	FreeEMS_LoaderComms *loaderComms;
	bool unattended;
	QString ripFileName;
	QString loadFileName;
	QString loadDirectory;
	QString loadRipDirectory;
	QString m_autoRipDirectory;
	QStringList cmdline_args;
	QString appDataDir;
	QString settingsFile;
	int flashTypeIndex;
	int m_loaderState; /* holds the current state of the loader see LOADER_STATES enum */
	int _numBurnsPerformed;
	bool m_fileLoaded;

public slots:
	void abort();
	void setAutoRipDir();
	void openFile();
	void connect();
	void rip();
	void eraseFlash();
	void load();
	void writeText(string message);
	void updateProgress(int percent);
	void configureProgress(int min, int max);
	void showAbout();
	void closeReset();
	void changeGUIState(int);
	void displayMessage(MESSAGE_TYPE type, QString message);
	void fillDevice();
};

#else
/* let us know if we are being untidy with headers */
#warning "Header file FREEEMS_LOADER_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
