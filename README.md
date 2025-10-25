# Air-Traffic-Control-Management-System
🎯 Overview
This project simulates a real-world Air Traffic Control (ATC) system managing airplane landing and takeoff operations at an airport with a single runway. The system demonstrates First Come First Serve (FCFS) queue management with priority handling for emergencies, making it a practical implementation of Queue Abstract Data Types (ADT) and Object-Oriented Programming principles.
# Real-World Problem Solved:

Managing multiple flight requests efficiently
Prioritizing emergency landings (low fuel, technical faults, medical emergencies)
Time-based fuel management simulation
Complete operation logging and statistics tracking
✨ Features
# Core Functionality:

✅ Dual Queue System: Separate queues for landing and takeoff requests
✅ FCFS Order Management: First Come First Serve processing
✅ Emergency Priority Queue: Automatic front-of-queue placement for emergencies
✅ Flight Data Management: Tracks flight number, fuel level, altitude, plane type, and emergency status
✅ Time-Based Simulation: Simulated clock with fuel degradation over time (2% per minute)
✅ Auto-Emergency Detection: Automatic emergency declaration when fuel drops below 20%
✅ Statistics Tracking: Real-time statistics for landings, takeoffs, and emergencies handled
✅ File Logging System: Complete session history logged to atc_log.txt
✅ Input Validation: Flight number format validation (PK100-PK999)
✅ Color-Coded Console Output: Visual distinction for emergencies, warnings, and success messages

# Flight Generation:

Manual Input: Detailed flight creation with custom parameters
Auto-Generation: Random flight generation with realistic data
Emergency Simulation: 10% random emergency chance with three types (Low Fuel, Technical Fault, Medical Emergency)


# 🛠️ Technologies & Concepts
# Programming Language:

C++ (Standard: C++11 or later)

# Libraries Used:

<iostream> - Input/output operations
<string> - String handling
<ctime> - Time and date functions
<cstdlib> - Random number generation
<fstream> - File input/output operations

# Data Structures Implemented:

Doubly Linked List: Custom implementation for queue nodes
Queue ADT: FIFO (First In First Out) operations
Priority Queue: Emergency handling mechanism

# OOP Concepts Applied:

Classes & Objects: Flight and Queue classes
Encapsulation: Private data members with public getters/setters
Abstraction: Queue ADT with clean interface
Data Hiding: Private node structure within Queue class

# Design Patterns:

ADT (Abstract Data Type): Queue implementation
Separation of Concerns: Distinct classes for Flight and Queue management
Menu-Driven Architecture: User interaction pattern
