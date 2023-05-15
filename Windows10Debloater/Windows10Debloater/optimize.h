#include <Windows.h>
#include <iostream>


void setregkeys() {
    RegSetValueExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\AutoComplete\\Append Completion", 0, REG_SZ, (BYTE*)"yes", strlen("yes") + 1);
    RegSetValueExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\AutoComplete\\AutoSuggest", 0, REG_SZ, (BYTE*)"yes", strlen("yes") + 1);

    // reduce dump file size
    RegSetValueExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\CrashControl\\CrashDumpEnabled", 0, REG_DWORD, (BYTE*)"\x3", sizeof(DWORD));

    // show all tray icons
    RegSetValueExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\EnableAutoTray", 0, REG_DWORD, (BYTE*)"\x0", sizeof(DWORD));

    // disable Remote Assistance
    RegSetValueExA(HKEY_LOCAL_MACHINE, "System\\CurrentControlSet\\Control\\Remote Assistance\\fAllowToGetHelp", 0, REG_DWORD, (BYTE*)"\x0", sizeof(DWORD));

    // disable shaking to minimize
    RegSetValueExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\DisallowShaking", 0, REG_DWORD, (BYTE*)"\x1", sizeof(DWORD));

    RegSetValueExA(HKEY_CLASSES_ROOT, "AllFilesystemObjects\\shellex\\ContextMenuHandlers\\Copy To", 0, REG_SZ, (BYTE*)"{C2FBB630-2971-11D1-A18C-00C04FD75D13}", strlen("{C2FBB630-2971-11D1-A18C-00C04FD75D13}") + 1);
    RegSetValueExA(HKEY_CLASSES_ROOT, "AllFilesystemObjects\\shellex\\ContextMenuHandlers\\Move To", 0, REG_SZ, (BYTE*)"{C2FBB631-2971-11D1-A18C-00C04FD75D13}", strlen("{C2FBB631-2971-11D1-A18C-00C04FD75D13}") + 1);

    RegSetValueExA(HKEY_CURRENT_USER, "Control Panel\\Desktop\\AutoEndTasks", 0, REG_SZ, (BYTE*)"1", strlen("1") + 1);
    RegSetValueExA(HKEY_CURRENT_USER, "Control Panel\\Desktop\\HungAppTimeout", 0, REG_SZ, (BYTE*)"1000", strlen("1000") + 1);
    RegSetValueExA(HKEY_CURRENT_USER, "Control Panel\\Desktop\\MenuShowDelay", 0, REG_SZ, (BYTE*)"0", strlen("0") + 1);
    RegSetValueExA(HKEY_CURRENT_USER, "Control Panel\\Desktop\\WaitToKillAppTimeout", 0, REG_SZ, (BYTE*)"2000", strlen("2000") + 1);
    RegSetValueExA(HKEY_CURRENT_USER, "Control Panel\\Desktop\\LowLevelHooksTimeout", 0, REG_SZ, (BYTE*)"1000", strlen("1000") + 1);
    RegSetValueExA(HKEY_CURRENT_USER, "Control Panel\\Mouse\\MouseHoverTime", 0, REG_SZ, (BYTE*)"0", strlen("0") + 1);
    RegSetValueExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\NoLowDiskSpaceChecks", 0, REG_DWORD, (BYTE*)"\1", sizeof(DWORD));

    HKEY hKey;
    DWORD data = 0x00000001;
    DWORD type = REG_DWORD;
    RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
    RegSetValueEx(hKey, TEXT("LinkResolveIgnoreLinkInfo"), 0, type, (const BYTE*)&data, sizeof(DWORD));
    RegSetValueEx(hKey, TEXT("NoResolveSearch"), 0, type, (const BYTE*)&data, sizeof(DWORD));
    RegSetValueEx(hKey, TEXT("NoResolveTrack"), 0, type, (const BYTE*)&data, sizeof(DWORD));
    RegSetValueEx(hKey, TEXT("NoInternetOpenWith"), 0, type, (const BYTE*)&data, sizeof(DWORD));
    RegCloseKey(hKey);

    data = 2000;
    type = REG_SZ;
    RegCreateKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Control"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
    RegSetValueEx(hKey, TEXT("WaitToKillServiceTimeout"), 0, type, (const BYTE*)&data, sizeof(DWORD));
    RegCloseKey(hKey);

    // Stopping services
    std::wstring services[] = { L"DiagTrack", L"diagsvc", L"diagnosticshub.standardcollector.service", L"dmwappushservice" };
    for (auto service : services) {
        std::wstring command = L"net stop " + service;
        std::string narrowCommand(command.begin(), command.end());
        system(narrowCommand.c_str());
    }

    // Setting registry values
    data = 4;
    RegCreateKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services\\DiagTrack"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
    RegSetValueEx(hKey, TEXT("Start"), 0, type, (const BYTE*)&data, sizeof(DWORD));
    RegCloseKey(hKey);

    RegCreateKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services\\diagsvc"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
    RegSetValueEx(hKey, TEXT("Start"), 0, type, (const BYTE*)&data, sizeof(DWORD));
    RegCloseKey(hKey);

    RegCreateKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services\\diagnosticshub.standardcollector.service"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
    RegSetValueEx(hKey, TEXT("Start"), 0, type, (const BYTE*)&data, sizeof(DWORD));
    RegCloseKey(hKey);

    RegCreateKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services\\dmwappushservice"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
    RegSetValueEx(hKey, TEXT("Start"), 0, type, (const BYTE*)&data, sizeof(DWORD));
    RegCloseKey(hKey);
}