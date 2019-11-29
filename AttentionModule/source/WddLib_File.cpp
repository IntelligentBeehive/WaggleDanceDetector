#include "WddLib.h"

namespace wdd {
	// save executable name
	char _NAME_OF_EXE[MAX_PATH];
	// save full path to executable
	char _FULL_PATH_EXE[MAX_PATH];
	std::string GLOB_DANCE_OUTPUT_PATH;

	namespace file {
		void getNameOfExe(char * out, std::size_t size, char * argv0)
		{
			std::string argv0_str(argv0);
			std::string exeName;

			std::size_t found = argv0_str.find_last_of("\\");

			if (found == std::string::npos)

				exeName = argv0_str;
			else
				exeName = argv0_str.substr(found + 1);

			// check if .exe is at the end
			found = exeName.find_last_of(".exe");
			if (found == std::string::npos)
				exeName += ".exe";

			strcpy_s(out, size, exeName.c_str());
		}
		void getExeFullPath(char * out, std::size_t size)
		{
			char BUFF[MAX_PATH];
			HMODULE hModule = GetModuleHandle(NULL);
			if (hModule != NULL)
			{
				GetModuleFileName(hModule, BUFF, sizeof(BUFF) / sizeof(char));
				// remove '\WaggleDanceDetector.exe' (or any other name exe has)
				_tcsncpy_s(out, size, BUFF, strlen(BUFF) - (strlen(_NAME_OF_EXE) + 1));
			}
			else
			{
				std::cerr << "Error! Module handle is NULL - can not retrive exe path!" << std::endl;
				exit(-2);
			}
		}

		bool fileExists(const std::string& file_name)
		{
			struct stat buffer;
			return (stat(file_name.c_str(), &buffer) == 0);
		}
		bool dirExists(const char * dirPath)
		{
			int result = PathIsDirectory((LPCTSTR)dirPath);

			if (result & FILE_ATTRIBUTE_DIRECTORY)
				return true;

			return false;
		}
	}
}