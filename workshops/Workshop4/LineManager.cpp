#include "LineManager.h"
#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
namespace seneca {

	//Constructor
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		std::ifstream inputFile(file);
		if (!inputFile) {
			throw "Error: Unable to open file: " + file;
		}
		Utilities util;
		std::string line;

		while (std::getline(inputFile, line)) {
			size_t next_pos = 0;
			bool more = true;

			std::string currentStationName = util.extractToken(line, next_pos, more);
			std::string nextStationName;

			if (more) {
				nextStationName = util.extractToken(line, next_pos, more);
			}
			auto currentStation = std::find_if(stations.begin(), stations.end(),
				[&](Workstation* ws) { return ws->getItemName() == currentStationName; });

			auto nextStation = std::find_if(stations.begin(), stations.end(),
				[&](Workstation* ws) { return ws->getItemName() == nextStationName; });

			if (currentStation != stations.end()) {
				m_activeLine.push_back(*currentStation);
				if (nextStation != stations.end()) {
					(*currentStation)->setNextStation(*nextStation);
				}
			}
		}
		auto firstStationIt = std::find_if(m_activeLine.begin(), m_activeLine.end(),
			[&](Workstation* ws) {
				return std::none_of(m_activeLine.begin(), m_activeLine.end(),
				[&](Workstation* other) { return other->getNextStation() == ws; });
			});

		if (firstStationIt != m_activeLine.end()) {
			m_firstStation = *firstStationIt;
		}
		else {
			throw "Error: Unable to identify the first station.";
		}

		// Set total orders count
		m_cntCustomerOrder = g_pending.size();

		
		
		
	}

	// Reorder stations
	void LineManager::reorderStations() {
		std::vector<Workstation*> reorderedLine;
		Workstation* current = m_firstStation;

		while (current) {
			reorderedLine.push_back(current);
			current = current->getNextStation();
		}

		m_activeLine = reorderedLine;
	}

	//Run one iteration of the assambly line
	bool LineManager::run(std::ostream & os) {
		static size_t iterationCount = 0;
		++iterationCount;

		os << "Line Manager Iteration: " << iterationCount << std::endl;

		// Move one order from g_pending to the first station
		if (!g_pending.empty()) {
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}

		// Fill and move orders for each station
		for (auto& station : m_activeLine) {
			station->fill(os);
		}

		for (auto& station : m_activeLine) {
			station->attemptToMoveOrder();
		}
		// Check if all orders are processed (completed or incomplete)
	    size_t totalOrdersProcessed = g_completed.size() + g_incomplete.size();
		if (totalOrdersProcessed == m_cntCustomerOrder) {
			return true; // All orders are either completed or cannot be filled
		}

		return false; // Continue processing
	}

	// Display all active stations in the current order
	void LineManager::display(std::ostream& os) const {
		for (const auto& station : m_activeLine) {
			station->display(os);
		}
	}
}