#ifndef _FILENODE_H_
#define _FILENODE_H_

#include <ctime>
#include <iostream>

class FileNode {
public:
	FileNode(char* fn) : //Receive pointer to filename string
		//Store filename and retrieve timestamp as time since Epoch (Avoid locality time differences)
		filename(fn), timestamp(std::time(nullptr)) {} 
	
	//Filename string should be dynamically allocated at runtime so memory should be freed when file is removed from Database
	~FileNode() { 
	}

	//Return the pointer to the filename
	char* get_Filename() {
		return filename;
	}

	//Return time since last Epoch
	std::time_t get_Timestamp() {
		return timestamp;
	}

	//Print Filename and Date in Local Calendar Format
	void printFile() {
		std::cout << "File Name: " << filename
			<< "\n Date Last Updated: " << std::asctime(std::localtime(&timestamp)) << std::endl;
	}

	//Change Filename to provided Filename and print status of update
	//Currently assumes file extension is passed as part of file name string so no parsing occurs here)
	//Updates timestamp once update completes
	void updateFilename(char* fn) {
		std::cout << "Updating File Name...\n"
			<< "\tCurrent File Name: " << filename
			<< "\n\tNew File Name: " << fn;

		delete[] filename;
		filename = fn;

		std::cout << "\n\n Update Complete!";
	}


private:
	char* filename;
	std::time_t timestamp;
};
#endif
