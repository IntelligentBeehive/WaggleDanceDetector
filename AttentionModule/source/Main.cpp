#include "stdafx.h"
#include "DotDetectorLayer.h"
#include "InputVideoParameters.h"
#include "VideoFrameBuffer.h"
#include "WaggleDanceDetector.h"
#include "WaggleDanceExport.h"
#include <tclap/CmdLine.h>
#include "WddLib.h"

using namespace wdd;
using namespace std;


struct WddFrameAnalyseConfiguration {
	WddFrameAnalyseConfiguration(cv::Mat frame_input_monochrome, cv::Mat frame_target, VideoFrameBuffer* videoFrameBuffer, unsigned long long frame_counter, bool isVisual) {
		this->frame_input_monochrome = frame_input_monochrome;
		this->frame_target = frame_target;
		this->videoFrameBuffer = videoFrameBuffer;
		this->frame_counter = frame_counter;
		this->isVisual = isVisual;

	}
	cv::Mat frame_input_monochrome;
	cv::Mat frame_target;
	VideoFrameBuffer* videoFrameBuffer;
	unsigned long long frame_counter;
	bool isVisual;
};

char* version = "1.2.5";

int Cir_radius = 3;
cv::Scalar Cir_color_yel = cv::Scalar(255, 255, 0);
cv::Scalar Cir_color_gre = cv::Scalar(0, 255, 0);
cv::Scalar Cir_color_som = cv::Scalar(0, 0, 255);
//make the circle filled with value < 0
int Cir_thickness = -1;

inline void guidToString(GUID g, char * buf){
	char _buf[64];
	sprintf_s(_buf, "[%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x]",
		g.Data1, g.Data2, g.Data3,
		g.Data4[0], g.Data4[1], g.Data4[2],
		g.Data4[3], g.Data4[4], g.Data4[5],
		g.Data4[6], g.Data4[7]);

	strcpy_s(buf,64,_buf);	
}

void runTestMode(std::string videoFilename, double aux_dd_min_potential, int aux_wdd_signal_min_cluster_size, bool noGui);

void getCommandLineValues(int nargs, char** argv,
	double* dd_min_potential, int* wdd_signal_min_cluster_size, bool* autoStartUp, std::string* videofile, bool* noGui, std::string* dancePath) {

	try
	{
		// Define the command line object.
		TCLAP::CmdLine cmd("Command description message", ' ', version);

		// Define a value argument and add it to the command line.
		TCLAP::ValueArg<double> potArg("p", "potential", "Potential minimum value", false, 0.12, "double");
		cmd.add(potArg);

		// Define a value argument and add it to the command line.
		TCLAP::ValueArg<int> cluArg("c", "cluster", "Cluster minimum size", false, 6, "int");
		cmd.add(cluArg);

		// Define a switch and add it to the command line.
		TCLAP::SwitchArg autoSwitch("a", "auto", "Selects automatically configured cam", false);
		cmd.add(autoSwitch);

#if defined(TEST_MODE_ON)
		// path to test video input file
		TCLAP::ValueArg<std::string> testVidArg("t", "video", "path to video file", true, "", "string");
		cmd.add(testVidArg);

		// path to output of dance detection file
		TCLAP::ValueArg<std::string> outputArg("o", "output", "path to result file", false, "", "string");
		cmd.add(outputArg);

		// switch to turn off GUI/Video output
		TCLAP::SwitchArg noGUISwitch("n", "no-gui", "disable gui (video output)", false);
		cmd.add(noGUISwitch);
#endif
		// Parse the args.
		cmd.parse(nargs, argv);

		// Get the value parsed by each arg. 
		*dd_min_potential = potArg.getValue();
		*wdd_signal_min_cluster_size = cluArg.getValue();
		*autoStartUp = autoSwitch.getValue();
		*videofile = testVidArg.getValue();
		*noGui = noGUISwitch.getValue();
		*dancePath = outputArg.getValue();

		if (dancePath->size())
		{
			char BUFF[MAXCHAR];
			strcpy_s(BUFF, MAX_PATH, dancePath->c_str());
			GLOB_DANCE_OUTPUT_PATH = std::string(BUFF);
		}
		else
		{
			char BUFF[MAXCHAR];
			strcpy_s(BUFF, MAX_PATH, _FULL_PATH_EXE);
			strcat_s(BUFF, MAX_PATH, "\\dance.txt");
			GLOB_DANCE_OUTPUT_PATH = std::string(BUFF);
		}
	}
	catch (TCLAP::ArgException &e)
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}
}

