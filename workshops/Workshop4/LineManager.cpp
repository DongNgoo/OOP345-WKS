#include "LineManager.h"
#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <vector>
namespace seneca {

	//Constructor
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		std::ifstream inputFile(file);
		if (!inputFile) {
			throw "Error: Unable to open file: " + file;
		}

		//Parse file and set up workstation connection
		std::string record;
		while (std::getline(inputFile, record)) {
			auto delimeter = record.find('|');
			if (delimeter != std::string::npos) {
				std::string currentStation = record.substr(0, delimeter);
				std::string nextStation = record.substr(delimeter + 1);

				//Find workstation by name
				auto current = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
					return ws->getItemName() == currentStation;

					});
				auto next = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
					return ws->getItemName() == nextStation;
					});

				if (current != stations.end()) {
					(*current)->setNextStation(next != stations.end() ? *next : nullptr);
				}
			}
		}

		//Set up m_activeLine and find first station
		m_activeLine = stations;

		m_firstStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
			return std::none_of(stations.begin(), stations.end(), [&](Workstation* other) {
				return other->getNextStation() == ws;
				});
			});

		//Update the count of customer order

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
		static size_t iteration = 0;

		os << "Line Manager Iteration: " << ++iteration << std::endl;

		if (!g_pending.empty()) {
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}

		//Perfomr fill  operartion on each workstation
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			ws->fill(os);
			});

		// Attempt to move orders down the line
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			ws->attemptToMoveOrder();
			});

		// Check if all orders are processed
		return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
	}

	// Display all active stations in the current order
	void LineManager::display(std::ostream& os) const {
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* ws) {
			ws->display(os);
			});
	}
}