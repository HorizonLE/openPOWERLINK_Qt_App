/**
********************************************************************************
\file   StatusBar.cpp

\brief  Implements the status bar and its labels.

\author Ramakrishnan Periyakaruppan

\copyright (c) 2014, Kalycito Infotech Private Limited
					 All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.
	* Neither the name of the copyright holders nor the
	  names of its contributors may be used to endorse or promote products
	  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/*******************************************************************************
* INCLUDES
*******************************************************************************/
#include "StatusBar.h"
#include <QtWidgets/QLabel>
#include "QtCore/QLocale"

#include "api/OplkQtApi.h"
#include "oplk/debugstr.h"

StatusBar::StatusBar(QWidget *parent) :
	QStatusBar(parent),
	networkInterface(new QLabel("Network interface: ")),
	cdcFile(new QLabel("CDC file: ")),
	xapFile(new QLabel("XAP file: ")),
	nmtStatus(new QLabel("NMT status: ")),
	cycleTime(new QLabel("Cycle time: ")),
	refreshRate(new QLabel())
{
	this->networkInterface->setMinimumWidth(175);
	this->cdcFile->setMinimumWidth(175);
	this->xapFile->setMinimumWidth(175);

	this->addWidget(this->networkInterface);
	this->addWidget(this->cdcFile);
	this->addWidget(this->xapFile);

	QFont font;
	font.setCapitalization(QFont::AllUppercase);
	this->nmtStatus->setFont(font);

	this->nmtStatus->setMinimumWidth(100);
	this->cycleTime->setMinimumWidth(100);
	this->refreshRate->setMinimumWidth(100);

	this->cdcFile->setToolTip("CDC file");
	this->xapFile->setToolTip("Xap file");
	this->networkInterface->setToolTip("Network interface name");
	this->nmtStatus->setToolTip("The status of the POWERLINK stack");
	this->cycleTime->setToolTip("The POWERLINK cycle time of the network");
	this->refreshRate->setToolTip("Screen refresh rate");

	this->addPermanentWidget(this->nmtStatus);
	this->addPermanentWidget(this->cycleTime);
	this->addPermanentWidget(this->refreshRate);

	int index = this->metaObject()->indexOfSlot(
					QMetaObject::normalizedSignature(
					"HandleSyncWaitTimeChanged(ulong)").constData());
	Q_ASSERT(index != -1);
	// If asserted check for the Function name

	bool ret = OplkQtApi::RegisterSyncWaitTimeChangedEventHandler(*(this),
							this->metaObject()->method(index));
	Q_ASSERT(ret != false);
	// For the first time it is not receiving synctime.
	this->HandleSyncWaitTimeChanged(OplkQtApi::GetSyncWaitTime());
}

void StatusBar::UpdateNmtStatus(tNmtState nmtState)
{
	QString debugState = debugstr_getNmtStateStr(nmtState);

	QString state;
	bool firstIndex = true;

	foreach (const QChar &ch, debugState)
	{
		if (ch.isLetter() && ch.isUpper())
		{
			if (firstIndex)
				firstIndex = !firstIndex;
			else
				state += "_";
		}
		state += ch;
	}

	qDebug("%s", qPrintable(state));
	this->nmtStatus->setText(QString(" NMT status: %1")
				.arg(state));

	if (nmtState == kNmtMsPreOperational1)
		this->UpdateCycleTime();
}

void StatusBar::UpdateCycleTime()
{
	DWORD cycleTime;
	UINT size = sizeof (cycleTime);
	tOplkError oplkRet = oplk_readLocalObject(0x1006,
											  0x00,
											  (void*)(&cycleTime),
											  &size);
	// TODO Assert if err
	if (oplkRet != kErrorOk)
		qDebug("Cycle time read error: %s", debugstr_getRetValStr(oplkRet));

	this->cycleTime->setText(QString("Cycle time: %1 %2s")
							 .arg(QLocale(QLocale::English).toString((qulonglong)cycleTime))
							 .arg(QString::fromUtf8("\xc2\xb5")));
}

void StatusBar::HandleSyncWaitTimeChanged(ulong sleepTime)
{
	this->refreshRate->setText(QString(" Screen refresh rate: %1 ms ")
				.arg(QLocale(QLocale::English).toString((qulonglong)sleepTime)));
}

void StatusBar::SetCdcFilePath(QString& cdc)
{
	this->cdcFile->setToolTip(cdc);
	this->cdcFile->setText(QString(" CDC: %1")
							.arg(this->GetShortPath(cdc)));
}

void StatusBar::SetXapFilePath(QString& xap)
{
	this->xapFile->setToolTip(xap);
	this->xapFile->setText(QString(" XAP: %1")
						   .arg(this->GetShortPath(xap)));
}

void StatusBar::SetNetworkInterfaceName(const QString& name)
{
	const QString devName = name.simplified();
	this->networkInterface->setToolTip(devName);
	this->networkInterface->setText(QString(" Interface: %1")
									.arg(devName.left(30)));
}

// TODO: can be moved to Utility
const QString StatusBar::GetShortPath(const QString& path) const
{
	QString shortPath;
	QStringList splitCDC = path.split("/", QString::SkipEmptyParts);
	bool fillersAdded = false;
	for (UINT it = 0; it < splitCDC.size(); ++it)
	{
		if ((it < 2))
		{
			shortPath.append(splitCDC.at(it));
			shortPath.append("/");
		}
		else if ((it == (splitCDC.size() - 1)))
		{
			shortPath.append(splitCDC.at(it));
		}
		else
		{
			if (!fillersAdded)
			{
				shortPath.append(".../");
				fillersAdded = !fillersAdded;
			}
		}
	}
	return shortPath;
}
