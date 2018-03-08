// Copyright 2018 Austin Simpson

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
#include "QUSBPort.h"

// Qt
#include <QUuid>

// Windows
#include <windows.h>
#include <Initguid.h>
#include <SetupAPI.h>
#include <Usbiodef.h>

USBPortInfos QUSBPortInfo::availablePorts()
{
	USBPortInfos availablePorts;

	HDEVINFO hDevInfo = SetupDiGetClassDevsA(&GUID_DEVINTERFACE_USB_DEVICE, NULL, NULL, DIGCF_PRESENT|DIGCF_DEVICEINTERFACE);
	if (hDevInfo != INVALID_HANDLE_VALUE)
	{
		DWORD devIndex = 0;
		SP_DEVICE_INTERFACE_DATA devIntfData;

		devIntfData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

		while (SetupDiEnumDeviceInterfaces(hDevInfo, NULL, &GUID_DEVINTERFACE_USB_DEVICE, devIndex++, &devIntfData) == TRUE)
		{
			DWORD dwSize(0);

			if (SetupDiGetDeviceInterfaceDetailA(hDevInfo, &devIntfData, NULL, 0, &dwSize, NULL) == FALSE)
			{
				DWORD lastError = ::GetLastError();

				if (lastError == ERROR_INSUFFICIENT_BUFFER)
				{
					PSP_DEVICE_INTERFACE_DETAIL_DATA_A devIntfDetailData;

					devIntfDetailData = static_cast<PSP_DEVICE_INTERFACE_DETAIL_DATA_A>(::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, dwSize));
					if (devIntfDetailData != nullptr)
					{
						SP_DEVINFO_DATA devInfoData;
						devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

						devIntfDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A);

						if (SetupDiGetDeviceInterfaceDetailA(hDevInfo, &devIntfData, devIntfDetailData, dwSize, NULL, &devInfoData) == TRUE)
						{
							QString detailData = QString((const char*) devIntfDetailData->DevicePath);
							if (detailData.isEmpty() == false)
							{
								int index;
								QUSBPortInfo usbPortInfo;

								usbPortInfo._systemLocation = detailData;

								index = detailData.indexOf("vid_");
								index += 4;
								usbPortInfo._vendorIdentifier = detailData.mid(index, 4).toInt(NULL, 16);

								index = detailData.indexOf("pid_");
								index += 4;
								usbPortInfo._productIdentifier = detailData.mid(index, 4).toInt(NULL, 16);

								char buffer[MAX_PATH];
								DWORD nSize;
								DWORD dataType;

								if (SetupDiGetDeviceRegistryPropertyA(hDevInfo, &devInfoData, SPDRP_MFG, &dataType,
									(PBYTE) buffer, sizeof(buffer), &nSize) == TRUE)
								{
									usbPortInfo._manufacturer = QString((const char*) buffer);
								}
								else
								{
									usbPortInfo._manufacturer = "Unknown";
								}

								availablePorts.push_back(usbPortInfo);
							}
						}

						::HeapFree(::GetProcessHeap(), 0, devIntfDetailData);
					}
				}
			}
		}

		SetupDiDestroyDeviceInfoList(hDevInfo);
	}

	return availablePorts;
}
