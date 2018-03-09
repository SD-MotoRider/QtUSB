#pragma once
//Copyright 2018 Austin Simpson

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "QtUSB_global.h"

#include <QList>
#include <QString>

class QUSBPort;
class QUSBPortInfo;

typedef QList<QUSBPortInfo> USBPortInfos;
typedef USBPortInfos::iterator USBPortInfoIter;

class QTUSBSHARED_EXPORT QUSBPortInfo
{
public:
    QUSBPortInfo();
    explicit QUSBPortInfo(const QUSBPort& port);
    explicit QUSBPortInfo(const QString& name);
	QUSBPortInfo(const QUSBPortInfo& copyMe);
    ~QUSBPortInfo();

	QUSBPortInfo& operator=(const QUSBPortInfo& assignMe);
    void swap(QUSBPortInfo& other);

    QString portName() const;
    QString systemLocation() const;
    QString description() const;
    QString manufacturer() const;
    QString serialNumber() const;

    quint16 vendorIdentifier() const;
    quint16 productIdentifier() const;

    bool hasVendorIdentifier() const;
    bool hasProductIdentifier() const;

	static USBPortInfos availablePorts();

private:
	QString _portName;
	QString _systemLocation;
	QString _description;
	QString _manufacturer;
	QString _serialNumber;

	quint16 _vendorIdentifier;
	quint16 _productIdentifier;
};

