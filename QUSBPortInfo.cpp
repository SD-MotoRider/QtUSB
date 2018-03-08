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

#include "QUSBPortInfo.h"


QUSBPortInfo::QUSBPortInfo() :
	_vendorIdentifier(0),
	_productIdentifier(0)
{
}

QUSBPortInfo::QUSBPortInfo
(
	const QUSBPort& port
)
{
	Q_UNUSED(port);
}

QUSBPortInfo::QUSBPortInfo
(
	const QString& name
)
{
	Q_UNUSED(name);
}

QUSBPortInfo::QUSBPortInfo
(
	const QUSBPortInfo& copyMe
)
{
	_portName = copyMe._portName;
	_systemLocation = copyMe._systemLocation;
	_description = copyMe._description;
	_manufacturer = copyMe._manufacturer;
	_serialNumber = copyMe._serialNumber;

	_vendorIdentifier = copyMe._vendorIdentifier;
	_productIdentifier = copyMe._productIdentifier;
}

QUSBPortInfo::~QUSBPortInfo()
{

}

QUSBPortInfo& QUSBPortInfo::operator=
(
	const QUSBPortInfo& assignMe
)
{	_portName = assignMe._portName;
	_systemLocation = assignMe._systemLocation;
	_description = assignMe._description;
	_manufacturer = assignMe._manufacturer;
	_serialNumber = assignMe._serialNumber;

	_vendorIdentifier = assignMe._vendorIdentifier;
	_productIdentifier = assignMe._productIdentifier;

	return *this;
}

void QUSBPortInfo::swap
(
	QUSBPortInfo& other
)
{
	QUSBPortInfo temp(other);
	other = *this;
	*this = temp;
}

QString QUSBPortInfo::portName() const
{
	return _portName;
}

QString QUSBPortInfo::systemLocation() const
{
	return _systemLocation;
}

QString QUSBPortInfo::description() const
{
	return _description;
}

QString QUSBPortInfo::manufacturer() const
{
	return _manufacturer;
}

QString QUSBPortInfo::serialNumber() const
{
	return _serialNumber;
}

quint16 QUSBPortInfo::vendorIdentifier() const
{
	return _vendorIdentifier;
}

quint16 QUSBPortInfo::productIdentifier() const
{
	return _productIdentifier;
}

bool QUSBPortInfo::hasVendorIdentifier() const
{
	return _vendorIdentifier != 0;
}

bool QUSBPortInfo::hasProductIdentifier() const
{
	return _productIdentifier != 0;
}

