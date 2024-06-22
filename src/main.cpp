#include "pinyin/word.hpp"
#include "search.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Select_Browser.H>
#include <format>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

const std::array<DictionaryEntry, 2> entries{{
	// {parseWord("pin1yin1"), "拼音", "A writing system for Chinese pronunciation", {}},
	// {parseWord("yin1yue4"), "音樂", "Music", {}},
	DictionaryEntry("pin1yin1", "拼音", "A writing system for Chinese pronunciation"),
	DictionaryEntry("yin1yue4", "音樂", "Music"),
}};

int main() {
	Fl_Window *window = new Fl_Window(600, 480, "Chinese Dictionary");
	window->begin();

	// Searchbar panel
	Fl_Input *searchBar = new Fl_Input(200, 0, 400, 80);
	searchBar->box(FL_UP_BOX);
	searchBar->labelsize(18);
	searchBar->labelfont(FL_BOLD + FL_ITALIC);
	searchBar->labeltype(FL_SHADOW_LABEL);
	searchBar->textsize(36);

	// Definition
	Fl_Box *definitionPanel = new Fl_Box(200, 80, 400, 400);
	// definitionPanel->box(FL_UP_BOX);
	definitionPanel->labelsize(18);
	definitionPanel->labelfont(FL_BOLD + FL_ITALIC);
	// definitionPanel->labeltype(FL_SHADOW_LABEL);

	// Fl_Button *btn =
	// 	new Fl_Button(200, 200, 100, 100, "Fuck around and find out");
	// btn->box(FL_UP_BOX);
	// btn->labelsize(18);
	// btn->labelfont(FL_BOLD + FL_ITALIC);
	// btn->labeltype(FL_SHADOW_LABEL);

	Fl_Select_Browser *results = new Fl_Select_Browser(0, 0, 200, 480);
	// definitionPanel->box(FL_UP_BOX);
	// definitionPanel->labeltype(FL_SHADOW_LABEL);
	results->labelsize(18);
	results->labelfont(FL_BOLD + FL_ITALIC);
	results->callback([](Fl_Widget *widget, void *b) {
		Fl_Select_Browser *results = (Fl_Select_Browser *)(widget);
		auto definitionPanel = (Fl_Box*)b;

		int selected = results->selected(0);
		std::cout << selected << std::endl;
		std::cout << results->data(selected) << std::endl;

		// Set definition panel
		const DictionaryEntry& entry = entries[foundEntry.value()];
		std::stringstream ss;
		ss << entry.characters << "\n" << entry.definition;
		auto s = new std::string(ss.str());
		ctx->definitionPanel->label(s->c_str());
	    
	}, definitionPanel);

	struct SearchBarCallbackCtx {
		Fl_Box* definitionPanel;
		Fl_Select_Browser* results;
	};

	auto ctx = new SearchBarCallbackCtx { definitionPanel, results };

	searchBar->when(FL_WHEN_CHANGED);
	searchBar->callback([](Fl_Widget *widget, void *b) {
		Fl_Input *input = (Fl_Input *)(widget);
		auto ctx = (SearchBarCallbackCtx*)b;

		std::string_view query = input->value();
		std::span entries2 = entries;
		std::vector<SearchResult> results = searchInEntries(entries2, query);

		auto queryPinyin = parseWord(query);
		std::optional<int> foundEntry;

		for (int entryIdx = 0; entryIdx < entries.size(); entryIdx++) {
			const DictionaryEntry& entry = entries[entryIdx];
			auto found = true;

			if (entry.pinyin.size() != queryPinyin.size()) {
				continue;
			}

			for (int i = 0; i < entry.pinyin.size(); i++) {
				if (entry.pinyin[i] != queryPinyin[i]) {
					found = false;
					break;
				}
			}

			if (found) {
				foundEntry = entryIdx;
				break;
			}
		}

		if (foundEntry.has_value()) {
			const DictionaryEntry& entry = entries[foundEntry.value()];
			std::stringstream ss;
			ss << entry.characters << "\n" << entry.definition;
			auto s = new std::string(ss.str());
			ctx->definitionPanel->label(s->c_str());
		}

		ctx->results->clear();

		for (auto result : results) { 
			auto& entry = entries[result.entryIdx];
			// auto res* = new  "- " << entry.characters << ": " << entry.pinyin << std::endl;
			ctx->results->add(entry.characters.c_str(), );
		}
	}, ctx);

	

	window->end();
	window->show();
	return Fl::run();
}
