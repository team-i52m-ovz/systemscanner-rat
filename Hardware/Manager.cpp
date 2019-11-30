#include "Manager.h"

#include <fstream>
#include <iostream>
#include <string>

#include "SystemRat.h"

#include "WMIParser.h"

std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string>>> globalMap =
{
	{
		"Operating System",
		{
			{
				"Win32_OperatingSystem",
				{
					"Name",
					"BuildNumber",
					"BuildType",
					"CountryCode",
					"CurrentTimeZone",
					"Description",
					"FreePhysicalMemory",
					"FreeSpaceInPagingFiles",
					"FreeVirtualMemory",
					"InstallDate",
					"Manufacturer",
					"MaxNumberOfProcesses",
					"MaxProcessMemorySize",
					"NumberOfLicensedUsers",
					"NumberOfProcesses",
					"NumberOfUsers",
					"Organization",
					"SerialNumber",
					"ServicePackMajorVersion",
					"ServicePackMinorVersion",
					"Status",
					"SystemDevice",
					"SystemDirectory",
					"SystemDrive",
					"TotalVirtualMemorySize",
					"TotalVisibleMemorySize",
					"WindowsDirectory",
					"Version"
				}
			},
			{
				"Win32_ComputerSystem",
				{
					"Name",
					"AdminPasswordStatus",
					"BootupState",
					"Caption",
					"CreationClassName",
					"DNSHostName",
					"Domain",
					"LastLoadInfo",
					"Manufacturer",
					"Model",
					"NetworkServerModeEnabled",
					"NumberOfLogicalProcessors",
					"NumberOfProcessors",
					"PowerManagementSupported",
					"PrimaryOwnerName",
					"SystemFamily",
					"UserName",
					"WakeUpType",
					"Workgroup"
				}
			},
			{
				"Win32_NetworkClient",
				{
					"Name",
					"Manufacturer",
					"Status",
					"InstallDate",
					"Description",
					"Caption"
				}
			},
			{
				"Win32_NetworkConnection",
				{
					"Name",
					"UserName",
					"ResourceType",
					"ProviderName",
					"RemoteName",
					"RemotePath",
					"LocalName",
					"ConnectionType",
					"ConnectionState",
					"AccessMask",
					"InstallDate",
					"Description",
					"Caption",
					"Status"
				}
			},
			{
				"Win32_Registry",
				{
					"Name",
					"Description",
					"CurrentSize",
					"MaximumSize",
					"InstallDate",
					"Status"
				}
			},
			{
				"Win32_UserAccount",
				{
					"Name",
					"FullName",
					"AccountType",
					"Description",
					"LocalAccount",
					"InstallDate",
					"Status",
					"SID",
					"PasswordRequired",
					"PasswordChangeable",
					"PasswordExpires",
					"Lockout"
				}
			},
			{
				"Win32_WindowsProductActivation",
				{
					"ProductID",
					"Description",
					"IsNotificationOn",
					"RemainingEvaluationPeriod",
					"ServerName",
					"RemainingGracePeriod",
					"ActivationRequired"
				}
			}
		}
	},
	{
		"Hardware",
		{
			{
				"Win32_Refrigeration",
				{
					"Name",
					"InstallDate",
					"PowerManagementSupported",
					"DeviceID",
					"Availability",
					"ActiveCooling",
					"ConfigManagerErrorCode"
				}
			},
			{
				"Win32_Keyboard",
				{
					"Name",
					"PowerManagementSupported",
					"Password",
					"NumberOfFunctionKeys",
					"Layout",
					"IsLocked",
					"LastErrorCode",
					"InstallDate",
					"ErrorDescription",
					"DeviceID",
					"Description",
					"Availability"
				}
			},
			{
				"Win32_PointingDevice",
				{
					"Name",
					"Manufacturer",
					"NumberOfButtons",
					"DeviceID",
					"Handedness",
					"HardwareType",
					"IsLocked",
					"InstallDate",
					"PowerManagementSupported",
					"Resolution",
					"Availability",
					"ConfigManagerErrorCode",
					"ErrorDescription"
				}
			},
			{
				"Win32_DiskDrive",
				{
					"Name",
					"Model",
					"Manufacturer",
					"Availability",
					"Description",
					"DeviceID",
					"NeedsCleaning",
					"MaxBlockSize",
					"MediaLoaded",
					"SerialNumber",
					"Signature",
					"Size",
					"TotalCylinders",
					"TotalHeads",
					"TotalSectors",
					"MediaType",
					"Index",
					"CompressionMethod",
					"BytesPerSector",
					"LastErrorCode",
					"ErrorDescription",
					"Description"
				}
			},
			{
				"Win32_BaseBoard",
				{
					"Name",
					"Model",
					"Manufacturer",
					"InstallDate",
					"Weight",
					"Width",
					"Status",
					"SpecialRequirements",
					"SlotLayout",
					"SerialNumber",
					"RequiresDaughterBoard",
					"RequirementsDescription",
					"Removable",
					"Replaceable",
					"Product",
					"PoweredOn",
					"PartNumber",
					"Height",
					"Description",
					"Depth",
					"HostingBoard"
				}
			},
			{
				"Win32_BIOS",
				{
					"Name",
					"Manufacturer",
					"PrimaryBIOS",
					"SerialNumber",
					"LanguageEdition",
					"InstallDate",
					"EmbeddedControllerMinorVersion",
					"EmbeddedControllerMajorVersion",
					"Description",
					"CurrentLanguage",
					"CodeSet",
					"BuildNumber",
					"SoftwareElementID",
					"SystemBiosMajorVersion",
					"SystemBiosMinorVersion",
					"TargetOperatingSystem",
					"Version"
				}
			},
			{
				"Win32_Processor",
				{
					"Name",
					"Manufacturer",
					"MaxClockSpeed",
					"LoadPercentage",
					"Level",
					"NumberOfCores",
					"NumberOfEnabledCore",
					"NumberOfLogicalProcessors",
					"PartNumber",
					"PowerManagementSupported",
					"ProcessorId",
					"ProcessorType",
					"SerialNumber",
					"SocketDesignation",
					"ThreadCount",
					"InstallDate",
					"Family",
					"CurrentVoltage",
					"CpuStatus",
					"AddressWidth",
					"Architecture",
					"ErrorDescription"
				}
			},
			{
				"Win32_SoundDevice",
				{
					"Name",
					"Manufacturer",
					"MPU401Address",
					"InstallDate",
					"DeviceID",
					"PowerManagementSupported",
					"ProductName",
					"DMABufferSize",
					"Availability"
				}
			},
			{
				"Win32_USBController",
				{
					"Name",
					"Manufacturer",
					"InstallDate",
					"PowerManagementSupported",
					"ProtocolSupported",
					"MaxNumberControlled",
					"DeviceID",
					"Description",
					"Status",
					"ErrorDescription"
				}
			},
			{
				"Win32_DesktopMonitor",
				{
					"Name",
					"PowerManagementSupported",
					"ScreenWidth",
					"ScreenHeight",
					"PixelsPerYLogicalInch",
					"PixelsPerXLogicalInch",
					"MonitorManufacturer",
					"IsLocked",
					"DeviceID",
					"Description",
					"Availability"
				}
			}
		}
	},
	{
		"Installed Software",
		{
			{
				"Win32_Product",
				{
					"Name",
					"Vendor",
					"Version",
					"InstallLocation"
				}
			}
		}
	}
};

