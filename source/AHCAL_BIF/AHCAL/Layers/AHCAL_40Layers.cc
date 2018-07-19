/// \file AHCAL_40Layers.cc
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


#include "AHCAL_40Layers.h"
// to handle and acces to the elements in the LCIO generic Object

// -- std headers
#include <ctime>
#include <cstdlib>
#include <limits>
#include <map>
#include <vector>

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
#include "TMultiGraph.h"
#include "TList.h"

//using namespace lcio;

namespace dqm4hep
{
  // module plugin declaration
  DQM_PLUGIN_DECL( AHCAL_40Layers , "AHCAL_40Layers" )

  //-------------------------------------------------------------------------------------------------

  AHCAL_40Layers::AHCAL_40Layers() :
  DQMAnalysisModule()
  {
    setDetectorName("NO DETECTOR");
    setVersion(1, 0, 0);
  }

  //-------------------------------------------------------------------------------------------------

  AHCAL_40Layers::~AHCAL_40Layers()
  {
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode AHCAL_40Layers::readSettings(const TiXmlHandle xmlHandle)
  {
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- readSettings()" );

   // ########################################################################################################################################
    // Monitorize the DAQ errors
    m_DAQerrors= NULL;
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "DAQerrors", m_DAQerrors));

    // ########################################################################################################################################
    // TEMPERATURE
    // for (int i=0; i<48; i++){
    //   m_pTempAverage[i] = NULL;
    //   char elementString[100];
    //   sprintf(elementString, "TempAverage_%02d", i );
    //   RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, std::string(elementString), m_pTempAverage[i]));
    // }

