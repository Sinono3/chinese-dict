#include "FL/Enumerations.H"
#include "pinyin/word.hpp"
#include "search.hpp"
#include "csv.hpp"
#include "pinyin/pretty.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Select_Browser.H>
#include <FL/Fl_Window.H>
#include <cmath>
#include <format>
#include <iostream>
#include <sstream>
#include <string>

std::vector<DictionaryEntry> entries{{}};

struct AppContext {
	Fl_Input *searchBar;
	Fl_Select_Browser *results;
	// Definitions
	Fl_Group *definitionPanel;
	Fl_Box *headword;
	Fl_Box *pronunciation;
	Fl_Box *definition;
};

void updateResults(AppContext* ctx) {
	std::string_view query = ctx->searchBar->value();
	std::vector<SearchResult> results = searchInEntries(entries, query);

	ctx->results->clear();
	for (auto result : results) {
		auto &entry = entries[result.entryIdx];
		int *data = new int(result.entryIdx);
		ctx->results->add(entry.characters.c_str(), (void *)data);
	}
}

void openInsertWindow(AppContext* ctx) {
	Fl_Window *newWindow = new Fl_Window(500, 500, "Add Dictionary Entry");

	newWindow->begin();

	Fl_Box *titlelabel = new Fl_Box(0, 50, 500, 30, "Add New Dictionary Entry");
	titlelabel->labelsize(20);
	titlelabel->labelfont(FL_BOLD);

	Fl_Input *insertChar = new Fl_Input(200, 120, 200, 80, "Character: ");
	insertChar->box(FL_UP_BOX);
	insertChar->labelsize(18);
	insertChar->labelfont(FL_BOLD + FL_ITALIC);
	insertChar->labeltype(FL_SHADOW_LABEL);
	insertChar->textsize(36);

	Fl_Input *insertPinyin = new Fl_Input(200, 220, 200, 80, "Pinyin: ");
	insertPinyin->box(FL_UP_BOX);
	insertPinyin->labelsize(18);
	insertPinyin->labelfont(FL_BOLD + FL_ITALIC);
	insertPinyin->labeltype(FL_SHADOW_LABEL);
	insertPinyin->textsize(36);

	Fl_Input *insertDef = new Fl_Input(200, 320, 200, 80, "Definition: ");
	insertDef->box(FL_UP_BOX);
	insertDef->labelsize(18);
	insertDef->labelfont(FL_BOLD + FL_ITALIC);
	insertDef->labeltype(FL_SHADOW_LABEL);
	insertDef->textsize(36);

	Fl_Box *errorChar = new Fl_Box(100, 200, 500, 20);
	errorChar->labelcolor(FL_RED);
	errorChar->labelsize(10);
	Fl_Box *errorPinyin = new Fl_Box(100, 300, 500, 20);
	errorPinyin->labelcolor(FL_RED);
	errorPinyin->labelsize(10);
	Fl_Box *errorDef = new Fl_Box(100, 400, 500, 20);
	errorDef->labelcolor(FL_RED);
	errorDef->labelsize(10);

	// Creating the 'accept' button
	Fl_Button *acceptButton = new Fl_Button(250, 450, 80, 40, "Accept");
	acceptButton->color(0x00ff0000);

	struct InsertEntryCtx {
		Fl_Window *insertWindow;
		Fl_Input *charInput, *pinyinInput, *defInput;
		Fl_Box *errorChar, *errorPinyin, *errorDef;
		AppContext *app;
	};

	InsertEntryCtx *args = new InsertEntryCtx{
		newWindow, insertChar,	insertPinyin, insertDef,
		errorChar, errorPinyin, errorDef, ctx};
	acceptButton->callback(
		[](Fl_Widget *widget, void *data) {
			InsertEntryCtx *args = (InsertEntryCtx *)data;

			args->insertWindow->begin();

			if (args->charInput->size() == 0 ||
				args->pinyinInput->size() == 0 || args->defInput->size() == 0) {
				args->errorChar->label((args->charInput->size() == 0) ? "This field is required." : "");
				args->errorPinyin->label((args->pinyinInput->size() == 0) ? "This field is required." : "");
				args->errorDef->label((args->defInput->size() == 0) ? "This field is required." : "");
				args->insertWindow->redraw();
			} else {
				std::string headword = args->charInput->value();
				std::string pinyin = args->pinyinInput->value();
				std::string definition = args->defInput->value();
				entries.push_back(DictionaryEntry(pinyin, headword, definition));

				// update results with new entry
				updateResults(args->app);
				// hide window
				args->insertWindow->hide();
			}

			args->insertWindow->end();
			
		},
		(void *)args);

	// Creating the 'cancel' button
	Fl_Button *cancelButton = new Fl_Button(150, 450, 80, 40, "Cancel");
	cancelButton->color(FL_RED);

	cancelButton->callback(
		[](Fl_Widget *widget, void *data) {
			InsertEntryCtx *args = (InsertEntryCtx *)data;
			args->insertWindow->hide();
		},
		args);

	newWindow->end();
	newWindow->show();
}

