#include "main_window.h"
#include "merg.h"
#include <sstream>

using namespace std;

struct NameComp {

	bool operator()(WebPage* lhs, WebPage* rhs) {
		return lhs->filename() < rhs->filename();
	}
};

struct OutComp {

	bool operator()(WebPage* lhs, WebPage* rhs) {
		return lhs->outgoing_links().size() > rhs->outgoing_links().size();
	}
};

struct InComp {

	bool operator()(WebPage* lhs, WebPage* rhs) {
		return lhs->incoming_links().size() > rhs->incoming_links().size();
	}
};

MainWindow::MainWindow() {
	SearchEng e;
	engine = e;
	setWindowTitle("Search Engine");


	// Overall Layout
	overallLayout = new QHBoxLayout();




	// Search Terms display
	searchLayout = new QVBoxLayout();
	overallLayout->addLayout(searchLayout);
	searchTermsLabel = new QLabel("Search Term(s)");
	searchLayout->addWidget(searchTermsLabel);


	
	searchTextButton = new QHBoxLayout();
	searchLayout->addLayout(searchTextButton);
	searchTermsInput = new QLineEdit();
	searchTextButton->addWidget(searchTermsInput);
	searchButton = new QPushButton("Search");
	connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
	connect(searchTermsInput, SIGNAL(returnPressed()), this, SLOT(search()));
	searchTextButton->addWidget(searchButton);

	radioSearch = new QGroupBox();
	radioButtonsSearch = new QHBoxLayout();
	searchLayout->addWidget(radioSearch);
	andButton = new QRadioButton("AND");
	orButton = new QRadioButton("OR");
	singleButton = new QRadioButton("Single Term"); 
	singleButton->setChecked(true);
	radioButtonsSearch->addWidget(orButton);
	radioButtonsSearch->addWidget(andButton);
	radioButtonsSearch->addWidget(singleButton);
	radioSearch->setLayout(radioButtonsSearch);

	quitButton = new QPushButton("QUIT");
	connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
	searchLayout->addWidget(quitButton);

	searchLayout->addStretch();


	// Results and file list display
	fileLayout = new QVBoxLayout();
	overallLayout->addLayout(fileLayout);

	resultsLabel = new QLabel("Results");
	fileLayout->addWidget(resultsLabel);

	fileListWidget = new QListWidget();
	fileLayout->addWidget(fileListWidget);

	showFileButton = new QPushButton("Show File");
	connect(showFileButton, SIGNAL(clicked()), this, SLOT(showFile()));
	fileLayout->addWidget(showFileButton);

	sortByLabel = new QLabel("Sort By:");
	fileLayout->addWidget(sortByLabel);

	radioFile = new QGroupBox();
	radioButtonsFile = new QHBoxLayout();
	fileLayout->addWidget(radioFile);

	nameButton = new QRadioButton("File Name");
	nameButton->setChecked(true);
	outgoingButton = new QRadioButton("Number of Outgoing Links");
	incomingButton = new QRadioButton("Number of Incoming Links");
	radioButtonsFile->addWidget(nameButton);
	radioButtonsFile->addWidget(incomingButton);
	radioButtonsFile->addWidget(outgoingButton);
	connect(nameButton, SIGNAL(clicked()), this, SLOT(sortByName()));
	connect(outgoingButton, SIGNAL(clicked()), this, SLOT(sortByOut()));
	connect(incomingButton, SIGNAL(clicked()), this, SLOT(sortByIn()));
	radioFile->setLayout(radioButtonsFile);

	// Results window;
	otherWin = new QWidget;
	otherWin->hide();
	displayLayout = new QVBoxLayout();

	filenameLabel = new QLabel("");
	displayLayout->addWidget(filenameLabel);

	fileContentLabel = new QTextEdit("");
	fileContentLabel->setReadOnly(true);
	displayLayout->addWidget(fileContentLabel);


	linkLayout = new QHBoxLayout();
	displayLayout->addLayout(linkLayout);

	incomingLayout = new QVBoxLayout();
	linkLayout->addLayout(incomingLayout);
	incomingLabel = new QLabel("Incoming Links");
	incomingLayout->addWidget(incomingLabel);
	incomingList = new QListWidget();
	incomingLayout->addWidget(incomingList);
	updateButtonIn = new QPushButton("Update to Selected File");
	connect(updateButtonIn, SIGNAL(clicked()), this, SLOT(updateFileIn()));
	incomingLayout->addWidget(updateButtonIn);

	outgoingLayout = new QVBoxLayout();
	linkLayout->addLayout(outgoingLayout);
	outgoingLabel = new QLabel("Outgoing Links");
	outgoingLayout->addWidget(outgoingLabel);
	outgoingList = new QListWidget();
	outgoingLayout->addWidget(outgoingList);
	updateButtonOut = new QPushButton("Update to Selected File");
	connect(updateButtonOut, SIGNAL(clicked()), this, SLOT(updateFileOut()));
	outgoingLayout->addWidget(updateButtonOut);

	sortLinksByLabel = new QLabel("Sort By:");
	displayLayout->addWidget(sortLinksByLabel);

	radioDisplay = new QGroupBox();
	radioButtonsDisplay = new QHBoxLayout();
	displayLayout->addWidget(radioDisplay);
	nameDisplayButton = new QRadioButton("File Name");
	connect(nameDisplayButton, SIGNAL(clicked()), this, SLOT(sortByNameDisplay()));
	nameDisplayButton->setChecked(true);
	outgoingDisplayButton = new QRadioButton("Number of Outgoing Links");
	connect(outgoingDisplayButton, SIGNAL(clicked()), this, SLOT(sortByOutDisplay()));
	incomingDisplayButton = new QRadioButton("Number of Incoming Links");
	connect(incomingDisplayButton, SIGNAL(clicked()), this, SLOT(sortByInDisplay()));
	radioButtonsDisplay->addWidget(nameDisplayButton);
	radioButtonsDisplay->addWidget(outgoingDisplayButton);
	radioButtonsDisplay->addWidget(incomingDisplayButton);
	radioDisplay->setLayout(radioButtonsDisplay);




	closeButton = new QPushButton("Close");
	connect(closeButton, SIGNAL(clicked()), this, SLOT(hideFile()));
	displayLayout->addWidget(closeButton);
	otherWin->setLayout(displayLayout);





	setLayout(overallLayout);




}