    // DIF
    for (int i=0; i<48; i++){
      m_pTempDIF[i] = NULL;
      char elementString[100];
      sprintf(elementString, "TempDIF_%02d", i );
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, std::string(elementString), m_pTempDIF[i]));
    }

    // PWR
    for (int i=0; i<48; i++){
      m_pTempPWR[i] = NULL;
      char elementString[100];
      sprintf(elementString, "TempPWR_%02d", i );
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, std::string(elementString), m_pTempPWR[i]));
    }

    // book xml handler for layer temp multygraphs

    // for (int i=0; i<48; i++){
    //   char elementString[100];
    //   sprintf(elementString, "TempLayer_%02d", i );
    //   RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, std::string(elementString), m_pTempLayer[i]));
    // }

    // LDA Time Stamp
    
    m_pTimeStamp = NULL;
    char elementString[100];
    sprintf(elementString, "TimeStamp");
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, std::string(elementString), m_pTimeStamp))
    

    // ####################################################################################################################################
    // AHCAL section
    m_minimumBxid    = 2; 
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, DQMXmlHelper::readParameterValue(xmlHandle,"MinimumBxid", m_minimumBxid))
    LOG4CXX_INFO( dqmMainLogger , "minimum memcell : " << std::to_string(m_minimumMemcell) );
    m_minimumMemcell = 0;
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, DQMXmlHelper::readParameterValue(xmlHandle,"MinimumMemcell", m_minimumMemcell))
    LOG4CXX_INFO( dqmMainLogger , "minimum Bxid : " << std::to_string(m_minimumBxid) );
    m_defaultPedestal = 600;
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, DQMXmlHelper::readParameterValue(xmlHandle,"MinimumMemcell", m_defaultPedestal))
    LOG4CXX_INFO( dqmMainLogger , "Default pedestal value : " << std::to_string(m_defaultPedestal) );

    std::string m_geometryFilename = "";
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, DQMXmlHelper::readParameterValue(xmlHandle,"GeometryFilename", m_geometryFilename));
    dqm4hep::TiXmlDocument m_geometryFile(m_geometryFilename);
    
    if( ! m_geometryFile.LoadFile() )
      return dqm4hep::STATUS_CODE_FAILURE;

    const dqm4hep::TiXmlHandle xmlGeometryFileHandle(&m_geometryFile);

    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, AHCAL_40Layers::buildGeometryMap(xmlGeometryFileHandle));

    
    //---------------------------------------------------------------------
    //3-D hitmaps
    m_pMIP_600_3d = NULL;
    m_pPed_600_3d = NULL;
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "MIP_600", m_pMIP_600_3d));
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, "Ped_600", m_pPed_600_3d));

    //---------------------------------------------------------------------
    //MIP hitmaps
    for (int i=0; i<C_MAX_LAYERS; i++){
      m_pMIP_600[i] = NULL;
      char elementString[100];
      sprintf(elementString, "MIP_600_l%02d", i + 1);
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, std::string(elementString), m_pMIP_600[i]));
    }

    //---------------------------------------------------------------------
    //pure hitmaps
    for (int i=0; i<C_MAX_LAYERS; i++){
      m_pHIT_600[i] = NULL;
      char elementString[100];
      sprintf(elementString, "HIT_600_l%02d", i + 1);
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, std::string(elementString), m_pHIT_600[i]));
    }

    //---------------------------------------------------------------------
    //Ped hitmaps
    for (int i=0; i<C_MAX_LAYERS; i++){
      m_pPed_600[i] = NULL;
      char elementString[100];
      sprintf(elementString, "Ped_600_l%02d", i + 1);
      LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- readSettings() booking ped"<<i<<"+1" );

      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMXmlHelper::bookMonitorElement(this, xmlHandle, std::string(elementString), m_pPed_600[i]));
    }

    // ####################################################################################################################################
    //-----------------------------------------------------
    m_dumpEvent = false;
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- readSettings() dump event parsing" );
    RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, DQMXmlHelper::readParameterValue(xmlHandle,"DumpEvent", m_dumpEvent));

    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- readSettings() finished successfully" );
    return STATUS_CODE_SUCCESS;
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode AHCAL_40Layers::initModule()  {
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- init()" );
    // print directory structure of monitor element storage in console
    DQMModuleApi::cd(this);
    DQMModuleApi::ls(this, true);
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- init() finished" );

    //===== Temperature multigraphs =====

    for (int i=0; i<48; i++){
      for (int j = 0; j < 6; j++){
        m_pTempiLayer[i][j] = NULL;
        char elementString[100];
        sprintf(elementString, "Layer_%02d_Sensor_%01d", i, j);
        RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMModuleApi::bookObject(this, m_pTempiLayer[i][j], std::string(elementString), "", allocator_helper<TObject, TGraph>()));
      }
    }
    for (int i=0; i<48; i++){
      m_pTempLayer[i] = NULL;
      char elementString[100];
      sprintf(elementString, "TempLayer_%02d", i );
      // char title[100];
      // sprintf(elementString, "Temp (Layer) on LDA port %02d", i );
      RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMModuleApi::bookObject(this, m_pTempLayer[i], std::string(elementString), "", allocator_helper<TObject, TMultiGraph>()));    
      sprintf(elementString, "Temp (Layer) on LDA port %02d", i );
      m_pTempLayer[i]->setDrawOption("AP");
      m_pTempLayer[i]->setTitle(std::string(elementString));
    }


    for(int i = 0; i < 48; i++){
       for (int j = 0; j < 6; j++){
	 
	 m_pTempiLayer[i][j]->get<TGraph>()->SetLineWidth(3);
	 
	 if (j < 4) {
	   m_pTempiLayer[i][j]->get<TGraph>()->SetLineColor(j + 1);
	 } else m_pTempiLayer[i][j]->get<TGraph>()->SetLineColor(j + 2);
	   
	 
	  
	 m_pTempLayer[i]->get<TMultiGraph>()->Add(m_pTempiLayer[i][j]->get<TGraph>(), "PL");
       }
    }

    return STATUS_CODE_SUCCESS;
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode AHCAL_40Layers::endModule()  {
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- end()" );
    return STATUS_CODE_SUCCESS;
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode AHCAL_40Layers::processEvent(DQMEvent *pEvent)  {
    //int EventCntIndex = 1;
    int BxIDIndex = 1;
    int EvtNrIndex = 2;
    int ChipIDIndex = 3;
    int NChannelsIndex = 4;
    int TDCFirstChannelIndex = 5;
    int ADCFirstChannelIndex = TDCFirstChannelIndex+36;

    int TSLowIndex = 5;
    int TSHighIndex = 6;

    EVENT::LCEvent *pLCEvent = pEvent->getEvent<EVENT::LCEvent>();
    int EvtNr = pLCEvent->getEventNumber();
    if(!pLCEvent) return STATUS_CODE_FAILURE;
    if(m_dumpEvent) UTIL::LCTOOLS::dumpEvent(pLCEvent);
    const std::vector<std::string> *pCollectionNames = pLCEvent->getCollectionNames();
    
    //Time stamp variables

    //unsigned int ts_lu, ts_h_lu;
    int ts;
    

    //temperature variables
    float tdif;
    float tpwr;
    float tav;

    for(std::vector<std::string>::const_iterator colIter = pCollectionNames->begin(); colIter != pCollectionNames->end() ; ++colIter) {
      const std::string &collectionName(*colIter);
      EVENT::LCCollection *pLCCollection = pLCEvent->getCollection(collectionName);
      
      // #####################################################################################################################
      // temperature section
      // LOG4CXX_INFO( dqmMainLogger , "going through the collection: "<<collectionName ); 
      if(collectionName=="TempSensor") {
	const int nElements = pLCCollection->getNumberOfElements();
	//long64 epoch = pLCEvent->getTimeStamp();
	for(int e=0 ; e<nElements ; e++) {
	  const EVENT::LCGenericObject *const pTempRaw = dynamic_cast<const EVENT::LCGenericObject *const>(pLCCollection->getElementAt(e));
	  if(NULL == pTempRaw) continue;
	  int ldaPortNumber=pTempRaw->getIntVal(1);
	  if (ldaPortNumber>47) {
	    LOG4CXX_WARN( dqmMainLogger , "Wrong number port number in the temperature data: "<<ldaPortNumber<<". Skipping event "<< e ); 
	    continue;
	  }
	  LOG4CXX_INFO( dqmMainLogger , "Filling temperature for port: "<<ldaPortNumber ); 
	    
	  tdif = pTempRaw->getIntVal(8); 
	  tpwr = pTempRaw->getIntVal(9);		  
	  int ntemps=0, tempav=0;
	  for(int i=0; i<6; i++) { //indexes 2..7
	    int read_t=pTempRaw->getIntVal(2+i);
	    if((read_t < 900) && (read_t > 100)) {
	      ntemps++; 
	      tempav += read_t;
	    }  
	  }
	  
	  TObject* iObj;
	  TGraph* iGraph;
	  Float_t temp;

	  for(int SensorNr = 0; SensorNr < 6; SensorNr++) { //indexes 2..7                               
            int read_t = pTempRaw->getIntVal(2 + SensorNr);
            if((read_t < 900) && (read_t > 100)) {
	      temp = (1.0*read_t)/10.0;
	      //char grname[20];
	      //sprintf(grname, "Layer_%02d_Sensor_%01d", ldaPortNumber, SensorNr);
	      iObj = m_pTempLayer[ldaPortNumber]->get<TMultiGraph>()->GetListOfGraphs()->At(SensorNr); 
              iGraph = (TGraph*)iObj;
	      Int_t pointID = iGraph->GetN();
              iGraph->SetPoint(pointID, pointID, (temp + SensorNr/100));
            }
          }
	  if ((tdif>10) && (tdif < 90)) {
	    Int_t pointID = m_pTempDIF[ldaPortNumber]->get<TGraph>()->GetN();
	    m_pTempDIF[ldaPortNumber]->get<TGraph>()->SetPoint(pointID, pointID, tdif);
	  }
	  if ((tpwr>10) && (tpwr < 90)) {
	    Int_t pointID = m_pTempPWR[ldaPortNumber]->get<TGraph>()->GetN();
	    m_pTempPWR[ldaPortNumber]->get<TGraph>()->SetPoint(pointID, pointID, tpwr);
	  }

	  // if (ntemps>0) {
	  //   tempav=((1.0 * tempav)/ntemps)/10;
	  //   if ((tempav > 10.0) && (tempav < 90.0)) {
	  //     Int_t pointID = m_pTempAverage[ldaPortNumber]->get<TGraph>()->GetN();
	  //     m_pTempAverage[ldaPortNumber]->get<TGraph>()->SetPoint(pointID, pointID, tempav);
	  //   }
	  // }
	}//for elements in collection	
      } //tempsensor collection

      // #####################################################################################################################
      // AHCAL section

      if(collectionName=="EUDAQDataLDATS") {
	if(pLCCollection->getTypeName() == EVENT::LCIO::LCGENERICOBJECT) {

	  // int daqquality = pLCCollection->getParameters().getIntVal("DAQquality");
	  // if(daqquality==1) goodDAQ++; else badDAQ++;
	  const int nElements = pLCCollection->getNumberOfElements();
	   for(int e = 0 ; e < nElements ; e++) {

	     const EVENT::LCGenericObject *const pTS = dynamic_cast<const EVENT::LCGenericObject *const>(pLCCollection->getElementAt(e)); 	  

	     if(NULL == pTS) continue;

	     const int ts_l = pTS->getIntVal(TSLowIndex);
	     const int ts_h = pTS->getIntVal(TSHighIndex);

	     //=== conversion 2 parts of raw variable to time stamp ===
	     const uint64_t ts_lu = (uint64_t)ts_l;
	     const uint64_t ts_hu = (uint64_t)ts_h << 32;
	     ts = ts_hu|ts_lu;	     
	     //--------------------------------------------------------

	     //=== Filling graph ===
	     Int_t pointID = m_pTimeStamp->get<TGraph>()->GetN();
	     m_pTimeStamp->get<TGraph>()->SetPoint(pointID, EvtNr, ts);

	   }
	}
      }      

      if(collectionName=="EUDAQDataScCAL") {
	if(pLCCollection->getTypeName() == EVENT::LCIO::LCGENERICOBJECT) {
	  int daqquality = pLCCollection->getParameters().getIntVal("DAQquality");
	  if(daqquality==1) goodDAQ++; else badDAQ++;
	  const int nElements = pLCCollection->getNumberOfElements();
	  for(int e=0 ; e<nElements ; e++) {
	    const EVENT::LCGenericObject *const pAHCALRaw = dynamic_cast<const EVENT::LCGenericObject *const>(pLCCollection->getElementAt(e));
	    if(NULL == pAHCALRaw)continue;
	    const int nChannels = pAHCALRaw->getIntVal(NChannelsIndex);
	    if(nChannels!= 36) {
	      LOG4CXX_INFO( dqmMainLogger , "Wrong number of channels ("<<nChannels<<"), skip event" ); 
	      continue;
	    }
	    const int bxid=pAHCALRaw->getIntVal(BxIDIndex);
	    const int memcell=pAHCALRaw->getIntVal(EvtNrIndex);
	    float ratiobadDAQ = badDAQ / (badDAQ + goodDAQ) ;
	    Int_t ip = pAHCALRaw->getIntVal(ChipIDIndex);
	    if(badDAQ > 0 ) m_DAQerrors->get<TGraph>()->SetPoint(ip, pAHCALRaw->getIntVal(ChipIDIndex), ratiobadDAQ );
	    //if( daqquality!=1 ) continue;
	    for(int f=0; f<36; f++ ) {
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
	      tdc = tdcRAW & 0x0FFF;
	      adc = adcRAW& 0x0FFF;
	      
	      hitbit_adc = (adcRAW & 0x1000)?1:0;
	      gainbit_adc = (adcRAW & 0x2000)?1:0;
	      hitbit_tdc = (tdcRAW & 0x1000)?1:0;
	      gainbit_tdc = (tdcRAW & 0x2000)?1:0;

	      if(pAHCALRaw->getIntVal(0)==107) {	      //?????????
		std::cout<<"chip: "<<pAHCALRaw->getIntVal(ChipIDIndex) <<" mem:" <<pAHCALRaw->getIntVal(EvtNrIndex)<< " chn:"<<f<< " hb:"<<hitbit_adc<<hitbit_tdc<<" adc:"<<adc<<" tdc:"<<tdc<<std::endl;
	      }
	      if (memcell<m_minimumMemcell) continue;
	      if (bxid<m_minimumBxid) continue;
	      //if( hitbit_adc != hitbit_tdc) continue;
	      if (hitbit_adc != 1) continue;
	      int ijk = electronicsToIJK(pAHCALRaw->getIntVal(ChipIDIndex),f);
	      int I = ijk / 10000;
	      int J = ( ijk  % 10000 ) /100;
	      int K = ( ijk  % 10000 ) % 100;
	      if ((K<1) || (K>(C_MAX_LAYERS)) ) continue;
	      //LOG4CXX_DEBUG( dqmMainLogger , "Filling I="<<std::to_string(I)<<" J="<<std::to_string(J)<<" K="<<std::to_string(K)); 
	      if (adc > m_defaultPedestal) {
		m_pMIP_600_3d->get<TH3I>()->Fill(K,I,J,adc);
		m_pMIP_600[K-1]->get<TH2I>()->Fill(I,J,adc);
		m_pHIT_600[K-1]->get<TH2I>()->Fill(I,J,1);
	      }
	      if (adc <= 600) {
		m_pPed_600_3d->get<TH3I>()->Fill(K,I,J,adc);
		m_pPed_600[K-1]->get<TH2I>()->Fill(I,J,adc);
	      }
	    }
	    //---------------------------------------------------------------------------------------
	  }//for elements
	}// if LCGENERICOBJECT
      }//if collectionName == EUDAQDataScCAL
    }//for collections

    return STATUS_CODE_SUCCESS;
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode AHCAL_40Layers::startOfCycle()  {
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- startOfCycle()" );
    return STATUS_CODE_SUCCESS;
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode AHCAL_40Layers::endOfCycle()
  {
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- endOfCycle()" );

    // run all quality tests on all monitor elements
    RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, DQMModuleApi::runQualityTests(this));
    
    return STATUS_CODE_SUCCESS;
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode AHCAL_40Layers::startOfRun(DQMRun *pRun)
  {
    LOG4CXX_INFO( dqmMainLogger , "Module : " << getName() << " -- startOfRun()" );
    LOG4CXX_INFO( dqmMainLogger , "Run no " << pRun->getRunNumber() );
    //	time_t startTime = pRun->getStartTime();
    time_t startTime = std::chrono::system_clock::to_time_t(pRun->getStartTime());

    std::string timeStr;
    DQMCoreTool::timeToHMS(startTime, timeStr);

    goodDAQ = 0;
    badDAQ = 0;

    LOG4CXX_INFO( dqmMainLogger , "Start time " << timeStr );
    LOG4CXX_INFO( dqmMainLogger , "Detector is " << pRun->getDetectorName() );
    LOG4CXX_INFO( dqmMainLogger , "Description " << pRun->getDescription() );

    return STATUS_CODE_SUCCESS;
  }

  //-------------------------------------------------------------------------------------------------

  StatusCode AHCAL_40Layers::endOfRun(DQMRun *pRun)
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


  StatusCode AHCAL_40Layers::buildGeometryMap(const TiXmlHandle xmlHandle)
  {
    LOG4CXX_INFO( dqmMainLogger , "Building geometry map..." );
    //Getting the very first child of the XML file; in our case, this is the dqm4hepGeometryMap bracket.
    const dqm4hep::TiXmlHandle xmlFileHandle(xmlHandle.FirstChildElement().Element());
    //Giving a unique name to the globalGeometryProperties object
    dqm4hep::TiXmlHandle pGlobalPropertiesXmlElement(xmlFileHandle.FirstChild("globalGeometryProperties").Element());
    //Iterate over each layer
    for (dqm4hep::TiXmlElement *pLayerXmlElement = xmlFileHandle.FirstChild("layer").Element(); NULL != pLayerXmlElement; pLayerXmlElement = pLayerXmlElement->NextSiblingElement("layer"))  {
      dqm4hep::TiXmlHandle pLayerHandle(pLayerXmlElement);
      //Iterate over each chip
      for (dqm4hep::TiXmlElement *pChipXmlElement = pLayerHandle.FirstChild("chip").Element(); NULL != pChipXmlElement; pChipXmlElement = pChipXmlElement->NextSiblingElement("chip"))	  {
	dqm4hep::TiXmlHandle pChipHandle(pChipXmlElement);
	//Iterate over each channel
	for (dqm4hep::TiXmlElement *pChannelXmlElement = pChipHandle.FirstChild("channel").Element(); NULL != pChannelXmlElement; pChannelXmlElement = pChannelXmlElement->NextSiblingElement("channel"))	  {
	  int ChipID, ChannelID, I, J, K, ChpChnNum, ijkNum;
	  //Pull out all the data: chip number, channel number, ijk
	  pChipXmlElement->QueryValueAttribute<int>("id", &ChipID);
	  pChannelXmlElement->QueryValueAttribute<int>("id", &ChannelID);
	  pChannelXmlElement->QueryValueAttribute<int>("i", &I);
	  pChannelXmlElement->QueryValueAttribute<int>("j", &J);
	  pChannelXmlElement->QueryValueAttribute<int>("k", &K);
	  //Formatting data to go into our map
	  ChpChnNum = ChipID*100+ChannelID;
	  //I = 13 - I; //reverse the I axis in case the HBU is rotated
	  ijkNum = I*10000 + J*100 + K;
	  //Filling the map (Chip, Chn)->(I, J, K)
	  ijkmap.insert(std::make_pair(ChpChnNum, ijkNum));
	  //Filling the map (I, J, K)->(Chip, Chn)
	  chpchnmap.insert(std::make_pair(ijkNum, ChpChnNum));
	}//each channel
      }//each chip
    } //each layer
    std::cout<<chpchnmap.size()<<" "<< ijkmap.size()<<std::endl;
    LOG4CXX_INFO( dqmMainLogger , "Geometry map built successfully." );
    return STATUS_CODE_SUCCESS;
  }

  int AHCAL_40Layers::electronicsToIJK(int Chip, int Channel)
  {
    std::map<int, int>::iterator itMap;
    int index = Chip*100+Channel;
    int IJK = -1;
    // std::cout<<"electronicsToIJK "<<ijkmap.size()<<std::endl;
    //std::cout<<index<<" "<<Chip<<" "<<Channel<<std::endl;
    if(ijkmap.find(index) != ijkmap.end()) {
      itMap = ijkmap.find(index);
      IJK = itMap->second;
      //	std::cout<<"find: "<<IJK<<std::endl;
    }
    return IJK;
  }

  int AHCAL_40Layers::IJKToElectronics(int I, int J, int K)
  {
    std::map<int, int>::iterator itMap;
    int index = I*10000+J*100+K;
    int ChipChn= -1;
    if(chpchnmap.find(index) != chpchnmap.end())      {
      itMap = chpchnmap.find(index);
      ChipChn = itMap->second;
    }
    return ChipChn;
  }

  };//namespace