Manager::Manager()
	: m_networkManager{ JPC::Network::NetworkManager::getInstance() }
{}

void Manager::exec()
{
	std::ifstream inToken{ "token.txt" };
	std::ifstream in{ "host.txt" };
	std::string host{ "" };
	std::string token{ "" };
	in >> host;
	if (host.empty())
	{
		std::cout << "No host!!!Aborting\n";
		return;
	}
	while (!inToken.eof())
	{
		std::string message;
		inToken >> message;
		if (message.empty())
		{
			break;
		}
		token.append(message);
		if(!inToken.eof())
		token.append(" ");
	}
	inToken.close();

	SystemRat::WMIParser wmiParser{ globalMap };
	if (wmiParser.init())
	{
		std::cout << "Error init WMI. Aborting\n";
		return;
	}
	wmiParser.queryData();
	std::string data = wmiParser.generateJson();

	m_networkManager.initialize(host);
	//if (!token.empty())
	{
		m_networkManager.setToken(token);
	}
	if(token.empty())
	{
		std::string newToken;
		const bool rc = m_networkManager.getToken([&newToken](std::string token)
		{
			newToken = token;
		});
		if (!rc)
		{
			std::cout << "failed to receive token.Aborting\n";
		}
		std::ofstream outToken{ "token.txt" };
		outToken << newToken;
		outToken.close();

		m_networkManager.setToken(newToken);
	}

	const bool rc = m_networkManager.sendFile(data);
	if (!rc)
	{
		std::cout << "failed to send json. Aborting\n";
	}
}