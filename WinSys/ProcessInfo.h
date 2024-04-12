#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Keys.h"

namespace WinSys {
	using namespace std;

	struct ThreadInfo;

	struct ProcessInfo {

		const SYSTEM_PROCESS_INFORMATION* NativeInfo{ nullptr };
		const SYSTEM_PROCESS_INFORMATION_EXTENSION* ExtendedInfo{ nullptr };
		PCWSTR m_PackageFullName{ nullptr };

		template<typename TProcessInfo, typename TThreadInfo>
		friend class ProcessManager;

		const wstring& GetImageName() const { return m_ProcessName; }
		const wstring& GetNativeImagePath() const { return m_NativeImagePath; }
		const vector<shared_ptr<ThreadInfo>>& GetThreads() const;
		const wstring& GetUserName() const;

		int BasePriority;
		uint32_t Id;
		uint32_t ParentId;
		int32_t CPU;
		int32_t KernelCPU;

		ProcessOrThreadKey Key;

		void AddThread(shared_ptr<ThreadInfo> thread);
		void ClearThreads();

	private:
		wstring m_ProcessName;
		wstring m_NativeImagePath;
		mutable std::wstring m_UserName;
		vector<shared_ptr<ThreadInfo>> m_threads;
	};
}

