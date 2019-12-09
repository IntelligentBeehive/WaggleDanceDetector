#pragma once

#include "stdafx.h"

namespace wdd {
	// save executable name
	extern char _NAME_OF_EXE[MAX_PATH];
	// save full path to executable
	extern char _FULL_PATH_EXE[MAX_PATH];
	extern std::string GLOB_DANCE_OUTPUT_PATH;
	namespace file {
		void initNameOfExe(char * argv0);
		void initExeFullPath();
		bool fileExists(const std::string& file_name);
		bool dirExists(const char * dirPath);
	}
	namespace camera {
		std::size_t getNextUniqueCamID();
		void loadCamConfigFileReadLine(std::string line);
	}
	namespace math {
		// Converts an unsigned vector to degrees
		double uvecToDegree(cv::Point2d in);
	}
}