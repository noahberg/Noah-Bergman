#include "main_window.h"
#include <QApplication>

int main(int argc, char* argv[])
{
	if(argc < 2 || argc >3){
    std::cerr << "usage: ./search index_file...Please provide an index file" << std::endl;
    return 1;
  }
	QApplication app(argc, argv);

	MainWindow mainWindow;
	mainWindow.setIndexFile(std::string(argv[1]));
	mainWindow.initializeSearchEng();
	mainWindow.show();

	return app.exec();
}