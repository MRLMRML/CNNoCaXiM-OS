#include "Network.h"
#include "DRAMNode.h"
#include "PENode.h"
//#include "FakeNoC.h"

// global variables
std::string g_dataFolderPath{ "C:\\Users\\Hubiao\\source\\repos\\CNNoCaXiM-OS\\CNNoCaXiM-OS\\Data\\" };
std::string g_weightDataPath{ "WeightData.csv" };
std::string g_inputDataPath{ "InputData.csv" };
std::string g_outputDataPath{ "OutputData.csv" };

std::string g_recordFolderPath{ "C:\\Users\\Hubiao\\source\\repos\\CNNoCaXiM-OS\\CNNoCaXiM-OS\\Record\\" };
std::string g_timingRecordPath{ "TimingRecord.csv" };

int main()
{
	// timing
	Clock globalClock{};

	// create network
	Network* network{ new Network{} };
	network->setUpConnections();
	network->printRouterIDs();

	// create PE nodes
	PENode* peNode0{ new PENode{1, relu} };
	PENode* peNode1{ new PENode{2, relu} };
	PENode* peNode2{ new PENode{3, relu} };
	PENode* peNode3{ new PENode{4, relu} };
	PENode* peNode4{ new PENode{5, relu} };
	PENode* peNode5{ new PENode{6, relu} };
	PENode* peNode6{ new PENode{7, relu} };
	PENode* peNode7{ new PENode{8, relu} };
	PENode* peNode8{ new PENode{9, relu} };

	// create DRAM node
	DRAMNode* dramNode{ new DRAMNode{0, {1, 2, 3, 4, 5, 6, 7, 8, 9}} };

	// mount nodes on the network
	network->mountNode({ 1, 2 }, dramNode);
	network->mountNode({ 0, 1 }, peNode0);
	network->mountNode({ 2, 3 }, peNode1);
	network->mountNode({ 1, 0 }, peNode2);
	network->mountNode({ 0, 3 }, peNode3);
	network->mountNode({ 2, 1 }, peNode4);
	network->mountNode({ 0, 2 }, peNode5);
	network->mountNode({ 2, 2 }, peNode6);
	network->mountNode({ 1, 1 }, peNode7);
	network->mountNode({ 1, 3 }, peNode8);

	network->printNodeIDs();
	network->viewMappingTable();
	network->updateMappingTables();

	//start simulation
	for (int i{}; i < 2000; ++i)
	{
		network->updateEnable();
		dramNode->updateEnable();
		peNode0->updateEnable();
		peNode1->updateEnable();
		peNode2->updateEnable();
		peNode3->updateEnable();
		peNode4->updateEnable();
		peNode5->updateEnable();
		peNode6->updateEnable();
		peNode7->updateEnable();
		peNode8->updateEnable();

		dramNode->runOneStep();
		peNode0->runOneStep();
		peNode1->runOneStep();
		peNode2->runOneStep();
		peNode3->runOneStep();
		peNode4->runOneStep();
		peNode5->runOneStep();
		peNode6->runOneStep();
		peNode7->runOneStep();
		peNode8->runOneStep();
		network->runOneStep();
		globalClock.tickGlobalClock();
	}

	// sanitation
	delete peNode0;
	delete peNode1;
	delete peNode2;
	delete peNode3;
	delete peNode4;
	delete peNode5;
	delete peNode6;
	delete peNode7;
	delete peNode8;
	delete dramNode;
	delete network;
}