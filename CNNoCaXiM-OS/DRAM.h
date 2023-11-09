#pragma once
#include "DataStructures.h"
#include "SlaveInterface.h"
#include "Log.h"
#include "Clock.h"
#include <fstream>
#include <sstream>
#include <cstdio>

extern std::string g_dataFolderPath;
extern std::string g_weightDataPath;
extern std::string g_inputDataPath;
extern std::string g_outputDataPath;

extern std::string g_recordFolderPath;
extern std::string g_timingRecordPath;

class DRAM
{
public:
	DRAM() = default;
	void runOneStep();

	// With slave interface
	// DRAM(inputs) read by PE
	void receiveReadRequest();
	void sendReadResponse();

	// DRAM(outputs) written by PE
	void receiveWriteRequest();
	void sendWriteResponse();

	void recordInputReadTime();
	void recordOutputWrittenTime();

public:
	DRAMState m_dramState{};
	SlaveInterface m_slaveInterface{ };
	std::shared_ptr<Clock> m_localClock{ nullptr };

private:
};