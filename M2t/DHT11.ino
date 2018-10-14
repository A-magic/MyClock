unsigned char showTemp[] = { 0xA1, 0xE6 };//摄氏度,℃
unsigned char showHumi[] = { 0x25, 0x52, 0x48 };//%RH

void readDht()
{
	aa:
	int chk = DHT11.read(DHT11PIN);

	switch (chk)
	{
	case DHTLIB_OK:
		Serial.println("OK");
		break;
	case DHTLIB_ERROR_CHECKSUM:
		goto aa;
		Serial.println("Checksum error");
		
		break;
	case DHTLIB_ERROR_TIMEOUT:
		goto aa;
		Serial.println("Time out error");
		break;
	default:
		goto aa;
		Serial.println("Unknown error");
		break;
	}

}
