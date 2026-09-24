#include "UI.h"
#include "FocusManager.h"

// =ToDoListUI=====================================================================================================================

ToDoListUI::ToDoListUI(ToDoList& toDoList) : mToDoList{ toDoList } {}

ftxui::Component ToDoListUI::component() {
	ftxui::Component btnAdd{ 
		ftxui::Button("Add", [this]() {
			mIsEditing = false;

			mStringInputNameTask.clear();
			mStringInputShortDescriptionTask.clear();
			mStringInputCompletionDateAndTimeTask.clear();
			mStringInputCategoryTask.clear();
			mStringInputStatusTask.clear();
			mStringInputPriorityTask.clear();

			mPage = static_cast<int>(Page::pageForm);
		}, ftxui::ButtonOption::Ascii())
	};
	ftxui::Component btnDelete{ 
		ftxui::Button("Delete", [this]() {
			mToDoList.erase(mSelected);
		}, ftxui::ButtonOption::Ascii())
	};
	ftxui::Component btnEdit{ 
		ftxui::Button("Edit", [this]() {
			if (!mToDoList.getTasks().empty()) {
				mIsEditing = true;

				Task& task{ mToDoList.getTask(mSelected) };

				mStringInputNameTask = task.getName();
				mStringInputShortDescriptionTask = task.getShortDescription();
				mStringInputCompletionDateAndTimeTask = task.getCompletionDateAndTime();
				mStringInputCategoryTask = task.getCategory();
				mStringInputStatusTask = myTransformers::to_string(task.getStatus());
				mStringInputPriorityTask = myTransformers::to_string(task.getPriority());

				mPage = static_cast<int>(Page::pageForm);
			}
		}, ftxui::ButtonOption::Ascii())
	};
	ftxui::Component btnSave{ ftxui::Button("Save", [this]() {
		if (mIsEditing) {
			Task& task{ mToDoList.getTask(mSelected) };

			task.setName(mStringInputNameTask);
			task.setShortDescription(mStringInputShortDescriptionTask);
			task.setCompletionDateAndTime(mStringInputCompletionDateAndTimeTask);
			task.setCategory(mStringInputCategoryTask);
			task.setStatus(myTransformers::to_status(mStringInputStatusTask));
			task.setPriority(myTransformers::to_priority(mStringInputPriorityTask));
		}
		else {
			const Task task{
				mStringInputNameTask,
				mStringInputShortDescriptionTask,
				mStringInputCompletionDateAndTimeTask,
				mStringInputCategoryTask,
				myTransformers::to_status(mStringInputStatusTask),
				myTransformers::to_priority(mStringInputPriorityTask)
			};

			mToDoList.emplaceBack(task);
		}

		mPage = static_cast<int>(Page::pageToDoList);
	}, ftxui::ButtonOption::Ascii()) };

	ftxui::Component btnSetActive{
		ftxui::Button("Set Active", [this]() {
			if (!mToDoList.getTasks().empty()) {
				Task& task{ mToDoList.getTask(mSelected) };

				task.setStatus(Status::Active);
			}
		}, ftxui::ButtonOption::Ascii())
	};
	ftxui::Component btnSetInactive{
		ftxui::Button("Set Inactive", [this]() {
			if (!mToDoList.getTasks().empty()) {
				Task& task{ mToDoList.getTask(mSelected) };

				task.setStatus(Status::Inactive);
			}
		}, ftxui::ButtonOption::Ascii())
	};
	ftxui::Component btnSetCompleted{
		ftxui::Button("Set Completed", [this]() {
			if (!mToDoList.getTasks().empty()) {
				Task& task{ mToDoList.getTask(mSelected) };

				task.setStatus(Status::Completed);
			}
		}, ftxui::ButtonOption::Ascii())
	};

	ftxui::Component inputNameTask{ ftxui::Input({ &mStringInputNameTask, "Name" }) };
	ftxui::Component inputShortDescriptionTask{ ftxui::Input({ &mStringInputShortDescriptionTask, "ShortDescription" }) };
	ftxui::Component inputCompletionDateAndTimeTask{ ftxui::Input({ &mStringInputCompletionDateAndTimeTask, "CompletionDateAndTime" }) };
	ftxui::Component inputCategoryTask{ ftxui::Input({ &mStringInputCategoryTask, "Category" }) };
	ftxui::Component inputStatusTask{ ftxui::Input({ &mStringInputStatusTask, "Status: Active or Inactive or Completed" }) };
	ftxui::Component inputPriorityTask{ ftxui::Input({ &mStringInputPriorityTask, "Priority: Low or Medium or High or Critical" }) };
	
	ftxui::Component containerButtonsForToDoList{
		ftxui::Container::Horizontal({
			btnAdd,
			btnDelete,
			btnEdit,
			btnSetActive,
			btnSetInactive,
			btnSetCompleted
		})
	};
	
	ftxui::Component containerInputsForm{
		ftxui::Container::Vertical({
			inputNameTask,
			inputShortDescriptionTask,
			inputCompletionDateAndTimeTask,
			inputCategoryTask,
			inputStatusTask,
			inputPriorityTask,
			btnSave
		})
	};

	ftxui::Component pageToDoListUI{ 
		ftxui::Renderer(
			containerButtonsForToDoList, 
			[
				this, 
				btnAdd, 
				btnDelete, 
				btnEdit, 
				btnSetActive, 
				btnSetInactive, 
				btnSetCompleted
			]() {
			return ftxui::window(
				ftxui::text("[ToDoList]") | ftxui::bold | ftxui::color(ftxui::Color::Orange1),
				ftxui::vbox({
				ftxui::text(""),
				ftxui::hbox({
					ftxui::text("Numbers of tasks: " + std::to_string(mToDoList.getSize())) | ftxui::color(ftxui::Color::White)
				}) | ftxui::xflex,
				ftxui::text(""),
				ftxui::separator(),
				render(),
				ftxui::separator(),
				ftxui::hbox({
					btnAdd->Render() | ftxui::color(ftxui::Color::GrayDark),
					btnDelete->Render() | ftxui::color(ftxui::Color::GrayDark),
					btnEdit->Render() | ftxui::color(ftxui::Color::GrayDark),
					ftxui::filler(),
					btnSetActive->Render() | ftxui::color(ftxui::Color::GrayDark),
					btnSetInactive->Render() | ftxui::color(ftxui::Color::GrayDark),
					btnSetCompleted->Render() | ftxui::color(ftxui::Color::GrayDark),
				}) | ftxui::center | ftxui::xflex
			}) | ftxui::xflex ) | ftxui::color(ftxui::Color::GrayDark) | ftxui::xflex;
	}) };

	pageToDoListUI = ftxui::CatchEvent(pageToDoListUI, [this](ftxui::Event event)->bool {
		return handleEvent(event);
	});

	ftxui::Component pageFormUI{
		ftxui::Renderer(
			containerInputsForm, 
			[
				this, 
				inputNameTask, 
				inputShortDescriptionTask, 
				inputCompletionDateAndTimeTask, 
				inputCategoryTask,
				inputStatusTask,
				inputPriorityTask,
				btnSave
			]() {
			return ftxui::window(
				ftxui::text("[Form]") | ftxui::bold | ftxui::color(ftxui::Color::Orange1),
				ftxui::vbox({
				inputNameTask->Render(),
				ftxui::separator(),
				inputShortDescriptionTask->Render(),
				ftxui::separator(),
				inputCompletionDateAndTimeTask->Render(),
				ftxui::separator(),
				inputCategoryTask->Render(),
				ftxui::separator(),
				inputStatusTask->Render(),
				ftxui::separator(),
				inputPriorityTask->Render(),
				ftxui::separator(),
				btnSave->Render() | ftxui::center
				}) | ftxui::xflex
			) | ftxui::xflex;
		})
	};

	ftxui::Component pages{
		ftxui::Container::Tab({
			pageToDoListUI,
			pageFormUI
		}, &mPage)
	};

	ftxui::Component component{
		ftxui::Renderer(pages, [pages]() {
			return ftxui::vbox({
				pages->Render()
			}) | ftxui::xflex;
		})
	};

	return component;
}
ftxui::Element ToDoListUI::render() {
	const std::vector<Task>& tasks{ mToDoList.getTasks() };
	ftxui::Elements elements{};

	mTaskBoxes.resize(tasks.size());

	int end{ std::min(
		mScroll + visibleTasks,
		static_cast<int>(tasks.size())
	) };

	for (int i{ mScroll }; i < end; ++i) {
		const Task& task{ tasks[i] };
		const Status statusTask{ task.getStatus() };
		const Priority priorityTask{ task.getPriority() };

		ftxui::Element element{
			ftxui::hbox({
				ftxui::text('[' + myTransformers::to_string(statusTask).substr(0, 1) + ']') | myTransformers::to_color(statusTask),
				ftxui::vbox({
					ftxui::text(task.getName()) | myTransformers::to_color(statusTask),
					ftxui::text(task.getShortDescription()) | ftxui::color(ftxui::Color::GrayLight),
					ftxui::text(task.getCompletionDateAndTime()) | ftxui::color(ftxui::Color::GrayLight)
				}),
				ftxui::separator(),
				ftxui::vbox({
					ftxui::text(""),
					ftxui::text(task.getCategory()) | ftxui::color(ftxui::Color::GrayLight),
					ftxui::text(myTransformers::to_string(priorityTask)) | myTransformers::to_color(priorityTask)
				})
			}) | ftxui::borderLight | ftxui::color(ftxui::Color::GrayDark)
		};

		element = element | ftxui::reflect(mTaskBoxes[i]);

		if (i == mHovered) element = element | ftxui::inverted;
		if (i == mSelected) element = element | ftxui::bold;

		elements.emplace_back(element);
	}

	if (elements.empty()) elements.emplace_back(ftxui::text("The list is empty") | ftxui::dim);

	return ftxui::vbox(std::move(elements));
}
bool ToDoListUI::handleEvent(ftxui::Event event) {
	const std::vector<Task>& tasks{ mToDoList.getTasks() };

	if (event.is_mouse()) {
		ftxui::Mouse mouse{ event.mouse() };

		int end{ 
			std::min(
				mScroll + visibleTasks, 
				static_cast<int>(mTaskBoxes.size())
			)
		};

		for (int i{ mScroll }; i < end; ++i) {
			if (mTaskBoxes[i].Contain(mouse.x, mouse.y)) {
				mHovered = i;

				if (mouse.button == ftxui::Mouse::Left && mouse.motion == ftxui::Mouse::Pressed) {
					mSelected = i;
					return true;
				}

				break;
			}
		}

		if (mouse.button == ftxui::Mouse::WheelUp) {
			if (mSelected > 0) --mSelected;
			ensureVisible();
			return true;
		}

		if (mouse.button == ftxui::Mouse::WheelDown) {
			if (!tasks.empty() && mSelected + 1 < static_cast<int>(tasks.size())) ++mSelected;
			ensureVisible();
			return true;
		}
	}
	if (event == ftxui::Event::ArrowUp) {
		if (mSelected > 0) --mSelected;
		ensureVisible();
		return true;
	}
	if (event == ftxui::Event::ArrowDown) {
		if (!tasks.empty() && mSelected + 1 < static_cast<int>(tasks.size())) ++mSelected;
		ensureVisible();
		return true;
	}

	return false;
}
void ToDoListUI::ensureVisible() {
	if (mSelected < mScroll) mScroll = mSelected;
	if (mSelected >= mScroll + visibleTasks) mScroll = mSelected - visibleTasks + 1;
}