MainWindow::~MainWindow() {


}

void MainWindow::showFile() {
	int fileIndex = fileListWidget->currentRow();
	filenameLabel->setText(QString::fromStdString(resultsVector[fileIndex]->filename()));
	stringstream contents;
	contents << *resultsVector[fileIndex];
	fileContentLabel->clear();
	fileContentLabel->append(QString::fromStdString((contents.str())));

	MySetWebPage incoming;
	incoming = resultsVector[fileIndex]->incoming_links();
	incoming_links.clear();
	for(set<WebPage*>::iterator it = incoming.begin(); it != incoming.end(); ++it) {
		incoming_links.push_back(*it);
	}
	if(nameDisplayButton->isChecked()) {
		NameComp a;
		mergeSort(incoming_links, a);
	}
	else if(outgoingDisplayButton->isChecked()) {
		OutComp a;
		mergeSort(incoming_links, a);
	}
	else if(incomingDisplayButton->isChecked()) {
		InComp a;
		mergeSort(incoming_links, a);
	}

	incomingList->clear();
	for(unsigned int i = 0; i < incoming_links.size(); i++) {
		string current = incoming_links[i]->filename();
		incomingList->addItem(QString::fromStdString(current));
	}

	MySetWebPage outgoing;
	outgoing = resultsVector[fileIndex]->outgoing_links();
	outgoing_links.clear();
	for(set<WebPage*>::iterator it = outgoing.begin(); it != outgoing.end(); ++it) {
		outgoing_links.push_back(*it);
	}
	if(nameDisplayButton->isChecked()) {
		NameComp a;
		mergeSort(outgoing_links, a);
	}
	else if(outgoingDisplayButton->isChecked()) {
		OutComp a;
		mergeSort(outgoing_links, a);
	}
	else if(incomingDisplayButton->isChecked()) {
		InComp a;
		mergeSort(outgoing_links, a);
	}
	outgoingList->clear();
	for(unsigned int i = 0; i < outgoing_links.size(); i++) {
		string current = outgoing_links[i]->filename();
		outgoingList->addItem(QString::fromStdString(current));
	}



	otherWin->show();
}