int main(int nargs, char** argv)
{	
	// get full name of executable
	wdd::file::getNameOfExe(_NAME_OF_EXE, sizeof(_NAME_OF_EXE), argv[0]);

	// get the full path to executable 
	wdd::file::getExeFullPath(_FULL_PATH_EXE, sizeof(_FULL_PATH_EXE));

	char * compiletime = __TIMESTAMP__;
	printf("WaggleDanceDetection Version %s - compiled at %s\n\n",
		version, compiletime);

	// define values potentially set by command line
	double dd_min_potential;
	int wdd_signal_min_cluster_size;
	bool autoStartUp;
	std::string videofile;
	bool noGui;
	std::string dancePath;
	getCommandLineValues(nargs, argv, &dd_min_potential, &wdd_signal_min_cluster_size, &autoStartUp, &videofile, &noGui, &dancePath);

	// call in test env
	cout << "Commandline values set!" << endl;
	if(videofile.size())
	{	
		cout << "videofile is set! let's run in test mode";
		runTestMode(videofile, dd_min_potential, wdd_signal_min_cluster_size, noGui);
		exit(0);
	}

	GalaxyCameraCapture* camera = new GalaxyCameraCapture();
	camera->Initialize(gxstring(wdd::GLOB_DANCE_OUTPUT_PATH.c_str()));
	camera->Connect();


	// if autoStartUp flag, iterate camIdsLaunch and select first configured camId
	/*if(autoStartUp)
	{*/
	if (camera->StartCapture())
	{
		CImageDataPointer frame = camera->GetFrame();
		//frame->
	}
	//}

	printf("Starting WaggleDanceDetector");

	int param = -1, key;

	while(key = cv::waitKey(0))
	{
		switch(key)
		{
			//case 'p':	case 'P':	printf("Selected Parameter: Potential\n");		param = 0;		break;
			//case 'c':	case 'C':	printf("Selected Parameter: Cluster Number\n");	param = 1;		break;
			//case '+':	if(pCam)	pCam->IncrementCameraParameter(param);		break;
			//case '-':	if(pCam)	pCam->DecrementCameraParameter(param);		break;
		case 'i': default:
			printf("WaggleDanceDetection Version %s - compiled at %s\n\n",
				version, compiletime);

			printf("Currently dynamic parameter change is deactivated.\n");
			/*
			printf("Use the following keys to change camera parameters:\n"
			"\t'p' - select Potential parameter\n"
			"\t'c' - select min cluster number parameter\n"
			"\t'+' - increment selected parameter\n"
			"\t'-' - decrement selected parameter\n");
			*/
		}
	}

	/*
	printf("Use the following keys to change camera parameters:\n"
	"\t'g' - select gain parameter\n"
	"\t'e' - select exposure parameter\n"
	"\t'z' - select zoom parameter\n"
	"\t'r' - select rotation parameter\n"
	"\t'+' - increment selected parameter\n"
	"\t'-' - decrement selected parameter\n");
	// The <ESC> key will exit the program
	CLEyeCameraCapture *pCam = NULL;
	*/

	return 0;
}

