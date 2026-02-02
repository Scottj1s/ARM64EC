#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"
#include <filesystem>
#include <wil/win32_helpers.h>
#include <wil/resource.h>
#include <wil/result_macros.h>

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

std::wstring AppendStrings(std::wstring const& s1, std::wstring const& s2);

namespace winrt::CppPkgStatic::implementation
{
    App::App()
    {
        // Linking in an x64 lib compiled with FH4 adds a dependency on vcruntime140_1(d).dll, 
        // which is not included in the ARM64(x) distribution of VCLibs.UwpDesktop.
        // Debugging on an ARM64 device shows a split load of CRT DLLs:
        //  C:\Program Files\WindowsApps\Microsoft.VCLibs.140.00.Debug.UWPDesktop_14.0.33728.0_arm64__8wekyb3d8bbwe\vcruntime140d.dll
        //  C:\Windows\System32\vcruntime140_1d.dll
        // The vcruntime140_1d.dll above is ARM64EC [8664 machine (x64) (ARM64X)], 
        // so there is evidently no ARM64X [AA64 machine (ARM64) (ARM64X)] distribution of the DLL.
        // On a clean machine without vcredist_x64.exe being run, vcruntime140_1(d).dll won't be found.
        auto hello_world = AppendStrings(L"hello, ", L"world");

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

