/* This file is part of the KDE libraries
    Copyright (c) 2006 David Faure <faure@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include <QSignalSpy>
#include <QtTest/QtTest>
#include "kglobalsettingstest.h"

QTEST_MAIN(KGlobalSettingsTest)

#include <kglobalsettings.h>
#include <QtCore/QProcess>
#include <QtCore/QEventLoop>
#include <QDBusConnection>

/**
 * The strategy of this test is:
 * We install QSignalSpy instances on many signals from KGlobalSettings::self(),
 * and then we get another process (kglobalsettingsclient) to call emitChange(),
 * and we check that the corresponding signals are emitted, i.e. that our process
 * got the dbus signal.
 *
 * As a nice side-effect we automatically test a bit of KProcess as well :)
 */

void KGlobalSettingsTest::initTestCase()
{
    // Some signals are only emitted when we are running a full KDE session. If
    // we are not then KDE applications follow the platform palette and font
    // settings.
    qputenv("KDE_FULL_SESSION", "1");

    // change to the bin dir
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    QDBusConnectionInterface *bus = nullptr;
    if (!QDBusConnection::sessionBus().isConnected() || !(bus = QDBusConnection::sessionBus().interface())) {
        QFAIL("Session bus not found");
    }

    QVERIFY(!KGlobalSettings::showFilePreview(QUrl("audiocd:/")));
}

#define CREATE_ALL_SPYS \
    KGlobalSettings* settings = KGlobalSettings::self(); \
    settings->activate();                                                 \
    QSignalSpy palette_spy( settings, SIGNAL(kdisplayPaletteChanged()) ); \
    QSignalSpy font_spy( settings, SIGNAL(kdisplayFontChanged()) ); \
    QSignalSpy style_spy( settings, SIGNAL(kdisplayStyleChanged()) ); \
    QSignalSpy settings_spy( settings, SIGNAL(settingsChanged(int)) ); \
    QSignalSpy appearance_spy( settings, SIGNAL(appearanceChanged()) )

static void callClient(const QString &opt, const char *signalToWaitFor)
{
    QProcess proc;
    QString processName;
#ifdef Q_OS_WIN
    processName = "kglobalsettingsclient.exe";
#else
    if (QFile::exists("./kglobalsettingsclient.shell")) {
        processName = "./kglobalsettingsclient.shell";
    } else {
        QVERIFY(QFile::exists("./kglobalsettingsclient"));
        processName = "./kglobalsettingsclient";
    }
#endif
//     qDebug() << proc.args();
    proc.start(processName, QStringList() << opt);
    bool ok = proc.waitForFinished();
    QVERIFY(ok);

    QSignalSpy spy(KGlobalSettings::self(), signalToWaitFor);
    QVERIFY(spy.wait(5000));
}

void KGlobalSettingsTest::testPaletteChange()
{
    CREATE_ALL_SPYS;
    callClient("-p", SIGNAL(kdisplayPaletteChanged()));
#if QT_VERSION <= QT_VERSION_CHECK(5, 0, 0)
    qDebug() << "The port to Qt5 native event filters broke KXMessages for Qt4, test disabled";
#else
    QCOMPARE(palette_spy.size(), 1);
    QCOMPARE(font_spy.size(), 0);
    QCOMPARE(style_spy.size(), 0);
    QCOMPARE(settings_spy.size(), 0);
    QCOMPARE(appearance_spy.size(), 1);
#endif
}

void KGlobalSettingsTest::testFontChange()
{
    CREATE_ALL_SPYS;
    callClient("-f", SIGNAL(kdisplayFontChanged()));
#if QT_VERSION <= QT_VERSION_CHECK(5, 0, 0)
    qDebug() << "The port to Qt5 native event filters broke KXMessages for Qt4, test disabled";
#else
    QCOMPARE(palette_spy.size(), 0);
    QCOMPARE(font_spy.size(), 1);
    QCOMPARE(style_spy.size(), 0);
    QCOMPARE(settings_spy.size(), 0);
    QCOMPARE(appearance_spy.size(), 1);
#endif
}

void KGlobalSettingsTest::testSettingsChange()
{
    CREATE_ALL_SPYS;
    callClient("--ps", SIGNAL(settingsChanged(int)));
#if QT_VERSION <= QT_VERSION_CHECK(5, 0, 0)
    qDebug() << "The port to Qt5 native event filters broke KXMessages for Qt4, test disabled";
#else
    QCOMPARE(palette_spy.size(), 0);
    QCOMPARE(font_spy.size(), 0);
    QCOMPARE(style_spy.size(), 0);
    QCOMPARE(settings_spy.size(), 1);
    QCOMPARE(settings_spy.at(0).at(0).toInt(), (int)KGlobalSettings::SETTINGS_PATHS);
    QCOMPARE(appearance_spy.size(), 0);
#endif
}
