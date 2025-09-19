#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"
#include <filesystem>
#include <wil/win32_helpers.h>
#include <wil/resource.h>
#include <wil/result_macros.h>

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
struct DynamicRuntimeLoaderAutoInitialize
{
    DynamicRuntimeLoaderAutoInitialize() try 
    {
        // Get current module path
        auto moduleFileName = wil::GetModuleFileNameW(reinterpret_cast<HMODULE>(&__ImageBase));
        auto runtimePath = std::filesystem::path(moduleFileName.get());
        runtimePath.remove_filename();

        // Determine path of the Windows App Runtime to load, based on machine architecture
        USHORT processMachine;
        USHORT nativeMachine;
        THROW_IF_WIN32_BOOL_FALSE(IsWow64Process2(GetCurrentProcess(), &processMachine, &nativeMachine));
        if (nativeMachine == IMAGE_FILE_MACHINE_AMD64) 
        {
            // x64 process running natively on an x64 system, use x64 WAR
            runtimePath.append(L"Microsoft.WindowsAppRuntime.x64\\");
        }
        else if (nativeMachine == IMAGE_FILE_MACHINE_ARM64) 
        {
            // x64 process running emulated on an ARM64 system, use ARM64EC WAR
            runtimePath.append(L"Microsoft.WindowsAppRuntime.ARM64EC\\");
        }
        else
        {
            THROW_HR(E_UNEXPECTED);
        }

        // This env var is used by the SelfContained support to provide an absolute path
        // for DLLs referenced in the fusion manifest, triggered by PublishSingleFile=true.
        THROW_IF_WIN32_BOOL_FALSE(SetEnvironmentVariableW(L"MICROSOFT_WINDOWSAPPRUNTIME_BASE_DIRECTORY", runtimePath.c_str()));

        // Add runtime location to the path
        wil::unique_cotaskmem_string path;
        THROW_IF_FAILED(wil::GetEnvironmentVariableW(L"PATH", path));
        if (path)
        {
            auto newPath{ wil::str_concat<wil::unique_cotaskmem_string>(runtimePath.c_str(), L";", path) };
            THROW_IF_WIN32_BOOL_FALSE(SetEnvironmentVariableW(L"PATH", newPath.get()));
        }
        else
        {
            const auto lastError{ GetLastError() };
            THROW_HR_IF(HRESULT_FROM_WIN32(lastError), lastError != ERROR_ENVVAR_NOT_FOUND);
            THROW_IF_WIN32_BOOL_FALSE(SetEnvironmentVariableW(L"PATH", runtimePath.c_str()));
        }

        // Add runtime location to list of DLL directories 
        THROW_LAST_ERROR_IF_NULL(AddDllDirectory(runtimePath.c_str()));

        // Bootstrap the Windows App SDK runtime by loading the main DLL
        THROW_LAST_ERROR_IF_NULL(LoadLibraryExW(L"Microsoft.WindowsAppRuntime.dll", nullptr, 0));
    }
    // If we don't have a Windows App Runtime, we can't really do anything useful.
    CATCH_FAIL_FAST()
};
// Global instance to trigger the dynamic runtime loader initialization at process startup
static DynamicRuntimeLoaderAutoInitialize g_DynamicRuntimeLoaderAutoInitialize;

namespace winrt::CppPkg::implementation
{
    App::App()
    {
#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
        UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
            {
                if (IsDebuggerPresent())
                {
                    auto errorMessage = e.Message();
                    __debugbreak();
                }
            });
#endif
    }

    void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e)
    {
        window = make<MainWindow>();
        window.Activate();
    }
}

