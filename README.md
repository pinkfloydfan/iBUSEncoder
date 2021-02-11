# iBUSEncoder
Super-simple C++ code for encoding a serial FlySky iBUS signal, in order to (for example) interface with Betaflight flight controllers.

# Background
It's difficult to find coherent documentation for various serial receiver protocols online. Common ways of interfacing with a flight controller include Futaba SBUS, iBUS and PPM. SBUS requires a lot of muckery with inverting UARTs, and PPM may require more advanced microcontroller knowledge and working with interrupts and timers, making it difficult to write code which accepts various microcontroller architectures. Out of all serial protocols, iBUS is perhaps the simplest, yet afaik there isn't yet a library that encodes iBUS signals (however there are plenty that read them). Here's some sample code to demonstrate how to generate a iBUS signal. 

# iBUS protocol overview 
See the following material:
- http://blog.dsp.id.au/posts/2017/10/22/flysky-ibus-protocol/ 
- https://basejunction.wordpress.com/2015/08/23/en-flysky-i6-14-channels-part1/
These were my main sources of information.
TL;DR: The iBUS protocol consists of 32 bytes. The first 2 bytes are header information, while the last two bytes are a checksum. It's capable of encoding 14 channels as pairs of little-endian bytes.
I haven't yet had the chance to make this a working library. 

# iBUS protocol overview 
Refer to https://www.propwashed.com/ibus-betaflight-guide/#:~:text=Betaflight%20configuration%20with%20iBUS%20receivers,the%20%E2%80%9CSerial%20Receiver%20Provider%E2%80%9D.
Plug whatever pin you're Serial.write-ing into an RX pin of your flight controller, and set up the rest in Betaflight as per the article. 
