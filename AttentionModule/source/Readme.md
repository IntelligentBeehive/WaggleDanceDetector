========================================================================
	CONSOLE APPLICATION : WaggleDanceDetector Project Overview
========================================================================
# REQUIREMENTS
* Visual studio vs2017 or vs2019 with target framework 2017
* camera SDK (https://www.vision-camera.nl/Downloads)
* Opencv 4.1.2 installed and added to the environment variables
	* OPENCV_DIR = D:\lib\opencv\opencv
	* And add D:\lib\opencv\build\x64\vc15\bin to the PATH
	* Restart pc/shell session

# RUNNING
To run the software, you can call it from the commandline or debug it from visual studio.

To debug it, you need to supply it with a few commandline arguments. To do this, go to project options -> debugging and add the following arguments:
-t "C:\Users\leben\OneDrive\School\s4\OI\intelligentbeehive\data\vids\grayscale waggledance.mp4" -o result.txt
with any values that you wish.