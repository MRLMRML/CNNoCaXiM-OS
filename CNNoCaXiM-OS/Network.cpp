#include "Network.h"

void Network::setUpConnections()
{
#if defined(MESH)
	for (int j{}; j < NETWORK_DIMENSION_Y; ++j)
	{
		for (int i{}; i < NETWORK_DIMENSION_X; ++i)
		{
			if (i != NETWORK_DIMENSION_X - 1)
				m_links.setUpConnection(m_routers[i + j * NETWORK_DIMENSION_X].m_eastPort, m_routers[(i + 1) + j * NETWORK_DIMENSION_X].m_westPort);

			if (j != NETWORK_DIMENSION_Y - 1)
				m_links.setUpConnection(m_routers[i + j * NETWORK_DIMENSION_X].m_southPort, m_routers[i + (j + 1) * NETWORK_DIMENSION_X].m_northPort);
		}
	}
#endif

#if defined(TORUS)
	for (int j{}; j < NETWORK_DIMENSION_Y; ++j)
	{
		for (int i{}; i < NETWORK_DIMENSION_X; ++i)
		{
			if (i == NETWORK_DIMENSION_X - 1)
				m_links.setUpConnection(m_routers[i + j * NETWORK_DIMENSION_X].m_eastPort, m_routers[0 + j * NETWORK_DIMENSION_X].m_westPort);
			else
				m_links.setUpConnection(m_routers[i + j * NETWORK_DIMENSION_X].m_eastPort, m_routers[(i + 1) + j * NETWORK_DIMENSION_X].m_westPort);

			if (j == NETWORK_DIMENSION_Y - 1)
				m_links.setUpConnection(m_routers[i + j * NETWORK_DIMENSION_X].m_southPort, m_routers[i + 0 * NETWORK_DIMENSION_X].m_northPort);
			else
				m_links.setUpConnection(m_routers[i + j * NETWORK_DIMENSION_X].m_southPort, m_routers[i + (j + 1) * NETWORK_DIMENSION_X].m_northPort);
		}
	}
#endif

	std::cout << " Network: " << NETWORK_DIMENSION_X << " x " << NETWORK_DIMENSION_Y << " network created " << std::endl;
}

void Network::printRouterIDs()
{
	log(" Network: below is routers ID ");
	for (int j{}; j < NETWORK_DIMENSION_Y; ++j)
	{
		for (int i{}; i < NETWORK_DIMENSION_X; ++i)
		{
			std::cout << m_routers[i + j * NETWORK_DIMENSION_X].m_routerID;
		}
		std::cout << std::endl;
	}
}

void Network::mountNode(RouterID routerID, DRAMNode* node)
{
	m_links.setUpConnection(m_routers[routerID.y * NETWORK_DIMENSION_X + routerID.x].m_terminalPort, node->m_controller->m_port);
	m_routers[routerID.y * NETWORK_DIMENSION_X + routerID.x].m_NID = node->m_controller->m_NID;
	m_mappingTable.push_back({ routerID, node->m_controller->m_NID });
	logDebug(" Network: node mounted ");
}

void Network::mountNode(RouterID routerID, PENode* node)
{
	m_links.setUpConnection(m_routers[routerID.y * NETWORK_DIMENSION_X + routerID.x].m_terminalPort, node->m_NI->m_port);
	m_routers[routerID.y * NETWORK_DIMENSION_X + routerID.x].m_NID = node->m_NI->m_NID;
	m_mappingTable.push_back({ routerID, node->m_NI->m_NID });
	logDebug(" Network: node mounted ");
}

void Network::printNodeIDs()
{
	log(" Network: below is node IDs ");
	for (int j{}; j < NETWORK_DIMENSION_Y; ++j)
	{
		for (int i{}; i < NETWORK_DIMENSION_X; ++i)
		{
			if (m_routers[i + j * NETWORK_DIMENSION_X].m_NID != -1)
				std::cout << " " << m_routers[i + j * NETWORK_DIMENSION_X].m_NID;
			else
				std::cout << " -";
		}
		std::cout << std::endl;
	}
}

void Network::viewMappingTable()
{
	log(" Network: below is mapping table: ");
	log(" router ID | node ID ");
	for (auto& mappingTableLine : m_mappingTable)
	{
		std::cout << mappingTableLine.routerID << "| " << mappingTableLine.NID << std::endl;
	}
}

void Network::updateMappingTables()
{
	for (auto& router : m_routers)
	{
		router.m_mappingTable = m_mappingTable;
	}
}

void Network::terminateConnections()
{
	m_links.terminateAllConnections();
}

void Network::runOneStep()
{
	m_links.runOneStep();
	for (auto& router : m_routers)
	{
		router.runOneStep();
	}
}

void Network::updateEnable()
{
	m_links.updateEnable();
	for (auto& router : m_routers)
	{
		router.updateEnable();
	}
}