int main() {
	entries = loadFromCsv("dict.csv");

	// If empty, load test entries
	if (entries.empty()) {
		std::cout << "No csv file found, loading sample dictionary..." << std::endl;
		entries = loadFromCsv("sampleDict.csv");
	}

	Fl_Window *window = new Fl_Window(600, 480, "Chinese Dictionary");
	window->begin();

	// Definition
	Fl_Group *definitionPanel = new Fl_Group(200, 80, 400, 400);
	definitionPanel->begin();

	Fl_Box *headword = new Fl_Box(200, 80, 400, 100);
	headword->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP_LEFT);
	headword->labelsize(80);
	headword->labelfont(FL_BOLD);

	Fl_Box *pronunciation = new Fl_Box(200, 180, 400, 100);
	pronunciation->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP_LEFT);
	pronunciation->labelsize(30);
	pronunciation->labelfont(FL_BOLD);

	Fl_Box *definition = new Fl_Box(200, 280, 400, 200);
	definition->align(FL_ALIGN_INSIDE | FL_ALIGN_TOP_LEFT | FL_ALIGN_WRAP);
	definition->labelsize(20);
	definition->labelfont(FL_BOLD);

	definitionPanel->end();

	Fl_Select_Browser *results = new Fl_Select_Browser(0, 0, 200, 480);
	Fl_Input *searchBar = new Fl_Input(200, 0, 320, 80);
	searchBar->labelsize(18);
	searchBar->labelfont(FL_BOLD + FL_ITALIC);
	searchBar->labeltype(FL_SHADOW_LABEL);
	searchBar->textsize(36);
	searchBar->when(FL_WHEN_CHANGED);

	auto ctx = new AppContext { searchBar, results, definitionPanel, headword, pronunciation, definition };

	results->callback(
		[](Fl_Widget *widget, void *b) {
			auto results = (Fl_Select_Browser *)(widget);
			auto ctx = (AppContext *)b;

			int selected = results->value();
			// Selection defaults to 0 if no line is selected
			if (selected != 0) {
				int entryIdx = *((int *)results->data(selected));
				const DictionaryEntry &entry = entries[entryIdx];

				// Show definition
				std::stringstream pinyinStream;
				pinyinStream << (PrettyPinyinWord { entry.pinyin });
				auto pinyin = new std::string(pinyinStream.str());

				ctx->headword->label(entry.characters.c_str());
				ctx->pronunciation->label(pinyin->c_str());
				ctx->definition->label(entry.definition.c_str());
			} else {
				ctx->headword->label("");
				ctx->pronunciation->label("");
				ctx->definition->label("");
			}
		},
		ctx);
	searchBar->callback([] (auto widget, auto ctx) { updateResults((AppContext*)ctx); }, ctx);

	Fl_Button* addButton = new Fl_Button(520, 0, 80, 80, "Add");
	addButton->callback([] (auto widget, auto ctx) { openInsertWindow((AppContext*)ctx); }, ctx);

	// Initialize result list
	updateResults(ctx);

	window->end();
	window->show();

	if (Fl::run() == 0) {
		std::cout << "Saving dictionary..." << std::endl;
		saveToCsv("dict.csv", entries);
	}
}