// =TimerUI========================================================================================================================

TimerUI::TimerUI(Timer& timer) : mTimer { timer } {}

ftxui::Component TimerUI::component() {
	ftxui::Component btnStart{
		ftxui::Button("Start", [this]() {
			mTimer.start();
		}, ftxui::ButtonOption::Ascii())
	};
	ftxui::Component btnStop{
		ftxui::Button("Stop", [this]() {
			mTimer.stop();
		}, ftxui::ButtonOption::Ascii())
	};
	ftxui::Component btnReset{
		ftxui::Button("Reset", [this]() {
			mTimer.reset();
		}, ftxui::ButtonOption::Ascii())
	};
	ftxui::Component btnSkip{
		ftxui::Button("Skip", [this]() {
			mTimer.skip();
		}, ftxui::ButtonOption::Ascii())
	};
	ftxui::Component btnEdit{
		ftxui::Button("Edit", [this]() {
			mTimer.reset();

			mStringInputTimeToWorkTimer = std::to_string(mTimer.getTimeToWork().count() / maxSecondsInMinute);
			mStringInputMinTimeToRelaxTimer = std::to_string(mTimer.getMinTimeToRelax().count() / maxSecondsInMinute);
			mStringInputMaxTimeToRelaxTimer = std::to_string(mTimer.getMaxTimeToRelax().count() / maxSecondsInMinute);

			mPage = static_cast<int>(Page::pageForm);
		}, ftxui::ButtonOption::Ascii())
	};
	ftxui::Component btnSave{
		ftxui::Button("Save", [this]() {

			seconds timeToWork{ 
				static_cast<long long>(myTransformers::safeConvertSTOUI(mStringInputTimeToWorkTimer) * maxSecondsInMinute) 
			};
			seconds minTimeToRelax{
				static_cast<long long>(myTransformers::safeConvertSTOUI(mStringInputMinTimeToRelaxTimer) * maxSecondsInMinute)
			};
			seconds maxTimeToRelax{
				static_cast<long long>(myTransformers::safeConvertSTOUI(mStringInputMaxTimeToRelaxTimer) * maxSecondsInMinute)
			};

			mTimer.setTimeToWork(timeToWork);
			mTimer.setMinTimeToRelax(minTimeToRelax);
			mTimer.setMaxTimeToRelax(maxTimeToRelax);

			mPage = static_cast<int>(Page::pageTimer);
		}, ftxui::ButtonOption::Ascii())
	};

	ftxui::Component inputTimeToWorkTimer{
		ftxui::Input(&mStringInputTimeToWorkTimer, "TimeToWork")
	};
	ftxui::Component inputMinTimeToRelaxTimer{
		ftxui::Input(&mStringInputMinTimeToRelaxTimer, "MinTimeToRelax")
	};
	ftxui::Component inputMaxTimeToRelaxTimer{
		ftxui::Input(&mStringInputMaxTimeToRelaxTimer, "MaxTimeToRelax")
	};

	ftxui::Component containerForTimer{
		ftxui::Container::Horizontal({
			btnStart,
			btnStop,
			btnReset,
			btnSkip,
			btnEdit
		})
	};
	ftxui::Component containerForForm{
		ftxui::Container::Vertical({
			inputTimeToWorkTimer,
			inputMinTimeToRelaxTimer,
			inputMaxTimeToRelaxTimer,
			btnSave
		})
	};

	ftxui::Component pageTimerUI{ 
		ftxui::Renderer(
			containerForTimer, 
			[
				this,
				btnStart,
				btnStop,
				btnReset,
				btnSkip,
				btnEdit
			]() {
			return ftxui::window(
				ftxui::text("[Timer]") | ftxui::bold | ftxui::color(ftxui::Color::Orange1),
				ftxui::vbox({
					render(),
					ftxui::hbox({
						btnStart->Render() | ftxui::color(ftxui::Color::GrayDark),
						btnStop->Render() | ftxui::color(ftxui::Color::GrayDark),
						btnReset->Render() | ftxui::color(ftxui::Color::GrayDark),
						btnSkip->Render() | ftxui::color(ftxui::Color::GrayDark),
						btnEdit->Render() | ftxui::color(ftxui::Color::GrayDark),
					}) | ftxui::center | ftxui::xflex
				}) | ftxui::xflex) | ftxui::xflex | ftxui::color(ftxui::Color::GrayDark);
		}) };

	ftxui::Component pageFormUI{
		ftxui::Renderer(
			containerForForm, 
			[
				this,
				inputTimeToWorkTimer,
				inputMinTimeToRelaxTimer,
				inputMaxTimeToRelaxTimer,
				btnSave
			]() {
			return ftxui::window(
				ftxui::text("[Form]") | ftxui::bold | ftxui::color(ftxui::Color::Orange1),
				ftxui::vbox({
					inputTimeToWorkTimer->Render(),
					ftxui::separator(),
					inputMinTimeToRelaxTimer->Render(),
					ftxui::separator(),
					inputMaxTimeToRelaxTimer->Render(),
					ftxui::separator(),
					btnSave->Render() | ftxui::center
				}) | ftxui::xflex
			) | ftxui::xflex;
		})
	};

	ftxui::Component pages{
		ftxui::Container::Tab({
			pageTimerUI,
			pageFormUI
		}, &mPage)
	};

	ftxui::Component component{
		ftxui::Renderer(pages, [pages]() {
			return ftxui::vbox({
				pages->Render()
			}) | ftxui::xflex;
		})
	};

	return component;
}
ftxui::Element TimerUI::render() {
	return ftxui::vbox({
		ftxui::text("Current session: " + myTransformers::to_string(mTimer.getState())) | ftxui::bold | ftxui::color(ftxui::Color::Orange1) | ftxui::center,
		ftxui::filler(),
		ftxui::text(countdownToASCII(mTimer.showCountdown())) | ftxui::color(ftxui::Color::Green) | ftxui::center
	});
}

