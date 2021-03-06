/*
 *
 *  Copyright (c) 2015-2016
 *  name : Francis Banyikwa
 *  email: mhogomchungu@gmail.com
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QSettings>
#include <functional>
#include <memory>
#include <QStringList>
#include <QString>
#include <QMenu>
#include <QTimer>
#include <QTextEdit>
#include <QEventLoop>
#include "gsm.h"

namespace Ui {
class MainWindow ;
}

class Timer : public QObject
{
	Q_OBJECT
public:
	Timer()
	{
		connect( &m_timer,SIGNAL( timeout() ),this,SLOT( event() ) ) ;
	}
	void start( const QString& e )
	{
		m_text = e ;
		m_textEdit->setText( m_text ) ;
		m_timer.start( 1000 * 1 ) ;
	}
	void setTextEdit( QTextEdit * e )
	{
		m_textEdit = e ;
	}
	void stop()
	{
		m_textEdit->setText( QString() ) ;

		m_timer.stop() ;
	}
private slots:
	void event()
	{
		m_text += " ...." ;

		m_textEdit->setText( m_text ) ;
	}
private:
	QString m_text ;
	QTextEdit * m_textEdit ;
	QTimer m_timer ;
};

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow( bool log ) ;
	~MainWindow() ;
private slots:
	void enableConvert() ;
	void serverResponse( QString ) ;
	void pbSMS() ;
	void pbConnect() ;
	void pbSend() ;
	void pbQuit() ;
	void pbConvert() ;
	void disableSending() ;
	void enableSending() ;
	void setHistoryItem( QAction * ) ;
	void ussdCodeInfo( QAction * ) ;
	void updateTitle() ;
	void displayResult() ;
	void aboutToShow() ;
private:
	void invokeMethod( const char * ) ;
	void invokeMethod( const char *,const QString& ) ;
	QString topHistory() ;
	QString getSetting( const QString& ) ;

	int decodeType() ;
	void decodeText() ;
	bool Connect() ;
	bool getBoolSetting( const QString& ) ;

	void wait( int = 1 ) ;
	void send( const QString& = QString() ) ;
	void processResponce( const gsm::USSDMessage& ) ;
	void closeEvent( QCloseEvent * ) ;
	void setLocalLanguage() ;
	void setSetting( const QString&,const QString& ) ;
	void setSetting( const QString&,bool ) ;
	int  timeOutInterval() ;
	int  autowaitInterval() ;

	bool m_waiting ;
	int m_timeout ;

	int m_autowaitInterval ;

	QStringList m_autoSend ;

	std::unique_ptr< Ui::MainWindow > m_ui ;

	gsm::USSDMessage m_ussd ;

	QSettings m_settings ;

	Timer m_timer ;

	std::unique_ptr< gsm > m_gsm ;

	QMenu m_menu ;
};

#endif // MAINWINDOW_H
