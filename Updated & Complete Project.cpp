#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

// ANSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

class Flight
{
private:
	string flightNumber;
	int fuelLevel;
	int altitude;
	string planeType;
	time_t timeStamp;
	string emergencyType;

public:
	Flight(string fnum = "", int flevel = 100, int alt = 10000, string pType = "Commercial", string etype = "")
	{
		flightNumber = fnum;
		fuelLevel = flevel;
		altitude = alt;
		planeType = pType;
		emergencyType = etype;
		timeStamp = time(0);
	}

	string getFlightNumber() const
	{
		return flightNumber;
	}

	int getFuelLevel() const
	{
		return fuelLevel;
	}

	int getAltitude() const
	{
		return altitude;
	}

	string getPlaneType() const
	{
		return planeType;
	}

	string getEmergencyType() const
	{
		return emergencyType;
	}

	time_t getTimeStamp() const
	{
		return timeStamp;
	}

	void setFuelLevel(int fuel)
	{
		fuelLevel = fuel;
	}

	void setEmergencyType(string eType)
	{
		emergencyType = eType;
	}

	void displayInfo() const
	{
		cout << "[" << flightNumber << " | Fuel: " << fuelLevel << "% | Alt: " << altitude << "ft | Type: " << planeType;
		if (emergencyType != "")
		{
			cout << " | " << RED << "EMERGENCY: " << emergencyType << RESET;
		}
		cout << "]" << endl;
	}
};

class Queue
{
	struct Node
	{
		Flight flightData;
		Node* next;
		Node* prev;

		Node(Flight d = Flight())
		{
			flightData = d;
			next = nullptr;
			prev = nullptr;
		}
	};

	Node* front;
	Node* rear;

public:
	Queue(Node* front = nullptr, Node* rear = nullptr)
	{
		this->front = front;
		this->rear = rear;
	}

	bool isEmpty()
	{
		return (front == nullptr);
	}

	void enqueue(Flight fNum)
	{
		Node* newFlight = new Node(fNum);
		if (isEmpty())
		{
			front = rear = newFlight;
			return;
		}
		rear->next = newFlight;
		newFlight->prev = rear;
		rear = newFlight;
	}

	void dequeue()
	{
		if (isEmpty())
		{
			cout << "Queue is empty! Nothing to be popped!\n";
			return;
		}
		Node* temp = front;
		front = front->next;

		if (front == nullptr)
		{
			rear = nullptr;
		}
		else
		{
			front->prev = nullptr;
		}

		delete temp;
	}

	Flight peek()
	{
		if (isEmpty())
		{
			return Flight();
		}
		return front->flightData;
	}

	void handleEmergency(string flightNum)
	{
		if (isEmpty())
		{
			cout << "Queue is empty!\n";
			return;
		}
		if (front->flightData.getFlightNumber() == flightNum)
		{
			return;
		}
		else if (rear->flightData.getFlightNumber() == flightNum)
		{
			Node* moveToFront = rear;
			rear = rear->prev;
			rear->next = nullptr;

			moveToFront->next = front;
			front->prev = moveToFront;
			front = moveToFront;
			moveToFront->prev = nullptr;
			return;
		}

		Node* temp = front;
		while (temp != nullptr)
		{
			if (temp->flightData.getFlightNumber() == flightNum)
			{
				Node* moveToFront = temp;

				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;

				moveToFront->next = front;
				front->prev = moveToFront;
				front = moveToFront;
				moveToFront->prev = nullptr;
				return;
			}
			temp = temp->next;
		}
		cout << "No flight with " << flightNum << " has been found in the Queue!\n";
	}

	void updateFuelLevels(int minutes)
	{
		Node* temp = front;
		while (temp != nullptr)
		{
			int currentFuel = temp->flightData.getFuelLevel();
			int fuelDecrease = minutes * 2;
			int newFuelLevel = currentFuel - fuelDecrease;

			if (newFuelLevel < 0)
			{
				newFuelLevel = 0;
			}

			temp->flightData.setFuelLevel(newFuelLevel);
			if (newFuelLevel < 20 && temp->flightData.getEmergencyType() == "")
			{
				temp->flightData.setEmergencyType("Low Fuel");
			}
			temp = temp->next;
		}
	}

