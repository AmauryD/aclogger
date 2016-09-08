#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>

#if defined(_WIN32)
#include <windows.h>
#include <io.h>
#include <direct.h>
#define DIR_SEP '\\'
#define MK_DIR(PATH) _mkdir(PATH) 
#else
#include <unistd.h>
#define DIR_SEP '/'
#define MK_DIR(PATH) mkdir(PATH, 0777)
#endif

class Logger
{
public:
	Logger(void);
	virtual ~Logger(void);

	bool append(const std::string &text);
	bool write(const std::string &text);
	bool log(const std::string &text);
	bool setFile(const std::string &file);
	bool removeFile();
	bool clear();
private:
	bool isLogFile(const std::string &fileName);
	std::vector<std::string> extractFileDirs(const std::string &filename);
	bool dirExists(const std::string &dir);
	bool isFileSet();

	std::string _dir;
	std::ofstream _file;
	std::string _fileName;
};


#endif // LOGGER_H
