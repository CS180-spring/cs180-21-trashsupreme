#ifndef _FILENODE_H_
#define _FILENODE_H_

#include <ctime>

class FileNode {
public:
	FileNode() {}
	~FileNode() {}
	char* get_filename() {}
	std::time_t get_timestamp() {}

private:
	char* filename;
	std::time_t timestamp;
};
#endif _FILENODE_H_
