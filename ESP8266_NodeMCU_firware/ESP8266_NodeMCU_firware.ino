/*Author: Abhishek Shingane
 *Date: 18 02 2020
 * 
 * VERSION: 1.0.0
 * COMMUNICATION_PROTOCOL:1
 * FEATURES IMPLEMENTED
 * [O] Read and Write configuration from eeprom
 * 
 * FEATURES TO BE IMPLEMENTED
 * 
 * 
 * 
 * 
 * FEATURES THAT MAY BE IMPLEMENTED
 * 
 * 
 * 
 * 
 * 
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>



#define ON 1
#define OFF 0

struct Configuration{
  int version;
  char key[8];
  int IO_config[8]; /* 1: DIGITAL INPUT 2: DIGITAL OUTPUT*/
  char router_SSID[20];
  char router_password[20];
  char AP_SSID[20];
  char AP_password[20];
  char server_url[100];
}config;

Configuration read_config_eeprom(){
  Configuration config;
  EEPROM.begin(512);
  if(int(EEPROM.read(0))!= 14){                                               //Value at 0 address  is check byte.
    config.version = 0; //No configuration exists
    Serial.println("[read_config_eeprom] No configuration found");
    return config;                                                               //NO configuration found.
  }
  config.version=EEPROM.read(1);                                               // Get version ID
  for(int addr=2;addr<10;addr++){                                              // Key from 2 to 9 adddress 
    config.key[addr-2]=char(EEPROM.read(addr)); 
  }
  for(int addr=10,i=0;addr<18;i++,addr++){                                             // IO_config saved from 10 to 17
    config.IO_config[i]=int(EEPROM.read(addr));
  }
  for(int addr=20,i=0;addr<40;i++,addr++){
    config.router_SSID[i]=char(EEPROM.read(addr));
    if(char(EEPROM.read(addr))=='\0'){
      break;
    }
  }
  for(int addr=40,i=0;addr<60;i++,addr++){
    config.router_password[i]=char(EEPROM.read(addr));
    if(char(EEPROM.read(addr))=='\0'){
      break;
    }
  }
  for(int addr=60,i=0;addr<80;i++,addr++){
    config.AP_SSID[i]=char(EEPROM.read(addr));
    if(char(EEPROM.read(addr))=='\0'){
      break;
    }
  }
  for(int addr=80,i=0;addr<100;i++,addr++){
    config.AP_password[i]=char(EEPROM.read(addr));
    if(char(EEPROM.read(addr))=='\0'){
      break;
    }
  }

  for(int addr=100,i=0;addr<200;i++,addr++){
    config.server_url[i]=char(EEPROM.read(addr));
    if(char(EEPROM.read(addr))=='\0'){
      break;
    }
  }
  Serial.println("Configuration read");
 // Serial.println("Configuration Read successfully SSID %s password %s",config.router_SSID,config.router_password);
  return config; //Returns NULL if no config found.
}
int write_config_eeprom(Configuration config){
  EEPROM.begin(512);
  EEPROM.write(0,14); //Implies that configuration is valid.
  EEPROM.write(1,config.version);
  for(int addr=2;addr<10;addr++){                                              // Key from 2 to 9 adddress 
    EEPROM.write(addr,config.key[addr-2]); 
  }
  for(int addr=10,i=0;addr<18;i++,addr++){                                             // IO_config saved from 10 to 17
    EEPROM.write(addr,config.IO_config[i]);
  }
  for(int addr=20,i=0;addr<40;i++,addr++){
    EEPROM.write(addr,config.router_SSID[i]);
    if(char(config.router_SSID[i])=='\0'){
      break;
    }
  }
  for(int addr=40,i=0;addr<60;i++,addr++){
    EEPROM.write(addr,config.router_password[i]);
    if(char(config.router_password[i])=='\0'){
      break;
    }
  }
  for(int addr=60,i=0;addr<80;i++,addr++){
    EEPROM.write(addr,config.AP_SSID[i]);
    if(char(config.AP_SSID[i])=='\0'){
      break;
    }
  }
  for(int addr=80, i=0;addr<100;i++,addr++){
    EEPROM.write(addr,config.AP_password[i]);
    if(char(config.AP_password[i])=='\0'){
      break;
    }
  }
  for(int addr=100,i=0;addr<200;i++,addr++){
    EEPROM.write(addr,config.server_url[i]);
    if(char(config.server_url[i])=='\0'){
      break;
    }
  }

  EEPROM.commit();
  return 0;
}

int configure_wifi(Configuration config){
  
}

int configure_pin_mode(Configuration config){

}

int configure(){
  Configuration config = read_config_eeprom();
  configure_pin_mode(config);
  configure_wifi(config);
}



void test_write_config_eeprom(){ /*tests if write_config_eeprom writes to the eeprom correctly*/
  Configuration config;
  config.version=1;
  strcpy(config.key,"ABCDEFG\0");
  for(int i=0;i<8;i++){
    config.IO_config[i]=i*i; 
  }
  strcpy(config.router_SSID,"IITBhilai\0");
  strcpy(config.router_password,"IITBhilaipass\0");
  strcpy(config.AP_SSID,"APSSID\0");
  strcpy(config.AP_password,"pass\0");
  strcpy(config.server_url,"AAAAAAAAAAAAAAAAAAAA\0");
  write_config_eeprom(config);
  return ;
}

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  

}
