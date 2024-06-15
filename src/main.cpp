#include "pinyin/word.hpp"
#include "search.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Window.H>
#include <format>
#include <iostream>
#include <string>

const std::array<DictionaryEntry, 2> entries{
	{{parseWord("pin1yin1"), "拼音"}, {parseWord("yin1yue4"), "音樂"}}};

int main() {
	Fl_Window *window = new Fl_Window(600, 480, "Chinese Dictionary");
	window->begin();

	// Results
	// Searchbar panel
	Fl_Input *searchBar = new Fl_Input(200, 0, 400, 80, "我\n叫\n東\n石");
	searchBar->box(FL_UP_BOX);
	searchBar->labelsize(18);
	searchBar->labelfont(FL_BOLD + FL_ITALIC);
	searchBar->labeltype(FL_SHADOW_LABEL);
	searchBar->textsize(36);

	// Definition
	Fl_Box *definitionPanel = new Fl_Box(200, 80, 400, 400, "我叫東石");
	definitionPanel->box(FL_UP_BOX);
	definitionPanel->labelsize(18);
	definitionPanel->labelfont(FL_BOLD + FL_ITALIC);
	definitionPanel->labeltype(FL_SHADOW_LABEL);

	// Fl_Button *btn =
	// 	new Fl_Button(200, 200, 100, 100, "Fuck around and find out");
	// btn->box(FL_UP_BOX);
	// btn->labelsize(18);
	// btn->labelfont(FL_BOLD + FL_ITALIC);
	// btn->labeltype(FL_SHADOW_LABEL);

	searchBar->when(FL_WHEN_CHANGED);
	searchBar->callback([](Fl_Widget *widget, void *b) {
		Fl_Input *input = (Fl_Input *)(widget);
		std::string_view query = input->value();
		std::span entries2 = entries;
		std::vector<SearchResult> results = searchInEntries(entries2, query);
		system("clear");

		for (auto result : results) {
			auto& entry = entries[result.entryIdx];
			std::cout << "- " << entry.string << ": " << entry.pinyin <<
		std::endl;
		}
	});

	window->end();
	window->show();
	return Fl::run();
}