// =BlockerUI======================================================================================================================

BlockerUI::BlockerUI(Blocker& blocker) : mBlocker{ blocker } {}

ftxui::Component BlockerUI::component() {
	ftxui::Component btnAdd{
		ftxui::Button("Add", [this]() {
			mStringInputProcessName.clear();

			mPage = static_cast<int>(Page::pageForm);
		}, ftxui::ButtonOption::Ascii())
	};
	ftxui::Component btnDelete{
		ftxui::Button("Delete", [this]() {
			mBlocker.erase(mSelected);
		}, ftxui::ButtonOption::Ascii())
	};
	ftxui::Component btnSave{
		ftxui::Button("Save", [this]() {
			if(!mStringInputProcessName.empty())
				mBlocker.emplaceBack(mStringInputProcessName);

			mPage = static_cast<int>(Page::pageBlocker);
		}, ftxui::ButtonOption::Ascii())
	};

	ftxui::Component inputProcessName{
		ftxui::Input(&mStringInputProcessName, "ProcessName")
	};

	std::vector<std::string>* ptrList{ mBlocker.getList() };

	ftxui::Component menu{ ftxui::Menu(
		ptrList,
		&mSelected
	) };

	ftxui::Component containerForBlocker{
		ftxui::Container::Horizontal({
			btnAdd,
			btnDelete,
			menu
		})
	};
	ftxui::Component containerForForm{
		ftxui::Container::Vertical({
			inputProcessName,
			btnSave
		})
	};

	ftxui::Component pageBlockerUI{
		ftxui::Renderer(
			containerForBlocker, 
			[
				this,
				menu,
				btnAdd,
				btnDelete
			]() {
			return ftxui::window(
				ftxui::text("[Blocker]") | ftxui::bold | ftxui::color(ftxui::Color::Orange1),
				ftxui::vbox({
					ftxui::vbox({
						ftxui::text("Proccess name") | ftxui::color(ftxui::Color::GrayDark),
						ftxui::separator(),
						menu->Render() | ftxui::color(ftxui::Color::Orange1)
					}) | ftxui::xflex,
					ftxui::separator(),
					ftxui::hbox({
						btnAdd->Render(),
						btnDelete->Render()
					}) | ftxui::center | ftxui::xflex
				}) | ftxui::xflex
			) | ftxui::xflex | ftxui::color(ftxui::Color::GrayDark);
			})
	};
	ftxui::Component pageFormUI{
		ftxui::Renderer(
			containerForForm, 
			[
				this,
				inputProcessName,
				btnSave
			]() {
			return ftxui::window(
				ftxui::text("[Form]") | ftxui::bold | ftxui::color(ftxui::Color::Orange1),
				ftxui::vbox({
					inputProcessName->Render(),
					ftxui::separator(),
					btnSave->Render() | ftxui::center
				}) | ftxui::xflex
			) | ftxui::xflex;
		})
	};

	ftxui::Component pages{
		ftxui::Container::Tab({
			pageBlockerUI,
			pageFormUI
		}, &mPage) | ftxui::xflex
	};

	ftxui::Component component{
		ftxui::Renderer(pages, [pages]() {
			return ftxui::vbox({
				pages->Render()
			}) | ftxui::flex;
		})
	};

	return component;
}

