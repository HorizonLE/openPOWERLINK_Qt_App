/**
********************************************************************************
\file   DataSyncThread.h

\brief

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

#ifndef _DATASYNCTHREAD_H_
#define _DATASYNCTHREAD_H_

/*******************************************************************************
* INCLUDES
*******************************************************************************/

#include <QThread>
#include <oplk/errordefs.h>
#include "ProcessImageVariables.h"
#include "ProcessImageMemory.h"

#include <user/processimage/ProcessImageParser.h>

/**
 * @brief The DataSyncThread class
 */
class DataSyncThread : public QThread
{
	Q_OBJECT

public:
	/**
	 * @brief DataSyncThread
	 * @param parser
	 */
	DataSyncThread(ProcessImageParser &parser);

	/**
	 * @brief run
	 */
	void run();

signals:
	/**
	 * @brief SignalUpdateInputValues
	 */
	void SignalUpdateInputValues();

	/**
	 * @brief SignalUpdateOutputValues
	 */
	void SignalUpdateOutputValues();

private:
	/**
	 * @brief in
	 */
	ProcessImageIn *in;

	/**
	 * @brief out
	 */
	ProcessImageOut *out;

	/**
	 * @brief DataSyncThread
	 * @param syncThread
	 */
	DataSyncThread(const DataSyncThread& syncThread);
	DataSyncThread& operator=(const DataSyncThread& syncThread);

	/**
	 * @brief ProcessSync
	 * @return
	 */
	tOplkError ProcessSync();
};

#endif // _DATASYNCTHREAD_H_