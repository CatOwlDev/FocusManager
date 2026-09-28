#pragma once

#include <vector>
#include <algorithm>
#include <cstdlib>

#include <nlohmann/json.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

#include "ToDoList.h"
#include "Timer.h"
#include "Blocker.h"
#include "MyTransformers.h"

class FocusManager;

static constexpr int visibleTasks{ 3 };

enum class Page : int {
	pageToDoList = 0,
	pageTimer = 0,
	pageBlocker = 0,
	pageForm = 1
};

class ToDoListUI {
public:
	explicit ToDoListUI(ToDoList& toDoList);

	ftxui::Component component();
private:
	ftxui::Element render();
	bool handleEvent(ftxui::Event event);
	void ensureVisible();
private:
	ToDoList& mToDoList;

	std::vector<ftxui::Box> mTaskBoxes{};

	int mSelected{};
	int mHovered{};
	int mScroll{};
	int mPage{};

	bool mIsEditing{};

	std::string mStringInputNameTask{};
	std::string mStringInputShortDescriptionTask{};
	std::string mStringInputCompletionDateAndTimeTask{};
	std::string mStringInputCategoryTask{};
	std::string mStringInputPriorityTask{};
	std::string mStringInputStatusTask{};
};

class TimerUI {
public:
	explicit TimerUI(Timer& timer);

	ftxui::Component component();
private:
	ftxui::Element render();
private:
	Timer& mTimer;
	
	int mSelected{};
	int mPage{};

	std::string mStringInputTimeToWorkTimer{};
	std::string mStringInputMinTimeToRelaxTimer{};
	std::string mStringInputMaxTimeToRelaxTimer{};
};

class BlockerUI {
public:
	explicit BlockerUI(Blocker& blocker);

	ftxui::Component component();
private:
	Blocker& mBlocker;

	int mSelected{};
	int mPage{};

	std::string mStringInputProcessName{};
};

class FocusManagerUI {
public:
	FocusManagerUI(FocusManager* focusManager);
	~FocusManagerUI() = default;

	ftxui::Component component();
private:
	FocusManager* mPtrFocusManager;

	ToDoListUI mToDoListUI;
	TimerUI mTimerUI;
	BlockerUI mBlockerUI;
};