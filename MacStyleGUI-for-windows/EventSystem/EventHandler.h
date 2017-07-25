#pragma once
#include <windows.h>
#include <unordered_map>

namespace MacStyleGUI::EventSystem {

	class EventHandler {
	protected:
		std::unordered_map<UINT, LRESULT(*)(MSG Msg, VOID* args)> HandlerTable;
	public:
		virtual VOID AddHandler(UINT EventID, LRESULT(*HandlerFunction)(MSG, VOID*)) {
			HandlerTable.insert(std::make_pair(EventID, HandlerFunction));
		}

		virtual VOID ModifyHandler(UINT EventID, LRESULT(*HandlerFunction)(MSG, VOID*)) {
			auto it_found = HandlerTable.find(EventID);
			if (it_found != HandlerTable.end()) {
				it_found->second = HandlerFunction;
			}
		}

		virtual VOID RemoveHandler(UINT EventID) {
			HandlerTable.erase(EventID);
		}

		virtual LRESULT HandleEvent(UINT EventID, MSG Msg, VOID* args) {
			auto it_found = HandlerTable.find(EventID);
			if (it_found != HandlerTable.end())
				return it_found->second(Msg, args);
			return FALSE;
		}
	};
}