#ifndef _ACC_H_INCLUDED
#define _ACC_H_INCLUDED

#include "ACDC.h" // load the ACDC class
#include "EthernetInterface.h"
#include <algorithm>
#include <vector>
#include <map>
#include <thread>
#include <utility>
#include <memory>
//#include "yaml-cpp/yaml.h"
//#include "tomlplusplus/include/toml++/toml.h"
#include "constellation/core/config/Configuration.hpp"
#include "constellation/core/config/Dictionary.hpp"
#include "constellation/core/config/Value.hpp"

using namespace std;

#define NUM_CH 30 //maximum number of channels for one ACDC board
#define MAX_NUM_BOARDS 8 // maxiumum number of ACDC boards connectable to one ACC 

using namespace std;

class ACC
{
public:
	/*------------------------------------------------------------------------------------*/
	/*--------------------------------Constructor/Deconstructor---------------------------*/
	/*ID 5: Constructor*/
	ACC();
    ACC(const std::string& ip);

    /*ID 6: Destructor*/
	~ACC();
	

	/*------------------------------------------------------------------------------------*/
	/*-------------------------Local set functions for board setup------------------------*/
	/*-------------------Sets global variables, see below for description-----------------*/

	/*------------------------------------------------------------------------------------*/
	/*-------------------------Local set functions for board setup------------------------*/
    // void parseConfig(const YAML::Node& config);

	void parseConfig(const constellation::config::Configuration& config);
	/*ID:9 Create ACDC class instances for each connected ACDC board*/
	int createAcdcs(); 

    /*ID 10: Clear all ACDC class instances*/
	void clearAcdcs(); 

	/*ID:11 Queries the ACC for information about connected ACDC boards*/
    std::vector<int> whichAcdcsConnected(); 

	/*ID 12: Set up the software trigger*/
	void setSoftwareTrigger(unsigned int boardMask); 

	/*ID 13: Fires the software trigger*/
	void softwareTrigger(); 

	/*ID 15: Main listen fuction for data readout*/
    int listenForAcdcData(); 

	/*ID 16: Used to dis/enable transfer data from the PSEC chips to the buffers*/
	void enableTransfer(int onoff=0); 
	
	// parsing configuration and create ACDC objects 
	int initializeConfig(const constellation::config::Configuration& config);

	/*ID 17: Main init function that controls generalk setup as well as trigger settings*/
    // int initializeForDataReadout(const YAML::Node& config, const string& timestamp = "");
	int initializeForDataReadout(const std::string& timestamp = "");
	void initializeFile(const string& timestamp = "");
	/*ID 18: Tells ACDCs to clear their ram.*/ 	
	void dumpData(unsigned int boardMask); 

	/*ID 19: Pedestal setting procedure.*/
	bool setPedestals(unsigned int boardmask, unsigned int chipmask, unsigned int adc); 
    bool setPedestals(unsigned int boardmask, const std::vector<unsigned int>& pedestals);
    void setVddDLL(const std::vector<uint32_t>& vdd_dll_vec, bool resetDLL = false);

	/*ID 20: Switch for the calibration input on the ACC*/
	void toggleCal(int onoff, unsigned int channelmask = 0x7FFF,  unsigned int boardMask=0xFF); 

	/*ID 21: Set up the hardware trigger*/
	void setHardwareTrigSrc(int src, unsigned int boardMask = 0xFF); 

	/*ID 22: Special function to check the ports for connections to ACDCs*/
	void connectedBoards(); 

	/*ID 23: Wakes up the USB by requesting an ACC info frame*/
	void usbWakeup(); 

	/*ID 24: Special function to check connected ACDCs for their firmware version*/ 
	std::string versionCheck(bool debug = false);

	/*ID 25: Scan possible high speed link clock phases and select the optimal phase setting*/ 
	void scanLinkPhase(unsigned int boardMask, bool print = false);

    /*ID 26: Configure the jcPLL settings */
	void configJCPLL(unsigned int boardMask = 0xff);

    /*ID 27: Turn off triggers and data transfer off */
    void startRun();
	void startRun_R();
    void stopRun();
    void endRun();
    void resetLinks();
	//:::
	void resetACDC(unsigned int boardMask = 0xff); //resets the acdc boards
	void resetACC(); //resets the acdc boards 

    void startDAQThread();
    void joinDAQThread();
	
	std::vector<std::vector<uint64_t>> transmitData();
	/*------------------------------------------------------------------------------------*/
	/*--------------------------------------Write functions-------------------------------*/
	void writeErrorLog(string errorMsg); //writes an errorlog with timestamps for debugging
    bool running_;

    class ConfigParams
    {
    public:
        ConfigParams();
		
        std::string ip;
        bool rawMode;
        int eventNumber;
        int triggerMode;
        unsigned int boardMask;
        std::string label;
        bool reset;
        int accTrigPolarity;
        int validationStart;
        int validationWindow;

        int coincidentTrigMask;
        int coincidentTrigDelay[8];
        int coincidentTrigStretch[8];
    } params_;

private:
	/*------------------------------------------------------------------------------------*/
	/*---------------------------------Load neccessary classes----------------------------*/
    EthernetInterface eth_, eth_burst_;
    std::vector<ACDC> acdcs_; //a vector of active acdc boards. 

	//----------all neccessary global variables
    std::unique_ptr<std::thread> data_write_thread_;
    std::unique_ptr<std::thread> daq_thread_;
    int nEvtsMax_;

	static void got_signal(int);
    void sendJCPLLSPIWord(unsigned int word, unsigned int boardMask = 0xff, bool verbose = false);
    void writeThread();
    bool runWriteThread_;
};

#endif
