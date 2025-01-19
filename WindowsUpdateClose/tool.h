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
		DWORD dataSize = (DWORD)strlen(valueData) + 1; // 包括空终止符
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
	// 设置 wuauserv 的 ImagePath
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\wuauserv", "ImagePath", "%SystemRoot%\\system32\\svchost.exe -k netsvcs -p", REG_EXPAND_SZ);

	// 设置 WaaSMedicSvc 的 ImagePath
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\WaaSMedicSvc", "ImagePath", "%SystemRoot%\\system32\\svchost.exe -k wusvcs -p", REG_EXPAND_SZ);

	// 设置 PushToInstall 的 Start
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\PushToInstall", "Start", "3", REG_DWORD);

	// 设置 TrustedInstaller 的 Start
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\TrustedInstaller", "Start", "3", REG_DWORD);

	// 设置 wuauserv 的 Start
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\wuauserv", "Start", "2", REG_DWORD);

	// 设置 DoSvc 的 Start
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\DoSvc", "Start", "2", REG_DWORD);

	// 覆盖 WaaSMedicSvc 的 Start 为 3
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\WaaSMedicSvc", "Start", "3", REG_DWORD);

	// 设置 UsoSvc 的 Start
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\UsoSvc", "Start", "2", REG_DWORD);

	// 设置 BITS 的 Start
	setRegistryValue("SYSTEM\\ControlSet001\\Services\\BITS", "Start", "3", REG_DWORD);

	// 删除各个注册表值
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", "DisableWindowsUpdateAccess");
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "NoAutoUpdate");
	deleteRegistryValue("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoWindowsUpdate");
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", "DisableOSUpgrade");

	// 注意：这里处理整个键下的所有值，或者如果只想删除特定值，需要指定值名
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft", "WindowsStore"); // 删除整个键（如果需要）
	// 或者如果只想删除某个特定的值（如果有的话），需要知道确切的值名
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\WindowsStore", "SpecificValueName");

	// 由于上述注释中提到没有具体的值名，这里我们暂时跳过或假设删除整个键的操作在别处处理

	deleteRegistryValue("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate", "OSUpgrade");
	deleteRegistryValue("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate", "ReservationsAllowed");
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "AUOptions"); // 自动更新选项
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "ScheduledInstallDay"); // 计划安装日
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "ScheduledInstallTime"); // 计划安装时间
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "UseWUServer"); // 使用 WUServer
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "DetectUpdateInterval"); // 检测更新间隔
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "NoAutoRebootWithLoggedOnUsers"); // 登录用户时不自动重启

	deleteRegistryValue("SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", "SvOfferDeclined"); // 可能会因为“未找到名称”而打印信息
	deleteRegistryValue("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate\\Auto Update", "AUOptions"); // 另一个可能的自动更新选项位置
	deleteRegistryValue("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate\\Auto Update", "ElevationType"); // 升级类型

	// 其他可能的设置
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Windows\\System", "EnableLUA"); // 用户帐户控制 (UAC)
	deleteRegistryValue("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Windows", "DisableCAD"); // 禁用Ctrl+Alt+Delete
	deleteRegistryValue("SOFTWARE\\Policies\\Microsoft\\Internet Explorer\\Main", "DisableFirstRunCustomize"); // IE首次运行自定义

	// BITS 服务相关设置
	deleteRegistryValue("SYSTEM\\ControlSet001\\Services\\BITS", "WubLock"); // 可能会因为“未找到名称”而打印信息
	deleteRegistryValue("SYSTEM\\ControlSet001\\Services\\BITS", "Start"); // BITS服务启动类型


	return true;

}


static int SelectServerState() {
	HKEY hKey = NULL;
	DWORD lResult;
	DWORD value = 0;
    DWORD dwSize = sizeof(value);
	lResult = RegOpenKeyExA(
		HKEY_LOCAL_MACHINE, // 根键
		"SYSTEM\\ControlSet001\\Services\\wuauserv", // 子键路径
		0, // 保留为0
		KEY_READ, // 访问权限
		&hKey // 打开的键的句柄
	);
	if (lResult == ERROR_SUCCESS) {
		lResult = RegQueryValueExA(
			hKey, // 打开的键的句柄
			"Start", // 值名
			NULL, // 保留为NULL
			NULL, // 值类型
			(LPBYTE)&value, // 值数据
			&dwSize // 值数据大小
		);
	}
	if (hKey != NULL)CloseHandle(hKey);
	//4表示关闭
	if (value == 4) {
		return 0;
	}
	//2表示开启
	else if (value == 2) {
		return 1;
	}
	//其他值表示未知
	else {
        return 2;
	}
}