void MainWindow::updateFileIn() {
	int fileIndex = incomingList->currentRow();
	WebPage* selected = incoming_links[fileIndex];
	filenameLabel->setText(QString::fromStdString(selected->filename()));
	stringstream contents;
	contents << *selected;
	fileContentLabel->clear();
	fileContentLabel->append(QString::fromStdString((contents.str())));

	MySetWebPage incoming;
	incoming = selected->incoming_links();
	incoming_links.clear();
	for(set<WebPage*>::iterator it = incoming.begin(); it != incoming.end(); ++it) {
		incoming_links.push_back(*it);
	}
	if(nameDisplayButton->isChecked()) {
		NameComp a;
		mergeSort(incoming_links, a);
	}
	else if(outgoingDisplayButton->isChecked()) {
		OutComp a;
		mergeSort(incoming_links, a);
	}
	else if(incomingDisplayButton->isChecked()) {
		InComp a;
		mergeSort(incoming_links, a);
	}

	incomingList->clear();
	for(unsigned int i = 0; i < incoming_links.size(); i++) {
		string current = incoming_links[i]->filename();
		incomingList->addItem(QString::fromStdString(current));
	}

	MySetWebPage outgoing;
	outgoing = selected->outgoing_links();
	outgoing_links.clear();
	for(set<WebPage*>::iterator it = outgoing.begin(); it != outgoing.end(); ++it) {
		outgoing_links.push_back(*it);
	}
	if(nameDisplayButton->isChecked()) {
		NameComp a;
		mergeSort(outgoing_links, a);
	}
	else if(outgoingDisplayButton->isChecked()) {
		OutComp a;
		mergeSort(outgoing_links, a);
	}
	else if(incomingDisplayButton->isChecked()) {
		InComp a;
		mergeSort(outgoing_links, a);
	}
	outgoingList->clear();
	for(unsigned int i = 0; i < outgoing_links.size(); i++) {
		string current = outgoing_links[i]->filename();
		outgoingList->addItem(QString::fromStdString(current));
	}
}

void MainWindow::updateFileOut() {
	int fileIndex = outgoingList->currentRow();
	WebPage* selected = outgoing_links[fileIndex];
	filenameLabel->setText(QString::fromStdString(selected->filename()));
	stringstream contents;
	contents << *selected;
	fileContentLabel->clear();
	fileContentLabel->append(QString::fromStdString((contents.str())));

	MySetWebPage incoming;
	incoming = selected->incoming_links();
	incoming_links.clear();
	for(set<WebPage*>::iterator it = incoming.begin(); it != incoming.end(); ++it) {
		incoming_links.push_back(*it);
	}
	if(nameDisplayButton->isChecked()) {
		NameComp a;
		mergeSort(incoming_links, a);
	}
	else if(outgoingDisplayButton->isChecked()) {
		OutComp a;
		mergeSort(incoming_links, a);
	}
	else if(incomingDisplayButton->isChecked()) {
		InComp a;
		mergeSort(incoming_links, a);
	}

	incomingList->clear();
	for(unsigned int i = 0; i < incoming_links.size(); i++) {
		string current = incoming_links[i]->filename();
		incomingList->addItem(QString::fromStdString(current));
	}

	MySetWebPage outgoing;
	outgoing = selected->outgoing_links();
	outgoing_links.clear();
	for(set<WebPage*>::iterator it = outgoing.begin(); it != outgoing.end(); ++it) {
		outgoing_links.push_back(*it);
	}
	if(nameDisplayButton->isChecked()) {
		NameComp a;
		mergeSort(outgoing_links, a);
	}
	else if(outgoingDisplayButton->isChecked()) {
		OutComp a;
		mergeSort(outgoing_links, a);
	}
	else if(incomingDisplayButton->isChecked()) {
		InComp a;
		mergeSort(outgoing_links, a);
	}
	outgoingList->clear();
	for(unsigned int i = 0; i < outgoing_links.size(); i++) {
		string current = outgoing_links[i]->filename();
		outgoingList->addItem(QString::fromStdString(current));
	}
}

void MainWindow::sortByOutDisplay() {
	OutComp a;
	mergeSort(outgoing_links, a);
	mergeSort(incoming_links, a);

	outgoingList->clear();
	for(unsigned int i = 0; i < outgoing_links.size(); i++) {
		string current = outgoing_links[i]->filename();
		outgoingList->addItem(QString::fromStdString(current));
	}

	incomingList->clear();
	for(unsigned int i = 0; i < incoming_links.size(); i++) {
		string current = incoming_links[i]->filename();
		incomingList->addItem(QString::fromStdString(current));
	}


}

void MainWindow::sortByInDisplay() {
	InComp a;
	mergeSort(outgoing_links, a);
	mergeSort(incoming_links, a);

	outgoingList->clear();
	for(unsigned int i = 0; i < outgoing_links.size(); i++) {
		string current = outgoing_links[i]->filename();
		outgoingList->addItem(QString::fromStdString(current));
	}

	incomingList->clear();
	for(unsigned int i = 0; i < incoming_links.size(); i++) {
		string current = incoming_links[i]->filename();
		incomingList->addItem(QString::fromStdString(current));
	}


}


