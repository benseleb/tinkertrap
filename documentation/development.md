# Device Development

- [1. Motivation](#1-motivation)
  - [1.1. Traditional Camera Traps](#11-traditional-camera-traps)
  - [1.2. Basic Features](#12-basic-features)
  - [1.3. Limitations](#13-limitations)
- [2. TinkerTrap](#2-tinkertrap)
  - [2.1. The Idea](#21-the-idea)
- [3. Stages](#3-development-stages)
  - [3.1. Baby's First FPGA](#31-babys-first-fpga)
  - [3.2. A Proof-of-Concept](#32-a-proof-of-concept)
  - [3.3. Hijacking the ESP32-S3-EYE](#33-hijacking-the-esp32-s3-eye)
  - [3.4. Build-your-own P(CB)izza](#34-build-your-own-pcbizza)
- [4. Related Documents](#4-related-documents)
  - [4.1. Internal Development](#41-internal-development)
  - [4.2. Further Resources](#42-further-resources)

# 1. Motivation

## 1.1. Traditional Camera Traps

Camera traps, or remotely triggered cameras, have become an incredibly popular tool among ecologists and other wildlife professionals, despite being designed predominantly for hunters to observe game animals. At the most basic level, the modern camera trap can be described simply as a digital camera connected to an infrared sensor which can automatically detect animals [[1](https://www.wwf.org.uk/sites/default/files/2019-04/CameraTraps-WWF-guidelines.pdf)]. Typically mounted on trees or other natural supports in order to capture images of passing wildlife, they have been proven useful for detecting cryptic species, identifying species distributions, documenting predation, monitoring behavior, and estimating population sizes.

## 1.2. Basic Features

Camera traps must be able to take images at night. Thus they are all equipped with IR LEDs. Most camera traps use an IR-cut filter mechanism to push and pull a sliding filter over the sensor, depending on whether daytime or nighttime images are needed (left image). An alternative solution is to use two sensors, one with the IR-cut filter permanently installed, and the other without. This has the benefit of reducing any noise coming from an IR-filter mechanism (typically an audible 'click'), and also could enable instantaneous IR functionality if needed.

<!-- Pictures of different camera trap sensors styles -->
![image](https://user-images.githubusercontent.com/65932258/155892610-f3db632b-6c32-4226-8605-91e6cd289c6d.png)
![image](https://user-images.githubusercontent.com/65932258/155892611-fcf6a534-fce5-4e54-a185-3a26e2c26253.png)

All camera traps use a passive-infrared sensor to detect animals, typically an LHI 968 or equivalent. 

<!-- LHI968 PIR sensor -->
![image](https://user-images.githubusercontent.com/65932258/155892557-76a5c4f6-6fcc-43d8-a4f5-714e1c366b75.png) 

All camera traps include some kind of onboard user-interface in order to apply settings. Reconyx, one of the most respected camera trap manufacturers, only implements a two-line text display, and 5 buttons for control (left). Many other camera traps use an OLED display to enable immediate image/video review, typically for an added cost (center). The Bushnell NatureView camera trap (right) actually comes with a peripheral plug-in OLED display for framing/review. 

<!-- Different onboard interfaces -->
![image](https://user-images.githubusercontent.com/65932258/155892908-e3d788eb-f9a1-4162-ad46-1b51dd2c8639.png)
![image](https://user-images.githubusercontent.com/65932258/155892954-47e3e85a-76bf-4751-853c-d84cd42b065b.png)
![image](https://user-images.githubusercontent.com/65932258/155892979-205a4579-a8c5-421e-b97d-0051beafe76c.png)

OTS camera traps seem to be using the same (or similar) chipsets that are mass-produced and well guarded in terms of firmware. Thus, most camera traps share the same standard features. 

To get an idea of required features (and some hopeful improvements/additions), Meek and Pettit published a review in 2012, with [user-based design specifications for the ultimate camera trap for wildlife research](https://bioone.org/journals/wildlife-research/volume-39/issue-8/WR12138/User-based-design-specifications-for-the-ultimate-camera-trap-for/10.1071/WR12138.short).

##### BASIC CAMERA TRAP REQUIREMENTS
| FEATURE | TECHNICAL REQUIREMENT |
| :--- | :---: |
| TRIGGER TIME | < 0.5 s |
| BATTERY LIFE | > 80 d |
| RESOLUTION | > 2 MP |
| TIME STAMP | minute resolution |
| WATERPROOF | IP66 |

##### Other functional requirements: 
- Minimally programmable via an onboard interface
- Scalable sensitivity
- IR illumination
  
## 1.3. Limitations

Despite their ubiquity, commercial camera traps (CCTs) have critical limitations that present challenges for the study of certain species, habitats, and/or the behavior of interest. This is because wildlife researchers merely co-opt the tool from hunters, often having to stretch its capabilities to identify, assess abundance, and monitor the behavior of species. CCTs can only be stretched so far; they lack customizability for unique applications, and hardware limitations like fixed focal distances and thermally activated passive-infrared (PIR) sensors make them ill-suited for taxa other than larger mammals and birds (>1 kg). There is a growing need in the wildlife research community for a less restricted platform to facilitate unique studies and to enable modification for the reliable sampling of small animals—particularly reptiles, amphibians, and invertebrates. Besides being exclusive to medium to large sized mammals, CCTs also limit users to a basic triggering protocol and finite imaging options. 
In some cases, extensive modification of camera trap hardware and setup can improve effectiveness. The camera overhead augmented temperature (COAT) method is one such modification, but it typically voids any product warranty, has the potential to destroy an expensive piece of equipment, and only slightly enhances the functionality of the device. 
Other than a few intracacies, the base functionality of a camera trap is rather simple. In recent years, a few innovative solutions to the tool gap presented by CCTs have been proposed. In an attempt to address the restrictions of the traditional camera trap model, and in order to expand the usefulness of this very important tool, many have proposed the use of open-source electronic prototyping platforms. [[2](https://journals.plos.org/plosone/article?id=10.1371/journal.pone.0169758),[3](https://dl.acm.org/doi/10.1145/3290605.3300532),[4](https://www.sciencedirect.com/science/article/pii/S2468067220300195),[5](https://onlinelibrary.wiley.com/doi/full/10.1002/ece3.3040)]. These controllers have the capability to offer the user complete control over the imaging procedure of a camera trap while also offering compatibility with multiple sensors. Also, by weighing the input of multiple sensors in complex ways, it’s possible that open-source microcontrollers could expand camera trap functionality even further. 
Though many of these proposed platforms have been shown to offer added functionality over CCTs, they overlook fundamental requirements in cost, usability, and battery life, preventing their broader adoption. Proposed solutions are often more expensive than budget CCTs, which are <$250 USD and still prohibitively costly to many researchers; Proposed solutions have steep learning curves, poor resistance to field conditions, and require greater infrastructure to take advantage of added functionality; Proposed solutions often also sacrifice battery life to use power-hungry, software-based detection methods, like pixel change detection, and enable utilization of inefficient, electronic prototyping platforms like Raspberry Pi. 
All of this combined with the fact that open-source designs are not created with reproducability in mind, most previous efforts have been abandoned or implemented only as educational tools. Akiba and Alasdair give a brief description of existing camera trap hardware and more realistic OS design options in this [WILDLABS discussion](https://www.wildlabs.net/community/thread/694).

# 2. TinkerTrap

## 2.1. The Idea
To date, there is still no open-source camera trap platform to have seen widespread adoption within the wildlife research community. The goal of TinkerTrap is to overcome the restrictions of CCTs while avoiding pitfalls of previous OS solutions. For that to happen, it must be programmable and modular in order to allow the use of custom protocol, alternative sensors, and operation of simple peripherals (like lights or motors). High-level programming should not require an in-depth knowledge of programming languages or features, and altering sensors shouldn't require a soldering iron. Conversely, it should offer out-of-the-box CCT functionality for those that require it, maintaining essential features of CCTs such as long battery life and fast trigger time. All of these needs should be met  in a device that is reproducable and accessible. Lastly, the hope is to provide the barebones version of this platform at the lowest cost possible (assuming small batch orders of less than 20 units).
I would also like to design an assortment of plug-in modules (**a**) to provide a simple starting point for the integration of alternative trigger methods (besides PIR), new sensors and peripherals, various power sources, and wireless communication. For those that may be uncomfortable diving into IDEs and command lines, I’d like to prvide a graphical user interface (**b**) as a simplified, streamlined option for custom configuration.
<!-- sketch of plug-in modules and GUI -->
![image](https://user-images.githubusercontent.com/65932258/157113122-8268e6e8-5257-4f78-927a-15eac496159f.png)

# 3. Development Stages

## 3.1. Baby's First FPGA

Based on some of the options offered in the WILDLABS discussion, first attempted to use an FPGA in conjunction with an Arduino microcontroller. The intention was to have the FPGA do the more laborious tasks of wake-up, camera configuration, and image processing, while the microcontroller would act as an interface for users to change settings (alter behavior of the FPGA) and access basic image data. The napkin-sketch below shows the hopeful architecture. 
  
<!-- Napkin sketch of FPGA implementation -->
<img src="https://user-images.githubusercontent.com/65932258/155895946-c8ebf240-5dbd-4ffd-a089-1c298e004d12.png" width="700">    

  
I initially acquired an [Arduino Maker Vidor 4000](https://store-usa.arduino.cc/products/arduino-mkr-vidor-4000) to start testing with. The board comes with both an Arm SAMD21 microcontroller and an Intel Cyclone 10CL016 FPGA, and a number of other features relevant to camera trap functionality. 

<!-- Arduino Maker Vidor 4000 -->
| <img src="https://user-images.githubusercontent.com/65932258/156899179-78066261-094f-4bec-a35d-3bfeb4297e7a.png" width ="600"> | 
|:--:| 
|Arduino Maker Vidor 4000|

  
The VIDOR is an awesome board, but for someone with no FPGA or analog hardware experience, it was too difficult to make any progress with it. I didn't help that the resources that exist for the board are limited, and that a friendly Arduino-FPGA infrastructure proposed by the Arduino developers has not yet come to fruition. I still hope to use the board for a future project one day. 
After playing a bit with Arducam, an FPGA-based camera module for Arduino, I concluded that the baseline power consumption of an FPGA (due to current leakage, I believe) would be very difficult to optimize and overcome. Also, ArduCam's FPGA code is not open source, otherwise I may have lingered on this option longer. 
  
## 3.2. A Proof-of-Concept  
  
After reviewing a few more potential platforms to build on, I looked back to the [ESP32-CAM](https://www.digikey.com/en/products/detail/seeed-technology-co.,-ltd/113990580/9697033?utm_adgroup=Evaluation%20Boards%20-%20Sensors&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_Development%20Boards%2C%20Kits%2C%20Programmers&utm_term=&utm_content=Evaluation%20Boards%20-%20Sensors&gclid=Cj0KCQiA95aRBhCsARIsAC2xvfw4VLFGdVS1YPavnDXHzv1EQg6aT1j1IlLgKjaIzYuL541LPgZEd-8aAiIgEALw_wcB), a board I had overlooked earlier in my search. The ESP32-CAM is a very economic (< $10 USD) camera IoT device sporting an AIThinker ESP32S microcontroller. Most of the ESP32 line offers low power functionality (in the form of different sleep and wakeup modes), Wi-Fi and Bluetooth capabilities, and compatibility with multiple programming toolchains (Arduino IDE). The ESP32-CAM has a microSD card slot and comes with an OV2460 camera. Existing resources, tutorials, and code repositories made replication of a psuedo-camera trap simple, with the addition of an OTS PIR-sensor module. 

<!-- ESP32-CAM -->
| <img src="https://user-images.githubusercontent.com/65932258/157107767-47d88603-ea15-43b2-898a-708bdf025c34.png" width="300"> | 
|:--:| 
|ESP32-CAM|

<!-- ESP32-CAM breadboard prototype and power consumption estimates -->
<img src="https://user-images.githubusercontent.com/65932258/155895980-b4847d08-71ec-4a85-9fd5-4c0c58192175.png" width ="900">

Power consumption and trigger times of initial tests were not ideal, but they showed potential for optimization. Using the light sleep mode, which approximately doubles power consumption, wakeup time can be made negligible. However, the camera must perform auto exposure before acquiring an image for the best quality. This takes a substantial amount of time in the current implementation, which I alotted for with a 500ms delay (0.5 seconds is the maximum allowable trigger time).
Based on this reasonable progress, I put together a proof-of-concept device based on ESP32-CAM and a custom sub-board. 

<!-- ESP32-CAM Schematic Diagram -->
<img src="https://user-images.githubusercontent.com/65932258/156899701-2c26ac5d-6a3d-4dda-9f60-61f61bae65fb.png" width ="900">

<!-- POC Shield Layout -->
<img src="https://user-images.githubusercontent.com/65932258/157100086-577d002d-3bd1-4da2-9b90-66ff7fedf7f7.png" width ="900">
  
| Key Component      | Description |
|--------------------|----|
| ESP32-CAM     | It needs to take pictures somehow. |
| Exposed GPIO  | The ESP32-CAM GPIO are exposed on the sub-board. |
| FTDI Programmer Interface   | Connects the sub-board and the FTDI programmer (necessary to program the ESP32-CAM). |
| IR Flash Module | Connects the sub board.              |
| 5V Relay          | You can use it to control external peripherals. |
| Dip Switch Array        | You can use it to turn on/off the relay, PIR sensor, and IR flash, in case you wanted to access their dedicated GPIO for other purposes. |
| TPDT Switch       | Three positions functions: cuts power to the ESP32 (OFF), connects power; connects programming pin to GND (PROGRAM), and connects power; disconnects programming pin (ON)|
  
<!-- Assembled POC -->
<img src="https://user-images.githubusercontent.com/65932258/157100157-350a33df-f42a-4fb9-82bd-889c09d7d22e.png" width ="900">

<!-- Assembled POC and mounting to OTS enclosure -->
<img src="https://user-images.githubusercontent.com/65932258/157100213-c33c6242-97f3-4b1b-bd45-c11719210a2c.png" width ="900">

<!-- 3D model of POC and OTS enclosure -->
<img src="https://user-images.githubusercontent.com/65932258/157100307-12bb43ee-463e-4da3-8c89-3e06bc17a3a4.png" width ="900">

<!-- Design of enclosure lid using 3D models --> 
<img src="https://user-images.githubusercontent.com/65932258/157100690-e44c01a3-d23d-46b1-a8a9-63f0415709c9.png" width ="900">

<!-- Waterproofing the enclosure -->
![image](https://user-images.githubusercontent.com/65932258/157107363-2cbd8bc3-867a-43a6-be0c-07d3248684a0.png)
  
<!-- side-by-side with Reconyx -->
<img src="https://user-images.githubusercontent.com/65932258/157100354-df416fed-fe04-44f6-8cab-ba7a751c9779.png" width ="600">
<!-- deployed side-by-side with Reconyx -->
<img src="https://user-images.githubusercontent.com/65932258/157101213-54df41ba-afde-41e0-82ae-3ee2daa075ba.png" width ="300">

<!-- Collage of images from the field --> 
<img src="https://user-images.githubusercontent.com/65932258/157100419-5cb22d93-771d-4764-90da-520f5531e221.png" width ="900">

## 3.3. Hijacking the ESP32-S3-EYE

So... the [ESP32-S3-EYE](https://github.com/espressif/esp-who/blob/master/docs/en/get-started/ESP32-S3-EYE_Getting_Started_Guide.md#5-related-documents) recently came to my attention. It's almost a camera trap by itself! It has a camera, LCD, microSD slot, digital microphone, USB port for communication and power AND battery charging, battery charger chip, and multiple function buttons. It's also got an accelerometer, but I don't really have a use for that. 

<!-- ESP32-S3-EYE -->
| ![ESP32-S3-EYE](https://user-images.githubusercontent.com/65932258/155896141-9abaea1d-3b0f-407f-b358-a88c962f4b0e.png)| 
|:--:| 
|ESP32-S3-EYE|

With the exception of GPIO3, which is used to configure LED statuses, all GPIOs of the **ESP32-S3-WROOM-1** module have already been used to control specific components or functions of the board. That's unfornate, because there are 5 additional components necessary: the LED array, a motor-driver for the IR-cut filter mechanism, the PIR sensor, an RTC, and a power/settings switch. 

<!-- Schematic of GPIO assignments -->
![image](https://user-images.githubusercontent.com/65932258/162111161-7ad04dcc-5719-430a-bb87-d496ffd58c6d.png)

None of the buttons use GPIO (they use a built in button channel), so we might as well make use of them.
The LCD is certainly a nice feature, but I think it'll need to be scrapped. Plenty of camera traps lack one (check out Reconyx). This would free up 5 GPIO! 
Say we go all out, and control the LED flash digitally, get a digital H-bridge, connect the PIR sensor, and enter the settings function via software and another GPIO attached to the switch, that only leaves one GPIO left over! Kinda measly. I'd like to leave at least 3 open for future tools. I could implement the settings like some camera traps, where you must make a modification within 10 seconds or normal functionality commences. Then I could take advantage of the boot pin like I did on the previous prototype for flashing the chip. Maybe the PIR module could be removable - to free up one GPIO for an alternative sensor? 
That reminds me that the I2C pins are not brought out on the board. They would be accessible via the camera connector, or by removing the SMT accelerometer, or probably most easily via the ESP32 module itself. It'll look nasty but some small guage wire should do the job. 

<!-- Components on ESP32-S3-EYE main board -->
![image](https://user-images.githubusercontent.com/65932258/162114144-79b27dea-3653-4dd9-93cc-11a23a025691.png)

The 5 LCD GPIO would be accessible via the leftmost (as shown above) header pins on the main board, if I wanted to attach my own components. The right header pins are strapping pins. I found this little [breakout board](https://www.digikey.com/en/products/detail/chip-quik-inc./DR127D254P10F/5978230?utm_adgroup=Adapter%2C%20Breakout%20Boards&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_Prototyping%2C%20Fabrication%20Products&utm_term=&utm_content=Adapter%2C%20Breakout%20Boards&gclid=CjwKCAjw9LSSBhBsEiwAKtf0n7yZIdTWm1LecCvVJ6c8e7OIaB8mGqIcadDMeKHdxRRrGVmwKbxvIxoCCB8QAvD_BwE) that could make breadboarding a little bit easier! 

<!-- weird little SWD breakout board --> 
![image](https://user-images.githubusercontent.com/65932258/162117269-f57016ff-e019-4682-8f35-2d4e0c699dd2.png)

**(temporary) okay, so pressing questions right now are:**

This is the block diagram for the esp32-eye:
<!-- esp32-eye block diagram --> 
![image](https://user-images.githubusercontent.com/65932258/164318081-8a6ce1e9-ccda-4cc8-bc12-0d9277056041.png)


This is the imagined block diagram of my hijacked dev board: 
<!-- tinkertrap block diagram -->
![Picture3](https://user-images.githubusercontent.com/65932258/164318206-b5c51621-96eb-48ea-9d49-b494b4425689.png)

There are 8 necessary additions to be considered: 
1. **I2C OLED LCD**: I don't need the SPI LCD currently included. Instead, I can use a SSD1306 OLED LCD with I2C. It is important to ensure that this component isn't drawing power when the camera trap is idling.
2. **I2C RTC**: I also want to add an RTC on the I2C bus, likely the DS3231 or DS3232 (not sure if there are any dev modules of this one). Not so worried about power draw on this one.
3. **Light/dark sensor**: I need a comparator style light/dark sensor to tell my IR cut filter mechanism to flip, and to tell my LED array if it can turn on (with some kind of "allowance" transistor?).
4. **Motor driver**: The light/dark sensor must trigger a motor driver to activate the IR-cut filter mechanism. Since the motor direction will need to be reversed, depending on night or day, I'm not sure what additional components the connection entails.
5. **IR-cut filter mechanism**: The IR filter will remain in whichever position it is pushed. Ideally, it should only move twice a day (at sunrise and sunset), and toggling shouldn't be much of an issue - especially if we consider hysteresis. A JST connector to the board would be easiest to take advantage of - as most IR-cut filter mechanisms come with a male JST connector.
6. **LED Illumination Array**: I want to maintain digitally control, so that the array can be powered on in the daylight. OR-transistor gate? White LED array should open IR-cut filter.
7. **PIR Sensor**: I want an integrated PIR sensor (still the primary sensor of choice) with adjustable sensitivity. Not sure the Adafruit module is the best example to build from - I don't care about the length of the PIR pulse, plus it is pretty power hungry. Not sure what IC it takes advantage of.
8. **Power/Settings Switch**: Lastly, the device needs a switch. I'd be fine with a two-position switch, where the LCD will prompt the user to alter settings. If the user doesn't press any buttons in a specified time period, the device commences normal function. <-- This could all be done in software. However, I would also like a switch that puts the device in boot mode (for uploading new scripts), as I believe the current device has a button for this. The other ESP32 chips I used required a boot pin to be held low during the entire upload process - not sure about the esp32-eye. The existance of a button implies to me that the button must activate this mode without the need for holding the reset pin low. 

**frankenstein's dev board:**
![image](https://user-images.githubusercontent.com/65932258/164790159-6a90b9d6-83ee-4245-a381-033f60593da0.png)


## 3.4. Build-your-own P(CB)izza  

# 4. Related Documents

## [4.1. Internal Development](https://github.com/benseleb/tinkertrap/blob/main/documentation/development.md)


## [4.2. Further Resources](https://github.com/benseleb/tinkertrap/blob/main/documentation/resources.md)
  
~~4.x. Schematic
TinkerTrap v1.2 Main Board Schematic (PDF)
TinkerTrap v1.1 Main Board Schematic (PDF)~~

~~4.x. PCB Layout
TinkerTrap v1.2 Main Board PCB Layout (PDF)
TinkerTrap v1.1 Main Board PCB Layout (PDF)~~

