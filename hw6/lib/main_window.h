#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QRadioButton>
#include <QGroupBox>
#include <QTextEdit>

#include <string> 
#include <vector>
#include <map>

#include "webpage.h"
#include "searcheng.h"


class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();
	void setConfigFile(std::string config);
	std::vector<std::string> process_query(std::string query);
	void initializeSearchEng();


private slots:
	void search();
	void sortByIn();
	void sortByOut();
	void sortByName();
	void sortByRank();
	void showFile();
	void hideFile();
	void sortByOutDisplay();
	void sortByInDisplay();
	void sortByNameDisplay();
	void updateFileIn();
	void updateFileOut();

private:
	
	QWidget* otherWin;

	// Layouts for search
	QHBoxLayout* overallLayout;
	QVBoxLayout* searchLayout;
	QHBoxLayout* searchTextButton;
	QHBoxLayout* radioButtonsSearch;
	QGroupBox* radioSearch;
	QVBoxLayout* fileLayout;
	QGroupBox* radioFile;
	QHBoxLayout* radioButtonsFile;


	// Layouts for file display
	QVBoxLayout* displayLayout;
	QHBoxLayout* linkLayout;
	QVBoxLayout* incomingLayout;
	QVBoxLayout* outgoingLayout;
	QGroupBox* radioDisplay;
	QHBoxLayout* radioButtonsDisplay;

	// display widgets
	QLabel* filenameLabel;
	QTextEdit* fileContentLabel;
	QListWidget* outgoingList;
	QLabel* outgoingLabel;
	QListWidget* incomingList;
	QLabel* incomingLabel;
	QPushButton* closeButton;
	QLabel* sortLinksByLabel;
	QRadioButton* nameDisplayButton;
	QRadioButton* incomingDisplayButton;
	QRadioButton* outgoingDisplayButton;
	QPushButton* updateButtonIn;
	QPushButton* updateButtonOut;



	// Search Widgets
	QLabel* searchTermsLabel;
	QLineEdit* searchTermsInput;
	QPushButton* searchButton;
	QRadioButton* andButton;
	QRadioButton* orButton;
	QRadioButton* singleButton;
	QPushButton* quitButton;

	// File Widgets
	QLabel* resultsLabel;
	QListWidget* fileListWidget;
	QPushButton* showFileButton;
	QLabel* sortByLabel;
	QRadioButton* nameButton;
	QRadioButton* outgoingButton;
	QRadioButton* incomingButton;
	QRadioButton* rankButton;


	// data
	SearchEng engine;
	std::string configFile;
	std::map<std::string, WebPage*> index;
	std::vector<WebPage*> resultsVector;
	std::vector<WebPage*> outgoing_links;
	std::vector<WebPage*> incoming_links;


};