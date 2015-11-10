#include "lib/main_window.h"
#include <QApplication>

int main(int argc, char* argv[])
{
	if(argc >3){
    std::cerr << "usage: ./search config_file...Please provide only one file" << std::endl;
    return 1;
  	}
	QApplication app(argc, argv);

	MainWindow mainWindow;
	std::string blank;
	if(argc < 2)
		mainWindow.setConfigFile(blank);
	else
		mainWindow.setConfigFile(std::string(argv[1]));
	mainWindow.initializeSearchEng();
	mainWindow.show();

	return app.exec();
}