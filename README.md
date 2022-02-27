# TinkerTrap
open source camera trap repository

### BACKGROUND
Camera traps, or remotely triggered cameras, have become an incredibly popular tool among ecologists and other wildlife professionals. At the most basic level, the modern camera trap can be described simply as a digital camera connected to an infrared sensor which can automatically detect animals [[1](https://www.wwf.org.uk/sites/default/files/2019-04/CameraTraps-WWF-guidelines.pdf)]. Typically mounted on trees or other natural supports in order to capture images of passing wildlife, they have been proven useful for detecting cryptic species, identifying species distributions, documenting predation, monitoring behavior, and estimating population size. Despite their ubiquity, commercial camera traps have critical limitations that present challenges for the study of certain species, habitats, and/or the behavior of interest. 

The development of commercially available models has been driven almost entirely by the requirements of North American and European Hunters. Most models are equipped with passive-infrared (PIR) sensors that are specialized for detecting the thermal signatures of medium to large sized mammals and use cameras with fixed depths of field. For small animals, ectotherms, and insects, these PIR sensors are largely ineffective. 

In some cases, extensive modification of operating procedure and camera trap hardware can improve effectiveness. The camera overhead augmented temperature (COAT) method is one such modification, but it typically voids any product warranty, has the potential to destroy an expensive piece of equipment, and only slightly enhances the functionality of the device. Besides being exclusive to medium to large sized mammals, commercial camera traps also limit users to a basic triggering protocol and finite imaging options. 

In an attempt to address the restrictions of the traditional camera trap model, and in order to expand the usefulness of this very important tool, many have proposed the use of open-source electronic prototyping platforms such as Arduino and Raspberry Pi [[2](https://journals.plos.org/plosone/article?id=10.1371/journal.pone.0169758),[3](https://dl.acm.org/doi/10.1145/3290605.3300532),[4](https://www.sciencedirect.com/science/article/pii/S2468067220300195),[5](https://onlinelibrary.wiley.com/doi/full/10.1002/ece3.3040)]. These controllers have the capability to offer the user complete control over the imaging procedure of a camera trap while also offering compatibility with multiple sensors. Also, by weighing the input of multiple sensors in complex ways, it’s possible that open-source microcontrollers could expand camera trap functionality even further. However, these microcontroller-based platforms suffer from various drawbacks including cost, reduced lifespan/durability, lack of helpful resources, and high technical knowledge requirements. Thus, most previous efforts have been abandoned or implemented only as educational tools. To date, there is still no open-source camera trap platform to have seen widespread adoption within the wildlife research community.

### OTS CAMERA TRAP SETTINGS AND SPECIAL FEATURES

Camera traps must be able to take images at night. Thus they are all equipped with IR leds and an IR-cut filter. Most camera traps use an IR-cut filter mechanism to push and pull a sliding filter over the sensor, depending on whether daytime or nighttime images are needed (left image). An alternative solution is to use two sensors, one with the IR-cut filter permanently installed, and the other without. This has the benefit of reducing any noise coming from an IR-filter mechanism (typically an audible 'click'), and also could enable instantaneous IR functionality if needed. 

![image](https://user-images.githubusercontent.com/65932258/155892610-f3db632b-6c32-4226-8605-91e6cd289c6d.png)
![image](https://user-images.githubusercontent.com/65932258/155892611-fcf6a534-fce5-4e54-a185-3a26e2c26253.png)

All camera traps use a passive-infrared sensor to detect animals, typically an LHI 968 or equivalent. 

![image](https://user-images.githubusercontent.com/65932258/155892557-76a5c4f6-6fcc-43d8-a4f5-714e1c366b75.png)

All camera traps include some kind of onboard user-interface in order to apply settings. Reconyx, one of the most respected camera trap producers, only implements a two-line text display, and 5 buttons for control (left). Many other camera traps use an OLED display to enable immediate image/video review, typically for an added cost (center). The Bushnell NatureView camera trap (right) actually comes with a peripheral plug-in OLED display. 

![image](https://user-images.githubusercontent.com/65932258/155892908-e3d788eb-f9a1-4162-ad46-1b51dd2c8639.png)
![image](https://user-images.githubusercontent.com/65932258/155892954-47e3e85a-76bf-4751-853c-d84cd42b065b.png)
![image](https://user-images.githubusercontent.com/65932258/155892979-205a4579-a8c5-421e-b97d-0051beafe76c.png)

OTS camera traps seem to be using the same (or similar) chipsets that are mass-produced and well guarded in terms of firmware. Thus, most camera traps share the same standard features. To get an idea of these features (and some hopeful improvements/additions), Meek and Pettit published a review in 2012, with [user-based design specifications for the ultimate camera trap for wildlife research](https://bioone.org/journals/wildlife-research/volume-39/issue-8/WR12138/User-based-design-specifications-for-the-ultimate-camera-trap-for/10.1071/WR12138.short). Akiba and Alasdair give a brief description of camera trap hardware and potential OS design directions in this [WILDLABS discussion](https://www.wildlabs.net/community/thread/694).

## VERSION 1.0
![image](https://user-images.githubusercontent.com/65932258/155895946-c8ebf240-5dbd-4ffd-a089-1c298e004d12.png)

## VERSION 2.0
![image](https://user-images.githubusercontent.com/65932258/155895980-b4847d08-71ec-4a85-9fd5-4c0c58192175.png)

## VERSION 3.0

| ![ESP32-S3-EYE](https://user-images.githubusercontent.com/65932258/155896141-9abaea1d-3b0f-407f-b358-a88c962f4b0e.png)| 
|:--:| 
|ESP32-S3-EYE|

