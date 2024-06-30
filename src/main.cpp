#include "FL/Enumerations.H"
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

const std::array<DictionaryEntry, 21> entries{{
	DictionaryEntry("pin1yin1", "拼音", "A writing system for Chinese pronunciation"),
	DictionaryEntry("yin1yue4", "音樂", "Music"),
	DictionaryEntry("ni3hao3", "你好", "Hello!"),
	DictionaryEntry("ni3hao3ma0", "你好嗎", "How are you?"),
	DictionaryEntry("xi3huan1", "喜歡", "To like"),
	DictionaryEntry("lai2", "來", "To come"),
	DictionaryEntry("qu4", "去", "To go"),
	DictionaryEntry("chi1", "吃", "To eat"),
	DictionaryEntry("dou4fu3", "豆腐", "Tofu"),
	DictionaryEntry("wo3", "我", "I"),
	DictionaryEntry("ni3", "你", "You (male)"),
	DictionaryEntry("ta1", "他", "He"),
	DictionaryEntry("ni3", "妳", "You (female)"),
	DictionaryEntry("ta1", "她", "She"),
	DictionaryEntry("nin2", "您", "You (courteous)"),
	DictionaryEntry("shu1", "書", "Book"),
	DictionaryEntry("kan4shu1", "看書", "Read"),
	DictionaryEntry("dian4ying3", "電影", "Film/Movie"),
	DictionaryEntry("wang3qiu2", "網球", "Tennis"),
	DictionaryEntry("bang4qiu2", "棒球", "Baseball"),
	DictionaryEntry("lan2qiu2", "籃球", "Basketball")
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

	struct DefinitionPanel {
		Fl_Group* definitionPanel;
		Fl_Box* headword;
		Fl_Box* pronunciation;
		Fl_Box* definition;
	};

	DefinitionPanel *defPanel = new DefinitionPanel { definitionPanel, headword, pronunciation, definition };

	Fl_Select_Browser *results = new Fl_Select_Browser(0, 0, 200, 480);
	results->callback([](Fl_Widget *widget, void *b) {
		auto results = (Fl_Select_Browser *)(widget);
		auto defPanel = (DefinitionPanel*)b;

		int selected = results->value();
		// Selection defaults to 0 if no line is selectedj
		if (selected != 0) {
			int entryIdx = *((int*)results->data(selected));
			const DictionaryEntry& entry = entries[entryIdx];

			// Show definition
			std::stringstream pinyinStream;
			pinyinStream << entry.pinyin;
			auto pinyin = new std::string(pinyinStream.str());

			defPanel->headword->label(entry.characters.c_str());
			defPanel->pronunciation->label(pinyin->c_str());
			defPanel->definition->label(entry.definition.c_str());
		} else {
			defPanel->headword->label("");
			defPanel->pronunciation->label("");
			defPanel->definition->label("");
		}
	}, defPanel);

	struct SearchBarCallbackCtx {
		DefinitionPanel* definitionPanel;
		Fl_Select_Browser* results;
	};

	auto ctx = new SearchBarCallbackCtx { defPanel, results };

	searchBar->when(FL_WHEN_CHANGED);
	searchBar->callback([](Fl_Widget *widget, void *b) {
		auto input = (Fl_Input *)(widget);
		auto ctx = (SearchBarCallbackCtx*)b;

		std::string_view query = input->value();
		std::vector<SearchResult> results = searchInEntries(entries, query);

		ctx->results->clear();

		for (auto result : results) { 
			auto& entry = entries[result.entryIdx];
			int* data = new int(result.entryIdx);
			ctx->results->add(entry.characters.c_str(), (void*)data);
		}
	}, ctx);

	window->end();
	window->show();
	return Fl::run();
}
