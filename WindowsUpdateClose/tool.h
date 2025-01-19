#include <Windows.h>

static bool RegSetting() {
	const char* sub_key = "SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings";
	DWORD value = 65536;
	HKEY hKey = NULL;
	DWORD ret = false;
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, sub_key, &hKey);
	if (ret != ERROR_SUCCESS) {
		return false;
	}
	ret = RegSetKeyValueA(hKey, NULL, "FlightSettingsMaxPauseDays", REG_DWORD, &value, REG_DWORD);
	if (ret != ERROR_SUCCESS) {
		return false;
	}
	if (hKey != NULL) CloseHandle(hKey);
	return true;
}

static bool ServerClose() {
	HKEY hKey;
	LONG ret;
	DWORD value = 1;
	DWORD data_0 = 0;
	const char str_value[] = "localserver.localdomain.wsus";
	const char* str_value_2 = "wsus.localdomain.localserver";
	const char* debugger_value = "/";

	// DisableWindowsUpdateAccess
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", &hKey);
	if (ret == ERROR_SUCCESS) {
		value = 0x1;
		ret = RegSetKeyValueA(hKey, NULL, "DisableWindowsUpdateAccess", REG_DWORD, &value, sizeof(value));
		RegCloseKey(hKey);
	}

	// NoAutoUpdate
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", &hKey);
	if (ret == ERROR_SUCCESS) {
		value = 0x1;
		ret = RegSetKeyValueA(hKey, NULL, "NoAutoUpdate", REG_DWORD, &value, sizeof(value));
		RegCloseKey(hKey);
	}

	// NoWindowsUpdate
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", &hKey);
	if (ret == ERROR_SUCCESS) {
		value = 0x1;
		ret = RegSetKeyValueA(hKey, NULL, "NoWindowsUpdate", REG_DWORD, &value, sizeof(value));
		RegCloseKey(hKey);
	}

	// DisableOSUpgrade
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", &hKey);
	if (ret == ERROR_SUCCESS) {
		value = 0x1;
		ret = RegSetKeyValueA(hKey, NULL, "DisableOSUpgrade", REG_DWORD, &value, sizeof(value));
		RegCloseKey(hKey);
	}

	// WindowsStore (assuming REG_DWORD with value 1)
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows", &hKey);
	if (ret == ERROR_SUCCESS) {
		value = 0x1;
		ret = RegSetKeyValueA(hKey, NULL, "WindowsStore", REG_DWORD, &value, sizeof(value));
		RegCloseKey(hKey);
	}

	// OSUpgrade
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate", &hKey);
	if (ret == ERROR_SUCCESS) {
		data_0 = 0x0;
		ret = RegSetKeyValueA(hKey, NULL, "OSUpgrade", REG_DWORD, &data_0, sizeof(data_0));
		RegCloseKey(hKey);
	}

	// ReservationsAllowed
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate", &hKey);
	if (ret == ERROR_SUCCESS) {
		data_0 = 0x0;
		ret = RegSetKeyValueA(hKey, NULL, "ReservationsAllowed", REG_DWORD, &data_0, sizeof(data_0));
		RegCloseKey(hKey);
	}

	// DoNotConnectToWindowsUpdateInternetLocations
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", &hKey);
	if (ret == ERROR_SUCCESS) {
		value = 0x1;
		ret = RegSetKeyValueA(hKey, NULL, "DoNotConnectToWindowsUpdateInternetLocations", REG_DWORD, &value, sizeof(value));
		RegCloseKey(hKey);
	}

	// UseWUServer
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", &hKey);
	if (ret == ERROR_SUCCESS) {
		value = 0x1;
		ret = RegSetKeyValueA(hKey, NULL, "UseWUServer", REG_DWORD, &value, sizeof(value));
		RegCloseKey(hKey);
	}

	// WUServer
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", &hKey);
	if (ret == ERROR_SUCCESS) {
		ret = RegSetValueExA(hKey, "WUServer", 0, REG_SZ, (const BYTE*)str_value, sizeof(str_value));
		RegCloseKey(hKey);
	}

	// WUStatusServer
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", &hKey);
	if (ret == ERROR_SUCCESS) {
		ret = RegSetValueExA(hKey, "WUStatusServer", 0, REG_SZ, (const BYTE*)str_value, sizeof(str_value));
		RegCloseKey(hKey);
	}

	// UpdateServiceUrlAlternate
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", &hKey);
	if (ret == ERROR_SUCCESS) {
		ret = RegSetValueExA(hKey, "UpdateServiceUrlAlternate", 0, REG_SZ, (const BYTE*)str_value_2, strlen(str_value_2) + 1);
		RegCloseKey(hKey);
	}

	// TrayIconVisibility
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", &hKey);
	if (ret == ERROR_SUCCESS) {
		data_0 = 0x0;
		ret = RegSetKeyValueA(hKey, NULL, "TrayIconVisibility", REG_DWORD, &data_0, sizeof(data_0));
		RegCloseKey(hKey);
	}

	// wuauserv Start
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Services\\wuauserv", &hKey);
	if (ret == ERROR_SUCCESS) {
		value = 0x4; // Changed to 4 in the last entry
		ret = RegSetKeyValueA(hKey, NULL, "Start", REG_DWORD, &value, sizeof(value));
		RegCloseKey(hKey);
	}

	// wuauserv ImagePath
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Services\\wuauserv", &hKey);
	if (ret == ERROR_SUCCESS) {
		const char* image_path = "%SystemRoot%\\system32\\svchost.exe -k wusvcs -p";
		ret = RegSetValueExA(hKey, "ImagePath", 0, REG_EXPAND_SZ, (const BYTE*)image_path, strlen(image_path) + 1);
		RegCloseKey(hKey);
	}

	// PushToInstall Start
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Services\\PushToInstall", &hKey);
	if (ret == ERROR_SUCCESS) {
		value = 0x3;
		ret = RegSetKeyValueA(hKey, NULL, "Start", REG_DWORD, &value, sizeof(value));
		RegCloseKey(hKey);
	}

	// TrustedInstaller Start
	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Services\\TrustedInstaller", &hKey);
	if (ret == ERROR_SUCCESS) {
		value = 0x3;
		RegSetKeyValueA(hKey, NULL, "Start", REG_DWORD, &value, sizeof(value));
		RegCloseKey(hKey);
	}


	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Services\\wuauserv", &hKey);
	if (ret == ERROR_SUCCESS) {
		value = 0x4;
		ret = RegSetKeyValueA(hKey, NULL, "Start", REG_DWORD, &value, sizeof(value));
		RegCloseKey(hKey);
	}

	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Services\\wuauserv", &hKey);
	if (ret == ERROR_SUCCESS) {
		value = 0x1;
		ret = RegSetKeyValueA(hKey, NULL, "WubLock", REG_DWORD, &value, sizeof(value));
		RegCloseKey(hKey);
	}

	ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Services\\DoSvc", &hKey);
	if (ret == ERROR_SUCCESS) {
		value = 0x4;
		ret = RegSetKeyValueA(hKey, 0, "Start", REG_DWORD, &value, sizeof(value));
		RegCloseKey(hKey);
	}
	return true;
}


