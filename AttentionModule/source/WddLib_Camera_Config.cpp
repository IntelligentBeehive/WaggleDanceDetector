#include "WddLib.h"
namespace wdd {
	namespace camera {
		// saves loaded, modified camera configs
		std::vector<CamConf> camConfs;
		// saves the next unique camId
		std::size_t nextUniqueCamID = 0;
		char camConfPath[] = "\\cams.config";

		std::size_t getNextUniqueCamID() {
			return nextUniqueCamID++;
		}

		// format of config file:
		// <camId> <GUID> <Arena.p1> <Arena.p2> <Arena.p3> <Arena.p4>
		void loadCamConfigFileReadLine(std::string line)
		{
			char * delimiter = " ";
			std::size_t pos = 0;

			std::size_t tokenNumber = 0;

			std::size_t camId = NULL;
			char guid_str[64];
			std::array<cv::Point2i, 4> arena;

			//copy & convert to char *
			char * string1 = _strdup(line.c_str());

			// parse the line
			char *token = NULL;
			char *next_token = NULL;
			token = strtok_s(string1, delimiter, &next_token);

			int arenaPointNumber = 0;
			while (token != NULL)
			{
				int px, py;

				// camId
				if (tokenNumber == 0)
				{
					camId = atoi(token);
				}
				// guid
				else if (tokenNumber == 1)
				{
					strcpy_s(guid_str, token);
				}
				else
				{
					switch (tokenNumber % 2)
					{
						// arena.pi.x
					case 0:
						px = atoi(token);
						break;
						// arena.pi.y
					case 1:
						py = atoi(token);
						arena[arenaPointNumber++] = cv::Point2i(px, py);
						break;
					}

				}

				tokenNumber++;
				token = strtok_s(NULL, delimiter, &next_token);
			}
			free(string1);
			free(token);

			if (tokenNumber != 10)
				std::cerr << "Warning! cams.config file contains corrupted line with total tokenNumber: " << tokenNumber << std::endl;

			struct CamConf c;
			c.camId = camId;
			strcpy_s(c.guid_str, guid_str);
			c.arena = arena;
			c.configured = true;

			// save loaded CamConf to global vector
			camConfs.push_back(c);

			// keep track of loaded camIds and alter nextUniqueCamID accordingly
			if (camId >= nextUniqueCamID)
				nextUniqueCamID = camId + 1;
		}
		void loadCamConfigFile()
		{
			char BUFF[MAX_PATH];
			strcpy_s(BUFF, MAX_PATH, wdd::_FULL_PATH_EXE);
			strcat_s(BUFF, MAX_PATH, camConfPath);

			if (!wdd::file::fileExists(BUFF))
			{
				// create empty file
				std::fstream f;
				f.open(BUFF, std::ios::out);
				f << std::flush;
				f.close();
			}

			std::string line;
			std::ifstream camconfigfile;
			camconfigfile.open(BUFF);

			if (camconfigfile.is_open())
			{
				while (getline(camconfigfile, line))
				{
					loadCamConfigFileReadLine(line);
				}
				camconfigfile.close();
			}
			else
			{
				std::cerr << "Error! Can not open cams.config file!" << std::endl;
				exit(111);
			}
		}
		void saveCamConfigFile()
		{
			char BUFF[MAX_PATH];
			strcpy_s(BUFF, MAX_PATH, _FULL_PATH_EXE);
			strcat_s(BUFF, MAX_PATH, camConfPath);
			FILE * camConfFile_ptr;
			fopen_s(&camConfFile_ptr, BUFF, "w+");

			for (auto it = camConfs.begin(); it != camConfs.end(); ++it)
			{
				if (it->configured)
				{
					fprintf_s(camConfFile_ptr, "%d %s ", it->camId, it->guid_str);
					for (unsigned i = 0; i < 4; i++)
						fprintf_s(camConfFile_ptr, "%d %d ", it->arena[i].x, it->arena[i].y);
					fprintf_s(camConfFile_ptr, "\n");
				}
			}
			fclose(camConfFile_ptr);
		}
	}
}