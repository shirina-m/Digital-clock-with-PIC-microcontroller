# 🕒 Digital Clock with Full Control using PIC16F877A & DS1307

This project implements a **24-hour format digital clock** with full time-setting capabilities using the **PIC16F877A microcontroller** and a **DS1307 Real-Time Clock (RTC) module**. The time is displayed in real-time on an LCD screen and can be adjusted via buttons connected to the microcontroller.

---

## 🧰 Components Used

- PIC16F877A Microcontroller  
- DS1307 RTC Module  
- LCD (16x2) Display  
- 8 MHz Crystal Oscillator  
- 2x 22pF Capacitors  
- 10kΩ Potentiometer (for LCD contrast)  
- Pull-up Resistors  
- Push Buttons (Hour & Minute adjustment)  
- Jumper Wires  
- Breadboard (for prototyping)  

---

## 🧪 Simulation (Proteus)

The project was first simulated using **Proteus**, showing correct interfacing of:

- PIC16F877A and DS1307 via software I2C
- LCD displaying real-time clock (HH:MM:SS)
- Pull-up resistors for stable communication with the RTC

---

## 💻 Code (MikroC)

The code is written in **MikroC for PIC**, utilizing:

- Software I²C to communicate with the DS1307
- LCD control using 4-bit mode
- Button-driven time adjustment
- Real-time clock reading and display logic

### Key Features:
- ✅ 24-hour format
- ✅ Increment hours/minutes using RD0/RD1 buttons
- ✅ Debounced button logic
- ✅ Real-time synchronization with DS1307
- ✅ Displays `DIGITAL CLOCK` and live time on 16x2 LCD

## 🔧 Hardware Setup (Breadboard)

The project was successfully tested on a breadboard with:

- LCD connected to PORTB
- DS1307 connected via RC3 (SCL) and RC4 (SDA)
- Buttons connected to RD0 (Hour+) and RD1 (Minute+)
- Pull-up resistors used on I2C lines

---

## 📷 Preview

<img width="1001" height="644" alt="image" src="https://github.com/user-attachments/assets/545731b7-086f-437c-8910-386a576027ea" />
<img width="646" height="409" alt="image" src="https://github.com/user-attachments/assets/765bce86-6f81-4194-a5af-274249bb3cd2" />

