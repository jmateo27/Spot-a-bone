#include "includes/nfcReader.h"



tagWithUID tagDatabase[] = {
	{{1, true}, {0x04, 0x86, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{2, true}, {0x04, 0x87, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{3, true}, {0x04, 0x85, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{4, true}, {0x04, 0x84, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{5, true}, {0x04, 0x83, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{6, true}, {0x04, 0x82, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{7, true}, {0x04, 0x81, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{8, true}, {0x04, 0x9a, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{9, true}, {0x04, 0x80, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{10, true}, {0x04, 0x7f, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{1, false}, {0x04, 0x7e, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{2, false}, {0x04, 0x7d, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{3, false}, {0x04, 0x7c, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{4, false}, {0x04, 0x7b, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{5, false}, {0x04, 0x79, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{6, false}, {0x04, 0x7a, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{7, false}, {0x04, 0x77, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{8, false}, {0x04, 0x75, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{9, false}, {0x04, 0x76, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	{{10, false}, {0x04, 0x78, 0x6a, 0xb1, 0x70, 0x00, 0x00}},
	};

int numTags = 20;

void NFC_init(NFC_descriptor *desc)
{
	// Initialize libnfc and set the nfc_context
	nfc_init(&(desc->cont));
	if (desc->cont == NULL)
	{
		printf("Unable to init libnfc (malloc)\n");
		exit(EXIT_FAILURE);
	}

	// Open, using the first available NFC device which can be in order of selection:
	//   - default device specified using environment variable or
	//   - first specified device in libnfc.conf (/etc/nfc) or
	//   - first specified device in device-configuration directory (/etc/nfc/devices.d) or
	//   - first auto-detected (if feature is not disabled in libnfc.conf) device
	desc->dev = nfc_open(desc->cont, NULL);

	if (desc->dev == NULL)
	{
		printf("ERROR: %s\n", "Unable to open NFC device.");
		exit(EXIT_FAILURE);
	}
	// Set opened NFC device to initiator mode
	if (nfc_initiator_init(desc->dev) < 0)
	{
		nfc_perror(desc->dev, "nfc_initiator_init");
		exit(EXIT_FAILURE);
	}

	printf("NFC reader: %s initialized.\n", nfc_device_get_name(desc->dev));
	return;
}

void NFC_poll(NFC_descriptor *desc, tag* theTag)
{
	// Poll for a ISO14443A (MIFARE) tag
	const nfc_modulation nmMifare = {
		.nmt = NMT_ISO14443A,
		.nbr = NBR_106,
	};
	tag nullTag = {0, false};

	if (nfc_initiator_select_passive_target(desc->dev, nmMifare, NULL, 0, &(desc->targ)) > 0)
	{
		NFC_findOutWhichTag((desc->targ).nti.nai.abtUid, (desc->targ).nti.nai.szUidLen, theTag);
	}
	else{
		*theTag = nullTag;
	}
}

void NFC_cleanup(NFC_descriptor *desc)
{
	// Close NFC device
	nfc_close(desc->dev);
	// Release the context
	nfc_exit(desc->cont);
}

void NFC_findOutWhichTag(const uint8_t *pbtData, const size_t szBytes, tag* theTag)
{
	size_t szPos;
	bool equal = true;
	for (int i = 0; i < numTags; i++)
	{
		equal = true;
		for (szPos = 0; szPos < szBytes; szPos++)
		{
			if (pbtData[szPos] != tagDatabase[i].UID[szPos])
			{
				equal = false;
				break;
			}
		}
		if (equal)
		{
			*theTag = tagDatabase[i].theTag;
			//return i + 1;
			return;
		}
	}
}

// void NFC_queueUp(int tagNum)
// {
// 	FILE *pFile;
// 	while ((pFile = fopen(queueFileName, "ab")) == NULL); // Wait if cannot open... (somewhat like a mutex)

// 	char toWrite[maxTagTens];
// 	sprintf(toWrite, "s%d\n", tagNum);
// 	fprintf(pFile, toWrite);

// 	fclose(pFile);
// }