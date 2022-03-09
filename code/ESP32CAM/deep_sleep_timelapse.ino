/******
  Author: Benjamin Seleb
  
  This script benefits from work done by Rui Santos (complete project details at 
  https://RandomNerdTutorials.com/esp32-cam-pir-motion-detector-photo-capture/)
 
  IMPORTANT!!!
   - Select Board "AI Thinker ESP32-CAM"
   - GPIO 0 must be connected to GND to upload a sketch
   - After connecting GPIO 0 to GND, press the ESP32-CAM on-board RESET button to put your board in flashing mode

  The following pins are available on the Fieldcam: 
  GPIO 0 - Flash pin, unusable during flash, internally connected to 10k Ohm pull-up resistor 
  GPIO 1 - TX, unusable during flash or when using serial monitor
  GPIO 2 - Available if not using SD card
  GPIO 3 - RX, unusable during flash or when using serial monitor
  GPIO 4 - Front LED, connected to front Flash LED, Available if using SD card in 1-bit mode or not using SD card
  GPIO 12 - Available if using SD Card in 1-bit mode or not using SD card
  GPIO 13 - Available if using SD Card in 1-bit mode or not using SD card
  GPIO 14 - Available if not using SD card
  GPIO 15 - Available if not using SD card
  GPIO 16 - Used with PSRAM, internally connected to 10k Ohm pull-up resistor, not connected to RTC
  GPIO 33 - Rear LED, connected to rear indicator LED with inverted logic, no external connection

  Note that to use SD card and GPIO 4, 12, and 13, 1-bit mode be used when initializing SD card 
  GPIOs 2, 4, 12, 13, 14, and 15 are RTC and support ADC
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/
 
#include "esp_camera.h"
#include "Arduino.h"
#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems
#include "driver/rtc_io.h"
#include <EEPROM.h>            // read and write from flash memory

RTC_DATA_ATTR int bootCount = 0;

void setup() {

  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector

  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL); // disable the wakeup pins

  int interval = 120; // time lapse interval (seconds) 
  
  Serial.begin(115200);
  //Serial.setDebugOutput(true);

  switch(esp_sleep_get_wakeup_cause())
  {
    case ESP_SLEEP_WAKEUP_EXT1: 
      Serial.println("Wakeup caused by external signal using RTC_CNTRL");    
      break;  
         
    case ESP_SLEEP_WAKEUP_EXT0: 
      Serial.println("Wakeup caused by external signal using RTC_IO"); 
      break;
      
    case ESP_SLEEP_WAKEUP_TIMER: // wakeup caused by timer
      Serial.println("Wakeup caused by timer");
      captureImage("bhamla_1_timelapse_Aug5", 1, true); // capture image
      esp_sleep_enable_timer_wakeup(interval * 1000000); // re-enable timer
      break; 
      
    case ESP_SLEEP_WAKEUP_TOUCHPAD: 
      Serial.println("Wakeup caused by touchpad"); 
      break;
      
    case ESP_SLEEP_WAKEUP_ULP: 
      Serial.println("Wakeup caused by ULP program"); 
      break;
      
    default : 
      Serial.println("Wakeup was not caused by deep sleep"); 
      //i.e. startup -- implement special startup?
      captureImage("startup_image", 1, true);
      esp_sleep_enable_timer_wakeup(1 * 1000000);    
      break;
  }

  delay(250); 
  goToSleep(); // call go to sleep function
}
 
void loop() { //This loop only runs in error 
  pinMode(33, OUTPUT);
  digitalWrite(33, LOW); 
  delay(250); 
  digitalWrite(33, HIGH); 
  delay(250); 
}

void captureImage(String camName, int photoCount, bool flash) {
  initCamera(); //initialize OV2640 camera
  delay(1000); //put in a pause for auto exposure? 

  //------------------------------------PRE IMAGE ACQUISITION---------------------------------------
    /***** 
       Specify the GPIO pins to be used before image acquisition. Be careful to stop necessary 
       GPIO required for use image acquistion
    *********/

  //-----------------------------------IMAGE ACQUISITION--------------------------------------------
  for (int i = 1; i <= photoCount; i++) {
    
    // Specify any GPIO pins to be used during image acquisition (i.e. GPIO 4, 12, and 13)

    // Turn on LED before acquiring image
    if(flash) {
      rtc_gpio_hold_dis(GPIO_NUM_4); 
      pinMode(4, OUTPUT); // Controls flash
      digitalWrite(4, HIGH);
    }

    // Determine trigger time (not necessary for timelapse)
    // if(i == 1) Serial.printf("Image captured in %d miliseconds\n", millis());

    camera_fb_t * fb = NULL;
  
    // Take Picture with Camera
    fb = esp_camera_fb_get();  
    if(!fb) {
      Serial.println("Camera capture failed");
      errorOccured();
      return;
    }
  
    // Turn off LED after acquiring image
    if(flash) digitalWrite(4, LOW);

  //-----------------------------------SAVING IMAGE DATA--------------------------------------------

    saveImage(camName, true, fb); 
    esp_camera_fb_return(fb); 
  }
  
  //-----------------------------------POST IMAGE ACQUISITION---------------------------------------
    // Specify the GPIO pins to be used after image acquisition (i.e. GPIO 4, 12, and 13)

  /*pinMode(12, OUTPUT); 
  digitalWrite(12, HIGH); 
  delay(250); 
  digitalWrite(12, LOW); 
  */
}

