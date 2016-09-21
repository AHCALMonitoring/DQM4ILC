 /// \file AHCALRawModuleGlobal.h
/*
 *
 *-------------------------------------------------------------
 * AHCALRawModuleChannel.cc source template automatically modified from 
 * CaloHitModule  generated by a class generator
 * by A. Irles, DESY, 23 March 2016
 *--------------------------------------------------------------
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

#ifndef Testbeam_H
#define Testbeam_H

#include "dqm4hep/DQMAnalysisModule.h"

namespace dqm4hep
{

class DQMMonitorElement;

/** Testbeam class
 */ 
class Testbeam : public DQMAnalysisModule
{
public:
	Testbeam();
	~Testbeam();

	StatusCode initModule();
	StatusCode readSettings(const TiXmlHandle xmlHandle);
	StatusCode processEvent(DQMEvent *pEvent);
	StatusCode startOfCycle();
	StatusCode endOfCycle();
	StatusCode startOfRun(DQMRun *pRun);
	StatusCode endOfRun(DQMRun *pRun);
	StatusCode endModule();

protected:

	// 4 channels info
        DQMMonitorElementPtr                        m_pADC_01_a;
        DQMMonitorElementPtr                        m_pADC_02_a;
        DQMMonitorElementPtr                        m_pADC_03_a;
        DQMMonitorElementPtr                        m_pADC_04_a;
	DQMMonitorElementPtr                        m_pADC_05_a;
        DQMMonitorElementPtr                        m_pADC_06_a;
        DQMMonitorElementPtr                        m_pADC_07_a;
        DQMMonitorElementPtr                        m_pADC_08_a;
	DQMMonitorElementPtr                        m_pADC_09_a;
        DQMMonitorElementPtr                        m_pADC_10_a;
        DQMMonitorElementPtr                        m_pADC_11_a;
        DQMMonitorElementPtr                        m_pADC_12_a;
	DQMMonitorElementPtr                        m_pADC_13_a;
        DQMMonitorElementPtr                        m_pADC_14_a;
        DQMMonitorElementPtr                        m_pADC_15_a;

        DQMMonitorElementPtr                        m_pTDC_01_a;
        DQMMonitorElementPtr                        m_pTDC_02_a;
        DQMMonitorElementPtr                        m_pTDC_03_a;
        DQMMonitorElementPtr                        m_pTDC_04_a;
	DQMMonitorElementPtr                        m_pTDC_05_a;
        DQMMonitorElementPtr                        m_pTDC_06_a;
        DQMMonitorElementPtr                        m_pTDC_07_a;
        DQMMonitorElementPtr                        m_pTDC_08_a;
	DQMMonitorElementPtr                        m_pTDC_09_a;
        DQMMonitorElementPtr                        m_pTDC_10_a;
        DQMMonitorElementPtr                        m_pTDC_11_a;
        DQMMonitorElementPtr                        m_pTDC_12_a;
	DQMMonitorElementPtr                        m_pTDC_13_a;
        DQMMonitorElementPtr                        m_pTDC_14_a;
        DQMMonitorElementPtr                        m_pTDC_15_a;

	//------------------------
        DQMMonitorElementPtr                        m_pADC_01_b;
        DQMMonitorElementPtr                        m_pADC_02_b;
        DQMMonitorElementPtr                        m_pADC_03_b;
        DQMMonitorElementPtr                        m_pADC_04_b;
	DQMMonitorElementPtr                        m_pADC_05_b;
        DQMMonitorElementPtr                        m_pADC_06_b;
        DQMMonitorElementPtr                        m_pADC_07_b;
        DQMMonitorElementPtr                        m_pADC_08_b;
	DQMMonitorElementPtr                        m_pADC_09_b;
        DQMMonitorElementPtr                        m_pADC_10_b;
        DQMMonitorElementPtr                        m_pADC_11_b;
        DQMMonitorElementPtr                        m_pADC_12_b;
	DQMMonitorElementPtr                        m_pADC_13_b;
        DQMMonitorElementPtr                        m_pADC_14_b;
        DQMMonitorElementPtr                        m_pADC_15_b;

        DQMMonitorElementPtr                        m_pTDC_01_b;
        DQMMonitorElementPtr                        m_pTDC_02_b;
        DQMMonitorElementPtr                        m_pTDC_03_b;
        DQMMonitorElementPtr                        m_pTDC_04_b;
	DQMMonitorElementPtr                        m_pTDC_05_b;
        DQMMonitorElementPtr                        m_pTDC_06_b;
        DQMMonitorElementPtr                        m_pTDC_07_b;
        DQMMonitorElementPtr                        m_pTDC_08_b;
	DQMMonitorElementPtr                        m_pTDC_09_b;
        DQMMonitorElementPtr                        m_pTDC_10_b;
        DQMMonitorElementPtr                        m_pTDC_11_b;
        DQMMonitorElementPtr                        m_pTDC_12_b;
	DQMMonitorElementPtr                        m_pTDC_13_b;
        DQMMonitorElementPtr                        m_pTDC_14_b;
        DQMMonitorElementPtr                        m_pTDC_15_b;

