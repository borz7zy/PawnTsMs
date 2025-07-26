#if defined _PAWN_TS_MS
	#endinput
#endif
#define _PAWN_TS_MS

native GetTsString(myString[], size = sizeof(myString));
native GetTsStringFormatted(myString[], size = sizeof(myString));
native ParseMyTs(const myTs[], myString[], size = sizeof(myString));