	void display()
	{
		if (isEmpty())
		{
			cout << "Queue is empty!\n";
			return;
		}

		Node* temp = front;
		while (temp != nullptr)
		{
			temp->flightData.displayInfo();
			temp = temp->next;
		}
	}
};

Flight createFlight()
{
	string fnum, pType, eType = "";
	int fuel, alt;
	char hasEmergency;

	cout << "\n--- Enter Flight Details ---\n";
	cout << "Flight Number (e.g., PK201): ";
	cin >> fnum;

	cout << "Fuel Level (0-100): ";
	cin >> fuel;
	while (fuel < 0 || fuel > 100)
	{
		cout << "Invalid! Enter fuel (0-100): ";
		cin >> fuel;
	}

	cout << "Altitude (ft): ";
	cin >> alt;

	cout << "Plane Type (Commercial/Cargo/Private): ";
	cin >> pType;

	cout << "Emergency? (y/n): ";
	cin >> hasEmergency;
	if (hasEmergency == 'y' || hasEmergency == 'Y')
	{
		cout << "Emergency Type:\n";
		cout << "1. Low Fuel\n";
		cout << "2. Technical Fault\n";
		cout << "3. Medical Emergency\n";
		cout << "Choice: ";
		int eChoice;
		cin >> eChoice;
		if (eChoice == 1)
			eType = "Low Fuel";
		else if (eChoice == 2)
			eType = "Technical Fault";
		else if (eChoice == 3)
			eType = "Medical Emergency";
	}

	return Flight(fnum, fuel, alt, pType, eType);
}

Flight generateRandomFlight()
{
	string fnum = "PK" + to_string(rand() % 900 + 100);
	int fuel = rand() % 81 + 20;
	int alt = rand() % 30001 + 5000;

	string types[] = { "Commercial", "Cargo", "Private" };
	string pType = types[rand() % 3];

	string eType = "";
	if (rand() % 10 == 0)  // 10% chance of emergency
	{
		if (fuel < 30)  // If fuel is low, must be Low Fuel emergency
		{
			eType = "Low Fuel";
		}
		else  // If fuel is good, can only be Technical or Medical
		{
			string emergencies[] = { "Technical Fault", "Medical Emergency" };
			eType = emergencies[rand() % 2];
		}
	}

	return Flight(fnum, fuel, alt, pType, eType);
}

bool isValidFlightNumber(string flightNum)
{
	// Check minimum length
	if (flightNum.length() < 5)
	{
		return false;
	}

	// Check starts with "PK"
	if (flightNum[0] != 'P' || flightNum[1] != 'K')
	{
		return false;
	}

	// Extract number part
	string numPart = flightNum.substr(2);

	// Check if numeric
	for (char c : numPart)
	{
		if (!isdigit(c))
		{
			return false;
		}
	}

	// Convert to number and check range
	int num = stoi(numPart);
	if (num < 100 || num > 999)
	{
		return false;
	}

	return true;
}