	//------------------------
        DQMMonitorElementPtr                        m_pADC_01_c;
        DQMMonitorElementPtr                        m_pADC_02_c;
        DQMMonitorElementPtr                        m_pADC_03_c;
        DQMMonitorElementPtr                        m_pADC_04_c;
	DQMMonitorElementPtr                        m_pADC_05_c;
        DQMMonitorElementPtr                        m_pADC_06_c;
        DQMMonitorElementPtr                        m_pADC_07_c;
        DQMMonitorElementPtr                        m_pADC_08_c;
	DQMMonitorElementPtr                        m_pADC_09_c;
        DQMMonitorElementPtr                        m_pADC_10_c;
        DQMMonitorElementPtr                        m_pADC_11_c;
        DQMMonitorElementPtr                        m_pADC_12_c;
	DQMMonitorElementPtr                        m_pADC_13_c;
        DQMMonitorElementPtr                        m_pADC_14_c;
        DQMMonitorElementPtr                        m_pADC_15_c;

        DQMMonitorElementPtr                        m_pTDC_01_c;
        DQMMonitorElementPtr                        m_pTDC_02_c;
        DQMMonitorElementPtr                        m_pTDC_03_c;
        DQMMonitorElementPtr                        m_pTDC_04_c;
	DQMMonitorElementPtr                        m_pTDC_05_c;
        DQMMonitorElementPtr                        m_pTDC_06_c;
        DQMMonitorElementPtr                        m_pTDC_07_c;
        DQMMonitorElementPtr                        m_pTDC_08_c;
	DQMMonitorElementPtr                        m_pTDC_09_c;
        DQMMonitorElementPtr                        m_pTDC_10_c;
        DQMMonitorElementPtr                        m_pTDC_11_c;
        DQMMonitorElementPtr                        m_pTDC_12_c;
	DQMMonitorElementPtr                        m_pTDC_13_c;
        DQMMonitorElementPtr                        m_pTDC_14_c;
        DQMMonitorElementPtr                        m_pTDC_15_c;


	//------------------------
        DQMMonitorElementPtr                        m_pADC_01_d;
        DQMMonitorElementPtr                        m_pADC_02_d;
        DQMMonitorElementPtr                        m_pADC_03_d;
        DQMMonitorElementPtr                        m_pADC_04_d;
	DQMMonitorElementPtr                        m_pADC_05_d;
        DQMMonitorElementPtr                        m_pADC_06_d;
        DQMMonitorElementPtr                        m_pADC_07_d;
        DQMMonitorElementPtr                        m_pADC_08_d;
	DQMMonitorElementPtr                        m_pADC_09_d;
        DQMMonitorElementPtr                        m_pADC_10_d;
        DQMMonitorElementPtr                        m_pADC_11_d;
        DQMMonitorElementPtr                        m_pADC_12_d;
	DQMMonitorElementPtr                        m_pADC_13_d;
        DQMMonitorElementPtr                        m_pADC_14_d;
        DQMMonitorElementPtr                        m_pADC_15_d;

        DQMMonitorElementPtr                        m_pTDC_01_d;
        DQMMonitorElementPtr                        m_pTDC_02_d;
        DQMMonitorElementPtr                        m_pTDC_03_d;
        DQMMonitorElementPtr                        m_pTDC_04_d;
	DQMMonitorElementPtr                        m_pTDC_05_d;
        DQMMonitorElementPtr                        m_pTDC_06_d;
        DQMMonitorElementPtr                        m_pTDC_07_d;
        DQMMonitorElementPtr                        m_pTDC_08_d;
	DQMMonitorElementPtr                        m_pTDC_09_d;
        DQMMonitorElementPtr                        m_pTDC_10_d;
        DQMMonitorElementPtr                        m_pTDC_11_d;
        DQMMonitorElementPtr                        m_pTDC_12_d;
	DQMMonitorElementPtr                        m_pTDC_13_d;
        DQMMonitorElementPtr                        m_pTDC_14_d;
        DQMMonitorElementPtr                        m_pTDC_15_d;

	int m_ChannelNr_a;
	int m_ChannelNr_b;
	int m_ChannelNr_c;
	int m_ChannelNr_d;

	int m_asicNr_a;
	int m_asicNr_b;
	int m_asicNr_c;
	int m_asicNr_d;


	bool                                        m_dumpEvent;


}; 

} 

#endif  //  Testbeam_H
