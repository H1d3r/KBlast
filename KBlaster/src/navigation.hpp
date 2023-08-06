#pragma once

// Windows versions
typedef enum _WINDOWS_VERSION
{

    WINDOWS_UNSUPPORTED,
    WINDOWS_REDSTONE_1,		// 14393,
    WINDOWS_REDSTONE_2,		// 15063,
    WINDOWS_REDSTONE_3,		// 16299,
    WINDOWS_REDSTONE_4,		// 17134,
    WINDOWS_REDSTONE_5,		// 17763
    WINDOWS_19H1, 			// 18362
    WINDOWS_19H2,			// 18363
    WINDOWS_20H1,			// 19041
    WINDOWS_20H2,			// 19042
    WINDOWS_21H1,			// 19043
    WINDOWS_21H2,			// 19044
    WINDOWS_22H2            // 19045

} WINDOWS_VERSION, * PWINDOWS_VERSION;

const ULONG EPROCESS_SIGNATURE_LEVEL_OFFSET[] =
{
    0x00,		// WINDOWS_UNSUPPORTED
    0x06C0,   	// WINDOWS_REDSTONE_1
    0x06C8,   	// WINDOWS_REDSTONE_2
    0x06C8,   	// WINDOWS_REDSTONE_3
    0x06C8,   	// WINDOWS_REDSTONE_4
    0x06C8,   	// WINDOWS_REDSTONE_5
    0x06F8,		// WINDOWS_19H1
    0x0878,  	// WINDOWS_19H2
    0x0878,   	// WINDOWS_20H1
    0x0878,   	// WINDOWS_20H2
    0x0878,   	// WINDOWS_21H1
    0x0878,   	// WINDOWS_21H2
    0x0878    	// WINDOWS_22H2
};

const ULONG EPROCESS_ACTIVEPROCESSLINKS_OFFSET[] =
{
    0x00,		// WINDOWS_UNSUPPORTED
    0x02F0,   	// WINDOWS_REDSTONE_1
    0x06CA,   	// WINDOWS_REDSTONE_2
    0x02E8,   	// WINDOWS_REDSTONE_3
    0x02E8,   	// WINDOWS_REDSTONE_4
    0x02E8,   	// WINDOWS_REDSTONE_5
    0x02F0,		// WINDOWS_19H1
    0x0448,  	// WINDOWS_19H2
    0x0448,   	// WINDOWS_20H1
    0x0448,   	// WINDOWS_20H2
    0x0448,   	// WINDOWS_21H1
    0x0448,   	// WINDOWS_21H2
    0x0448    	// WINDOWS_22H2
};

const ULONG EPROCESS_SEAUDITPROCESSCREATIONINFO_OFFSET[] =
{
    0x00,		// WINDOWS_UNSUPPORTED
    0x0468,   	// WINDOWS_REDSTONE_1
    0x0468,   	// WINDOWS_REDSTONE_2
    0x0468,   	// WINDOWS_REDSTONE_3
    0x0468,   	// WINDOWS_REDSTONE_4
    0x0468,   	// WINDOWS_REDSTONE_5
    0x0468,		// WINDOWS_19H1
    0x05C0,  	// WINDOWS_19H2
    0x05C0,   	// WINDOWS_20H1
    0x05C0,   	// WINDOWS_20H2
    0x05C0,   	// WINDOWS_21H1
    0x05C0,   	// WINDOWS_21H2
    0x05C0    	// WINDOWS_22H2
};

const ULONG EPROCESS_TOKEN_OFFSET[] =
{
    0x00,		// WINDOWS_UNSUPPORTED
    0x0358,   	// WINDOWS_REDSTONE_1
    0x0358,   	// WINDOWS_REDSTONE_2
    0x0358,   	// WINDOWS_REDSTONE_3
    0x0358,   	// WINDOWS_REDSTONE_4
    0x0358,   	// WINDOWS_REDSTONE_5
    0x0360,		// WINDOWS_19H1
    0x04B8,  	// WINDOWS_19H2
    0x04B8,   	// WINDOWS_20H1
    0x04B8,   	// WINDOWS_20H2
    0x04B8,   	// WINDOWS_21H1
    0x04B8,   	// WINDOWS_21H2
    0x04B8    	// WINDOWS_22H2
};