int main()
{
	srand(time(0));

	Queue landingQueue;
	Queue takeoffQueue;
	int choice;
	string flightNumber;
	int simulationTime = 0;
	int totalLandingsProcessed = 0;
	int totalTakeoffsProcessed = 0;
	int emergenciesHandled = 0;

	ofstream logFile;

	cout << "\n========================================\n";
	cout << CYAN << "   AIR TRAFFIC CONTROL SYSTEM (ATC)\n" << RESET;
	cout << "========================================\n";

	logFile.open("atc_log.txt", ios::app);
	if (!logFile)
	{
		cout << YELLOW << "[WARNING] Could not create log file!\n" << RESET;
	}
	else
	{
		logFile << "\n========== NEW SESSION STARTED ==========\n";
		time_t now = time(0); // time(0) = "What time is it?" means get clock reading
		char timeStr[26]; // timeStr[26] = "Give me a notepad with 26 spaces"
		ctime_s(timeStr, sizeof(timeStr), &now); // ctime_s() = "Write the time in readable format on that notepad"
		logFile << "Session Time: " << timeStr;
		logFile << "=========================================\n\n";
	}

	do
	{
		cout << "\n" << CYAN << "--- ATC MENU ---" << RESET << "\n";
		cout << " 1. Add Landing Request\n";
		cout << " 2. Add Takeoff Request\n";
		cout << " 3. Process Landing (Give Clearance)\n";
		cout << " 4. Process Takeoff (Give Clearance)\n";
		cout << " 5. Declare Emergency (Move to Front)\n";
		cout << " 6. Display Landing Queue\n";
		cout << " 7. Display Takeoff Queue\n";
		cout << " 8. Display Both Queues\n";
		cout << " 9. Add Random Landing Request\n";
		cout << "10. Add Random Takeoff Request\n";
		cout << "11. Use Detailed Input (createFlight)\n";
		cout << "12. Advance Time (simulate time passing)\n";
		cout << "13. Display Statistics\n";
		cout << "14. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			cout << "Enter flight number (e.g., PK201): ";
			cin >> flightNumber;

			if (!isValidFlightNumber(flightNumber))
			{
				cout << RED << "[ERROR] Invalid flight number! Must be PK100-PK999\n" << RESET;
				break;
			}

			Flight f(flightNumber);
			landingQueue.enqueue(f);
			cout << GREEN << flightNumber << " has requested to land. Added to landing queue.\n" << RESET;

			logFile << "[" << simulationTime << "min] " << flightNumber << " requested landing\n";
			logFile.flush();
			break;
		}

		case 2:
		{
			cout << "Enter flight number (e.g., PK250): ";
			cin >> flightNumber;

			if (!isValidFlightNumber(flightNumber))
			{
				cout << RED << "[ERROR] Invalid flight number! Must be PK100-PK999\n" << RESET;
				break;
			}

			Flight f(flightNumber);
			takeoffQueue.enqueue(f);
			cout << GREEN << flightNumber << " has requested takeoff clearance. Added to takeoff queue.\n" << RESET;

			logFile << "[" << simulationTime << "min] " << flightNumber << " requested takeoff\n";
			logFile.flush();
			break;
		}

		case 3:
		{
			if (!landingQueue.isEmpty())
			{
				Flight nextFlight = landingQueue.peek();
				string flightNumber = nextFlight.getFlightNumber();
				cout << "\n[ATC] Processing landing request...\n";
				cout << GREEN << "[ATC] " << flightNumber << " has been given LANDING CLEARANCE!\n" << RESET;
				totalLandingsProcessed++;

				logFile << "[" << simulationTime << "min] " << flightNumber << " given LANDING clearance\n";
				logFile.flush();

				landingQueue.dequeue();
			}
			else
			{
				cout << "\n[ATC] No planes in landing queue.\n";
			}
			break;
		}

		case 4:
		{
			if (!takeoffQueue.isEmpty())
			{
				Flight nextFlight = takeoffQueue.peek();
				string flightNumber = nextFlight.getFlightNumber();
				cout << "\n[ATC] Processing takeoff request...\n";
				cout << GREEN << "[ATC] " << flightNumber << " has been given TAKEOFF CLEARANCE!\n" << RESET;
				totalTakeoffsProcessed++;

				logFile << "[" << simulationTime << "min] " << flightNumber << " given TAKEOFF clearance\n";
				logFile.flush();

				takeoffQueue.dequeue();
			}
			else
			{
				cout << "\n[ATC] No planes in takeoff queue.\n";
			}
			break;
		}

		case 5:
		{
			cout << "Enter flight number declaring emergency: ";
			cin >> flightNumber;
			cout << "\n" << RED << "[EMERGENCY] " << RESET << flightNumber << " has declared an emergency!\n";
			landingQueue.handleEmergency(flightNumber);
			cout << "[ATC] " << flightNumber << " moved to front of landing queue (PRIORITY).\n";
			emergenciesHandled++;

			logFile << "[" << simulationTime << "min] EMERGENCY: " << flightNumber << " moved to front of landing queue\n";
			logFile.flush();
			break;
		}

		case 6:
		{
			cout << "\n--- LANDING QUEUE ---\n";
			landingQueue.display();
			if (!landingQueue.isEmpty())
			{
				Flight nextFlight = landingQueue.peek();
				string flightNumber = nextFlight.getFlightNumber();
				cout << BLUE << "Next for landing: " << flightNumber << RESET << "\n";
			}
			break;
		}

		case 7:
		{
			cout << "\n--- TAKEOFF QUEUE ---\n";
			takeoffQueue.display();
			if (!takeoffQueue.isEmpty())
			{
				Flight nextFlight = takeoffQueue.peek();
				string flightNumber = nextFlight.getFlightNumber();
				cout << BLUE << "Next for takeoff: " << flightNumber << RESET << "\n";
			}
			break;
		}

		case 8:
		{
			cout << "\n========== CURRENT QUEUE STATUS ==========\n";
			cout << "Landing Queue:\n";
			landingQueue.display();
			cout << "\nTakeoff Queue:\n";
			takeoffQueue.display();
			cout << "==========================================\n";
			break;
		}

		case 9:
		{
			Flight f = generateRandomFlight();
			landingQueue.enqueue(f);
			cout << GREEN << f.getFlightNumber() << " (AUTO-GENERATED) has requested to land.\n" << RESET;

			logFile << "[" << simulationTime << "min] " << f.getFlightNumber() << " (AUTO-GENERATED) requested landing\n";
			logFile.flush();
			break;
		}

		case 10:
		{
			Flight f = generateRandomFlight();
			takeoffQueue.enqueue(f);
			cout << GREEN << f.getFlightNumber() << " (AUTO-GENERATED) has requested takeoff.\n" << RESET;

			logFile << "[" << simulationTime << "min] " << f.getFlightNumber() << " (AUTO-GENERATED) requested takeoff\n";
			logFile.flush();
			break;
		}

		case 11:
		{
			Flight f = createFlight();
			cout << "\nAdd to (1) Landing or (2) Takeoff queue? ";
			int qChoice;
			cin >> qChoice;
			if (qChoice == 1)
			{
				landingQueue.enqueue(f);
				cout << "Added to landing queue.\n";
				logFile << "[" << simulationTime << "min] " << f.getFlightNumber() << " (DETAILED) requested landing\n";
			}
			else
			{
				takeoffQueue.enqueue(f);
				cout << "Added to takeoff queue.\n";
				logFile << "[" << simulationTime << "min] " << f.getFlightNumber() << " (DETAILED) requested takeoff\n";
			}
			logFile.flush();
			break;
		}

		case 12:
		{
			int minutes;
			cout << "Advance by how many minutes? ";
			cin >> minutes;
			simulationTime += minutes;

			landingQueue.updateFuelLevels(minutes);
			takeoffQueue.updateFuelLevels(minutes);

			cout << "\n[TIME] " << minutes << " minutes passed. Current time: " << simulationTime << " minutes\n";
			cout << YELLOW << "[WARNING] Check queues for low fuel emergencies!" << RESET << "\n";

			logFile << "[" << simulationTime << "min] Time advanced by " << minutes << " minutes (Total: " << simulationTime << "min)\n";
			logFile.flush();
			break;
		}

		case 13:
		{
			cout << "\n" << CYAN << "========== ATC STATISTICS ==========" << RESET << "\n";
			cout << "Total Landings Processed: " << totalLandingsProcessed << "\n";
			cout << "Total Takeoffs Processed: " << totalTakeoffsProcessed << "\n";
			cout << "Total Emergencies Handled: " << emergenciesHandled << "\n";
			cout << "Simulation Time: " << simulationTime << " minutes\n";
			cout << CYAN << "====================================" << RESET << "\n";
			break;
		}

		case 14:
		{
			logFile << "\n========== SESSION ENDED ==========\n";
			logFile << "Total Landings: " << totalLandingsProcessed << "\n";
			logFile << "Total Takeoffs: " << totalTakeoffsProcessed << "\n";
			logFile << "Total Emergencies: " << emergenciesHandled << "\n";
			logFile << "Simulation Time: " << simulationTime << " minutes\n";
			logFile << "===================================\n\n";
			logFile.close();

			cout << "\n" << CYAN << "[ATC] Shutting down Air Traffic Control system..." << RESET << "\n";
			cout << "Goodbye!\n";
			break;
		}

		default:
			cout << "\n" << RED << "[ERROR] Invalid choice! Please enter 1-14.\n" << RESET;
		}

	} while (choice != 14);

	return 0;
}