//
//	Layer 1: DotDetector Configuration
//
int DD_FREQ_MIN = 11;
int DD_FREQ_MAX = 17;
double DD_FREQ_STEP = 1;
//	Layer 2: Waggle SIGNAL Configuration
double WDD_SIGNAL_DD_MAXDISTANCE = 2.3;
//	Layer 3: Waggle Dance Configuration
double	WDD_DANCE_MAX_POSITION_DISTANCEE = sqrt(4);
int		WDD_DANCE_MAX_FRAME_GAP = 3;
int		WDD_DANCE_MIN_CONSFRAMES = 20;
//
//	Global: video configuration
//
int FRAME_RED_FAC = 1;//4 -> 1/16 -> 320 ?= x * 1/16 -> 
//
//	Develop: Waggle Dance Configuration
//
bool wdd_write_dance_file = true;
bool wdd_write_signal_file = false;
int wdd_verbose = 0;

void analyseFrame(WaggleDanceDetector* wdd, cv::Mat* frame_input, WddFrameAnalyseConfiguration* conf) {
	const std::map<std::size_t, cv::Point2d> * WDDSignalId2PointMap = wdd->getWDDSignalId2PointMap();
	const std::vector<DANCE> * WDDFinishedDances = wdd->getWDDFinishedDancesVec();

	const std::map<std::size_t, cv::Point2d>  WDDDance2PointMap;

	//convert BGR -> Gray
	cv::cvtColor(*frame_input, conf->frame_input_monochrome, CV_BGR2GRAY);

	// save to global Frame Buffer
	conf->videoFrameBuffer->addFrame(&conf->frame_input_monochrome);

	// subsample
	cv::resize(conf->frame_input_monochrome, conf->frame_target, conf->frame_target.size(),
		0, 0, cv::INTER_AREA);

	// feed WDD with tar_frame
	if (conf->frame_counter < WDD_FBUFFER_SIZE - 1)
	{
		wdd->copyInitialFrame(conf->frame_counter, false);
	}
	else if (conf->frame_counter == WDD_FBUFFER_SIZE - 1)
	{
		wdd->copyInitialFrame(conf->frame_counter, true);
	}
	else
	{
		wdd->copyFrame(conf->frame_counter);
	}

	// output visually if enabled
	if (conf->isVisual)
	{
		if (DotDetectorLayer::DD_SIGNALS_NUMBER > 0)
		{
			for (auto it = DotDetectorLayer::DD_SIGNALS_IDs.begin(); it != DotDetectorLayer::DD_SIGNALS_IDs.end(); ++it)
				cv::circle(*frame_input, DotDetectorLayer::DD_POSITIONS.at(*it)*std::pow(2, FRAME_RED_FAC), 2, Cir_color_som, Cir_thickness);
		}
		//check for WDD Signal
		if (wdd->isWDDSignal())
		{
			for (std::size_t i = 0; i < wdd->getWDDSignalNumber(); i++)
			{
				cv::circle(*frame_input, (*WDDSignalId2PointMap).find(i)->second*std::pow(2, FRAME_RED_FAC),
					Cir_radius, Cir_color_yel, Cir_thickness);
			}
		}
		bool waitLongerThanEver = false;
		if (wdd->isWDDDance())
		{

			for (auto it = WDDFinishedDances->begin(); it != WDDFinishedDances->end(); ++it)
			{
				if ((*it).DANCE_FRAME_END >= conf->frame_counter - 10)
				{
					cv::circle(*frame_input, (*it).positions[0] * std::pow(2, FRAME_RED_FAC),
						Cir_radius, Cir_color_gre, Cir_thickness);
					cv::line(*frame_input, (*it).positions[0] * std::pow(2, FRAME_RED_FAC), (*it).positions[0] * std::pow(2, FRAME_RED_FAC) - (*it).orient_uvec * 1000 * std::pow(2, FRAME_RED_FAC), Cir_color_yel);
					cv::line(*frame_input, (*it).positions[0] * std::pow(2, FRAME_RED_FAC), (*it).positions[0] * std::pow(2, FRAME_RED_FAC) + (*it).naive_orientation * 1000 * std::pow(2, FRAME_RED_FAC), Cir_color_gre);
					waitLongerThanEver = true;
				}
			}
		}

		cv::imshow("Video", *frame_input);
		cv::waitKey(10);
		if (waitLongerThanEver)
			Sleep(1000);
	}
#ifdef WDD_DDL_DEBUG_FULL
	if (conf->frame_counter >= WDD_FBUFFER_SIZE - 1)
		printf("Frame# %llu\t DD_SIGNALS_NUMBER: %d\n", WaggleDanceDetector::WDD_SIGNAL_FRAME_NR, DotDetectorLayer::DD_SIGNALS_NUMBER);

	if (conf->frame_counter >= WDD_DDL_DEBUG_FULL_MAX_FRAME - 1)
	{
		std::cout << "************** WDD_DDL_DEBUG_FULL DONE! **************" << std::endl;
		printf("WDD_DDL_DEBUG_FULL captured %d frames.\n", WDD_DDL_DEBUG_FULL_MAX_FRAME);
		//capture.release();
		exit(0);
	}
#endif
}

