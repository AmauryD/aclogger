#include "Logger.h"

Logger::Logger(void)
{
    char buffer[20];
    sprintf(buffer,"aclogger%c",DIR_SEP);
    _dir = buffer;
}

Logger::~Logger(void)
{
}

std::vector<std::string> Logger::extractFileDirs(const std::string &filename)
{
	std::vector<std::string> directories;
	std::string copy = filename;
	size_t last_slash_idx = copy.rfind(DIR_SEP);
	while (std::string::npos != last_slash_idx)
	{
		copy.erase(last_slash_idx);
		directories.push_back(copy);
		last_slash_idx = copy.rfind(DIR_SEP);
	}
	std::reverse(directories.begin(), directories.end());
	return directories;
}

bool Logger::dirExists(const std::string &dir)
{
    if(access(dir.c_str(),0)) {
        struct stat dirStats;
        int res = stat(dir.c_str(),&dirStats); //parse stats
		if (res == 0) {
			if (dirStats.st_mode && S_IFDIR)
				return true;
			else
				return false;
		}
    }
    return false;
}

bool Logger::setFile(const std::string &file)
{
	if(!isLogFile(file))
		return false;
	std::string s;
	s.append(_dir).append(file);
	std::replace(s.begin(), s.end(), '|', DIR_SEP);
	_fileName = s;

	std::vector<std::string> dirs(extractFileDirs(_fileName));

	for (unsigned int i(0); i < dirs.size(); i++)
	{
		std::string dir = dirs.at(i);
		if (!dirExists(dir)) {
			MK_DIR(dir.c_str());
		}
	}

	return true;
}

bool Logger::isFileSet()
{
	return (_fileName.c_str() != "");
}

bool Logger::isLogFile(const std::string &fileName)
{
	return (fileName.substr(fileName.find_last_of(".") + 1).compare(std::string("log")) == 0);
}

bool Logger::log(const std::string &text)
{
	if(!isFileSet()) return false;
	char buffer[80];

	time_t t = time(0);
	struct tm * now = localtime(&t);
    strftime(buffer,80,"%d-%m-%Y %I:%M:%S",now);

	_file.open(_fileName.c_str(), std::ios_base::app);
	if(!_file.is_open()) return false;

	_file << buffer << " -> " << text.c_str() << std::endl;
    _file.close();
	return true;
}

bool Logger::clear()
{
	if(!isFileSet()) return false;
	_file.open(_fileName, std::ofstream::trunc);
	if (!_file.is_open()) return false;
	_file.close();
	return true;
}

bool Logger::removeFile()
{
	if (!isFileSet())
		return false;
	if (_file.is_open()) 
		return false;
	if (remove(_fileName.c_str()) == 0) 
		return true;
	return false;
}

bool Logger::write(const std::string &text)
{
	 if(!isFileSet()) return false;
	 _file.open(_fileName.c_str(), std::ios_base::out);
	 if(!_file.is_open()) return false;
     _file << text.c_str() << std::endl;
     _file.close();
     return true;
}

bool Logger::append(const std::string &text)
{
     if(!isFileSet()) return false;
	 _file.open(_fileName.c_str(), std::ios_base::app);
	 if(!_file.is_open()) return false;
     _file << text.c_str() << std::endl;
     _file.close();
     return true;
}