static void setRegistryValue(const char* subKey, const char* valueName, const char* valueData, DWORD dataType) {
	HKEY hKey = NULL;
	LONG ret = RegCreateKeyA(HKEY_LOCAL_MACHINE, subKey, &hKey);
	if (ret == ERROR_SUCCESS) {
		DWORD dataSize = (DWORD)strlen(valueData) + 1; // ��������ֹ��
		ret = RegSetValueExA(hKey, valueName, 0, dataType, (const BYTE*)valueData, dataSize);
	}
	if (hKey != NULL)RegCloseKey(hKey);
}

static void deleteRegistryValue(const char* subKey, const char* valueName) {
	HKEY hKey = NULL;
	LONG ret = RegOpenKeyA(HKEY_LOCAL_MACHINE, subKey, &hKey);
	if (ret == ERROR_SUCCESS) {
		ret = RegDeleteValueA(hKey, valueName);
	}
	if (hKey != NULL)RegCloseKey(hKey);
}


static bool ServerOpen() {
	// ���� wuauserv �� ImagePath
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\wuauserv", "ImagePath", "%SystemRoot%\\system32\\svchost.exe -k netsvcs -p", REG_EXPAND_SZ);

	// ���� WaaSMedicSvc �� ImagePath
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\WaaSMedicSvc", "ImagePath", "%SystemRoot%\\system32\\svchost.exe -k wusvcs -p", REG_EXPAND_SZ);

	// ���� PushToInstall �� Start
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\PushToInstall", "Start", "3", REG_DWORD);

	// ���� TrustedInstaller �� Start
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\TrustedInstaller", "Start", "3", REG_DWORD);

	// ���� wuauserv �� Start
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\wuauserv", "Start", "2", REG_DWORD);

	// ���� DoSvc �� Start
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\DoSvc", "Start", "2", REG_DWORD);

	// ���� WaaSMedicSvc �� Start Ϊ 3
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\WaaSMedicSvc", "Start", "3", REG_DWORD);

	// ���� UsoSvc �� Start
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\UsoSvc", "Start", "2", REG_DWORD);

	// ���� BITS �� Start
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\BITS", "Start", "3", REG_DWORD);

	// ɾ������ע���ֵ
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", "DisableWindowsUpdateAccess");
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "NoAutoUpdate");
	deleteRegistryValue("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoWindowsUpdate");
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", "DisableOSUpgrade");

	// ע�⣺���ﴦ���������µ�����ֵ���������ֻ��ɾ���ض�ֵ����Ҫָ��ֵ��
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft", "WindowsStore"); // ɾ���������������Ҫ��
	// �������ֻ��ɾ��ĳ���ض���ֵ������еĻ�������Ҫ֪��ȷ�е�ֵ��
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\WindowsStore", "SpecificValueName");

	// ��������ע�����ᵽû�о����ֵ��������������ʱ���������ɾ���������Ĳ����ڱ𴦴���

	deleteRegistryValue("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate", "OSUpgrade");
	deleteRegistryValue("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate", "ReservationsAllowed");
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "AUOptions"); // �Զ�����ѡ��
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "ScheduledInstallDay"); // �ƻ���װ��
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "ScheduledInstallTime"); // �ƻ���װʱ��
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "UseWUServer"); // ʹ�� WUServer
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "DetectUpdateInterval"); // �����¼��
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "NoAutoRebootWithLoggedOnUsers"); // ��¼�û�ʱ���Զ�����

	deleteRegistryValue("SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", "SvOfferDeclined"); // ���ܻ���Ϊ��δ�ҵ����ơ�����ӡ��Ϣ
	deleteRegistryValue("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate\\Auto Update", "AUOptions"); // ��һ�����ܵ��Զ�����ѡ��λ��
	deleteRegistryValue("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate\\Auto Update", "ElevationType"); // ��������

	// �������ܵ�����
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\System", "EnableLUA"); // �û��ʻ����� (UAC)
	deleteRegistryValue("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Windows", "DisableCAD"); // ����Ctrl+Alt+Delete
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Main", "DisableFirstRunCustomize"); // IE�״������Զ���

	// BITS �����������
	deleteRegistryValue("SYSTEM\\ControlSet001\\Services\\BITS", "WubLock"); // ���ܻ���Ϊ��δ�ҵ����ơ�����ӡ��Ϣ
	deleteRegistryValue("SYSTEM\\ControlSet001\\Services\\BITS", "Start"); // BITS������������


	return true;

}


static int SelectServerState() {
	HKEY hKey = NULL;
	DWORD lResult;
	DWORD value = 0;
    DWORD dwSize = sizeof(value);
	lResult = RegOpenKeyExA(
		HKEY_LOCAL_MACHINE, // ����
		"SYSTEM\\ControlSet001\\Services\\wuauserv", // �Ӽ�·��
		0, // ����Ϊ0
		KEY_READ, // ����Ȩ��
		&hKey // �򿪵ļ��ľ��
	);
	if (lResult == ERROR_SUCCESS) {
		lResult = RegQueryValueExA(
			hKey, // �򿪵ļ��ľ��
			"Start", // ֵ��
			NULL, // ����ΪNULL
			NULL, // ֵ����
			(LPBYTE)&value, // ֵ����
			&dwSize // ֵ���ݴ�С
		);
	}
	if (hKey != NULL)CloseHandle(hKey);
	//4��ʾ�ر�
	if (value == 4) {
		return 0;
	}
	//2��ʾ����
	else if (value == 2) {
		return 1;
	}
	//����ֵ��ʾδ֪
	else {
        return 2;
	}
}