cv::VideoWriter* openVideoOutputStream(cv::VideoCapture* inputStream, std::string outputVideoName) {
	cv::Size S = cv::Size((int)inputStream->get(cv::CAP_PROP_FRAME_WIDTH),    //Acquire input size
		(int)inputStream->get(cv::CAP_PROP_FRAME_HEIGHT));
	int ex = static_cast<int>(inputStream->get(cv::CAP_PROP_FOURCC));

	cv::VideoWriter outputVideo;
	outputVideo.open(outputVideoName, ex, inputStream->get(cv::CAP_PROP_FPS), S, true);

	return &outputVideo;
}

void runTestMode(std::string videoFilename, double aux_DD_MIN_POTENTIAL, int aux_WDD_SIGNAL_MIN_CLUSTER_SIZE, bool noGui)
{
	std::cout<<"************** Run started in test mode **************" << endl;
	if(!wdd::file::fileExists(videoFilename))
	{
		std::cerr<<"Error! Wrong video path!" << endl;
		exit(-201);
	}
	cout << "let's try to get the videoCapture" << endl;	
	cv::VideoCapture capture(videoFilename);
	cout << "videocapture received" << endl;
	
	cout << "open suceeded" << endl;
	double DD_MIN_POTENTIAL = aux_DD_MIN_POTENTIAL;

	int	WDD_SIGNAL_MIN_CLUSTER_SIZE = aux_WDD_SIGNAL_MIN_CLUSTER_SIZE;

	// prepare frame_counter
	unsigned long long frame_counter_global = 0;
	unsigned long long frame_counter_warmup = 0;
	cout << "get input parameters..." << endl;
	InputVideoParameters vp(&capture);
	int FRAME_WIDTH = vp.getFrameWidth();
	int FRAME_HEIGHT = vp.getFrameHeight();
	int FRAME_RATE = 25;
	cout << "width: " << FRAME_WIDTH << " and height: " << FRAME_HEIGHT << " at framerate: " << FRAME_RATE << endl;

	struct CamConf c;
	c.camId = wdd::camera::getNextUniqueCamID();
	strcpy_s(c.guid_str, "virtual-cam-config");
	c.arena[0] = cv::Point2i(0,0);
	c.arena[1] = cv::Point2i(320-1,0);
	c.arena[2] = cv::Point2i(320-1,240-1);
	c.arena[3] = cv::Point2i(0,240-1);
	// prepare videoFrameBuffer
	VideoFrameBuffer videoFrameBuffer(frame_counter_global, cv::Size(FRAME_WIDTH, FRAME_HEIGHT), cv::Size(20,20), c);

	cv::Mat frame_input;
	cv::Mat frame_input_monochrome;
	cv::Mat frame_target;
	if(!noGui)
		cv::namedWindow("Video");

	/* prepare frame_counter */
	unsigned long long frame_counter = 0;

	/* prepare buffer to hold mono chromized input frame */
	frame_input_monochrome =
		cv::Mat(FRAME_HEIGHT, FRAME_WIDTH, CV_8UC1);

	/* prepare buffer to hold target frame */
	double resize_factor =  pow(2.0, FRAME_RED_FAC);

	int frame_target_width = cvRound(FRAME_WIDTH/resize_factor);
	int frame_target_height = cvRound(FRAME_HEIGHT/resize_factor);

	std::cout<<"Printing WaggleDanceDetector frame parameter:"<<std::endl;
	printf("frame_height: %d\n", frame_target_height);
	printf("frame_width: %d\n", frame_target_width);
	printf("frame_rate: %d\n", FRAME_RATE);
	printf("frame_red_fac: %d\n", FRAME_RED_FAC);
	frame_target = cv::Mat(frame_target_height, frame_target_width, CV_8UC1);

	/*
	prepare DotDetectorLayer config vector
	*/
	std::vector<double> ddl_config;
	ddl_config.push_back(DD_FREQ_MIN);
	ddl_config.push_back(DD_FREQ_MAX);
	ddl_config.push_back(DD_FREQ_STEP);
	ddl_config.push_back(FRAME_RATE);
	ddl_config.push_back(FRAME_RED_FAC);
	ddl_config.push_back(DD_MIN_POTENTIAL);

	std::vector<cv::Point2i> dd_positions;
	for(int i = 0; i < frame_target_width; i++)
	{
		for(int j = 0; j < frame_target_height; j++)
		{
			// x (width), y(height)
			dd_positions.push_back(cv::Point2i(i,j));
		}
	}
	printf("Initialize with %d DotDetectors (DD_MIN_POTENTIAL=%.1f).\n", dd_positions.size(), DD_MIN_POTENTIAL);

	/*
	* prepare WaggleDanceDetector config vector
	*/
	std::vector<double> wdd_config;
	// Layer 2
	wdd_config.push_back(WDD_SIGNAL_DD_MAXDISTANCE);
	wdd_config.push_back(WDD_SIGNAL_MIN_CLUSTER_SIZE);
	// Layer 3
	wdd_config.push_back(WDD_DANCE_MAX_POSITION_DISTANCEE);
	wdd_config.push_back(WDD_DANCE_MAX_FRAME_GAP);
	wdd_config.push_back(WDD_DANCE_MIN_CONSFRAMES);

	WaggleDanceDetector wdd(
		dd_positions,
		&frame_target,
		ddl_config,
		wdd_config,
		&videoFrameBuffer,
		c,
		wdd_write_signal_file,
		wdd_write_dance_file,
		wdd_verbose
	);
	WddFrameAnalyseConfiguration frameAnalysisConfig(
		frame_input_monochrome, 
		frame_target, 
		&videoFrameBuffer, 
		frame_counter, 
		!noGui
	);

	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	std::vector<double> bench_res;

	//cv::VideoWriter outputVideo = *openVideoOutputStream(&capture, videoFilename + ".output.avi");

	cv::Size S = cv::Size((int)capture.get(cv::CAP_PROP_FRAME_WIDTH),    //Acquire input size
		(int)capture.get(cv::CAP_PROP_FRAME_HEIGHT));
	int ex = static_cast<int>(capture.get(cv::CAP_PROP_FOURCC));

	cv::VideoWriter outputVideo;
	outputVideo.open(videoFilename + ".output.avi", ex, capture.get(cv::CAP_PROP_FPS), S, true);

	while(capture.read(frame_input))
	{
		outputVideo << frame_input;
		analyseFrame(&wdd, &frame_input, &frameAnalysisConfig);

		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
		frameAnalysisConfig.frame_counter++;
		// benchmark output
		if ((frameAnalysisConfig.frame_counter % 100) == 0)
		{
			std::chrono::duration<double> sec = std::chrono::steady_clock::now() - start;

			cout<<"fps: " << 100 / sec.count() << "(" << cvRound(sec.count() * 1000) << "ms)" << std::endl;

			bench_res.push_back(100 / sec.count());

			start = std::chrono::steady_clock::now();
		}
	}

	outputVideo.release();
	capture.release();
}