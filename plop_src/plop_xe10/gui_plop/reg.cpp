// reg.cpp : Defines the entry point for the console application.
//


// QueryKey - Enumerates the subkeys of key and its associated values.
//     hKey - Key whose subkeys and values are to be enumerated.

#include <windows.h>
#include <stdio.h>
#include <shlwapi.h>
// #include <char.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
 

void read_reg_val (char *key, char *subkey, char *val)
{
   HKEY hTestKey;
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
	DWORD    cbMaxSubKey;              // longest subkey size
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
	FILETIME ftLastWriteTime;      // last write time

	TCHAR valuestring [100];
	DWORD vallen = 100;
 
    DWORD i, retCode; 

    TCHAR  achValue[MAX_VALUE_NAME]; 
    DWORD cchValue = MAX_VALUE_NAME; 

   if( RegOpenKeyEx( HKEY_LOCAL_MACHINE,
        TEXT (key),
		(unsigned long) subkey,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
      )
      {

		achValue[0] = '\0';
		retCode = RegEnumValue(hTestKey,
			0,
			achValue,
			&cchValue,
			NULL,
			NULL,
			(LPBYTE)val,
			&vallen);
   }
   
   RegCloseKey(hTestKey);
}

