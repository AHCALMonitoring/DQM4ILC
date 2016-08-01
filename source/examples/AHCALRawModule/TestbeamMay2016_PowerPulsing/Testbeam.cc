
/// \file Testbeam.cc
/*
 *-------------------------------------------------------------
 * AHCALRawModule.cc source template automatically modified from 
 * CaloHitModule  generated by a class generator
 * by A. Irles, DESY, 23 March 2016
 *--------------------------------------------------------------
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


#include "Testbeam.h"
// to handle and acces to the elements in the LCIO generic Object

// -- std headers
#include <ctime>
#include <cstdlib>
#include <limits>

//#ifndef USELCIO
//#define USELCIO
#include "EVENT/LCGenericObject.h"
#include "EVENT/LCCollection.h"
#include "EVENT/LCEvent.h"
#include "EVENT/LCIO.h"
#include "UTIL/CellIDDecoder.h"
#include "UTIL/LCTOOLS.h"
//#endif

// -- dqm4hep headers
#include "dqm4hep/DQMMonitorElement.h"
#include "dqm4hep/DQMCoreTool.h"
#include "dqm4hep/DQMRun.h"
#include "dqm4hep/DQMXmlHelper.h"
#include "dqm4hep/DQMEvent.h"
#include "dqm4hep/DQMQualityTest.h"
#include "dqm4hep/DQMModuleApi.h"
#include "dqm4hep/DQMPlugin.h"

// -- root headers
#include "TRandom.h"
#include "TString.h" // Added by Tom for TString handling


//using namespace lcio;

namespace dqm4hep
{
  // module plugin declaration
  DQM_PLUGIN_DECL( Testbeam , "Testbeam" )

  //-------------------------------------------------------------------------------------------------

  Testbeam::Testbeam() :
  DQMAnalysisModule()
  {
    setDetectorName("NO DETECTOR");
    setVersion(1, 0, 0);
  }

  //-------------------------------------------------------------------------------------------------

  Testbeam::~Testbeam()
  {
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode Testbeam::readSettings(const TiXmlHandle xmlHandle)
  {
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- readSettings()" );


    //---------------------------------------------------------------------
    // memcell
    m_memcell = 0;
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, 
                            DQMXmlHelper::readParameterValue(xmlHandle, "memcell", m_memcell));
    //---------------------------------------------------------------------
    // chips and channels to scan
    m_ChipID1 = 0;
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, 
                            DQMXmlHelper::readParameterValue(xmlHandle, "ChipID1", m_ChipID1));
    m_ChipID2 = 0;
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, 
                            DQMXmlHelper::readParameterValue(xmlHandle, "ChipID2", m_ChipID2));
    m_ChipID3 = 0;
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, 
                            DQMXmlHelper::readParameterValue(xmlHandle,"ChipID3", m_ChipID3));
    m_ChipID4 = 0;
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, 
                            DQMXmlHelper::readParameterValue(xmlHandle,"ChipID4", m_ChipID4));

    // Reading in our channel numers from the XML file
    m_ChannelNum1 = 0;
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, 
                            DQMXmlHelper::readParameterValue(xmlHandle,"ChannelNum1", m_ChannelNum1));
    m_ChannelNum2 = 0;
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, 
                            DQMXmlHelper::readParameterValue(xmlHandle, "ChannelNum2", m_ChannelNum2));
    m_ChannelNum3 = 0;
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, 
                            DQMXmlHelper::readParameterValue(xmlHandle, "ChannelNum3", m_ChannelNum3));
    m_ChannelNum4 = 0;
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, 
                            DQMXmlHelper::readParameterValue(xmlHandle, "ChannelNum4", m_ChannelNum4));
  
    //---------------------------------------------------------------------
    //ADC hitmaps
    m_pADC_300 = NULL;
    m_pADC_300_memcell = NULL;
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "ADC_300", m_pADC_300));
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "ADC_300_memcell", m_pADC_300_memcell));

    //-----------------------------------------------------
    // channels, ADC & TDC
    // chan_1
    m_pADC_1 = NULL;
    m_pTDC_1 = NULL;
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "ADC_1", m_pADC_1));
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "TDC_1", m_pTDC_1));
    // chan_2
    m_pADC_2 = NULL;
    m_pTDC_2 = NULL;
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "ADC_2", m_pADC_2));
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "TDC_2", m_pTDC_2));
    // chan_3
    m_pADC_3 = NULL;
    m_pTDC_3 = NULL;
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "ADC_3", m_pADC_3));
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "TDC_3", m_pTDC_3));
    // chan_4
    m_pADC_4 = NULL;
    m_pTDC_4 = NULL;
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "ADC_4", m_pADC_4));
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "TDC_4", m_pTDC_4));

    //-----------------------------------------------------
    // channels, ADC & TDC, memcell chosen
    // chan_1
    m_pADC_memcell_1 = NULL;
    m_pTDC_memcell_1 = NULL;
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "ADC_memcell_1", m_pADC_memcell_1));
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "TDC_memcell_1", m_pTDC_memcell_1));
    // chan_2
    m_pADC_memcell_2 = NULL;
    m_pTDC_memcell_2 = NULL;
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "ADC_memcell_2", m_pADC_memcell_2));
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "TDC_memcell_2", m_pTDC_memcell_2));
    // chan_3
    m_pADC_memcell_3 = NULL;
    m_pTDC_memcell_3 = NULL;
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "ADC_memcell_3", m_pADC_memcell_3));
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "TDC_memcell_3", m_pTDC_memcell_3));
    // chan_4
    m_pADC_memcell_4 = NULL;
    m_pTDC_memcell_4 = NULL;
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "ADC_memcell_4", m_pADC_memcell_4));
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "TDC_memcell_4", m_pTDC_memcell_4));

    //-----------------------------------------------------

    m_pMemCell_1 = NULL;
    m_pMemCell_2 = NULL;
    m_pMemCell_3 = NULL;
    m_pMemCell_4 = NULL;
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "MemCell_1", m_pMemCell_1));
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "MemCell_2", m_pMemCell_2));
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "MemCell_3", m_pMemCell_3));
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "MemCell_4", m_pMemCell_4));

    //-----------------------------------------------------
    m_dumpEvent = false;
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, DQMXmlHelper::readParameterValue(xmlHandle,
													     "DumpEvent", m_dumpEvent));

    return STATUS_CODE_SUCCESS;
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode Testbeam::initModule()
  {
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- init()" );

    // print directory structure of monitor element storage in console
    DQMModuleApi::cd(this);
    DQMModuleApi::ls(this, true);

    return STATUS_CODE_SUCCESS;
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode Testbeam::endModule()
  {
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- end()" );
    return STATUS_CODE_SUCCESS;
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode Testbeam::processEvent(DQMEvent *pEvent)
  {

    int CycleNrIndex = 0;
    int BxIDIndex = 1;
    int EvtNrIndex = 2;
    int ChipIDIndex = 3;
    int NChannelsIndex = 4;
    int TDCFirstChannelIndex = 5;
    int ADCFirstChannelIndex = TDCFirstChannelIndex+36;


    EVENT::LCEvent *pLCEvent = pEvent->getEvent<EVENT::LCEvent>();

    if(!pLCEvent)
      return STATUS_CODE_FAILURE;

    if(m_dumpEvent)
      UTIL::LCTOOLS::dumpEvent(pLCEvent);


    const std::vector<std::string> *pCollectionNames = pLCEvent->getCollectionNames();

    for(std::vector<std::string>::const_iterator colIter = pCollectionNames->begin();
	colIter != pCollectionNames->end() ; ++colIter)
      {

	const std::string &collectionName(*colIter);

	EVENT::LCCollection *pLCCollection = pLCEvent->getCollection(collectionName);

	// if(collectionName=="TempSensor")
	//   {

	    

	//   }

	if(collectionName=="EUDAQDataScCAL")
	  {

	    if(pLCCollection->getTypeName() == EVENT::LCIO::LCGENERICOBJECT)
	      {

		const int nElements = pLCCollection->getNumberOfElements();
		for(int e=0 ; e<nElements ; e++)
		  {
		    const EVENT::LCGenericObject *const pAHCALRaw = 
		      dynamic_cast<const EVENT::LCGenericObject *const>(pLCCollection->getElementAt(e));

		    if(NULL == pAHCALRaw)
		      continue;

		    const int nChannels = pAHCALRaw->getIntVal(NChannelsIndex);
		    if(nChannels!= 36) {
		      LOG4CXX_INFO( dqmMainLogger , "Wrong number of channels ("<<nChannels<<"), skip event" ); 
		      continue;
		    }

		    for(int f=0 ; f<nChannels ; f++)		// This loop iterates over the channels in each readout cycle
		      {

			// Vectors for storing our TDC and ADC by channel

			int tdcRAW;
			int adcRAW;
			int tdc;
			int adc;
			int hitbit_tdc;
			int gainbit_tdc;
			int hitbit_adc;
			int gainbit_adc;

			tdcRAW = pAHCALRaw->getIntVal(TDCFirstChannelIndex+f);
			adcRAW = pAHCALRaw->getIntVal(ADCFirstChannelIndex+f);

			tdc = tdcRAW%4096;
			adc = adcRAW%4096;

			hitbit_adc = (adcRAW & 0x1000)?1:0;
			gainbit_adc = (adcRAW & 0x2000)?1:0;

			hitbit_tdc = (tdcRAW & 0x1000)?1:0;
			gainbit_tdc = (tdcRAW & 0x2000)?1:0;

			//	std::cout<<m_ChipIDLayer1<<" "<< m_ChipIDLayer2<<" "<<m_ChipIDLayer3<<" "<<m_ChannelNum1<<" "<<m_ChannelNum2<<" "<<m_ChannelNum3<<" "<<m_ChannelNum4<<std::endl;


			bool Ch_1=false, Ch_2=false, Ch_3=false, Ch_4=false; 
                        if(f == m_ChannelNum1 ) Ch_1=true;
                        if(f == m_ChannelNum2 ) Ch_2=true;
                        if(f == m_ChannelNum3 ) Ch_3=true;
                        if(f == m_ChannelNum4 ) Ch_4=true;

			if(hitbit_adc != hitbit_tdc || pAHCALRaw->getIntVal(EvtNrIndex) == 0) continue;

			if(  hitbit_adc==1 ){//) {

			  //------------------------
			  if(pAHCALRaw->getIntVal(ChipIDIndex) == m_ChipID1 && Ch_1 && adc> 500 ) 
			    m_pMemCell_1->get<TH1I>()->Fill(pAHCALRaw->getIntVal(EvtNrIndex));
			  if(pAHCALRaw->getIntVal(ChipIDIndex) == m_ChipID2 && Ch_2 && adc> 500 )  
			    m_pMemCell_2->get<TH1I>()->Fill(pAHCALRaw->getIntVal(EvtNrIndex));
			  if(pAHCALRaw->getIntVal(ChipIDIndex) == m_ChipID3 && Ch_3 && adc> 500 )  
			    m_pMemCell_3->get<TH1I>()->Fill(pAHCALRaw->getIntVal(EvtNrIndex));
			  if(pAHCALRaw->getIntVal(ChipIDIndex) == m_ChipID4 && Ch_4 && adc> 500 )  
			    m_pMemCell_4->get<TH1I>()->Fill(pAHCALRaw->getIntVal(EvtNrIndex));                         
			}

			if(  hitbit_adc==1 && pAHCALRaw->getIntVal(BxIDIndex)<50) {//) {

			  //------------------------
			  if(pAHCALRaw->getIntVal(ChipIDIndex) == m_ChipID1 && Ch_1)  {
			    m_pADC_1->get<TH1I>()->Fill(adc);
			    m_pTDC_1->get<TH1I>()->Fill(tdc);
			    if( adc> 300 ) m_pMemCell_1->get<TH1I>()->Fill(pAHCALRaw->getIntVal(EvtNrIndex));

			  }
			  
			  if(pAHCALRaw->getIntVal(ChipIDIndex) == m_ChipID2 && Ch_2)  {
                            m_pADC_2->get<TH1I>()->Fill(adc);
                            m_pTDC_2->get<TH1I>()->Fill(tdc);
			    if( adc> 300 )  m_pMemCell_2->get<TH1I>()->Fill(pAHCALRaw->getIntVal(EvtNrIndex));
                          }

			  if(pAHCALRaw->getIntVal(ChipIDIndex) == m_ChipID3 && Ch_3)  {
                            m_pADC_3->get<TH1I>()->Fill(adc);
                            m_pTDC_3->get<TH1I>()->Fill(tdc);
			    if( adc> 300 )  m_pMemCell_3->get<TH1I>()->Fill(pAHCALRaw->getIntVal(EvtNrIndex));
                          }

			  if(pAHCALRaw->getIntVal(ChipIDIndex) == m_ChipID4 && Ch_4)  {
                            m_pADC_4->get<TH1I>()->Fill(adc);
                            m_pTDC_4->get<TH1I>()->Fill(tdc);
			    if( adc> 300 )  m_pMemCell_4->get<TH1I>()->Fill(pAHCALRaw->getIntVal(EvtNrIndex));
                          }
			}

			if(  hitbit_adc==1  && pAHCALRaw->getIntVal(BxIDIndex)>150 && pAHCALRaw->getIntVal(BxIDIndex)<200){//

			  //------------------------
			  if(pAHCALRaw->getIntVal(ChipIDIndex) == m_ChipID1 && Ch_1)  {
			    m_pADC_memcell_1->get<TH1I>()->Fill(adc);
			    m_pTDC_memcell_1->get<TH1I>()->Fill(tdc);
			  }

			  if(pAHCALRaw->getIntVal(ChipIDIndex) == m_ChipID2 && Ch_2)  {
                            m_pADC_memcell_2->get<TH1I>()->Fill(adc);
                            m_pTDC_memcell_2->get<TH1I>()->Fill(tdc);
                          }

			  if(pAHCALRaw->getIntVal(ChipIDIndex) == m_ChipID3 && Ch_3)  {
                            m_pADC_memcell_3->get<TH1I>()->Fill(adc);
                            m_pTDC_memcell_3->get<TH1I>()->Fill(tdc);
                          }

			  if(pAHCALRaw->getIntVal(ChipIDIndex) == m_ChipID4 && Ch_4)  {
                            m_pADC_memcell_4->get<TH1I>()->Fill(adc);
                            m_pTDC_memcell_4->get<TH1I>()->Fill(tdc);
                          }
			}

			//--------------------------
			//--- ADC hitmaps
			//	if( adc>300 && m_memcell == pAHCALRaw->getIntVal(EvtNrIndex)) m_pADC_300_memcell->get<TH2I>()->Fill(f,pAHCALRaw->getIntVal(ChipIDIndex));
			//	if( adc>300 ) m_pADC_300->get<TH2I>()->Fill(f,pAHCALRaw->getIntVal(ChipIDIndex));

			if( adc>300 && pAHCALRaw->getIntVal(BxIDIndex)>150 && pAHCALRaw->getIntVal(BxIDIndex)<200) m_pADC_300_memcell->get<TH2I>()->Fill(f,pAHCALRaw->getIntVal(ChipIDIndex));
			if( adc>300 && pAHCALRaw->getIntVal(BxIDIndex)<50) m_pADC_300->get<TH2I>()->Fill(f,pAHCALRaw->getIntVal(ChipIDIndex));



		      }//for f

		  }//for elements

	      }// if LCGENERICOBJECT

	  }//if collectionName == EUDAQDataScCAL
      }// iterator


    return STATUS_CODE_SUCCESS;

  }

  //-------------------------------------------------------------------------------------------------

  StatusCode Testbeam::startOfCycle()
  {
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- startOfCycle()" );
    return STATUS_CODE_SUCCESS;
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode Testbeam::endOfCycle()
  {
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- endOfCycle()" );

    // run all quality tests on all monitor elements
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMModuleApi::runQualityTests(this));

    return STATUS_CODE_SUCCESS;
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode Testbeam::startOfRun(DQMRun *pRun)
  {
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- startOfRun()" );
    LOG4CXX_INFO( dqmMainLogger , "Run no " << pRun->getRunNumber() );
    //	time_t startTime = pRun->getStartTime();
    time_t startTime = std::chrono::system_clock::to_time_t(pRun->getStartTime());

    std::string timeStr;
    DQMCoreTool::timeToHMS(startTime, timeStr);

    LOG4CXX_INFO( dqmMainLogger , "Start time " << timeStr );
    LOG4CXX_INFO( dqmMainLogger , "Detector is " << pRun->getDetectorName() );
    LOG4CXX_INFO( dqmMainLogger , "Description " << pRun->getDescription() );

    return STATUS_CODE_SUCCESS;
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode Testbeam::endOfRun(DQMRun *pRun)
  {
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- endOfRun()" );
    LOG4CXX_INFO( dqmMainLogger , "Run no " << pRun->getRunNumber() );

    //	time_t endTime = pRun->getEndTime();
    time_t endTime = std::chrono::system_clock::to_time_t(pRun->getEndTime());
    std::string timeStr;
    DQMCoreTool::timeToHMS(endTime, timeStr);

    LOG4CXX_INFO( dqmMainLogger , "End time " << timeStr );

    return STATUS_CODE_SUCCESS;
  }

};
