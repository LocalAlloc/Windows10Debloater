#include <windows.h>
#include <stdio.h>
#include <srrestoreptapi.h>
#include <WbemIdl.h>
#include <iostream>
#include <comdef.h>
#include "resource.h"
#include "optimize.h"
using namespace std;
#pragma comment(lib, "wbemuuid.lib")
bool ExtractResource(int iId, LPCWSTR pDest) {
    HRSRC aResourceH = FindResource(NULL, MAKEINTRESOURCE(iId), L"PS1");
    if (!aResourceH) {
        printf("unable to find resource");
        return false;
    }

    HGLOBAL aResourceHGlobal = LoadResource(NULL, aResourceH);
    if (!aResourceHGlobal) {
        printf("unable to load resource");
        return false;
    }

    unsigned char* aFilePtr = (unsigned char*)LockResource(aResourceHGlobal);
    if (!aFilePtr) {
        printf("Unable to lock resource");
        return false;
    }

    unsigned long aFileSize = SizeofResource(NULL, aResourceH);

    HANDLE file_handle = CreateFile(pDest, FILE_ALL_ACCESS, 0, NULL, CREATE_ALWAYS, 0, NULL);
    if (INVALID_HANDLE_VALUE == file_handle) {
        int err = GetLastError();
        if ((ERROR_ALREADY_EXISTS == err) || (32 == err)) {
            return true;
        }
        return false;
    }

    unsigned long numWritten;
    WriteFile(file_handle, aFilePtr, aFileSize, &numWritten, NULL);
    CloseHandle(file_handle);

    return true;
}
int main()
{
    // Disable unnecessary services
    /*DiagTrack: Connected User Experiences and Telemetry
    PrintNotify: Printer Extensions and Notifications
    RetailDemo: Retail Demo Service
    PimIndexMaintenanceSvc: Contact Data
    MapsBroker: Downloaded Maps Manager
    BcastDVRUserService: Game DVR and Broadcasting
    dmwappushsvc: DMW Application Push Service
    RemoteRegistry: Remote Registry
    SharedAccess: Internet Connection Sharing (ICS)
    XboxNetApiSvc: Xbox Live Networking Se
    rvice
    TabletInputService: Touch Keyboard and Handwriting Panel Service
    ConnectedDevicesPlatformUserSvc: Connected Devices Platform User Service
    MessagingService_8wekyb3d8bbwe: Messaging Service
    WalletService_8wekyb3d8bbwe: Wallet Service
    XboxGipSvc: Xbox Game Input Protocol Service
    XboxLiveAuthManager: Xbox Live Auth Manager
    XboxLiveGameSave: Xbox Live Game Save
    XboxLiveNetworkingService: Xbox Live Networking Service*/
    ExtractResource(IDR_PS12, L"C:\\Windows\\Temp\\debloater.ps1");
    HINSTANCE result = ShellExecute(NULL, L"runas", L"powershell.exe",
        L"Enable-ComputerRestore -Drive C:\\", NULL, SW_SHOWNORMAL);

    // Check if the command was executed successfully
    if ((int)result <= 32)
    {
        std::cerr << "Failed to execute command: " << GetLastError() << std::endl;
        return 1;
    }
    Sleep(4000);
    system("wmic.exe /Namespace:\\\\root\\default Path SystemRestore Call CreateRestorePoint \"Windows_10_Optimizer_Restore_Point\", 100, 7");
    Sleep(8000);
    // Wait for the command to complete
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE; // Hide the console window

    // Change the path to your PowerShell script file
    WCHAR scriptPath[] = L"C:\\Windows\\Temp\\debloater.ps1";
    WCHAR command[] = L"powershell.exe -ExecutionPolicy Bypass -File ";

    // Concatenate the command and script path
    WCHAR fullCommand[MAX_PATH];
    wcscpy_s(fullCommand, MAX_PATH, command);
    wcscat_s(fullCommand, MAX_PATH, scriptPath);

    // Start the PowerShell process
    if (!CreateProcess(NULL, fullCommand, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("Failed to start PowerShell process. Error: %d\n", GetLastError());
        return 1;
    }
    setregkeys();
    // Wait for the process to exit
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close the process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (scm)
    {
        SC_HANDLE service = OpenService(scm, L"wuauserv", SERVICE_STOP | SERVICE_DISABLED);
        if (service)
        {
            ControlService(service, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service);
        }
        SC_HANDLE service1 = OpenService(scm, L"DiagTrack", SERVICE_STOP | SERVICE_DISABLED);
        if (service1)
        {
            ControlService(service1, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service1, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service1);
        }
        SC_HANDLE service2 = OpenService(scm, L"PrintNotify", SERVICE_STOP | SERVICE_DISABLED);
        if (service2)
        {
            ControlService(service2, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service2, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service2);
        }
        SC_HANDLE service3 = OpenService(scm, L"RetailDemo", SERVICE_STOP | SERVICE_DISABLED);
        if (service3)
        {
            ControlService(service3, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service3, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service3);
        }
        SC_HANDLE service4 = OpenService(scm, L"PimIndexMaintenanceSvc", SERVICE_STOP | SERVICE_DISABLED);
        if (service4)
        {
            ControlService(service4, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service4, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service4);
        }
        SC_HANDLE service5 = OpenService(scm, L"MapsBroker", SERVICE_STOP | SERVICE_DISABLED);
        if (service5)
        {
            ControlService(service5, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service5, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service5);
        }
        SC_HANDLE service6 = OpenService(scm, L"BcastDVRUserService", SERVICE_STOP | SERVICE_DISABLED);
        if (service6)
        {
            ControlService(service6, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service6, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service6);
        }
        SC_HANDLE service7 = OpenService(scm, L"dmwappushsvc", SERVICE_STOP | SERVICE_DISABLED);
        if (service7)
        {
            ControlService(service7, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service7, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service7);
        }
        SC_HANDLE service8 = OpenService(scm, L"RemoteRegistry", SERVICE_STOP | SERVICE_DISABLED);
        if (service8)
        {
            ControlService(service8, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service8, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service8);
        }
        SC_HANDLE service9 = OpenService(scm, L"SharedAccess", SERVICE_STOP | SERVICE_DISABLED);
        if (service9)
        {
            ControlService(service9, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service9, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service9);
        }
        SC_HANDLE service10 = OpenService(scm, L"XboxNetApiSvc", SERVICE_STOP | SERVICE_DISABLED);
        if (service10)
        {
            ControlService(service10, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service10, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service10);
        }
        SC_HANDLE service11 = OpenService(scm, L"TabletInputService", SERVICE_STOP | SERVICE_DISABLED);
        if (service11)
        {
            ControlService(service11, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service11, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service11);
        }
        SC_HANDLE service12 = OpenService(scm, L"ConnectedDevicesPlatformUserSvc", SERVICE_STOP | SERVICE_DISABLED);
        if (service12)
        {
            ControlService(service12, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service12, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service12);
        }
        SC_HANDLE service13 = OpenService(scm, L"MessagingService_8wekyb3d8bbwe", SERVICE_STOP | SERVICE_DISABLED);
        if (service13)
        {
            ControlService(service13, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service13, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service13);
        }
        SC_HANDLE service14 = OpenService(scm, L"WalletService_8wekyb3d8bbwe", SERVICE_STOP | SERVICE_DISABLED);
        if (service14)
        {
            ControlService(service14, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service14, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service14);
        }
        SC_HANDLE service15 = OpenService(scm, L"XboxGipSvc", SERVICE_STOP | SERVICE_DISABLED);
        if (service15)
        {
            ControlService(service15, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service15, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service15);
        }
        SC_HANDLE service16 = OpenService(scm, L"XboxLiveAuthManager", SERVICE_STOP | SERVICE_DISABLED);
        if (service16)
        {
            ControlService(service16, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service16, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service16);
        }
        SC_HANDLE service17 = OpenService(scm, L"XboxLiveGameSave", SERVICE_STOP | SERVICE_DISABLED);
        if (service17)
        {
            ControlService(service17, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service17, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service17);
        }
        SC_HANDLE service18 = OpenService(scm, L"XboxLiveNetworkingService", SERVICE_STOP | SERVICE_DISABLED);
        if (service18)
        {
            ControlService(service18, SERVICE_CONTROL_STOP, NULL);
            ChangeServiceConfig(service18, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            CloseServiceHandle(service18);
        }
        CloseServiceHandle(scm);
    }
    printf("Enhancing Privacy...");
    HKEY hKey;
    DWORD dwValue = 0;
    DWORD dwSize = sizeof(dwValue);

    // Open the registry key
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
    {
        // Disable telemetry
        RegSetValueEx(hKey, L"AllowTelemetry", 0, REG_DWORD, (LPBYTE)&dwValue, dwSize);

        // Close the registry key
        RegCloseKey(hKey);
    }
    // Disable telemetry services
    system("sc stop DiagTrack");
    system("sc stop dmwappushservice");
    system("sc stop WMPNetworkSvc");
    system("sc stop WerSvc");
    system("sc stop PcaSvc");

    // Disable telemetry tasks
    system("schtasks /change /tn \"Microsoft\\Windows\\Customer Experience Improvement Program\\Consolidator\" /disable");
    system("schtasks /change /tn \"Microsoft\\Windows\\Customer Experience Improvement Program\\KernelCeipTask\" /disable");
    system("schtasks /change /tn \"Microsoft\\Windows\\Customer Experience Improvement Program\\Uploader\" /disable");

    printf("Telemetry disabled successfully.\n");

    if (MessageBoxA(NULL, "Disable Visual Effects?!", "", MB_YESNO | MB_ICONQUESTION) == IDYES){
        // Disable visual effects
        SystemParametersInfo(SPI_SETCLIENTAREAANIMATION, 0, (PVOID)FALSE, SPIF_SENDCHANGE);
        SystemParametersInfo(SPI_SETMENUANIMATION, 0, (PVOID)FALSE, SPIF_SENDCHANGE);
        SystemParametersInfo(SPI_SETMOUSEHOVERWIDTH, 0, (PVOID)0, SPIF_SENDCHANGE);
        SystemParametersInfo(SPI_SETMOUSEHOVERHEIGHT, 0, (PVOID)0, SPIF_SENDCHANGE);
        SystemParametersInfo(SPI_SETMOUSEHOVERTIME, 0, (PVOID)0, SPIF_SENDCHANGE);
        SystemParametersInfo(SPI_SETMOUSECLICKLOCK, 0, (PVOID)0, SPIF_SENDCHANGE);
        SystemParametersInfo(SPI_SETFONTSMOOTHINGCONTRAST, 0, (PVOID)0, SPIF_SENDCHANGE);
        SystemParametersInfo(SPI_SETFONTSMOOTHINGTYPE, 0, (PVOID)0, SPIF_SENDCHANGE);
        SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, 0, (PVOID)FALSE, SPIF_SENDCHANGE);
        SystemParametersInfo(SPI_SETBORDER, 0, (PVOID)FALSE, SPIF_SENDCHANGE);

    }
    else {
        MessageBoxA(NULL, "Okay", "", MB_OK | MB_ICONINFORMATION);
    }
    printf("Sucessfully Optimized Windows!");

    return 0;
}
