#include "nfcReader.h"

int main(int argc, const char *argv[])
{
	runCommand("config-pin P9_18 i2c");
	runCommand("config-pin P9_17 i2c");

	nfc_device *pnd;
	nfc_target nt;

	// Allocate only a pointer to nfc_context
	nfc_context *context;

	// Initialize libnfc and set the nfc_context
	nfc_init(&context);
	if (context == NULL)
	{
		printf("Unable to init libnfc (malloc)\n");
		exit(EXIT_FAILURE);
	}

	// Display libnfc version
	const char *acLibnfcVersion = nfc_version();
	(void)argc;
	printf("%s uses libnfc %s\n", argv[0], acLibnfcVersion);

	// Open, using the first available NFC device which can be in order of selection:
	//   - default device specified using environment variable or
	//   - first specified device in libnfc.conf (/etc/nfc) or
	//   - first specified device in device-configuration directory (/etc/nfc/devices.d) or
	//   - first auto-detected (if feature is not disabled in libnfc.conf) device
	pnd = nfc_open(context, NULL);

	if (pnd == NULL)
	{
		printf("ERROR: %s\n", "Unable to open NFC device.");
		exit(EXIT_FAILURE);
	}
	// Set opened NFC device to initiator mode
	if (nfc_initiator_init(pnd) < 0)
	{
		nfc_perror(pnd, "nfc_initiator_init");
		exit(EXIT_FAILURE);
	}

	printf("NFC reader: %s opened\n", nfc_device_get_name(pnd));

	// Poll for a ISO14443A (MIFARE) tag
	const nfc_modulation nmMifare = {
		.nmt = NMT_ISO14443A,
		.nbr = NBR_106,
	};
	if (nfc_initiator_select_passive_target(pnd, nmMifare, NULL, 0, &nt) > 0)
	{
		printf("The following (NFC) ISO14443A tag was found:\n");
		printf("    ATQA (SENS_RES): ");
		print_hex(nt.nti.nai.abtAtqa, 2);
		printf("       UID (NFCID%c): ", (nt.nti.nai.abtUid[0] == 0x08 ? '3' : '1'));
		print_hex(nt.nti.nai.abtUid, nt.nti.nai.szUidLen);
		printf("      SAK (SEL_RES): ");
		print_hex(&nt.nti.nai.btSak, 1);
		if (nt.nti.nai.szAtsLen)
		{
			printf("          ATS (ATR): ");
			print_hex(nt.nti.nai.abtAts, nt.nti.nai.szAtsLen);
		}
	}
	// Close NFC device
	nfc_close(pnd);
	// Release the context
	nfc_exit(context);
	exit(EXIT_SUCCESS);
}

// static int initI2cBus(char *bus, int address)
// {
// 	int i2cFileDesc = open(bus, O_RDWR);
// 	if (i2cFileDesc < 0)
// 	{
// 		printf("I2C DRV: Unable to open bus for read/write (%s)\n", bus);
// 		perror("Error is:");
// 		exit(-1);
// 	}

// 	int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
// 	if (result < 0)
// 	{
// 		perror("Unable to set I2C device to slave address.");
// 		exit(-1);
// 	}
// 	return i2cFileDesc;
// }

// void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value)
// {
// 	unsigned char buff[2];
// 	buff[0] = regAddr;
// 	buff[1] = value;
// 	int res = write(i2cFileDesc, buff, 2);
// 	if (res != 2)
// 	{
// 		perror("I2C: Unable to write i2c register.");
// 		exit(1);
// 	}
// }

// static unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr)
// {
// 	// To read a register, must first write the address
// 	int res = write(i2cFileDesc, &regAddr, sizeof(regAddr));
// 	if (res != sizeof(regAddr))
// 	{
// 		perror("Unable to write i2c register.");
// 		exit(-1);
// 	}

// 	// Now read the value and return it
// 	char value = 0;
// 	res = read(i2cFileDesc, &value, sizeof(value));
// 	if (res != sizeof(value))
// 	{
// 		perror("Unable to read i2c register");
// 		exit(-1);
// 	}
// 	return value;
// }

static void print_hex(const uint8_t *pbtData, const size_t szBytes)
{
	size_t szPos;
	for (szPos = 0; szPos < szBytes; szPos++)
	{
		printf("%02x  ", pbtData[szPos]);
	}
	printf("\n");
}

void runCommand(char *command)
{
	// Execute the shell command (output into pipe)
	FILE *pipe = popen(command, "r");
	// Ignore output of the command; but consume it
	// so we don't get an error when closing the pipe.
	char buffer[1024];
	while (!feof(pipe) && !ferror(pipe))
	{
		if (fgets(buffer, sizeof(buffer), pipe) == NULL)
			break;
		// printf("--> %s", buffer); // Uncomment for debugging
	}
	// Get the exit code from the pipe; non-zero is an error:
	int exitCode = WEXITSTATUS(pclose(pipe));
	if (exitCode != 0)
	{
		perror("Unable to execute command:");
		printf(" command: %s\n", command);
		printf(" exit code: %d\n", exitCode);
	}
}