void MainWindow::sortByNameDisplay() {
	NameComp a;
	mergeSort(outgoing_links, a);
	mergeSort(incoming_links, a);

	outgoingList->clear();
	for(unsigned int i = 0; i < outgoing_links.size(); i++) {
		string current = outgoing_links[i]->filename();
		outgoingList->addItem(QString::fromStdString(current));
	}

	incomingList->clear();
	for(unsigned int i = 0; i < incoming_links.size(); i++) {
		string current = incoming_links[i]->filename();
		incomingList->addItem(QString::fromStdString(current));
	}


}



void MainWindow::hideFile() {
	otherWin->hide();
}

vector<string> MainWindow::process_query(string query) {
	vector<string> queries;
	string current;
	for(unsigned int i = 0; i<query.length(); ++i) {
		if(query[i] == ' ' || query[i] == '\t' || query[i] == '\v') {
			if(!current.empty()) {
				queries.push_back(current);
				current.clear();
			}

		}
		else
			current += query[i];

	}
	if(!current.empty()) {
		queries.push_back(current);
	}

	return queries;
}

void MainWindow::setIndexFile(string index) {
	indexFile = index;
}

void MainWindow::initializeSearchEng() {
	PageParserMarkdown p;
	PageParser* parser = &p;
	engine.add_parse_from_index_file(indexFile, parser);
	index = engine.get_index();
	engine.link_pages();
}

void MainWindow::sortByOut() {
	if(fileListWidget->count() == 0)
		return;
	fileListWidget->clear();
	OutComp a;
	mergeSort(resultsVector, a);
	for(unsigned int i = 0; i < resultsVector.size(); i++) {
		stringstream display;
		display << resultsVector[i]->filename();
		display << ",	 number incoming links: ";
		display << resultsVector[i]->incoming_links().size();
		display << ", number outgoing links: ";
		display << resultsVector[i]->outgoing_links().size();
		fileListWidget->addItem(QString::fromStdString(display.str()));
	}
	fileListWidget->setCurrentRow(0);

}

void MainWindow::sortByIn() {
	if(fileListWidget->count() == 0)
		return;
	fileListWidget->clear();
	InComp a;
	mergeSort(resultsVector, a);
	for(unsigned int i = 0; i < resultsVector.size(); i++) {
		stringstream display;
		display << resultsVector[i]->filename();
		display << ",	 number incoming links: ";
		display << resultsVector[i]->incoming_links().size();
		display << ", number outgoing links: ";
		display << resultsVector[i]->outgoing_links().size();
		fileListWidget->addItem(QString::fromStdString(display.str()));
	}
	fileListWidget->setCurrentRow(0);

}

void MainWindow::sortByName() {
	if(fileListWidget->count() == 0)
		return;
	fileListWidget->clear();
	NameComp a;
	mergeSort(resultsVector, a);
	for(unsigned int i = 0; i < resultsVector.size(); i++) {
		stringstream display;
		display << resultsVector[i]->filename();
		display << ",	 number incoming links: ";
		display << resultsVector[i]->incoming_links().size();
		display << ", number outgoing links: ";
		display << resultsVector[i]->outgoing_links().size();
		fileListWidget->addItem(QString::fromStdString(display.str()));
	}
	fileListWidget->setCurrentRow(0);

}

void MainWindow::search() {
	if(searchTermsInput->text().isEmpty())
		return;

	string query = searchTermsInput->text().toStdString();
	vector<string> queries = process_query(query);
	MySetWebPage results;
	if(singleButton->isChecked()) {
		engine.search(query, &results);

	}
	else if(andButton->isChecked()) {
		engine.search(queries, true, &results);
	}
	else if(orButton->isChecked()) {
		engine.search(queries, false, &results);
	}

	fileListWidget->clear();

	resultsVector.clear();
	for(set<WebPage*>::iterator it = results.begin(); it != results.end(); ++it) {
		resultsVector.push_back(*it);
	}
	if(nameButton->isChecked()) {
		NameComp a;
		mergeSort(resultsVector, a);
	}
	else if(outgoingButton->isChecked()) {
		OutComp a;
		mergeSort(resultsVector, a);
	}
	else if(incomingButton->isChecked()) {
		InComp a;
		mergeSort(resultsVector, a);
	}

	for(unsigned int i = 0; i < resultsVector.size(); i++) {
		stringstream display;
		display << resultsVector[i]->filename();
		display << ",	 number incoming links: ";
		display << resultsVector[i]->incoming_links().size();
		display << ", number outgoing links: ";
		display << resultsVector[i]->outgoing_links().size();
		fileListWidget->addItem(QString::fromStdString(display.str()));
	}

	fileListWidget->setCurrentRow(0);


	searchTermsInput->setText("");


}

