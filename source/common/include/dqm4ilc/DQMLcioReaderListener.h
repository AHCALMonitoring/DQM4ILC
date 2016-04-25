  /// \file DQMLcioReaderListener.h
/*
 *
 * DQMLcioReaderListener.h header template automatically generated by a class generator
 * Creation date : jeu. nov. 6 2014
 *
 * This file is part of DQM4HEP libraries.
 *
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 *
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#ifndef DQMLCIOREADERLISTENER_H
#define DQMLCIOREADERLISTENER_H

// -- lcio headers
#include "IO/LCEventListener.h"
#include "IO/LCRunListener.h"

namespace EVENT { class LCEvent; }
namespace EVENT { class LCRunHeader; }
namespace IO { class LCReader; }
namespace dqm4hep { class DQMEventClient; }

namespace dqm4ilc
{

/** DQMLcioReaderListener class
 */
class DQMLcioReaderListener : public IO::LCRunListener, public IO::LCEventListener
{
 public:
	/** Constructor with a data service
	 */
	DQMLcioReaderListener(IO::LCReader *pLCReader);

	/** Destructor
	 */
	~DQMLcioReaderListener();

	/** Set the time for a usleep call between each event (in u secs)
	 */
	void setSleepTime(unsigned int usleepTime);

	/** Set the event collector client that will publish the event over the network
	 */
	void setEventClient(dqm4hep::DQMEventClient *pEventClient);

	/** Whether the listener has to simulate a spill time structure.
	 *  The time stamp is looked-up in LCEvents and a sleep(n) is
	 *  called between each event sending where n is the difference of time stamp
	 */
	void setSimulateSpill(bool simulate);

	void processEvent(EVENT::LCEvent *pLCEvent);
	void modifyEvent(EVENT::LCEvent *pLCEvent);
	void processRunHeader(EVENT::LCRunHeader *pLCRunHeader);
	void modifyRunHeader(EVENT::LCRunHeader *pLCRunHeader);

protected:

	dqm4hep::DQMEventClient           *m_pEventClient;
	IO::LCReader                      *m_pLCReader;
	unsigned int                       m_sleepTime;
	bool                               m_simulateSpill;
	EVENT::long64                      m_previousTimeStamp;
  std::string 		                   m_moduleLogStr;
};

}

#endif  //  DQMLCIOREADERLISTENER_H