// =FocusManagerUI======================================================================================================================

FocusManagerUI::FocusManagerUI(FocusManager* ptrFocusManager) :
	mPtrFocusManager{ ptrFocusManager },
	mToDoListUI{ mPtrFocusManager->getToDoList() },
	mTimerUI{ mPtrFocusManager->getTimer() },
	mBlockerUI{ mPtrFocusManager->getBlocker() } {}

ftxui::Component FocusManagerUI::component() {
	ftxui::Component btnHelp{
		ftxui::Button("Help", []() {
			std::string cmd{ "start " + std::string("https://github.com/CatOwlDev/FocusManager") };
			std::system(cmd.c_str());
		}, ftxui::ButtonOption::Ascii())
	};
	ftxui::Component btnExit{
		ftxui::Button("Exit", [this]() {
			mPtrFocusManager->stopRun();
		}, ftxui::ButtonOption::Ascii())
	};

	ftxui::Component containerMainParts{
		ftxui::Container::Horizontal({
			ftxui::Container::Vertical({
				mTimerUI.component(),
				mBlockerUI.component()
			}),
			mToDoListUI.component()
		})
	};

	ftxui::Component containerForFocusManager{
		ftxui::Container::Horizontal({
			btnHelp,
			btnExit,
			containerMainParts
		})
	};

	ftxui::Component focusManagerUI{
		ftxui::Renderer(
			containerForFocusManager, 
			[
				this,
				btnHelp,
				btnExit,
				containerMainParts
			]() {
			return ftxui::vbox({
				ftxui::hbox({
					ftxui::text("[FocusManager]") | ftxui::bold | ftxui::color(ftxui::Color::Orange1),
					ftxui::filler(),
					btnExit->Render(),
					btnHelp->Render()
				}),
				ftxui::separator(),
				containerMainParts->Render()
			}) | ftxui::borderLight | ftxui::color(ftxui::Color::GrayDark);
		})
	};

	return focusManagerUI;
}