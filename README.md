# Efficiency-Meter

A device used to measure the efficiency of DC/DC converters and as a USB tester.

This is an Arduino Nano-based device, utilizing the **LGT8F328P - (Enhanced Arduino-Compatible Microcontroller)**. This microcontroller provides more accurate measurements due to its 12-bit ADC.

For more information about the LGT8F328P, see the following link:
https://github.com/AhmedHafez2000/Arduino-Nano-Clone-LGT8F328P

#### Measurement Procedure:
- The efficiency of a DC/DC converter can be calculated by dividing the output power by the input power.
- First, connect a power supply to the V_Test terminals. Then, connect VIN to the input of the converter and VOUT to the output of the converter. Connect a constant load circuit or any other load to the LOAD terminal.
- Voltages are measured through voltage divider resistors.
- Input current is measured using a non-inverting amplifier, while output current is measured using a differential amplifier.
- The non-linear behavior of the OpAmps is corrected in the code using reference points, which are further explained in the code itself.

#### USB Tester:
Connect a micro or type-C USB cable to the input, then connect your phone or any USB device to the USB output to measure power consumption. Charging protocols using only D+ and D- will function normally.  
**NOTE**: Pressing the push button will enable the energy calculation feature if needed.

#### Key Features:
- **Voltage Ranges**: Can measure voltages from 0 to 22V (Max).
- **Current Ranges**: Can measure currents up to 10A (currently limited to 8A due to the power supply limitations).
- **Power Supply**: Can be powered using a Li-ion battery. The battery will charge when the device is turned off and a power supply or USB input is connected.

This measurement tool can be fabricated at home. A printable file is attached in the PCB folder.


#### NOTES:
- All designs are made with ease of home fabrication in mind, which is why we use wider traces where possible.
- There is a V3 of this project, and its schematic and PCB are also attached to this repo.
- The improvement in V3 is the addition of an ASC712 Hall Effect-Based Linear Current Sensor, and fewer top-layer jumpers are needed, with the LGT8F328P IC soldered directly onto the PCB.
- V2 is preferred for beginners and, in my opinion, is more reliable.


---

## DIY Sample
**The fabricated sample is based on V1 of this device but it is modified to match V2 that is puplished in this repo**

![](https://github.com/AhmedHafez2000/Efficiency-Meter/blob/main/Photos/IMG_3.jpg?raw=true)
![](https://github.com/AhmedHafez2000/Efficiency-Meter/blob/main/Photos/IMG_2.jpg?raw=true)
![](https://github.com/AhmedHafez2000/Efficiency-Meter/blob/main/Photos/IMG_4.jpg?raw=true)
![](https://github.com/AhmedHafez2000/Efficiency-Meter/blob/main/Photos/IMG_8.jpg?raw=true)
![](https://github.com/AhmedHafez2000/Efficiency-Meter/blob/main/Photos/IMG_9.jpg?raw=true)
![](https://github.com/AhmedHafez2000/Efficiency-Meter/blob/main/Photos/IMG_12.jpg?raw=true)

---

## Schematic
- #### V2:
![Schematic](https://github.com/AhmedHafez2000/Efficiency-Meter/blob/main/Schematic/Schematic_Efficiency-Meter-V2.png?raw=true)

- #### V3:
![Schematic](https://github.com/AhmedHafez2000/Efficiency-Meter/blob/main/Schematic/Schematic_Efficiency_Meter_V3.png?raw=true)

MT3608 boost converter is used to supply a stable voltage level.

---

## 2D PCB
- #### V2:
![2D PCB](https://github.com/AhmedHafez2000/Efficiency-Meter/blob/main/PCB/2D-Bot-V2.png?raw=true)

- #### V3:
![2D PCB](https://github.com/AhmedHafez2000/Efficiency-Meter/blob/main/PCB/V3-2D-Bot.png?raw=true)
**NOTE:** The top connection are jumper wires.

---

## 3D PCB
- #### V2:
![3D PCB](https://github.com/AhmedHafez2000/Efficiency-Meter/blob/main/PCB/3D-Top-V2.png?raw=true)
![3D PCB](https://github.com/AhmedHafez2000/Efficiency-Meter/blob/main/PCB/3D-Bot-V2.png?raw=true)

- #### V3:
![3D PCB](https://github.com/AhmedHafez2000/Efficiency-Meter/blob/main/PCB/V3-3D-Top.png?raw=true)
![3D PCB](https://github.com/AhmedHafez2000/Efficiency-Meter/blob/main/PCB/V3-3D-Bot.png?raw=true)