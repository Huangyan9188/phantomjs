/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtPrintSupport module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCore/QMetaMethod>
#include <QtGui/QGuiApplication>
#include <qpa/qplatformnativeinterface.h>
#include <qpa/qplatformprintplugin.h>

QT_BEGIN_NAMESPACE

class QCocoaPrinterSupportPlugin : public QPlatformPrinterSupportPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.QPlatformPrinterSupportFactoryInterface" FILE "cocoa.json")

public:
    QPlatformPrinterSupport *create(const QString &);
};

QPlatformPrinterSupport *QCocoaPrinterSupportPlugin::create(const QString &key)
{
    if (key.compare(key, QStringLiteral("cocoaprintersupport"), Qt::CaseInsensitive) != 0)
        return 0;
    QGuiApplication *app = qobject_cast<QGuiApplication *>(QCoreApplication::instance());
    if (!app)
        return 0;
    QPlatformNativeInterface *platformNativeInterface = app->platformNativeInterface();
    int at = platformNativeInterface->metaObject()->indexOfMethod("createPlatformPrinterSupport()");
    if (at == -1)
        return 0;
    QMetaMethod createPlatformPrinterSupport = platformNativeInterface->metaObject()->method(at);
    QPlatformPrinterSupport *platformPrinterSupport = 0;
    if (!createPlatformPrinterSupport.invoke(platformNativeInterface, Q_RETURN_ARG(QPlatformPrinterSupport *, platformPrinterSupport)))
        return 0;
    return platformPrinterSupport;
}

QT_END_NAMESPACE

#include "main.moc"
