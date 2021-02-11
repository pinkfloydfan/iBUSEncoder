//Very simple C++ code for writing IBUS. I've implemented this on an ESP32 as a part of my capstone project. 
//Major credits to the authors of: http://blog.dsp.id.au/posts/2017/10/22/flysky-ibus-protocol/ and https://basejunction.wordpress.com/2015/08/23/en-flysky-i6-14-channels-part1/
//iBUS consists of a 32-byte array, with two header bytes, 14 pairs of bytes in little endian containing channel values (1000-2000), and two bytes at the end as a checksum.
//The checksum is equal to 0xFFFF minus the value of bytes 1 to 30. 
//The data frame is sent every 7 milliseconds or so. 
//This code is not intended to compile on anything specific, nor is it efficient or elegant. However in the future if I get time I'll see if I can write it into a library. 


const int ibusPacketLength = 32; 
const int rcChannelNumber = 14;

//iBus theoretically supports 14 channels
int rcChannels[14] = {1500, 1400, 1300, 1200, 1100, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500}; 
uint8_t ibusPacket [ibusPacketLength];
uint32_t ibusTime = 0;

void prepareibusPacket() {

  //loop along the array of RC channels, and convert each value into two little endian bytes. 
  for (int i = 0; i < rcChannelNumber; i++) {
    uint16_t channelValue = rcChannels[i];

    //little endian conversiom
    uint8_t byte0 = channelValue % 256;
    uint8_t byte1 = channelValue / 256;

    ibusPacket[2*i + 2] = byte0;
    ibusPacket[2*i + 3] = byte1;
  }
  uint16_t total = 0xFFFF; 
  //for calculating checksum - use 0xFFFF and subtract each byte from i = 0 -> i = packetlength-2 from it 
  for (int i = 0; i<ibusPacketLength-2; i++) {
    total -= ibusPacket[i];
  }
  uint8_t checksumByte0 = total % 256;
  uint8_t checksumByte1 = total / 256;

  //write checksum to last two bytes
  ibusPacket[ibusPacketLength-2] = checksumByte0;
  ibusPacket[ibusPacketLength-1] = checksumByte1;

}

void loop() {
  
    uint32_t currentMillis = millis();

    /*
     * Here you can modify values of rcChannels while keeping it in 1000:2000 range
     */
    
      if (currentMillis > ibusTime) {
        prepareibusPacket() ;

        Serial1.write(ibusPacket, ibusPacketLength);

        ibusTime = currentMillis + 7;
    }






  // Look for and handle WebSocket data - disabled just in case this was interfering with sbus
  //webSocket.loop();
}