void initCamera(){
  //Configure Camera
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sscb_sda = 26;
  config.pin_sscb_scl = 27;
  config.pin_pwdn = 32;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
 
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA; // FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // Initialize Camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    errorOccured(); 
    return;
  }
}

void saveImage(String camName, bool bitMode, camera_fb_t* frameBuffer){
  int EEPROM_SIZE = 2; // define the number of bytes you want to access
  int number;
  int multiple;
  
  Serial.println("Starting SD Card"); //Initialize SD Card
  delay(250); 
  
  if(!SD_MMC.begin("/sdcard", true)){ // run the SD card in 1-bit mode -- slower, but more GPIO!
    Serial.println("SD Card Mount Failed");
    errorOccured();
    return;
  }

  uint8_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE){
    Serial.println("No SD Card attached");
    errorOccured();
    return;
  }

  bool reset;
  reset = fileCheck(SD_MMC, "/"); 

  if(reset) {
    Serial.println("resetting EEPROM"); 
    EEPROM.begin(2); // initialize EEPROM with predefined size
    EEPROM.write(0, 0);
    EEPROM.write(1, 0);
    EEPROM.commit();
    EEPROM.end();
  }

  EEPROM.begin(2); // initialize EEPROM with predefined size
  number = EEPROM.read(0)+1;
  multiple = EEPROM.read(1);
  
  if (number == 256){  
    number = 1; 
    multiple++;
  }
  if (multiple == 256) {
    Serial.println("EEPROM Overwritten");
    return; 
  }
  
  // Path where new picture will be saved in SD Card
  String path = "/" + camName + "_" + String(number + (multiple*255)) +".jpg";
 
  fs::FS &fs = SD_MMC;
 
  File file = fs.open(path.c_str(), FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file in writing mode");
    errorOccured();
  } else {
    file.write(frameBuffer->buf, frameBuffer->len); // payload (image), payload length
    Serial.printf("Saved file to path: %s\n", path.c_str());
    EEPROM.write(0, number);
    EEPROM.write(1, multiple);
    EEPROM.commit();
    EEPROM.end(); 
  }
  
  file.close();
}

bool fileCheck(fs::FS &fs, const char * dirname){
    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        errorOccured();
        return false;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        errorOccured();
        return false;
    }
    File file = root.openNextFile();
    file = root.openNextFile(); 
    if(!file){
      Serial.println("Directory is empty of files");
      return true; 
    } else {
      return false; 
    }
}

void goToSleep(){
  //Prepare necessary GPIO pins for deep sleep
  pinMode(4, OUTPUT); 
  digitalWrite(4, LOW); // Turns off the ESP32-CAM white on-board LED (flash)
  rtc_gpio_hold_en(GPIO_NUM_4); // Held low because floating value can drain battery
  
  Serial.println("Going to sleep now"); 
  delay(250);
  esp_deep_sleep_start();
}

void errorOccured(){
  pinMode(33, OUTPUT);
  digitalWrite(33, LOW); 
  delay(250); 
  digitalWrite(33, HIGH); 
  delay(250);
  digitalWrite(33, LOW); 
  delay(250); 
  digitalWrite(33, HIGH);
}
