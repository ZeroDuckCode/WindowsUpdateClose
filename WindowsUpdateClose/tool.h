#pragma once
#include <Windows.h>

static bool RegSetting() {
    const char* sub_key = "SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings";
    DWORD value = 65535;
    HKEY hKey = NULL;
    DWORD ret = false;
    ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, sub_key, &hKey);
    if (ret != ERROR_SUCCESS) {
        return false;
    }
    ret= RegSetKeyValueA(hKey, NULL, "FlightSettingsMaxPauseDays", REG_DWORD, &value, REG_DWORD);
    if (ret != ERROR_SUCCESS) {
        return false;
    }
    if( hKey != NULL) CloseHandle(hKey);
    return true;
}

static bool ServerClose() {
    return true;
}


static bool ServerOpen() {
    return true;

}


static int SelectServerState() {
    return true;

}