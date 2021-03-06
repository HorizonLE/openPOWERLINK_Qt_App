openPOWERLINK QT MN GUI
===================

[TOC]

An QT based advanced application which implements an openPOWERLINK MN using the 
Oplk_QT_wrapper library.

# Features {#sect_features}
 - Monitor the status of the nodes available in the network.
 - Send NMT commands to local and remote nodes.
 - Visualize the process-image data as variables and memory views.
 - Avoids the possibility of recompiling the application by using the xap.xml
 - Written with modular cross-platform C++ techniques.
 - Uses QT 5 libraries which creates stunning UIs and powerful native applications.
 - Uses CMake build system, an powerful cross-platform build system.

# Package dependencies to compile {#sect_dependencies}
## openPOWERLINK stack v2.x {#sect_dependencies_oplk}
An open-source [POWERLINK][2] protocol stack.

* Get the openPOWERLINK stack from [github][7].


## CMake {#sect_dependencies_cmake}
 * For building the library [CMake][5] is used. 
 * A CMake version 2.8.11 or higher is required!

	### Out-of-Source Builds {#sect_dependencies_cmake_build}
	 * CMake supports out-of-source builds. Therefore, all generated files are 
	   located in a separate build directory. This keeps your sources clean.

## Compiler {#sect_dependencies_compiler}
 * Windows: Microsoft visual C++ 2010 or higher
 * Linux: G++ v4.6.3 or higher

## Qt 5 framework {#sect_dependencies_qt}
[Qt][3] is a cross-platform application and UI framework for developers using C++.
The Qt framework can be downloaded from [here][4]. Download the installer 
specific to your platform.

 * Windows: Download and install Qt 5.2.x for Windows
 * Linux: Download and install Qt 5.2.x for Linux


# Build the GUI {#sect_build}

## Build the openPOWERLINK stack {#sect_build_oplk}
Please refer to "Building openPOWERLINK" section from [openPOWERLINK doc site][6]
to build the stack libraries.

## Build the openPOWERLINK QT API wrapper library {#sect_build_oplkqtwrap}

Please refer to `doc/plk_qt_api/Readme.md` to build the wrapper library. 

### Compilation (any platform) using `cmake-gui` {#sect_build_oplkqtwrap_cmake}
 - Set the source path to apps/plk_qt_mn_gui
 - Set the build path to apps/plk_qt_mn_gui/build/<platform-specific>
 - Click configure
	- The configuration will fail for the first time. 
	- Set the openPOWERLINK stack root path to `CONFIG_openPOWERLINK_ROOT_DIR` of CMake configuration.
		- Eg: `CONFIG_openPOWERLINK_ROOT_DIR` = D:/openPOWERLINK_V2/
	- If QT installation path is not found; set the QT install path `CONFIG_QT_INSTALL_PATH` of CMake configuration.
		- Eg: `CONFIG_QT_INSTALL_PATH` = C:/Qt/Qt5.2.1/5.2.1/msvc2010
	- Click configure to activate the changes.
- Choose the type of stack libraries from `CONFIG_openPOWERLINK_BUILD_TYPE`
	- windows
		- Link to application
	- Linux
		- Link to application
		- Link to user interface
		- Link to kernel stack daemon
- Click configure to activate the changes.
- The CMake scripts will find the openPOWERLINK and wrapper libraries.
- Follow platform specific documentation below.

#### Linux {#sect_build_oplkqtwrap_cmake_linux}
- Finally click generate button to generate the Makefiles. 
  (On Linux, CMake generates Makefiles by default).
- Go the chosen build path from the command prompt.

		` cd apps/plk_qt_mn_gui/build/<platform-specific> `
- Create the application using the command.

		`make clean && make install`
- The binaries with all dependencies will be available in 
  `bin/plk_qt_mn_gui/<platform>/<OPLK_STACK_CFG>`
- The user can generate the debug versions by changing the 
  `CMAKE_BUILD_TYPE[TODO check]` to "Debug".
- The debug version of the applications are are built with "_d" at the end of the names.

#### Windows {#sect_build_oplkqtwrap_win}
- Finally click generate to generate the Visual C++ project files.
- Go the chosen build path.
- Open the `oplkmn_qt_gui.sln` with Visual C++
- Build the INSTALL project to generate the executable.
- The binaries with all dependencies will be available in 
  `bin/plk_qt_mn_gui/<platform>/<OPLK_STACK_CFG>`
- The name of the libraries depends on for which stack it is built for.
  Refer to `CONFIG_openPOWERLINK_BUILD_TYPE`
- You can switch between debug and release builds easily from the Visual C++ 
  solution configurations.
- The debug libraries are built with "_d" at the end of the library name.


# Runtime dependencies {#sect_runtimedep}
The library is dependent on the openPOWERLINK 2.x and QT 5.2.x libraries. 
Here are the list of dependent libraries.

## Windows {#sect_runtimedep_win}
 - oplkmn-*(depends on chosen stack configuration chosen)* present in stack/libs/*
 - oplkqtwrap-*(depends on chosen stack configuration chosen)* present in stack/libs/*
 - wpcap.dll - PCAP library
 - Qt5Core.dll
 - Qt5Xml.dll
 - Qt5Widgets.dll
 - Qt5Gui.dll
 - icudt51.dll
 - icuin51.dll
 - icuuc51.dll
 - libEGL.dll
 - libGLESv2.dll
 - qwindows.dll - should be present in platforms/

## Linux {#sect_runtimedep_linux}
 - libpcap - PCAP library (only for selected configurations of openPOWERLINK stack)
 - Qt5Core.so
 - Qt5Xml.so
 - Qt5Widgets.so
 - Qt5Gui.so
 - icudt51.so
 - icuin51.so
 - icuuc51.so


# How to run {#sect_run}

## What all you need run the application? {#sect_run_needs}
### Hardware {#sect_run_needs_hardware}
 - An openPOWERLINK supported network interface cards
 - An openPOWERLINK supported Controlled Node
### Software {#sect_run_needs_software}
 - CDC and Xap.xml generated by [openCONFIGURATOR](1) 

## Execute {#sect_run_needs_execute}
 - Go to `bin/plk_qt_mn_gui/<platform>/<OPLK_STACK_CFG>`
 - Run the plk_qt_mn_gui (use sudo in Linux)
 - Choose the CDC and Xap.xml files by clicking on the Choose CDC menu
 - Select the network interface by clicking on the Select network interface menu
 - Click on the Run menu to start the openPOWERLINK stack.


[1]: http://sourceforge.net/projects/openconf/
[2]: http://sourceforge.net/projects/openpowerlink/
[3]: http://qt-project.org
[4]: http://download.qt-project.org/official_releases/qt/5.2
[5]: http://www.cmake.org
[6]: http://openpowerlink.sourceforge.net
[7]: https://github.com/Ramakrishnan45/openPOWERLINK_v2.0_QT