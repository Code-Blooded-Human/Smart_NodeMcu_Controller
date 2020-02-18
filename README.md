# Smart_NodeMcu_Controller
Firmware for Nodemcu based on Esp8266 to control the GPIO pins remotely.


## Syntax for protocol
Type: POST/JSON
JSON Structure for request
	{
		type:"REQ",
		mac-id:"",
		method:"", // [READ,WRITE,READ_CONFIG,WRITE_CONFIG,PING]
		content:"", // Defined in content section
		signature:""
	}


JSON Structure for response
	{
		type:"RES",
		status:"" //status code of req
		response:""
		signature:""
	}

##Structure of EEPROM
Bytewise array
[0] Version
[2:9] Key
[10:17] I/O Operation [input or output]
[18:19] buffer
[20:39] External Wifi SSID ends with \0
[40:59] Password
[60:79] AP SSID : Default will be macAddress without colons
[80:99] AP Password : Default will be reverse of mac id without colons
[100:149] Server endpoint, ends with \0



## Parts of firmware
### ON FIRST BOOT
	The nodemcu detects first boot and starts in AP mode and waits for configuration to be done, once done it reboots.

### ON Reboot 
	The device Reads  from server pin status for output pins  and accordingly turns them off.

### After reboot
	Nodemcu listens on port 80 for messages.