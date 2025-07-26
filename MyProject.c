// LCD connections
sbit LCD_RS at RB2_bit;
sbit LCD_EN at RB3_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;

sbit LCD_RS_Direction at TRISB2_bit;
sbit LCD_EN_Direction at TRISB3_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;

// I2C connections for DS1307
sbit Soft_I2C_Scl at RC3_bit;
sbit Soft_I2C_Sda at RC4_bit;
sbit Soft_I2C_Scl_Direction at TRISC3_bit;
sbit Soft_I2C_Sda_Direction at TRISC4_bit;

// Button connections
sbit Button_Hour_Up at RD0_bit;   // Button to increase hour
sbit Button_Minute_Up at RD1_bit; // Button to increase minute

// Variables for time
unsigned char seconds, minutes, hours;

// Function to convert BCD to decimal
unsigned char BCDToDec(unsigned char bcd) {
  return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

// Function to convert decimal to BCD
unsigned char DecToBCD(unsigned char dec) {
  return ((dec / 10) << 4) + (dec % 10);
}

// Function to initialize the DS1307 (set time if needed, or leave it as is)
void RTC_Init() {
  // Start the DS1307 oscillator
  Soft_I2C_Start();
  Soft_I2C_Write(0xD0); // Address of DS1307
  Soft_I2C_Write(0x00); // Point to seconds register
  Soft_I2C_Write(0x00); // Start oscillator with 0 seconds
  Soft_I2C_Stop();
}

// Function to read time from DS1307
void RTC_GetTime() {
  Soft_I2C_Start();
  Soft_I2C_Write(0xD0); // Address of DS1307
  Soft_I2C_Write(0x00); // Point to seconds register
  Soft_I2C_Stop();

  Soft_I2C_Start();
  Soft_I2C_Write(0xD1); // Read mode
  seconds = BCDToDec(Soft_I2C_Read(1)); // Read seconds
  minutes = BCDToDec(Soft_I2C_Read(1)); // Read minutes
  hours = BCDToDec(Soft_I2C_Read(0));   // Read hours
  Soft_I2C_Stop();

  // Validate the time to make sure no crazy values are returned (like 62 seconds)
  if (seconds >= 60) {
    seconds = 0; // Reset to 0 if invalid
  }
  if (minutes >= 60) {
    minutes = 0; // Reset to 0 if invalid
  }
  if (hours >= 24) {
    hours = 0; // Reset to 0 if invalid
  }
}

// Function to display time on LCD
void DisplayTime() {
  // Display "Digital Clock" starting from the second column
  Lcd_Out(1, 1, "DIGITAL CLOCK");

  // Display time in HH:MM:SS format starting from the fifth column
  Lcd_Chr(2, 5, (hours / 10) + '0');
  Lcd_Chr(2, 6, (hours % 10) + '0');
  Lcd_Chr(2, 7, ':');
  Lcd_Chr(2, 8, (minutes / 10) + '0');
  Lcd_Chr(2, 9, (minutes % 10) + '0');
  Lcd_Chr(2, 10, ':');
  Lcd_Chr(2, 11, (seconds / 10) + '0');
  Lcd_Chr(2, 12, (seconds % 10) + '0');
}

// Function to handle hour increment with button press
void IncrementHour() {
  static unsigned short button_state = 0; // Track the button state

  // Detect button press
  if (Button_Hour_Up == 0 && button_state == 0) { // Button pressed (low)
    if (hours < 23) {
      hours++;
    } else {
      hours = 0; // Reset to 0 if hour exceeds 23
    }
    button_state = 1; // Set state to indicate button was pressed
    Delay_ms(1); // Debounce delay
  } else if (Button_Hour_Up == 1) { // If button is released
    button_state = 0; // Reset button state for next press
  }
}

// Function to handle minute increment with button press
void IncrementMinute() {
  static unsigned short button_state = 0; // Track the button state

  // Detect button press
  if (Button_Minute_Up == 0 && button_state == 0) { // Button pressed (low)
    if (minutes < 59) {
      minutes++;
    } else {
      minutes = 0; // Reset to 0 if minute exceeds 59
    }
    button_state = 1; // Set state to indicate button was pressed
    Delay_ms(1); // Debounce delay
  } else if (Button_Minute_Up == 1) { // If button is released
    button_state = 0; // Reset button state for next press
  }
}

// Main function
void main() {
  // Initialize peripherals
  Soft_I2C_Init();
  Lcd_Init();
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);

  // Initialize RTC
  RTC_Init();

  // Configure RD0 and RD1 as inputs for buttons
  TRISD0_bit = 1;
  TRISD1_bit = 1;

  // Read the current time once at startup
  RTC_GetTime();

  // Main loop
  while (1) {
    IncrementHour();  // Check if the hour button is pressed
    IncrementMinute(); // Check if the minute button is pressed

    // Update the display with the current time
    DisplayTime();

    // Update time every second
    seconds++;
    if (seconds >= 60) {
      seconds = 0;
      minutes++;
      if (minutes >= 60) {
        minutes = 0;
        hours++;
        if (hours >= 24) {
          hours = 0;
        }
      }
    }

    Delay_ms(1000);   // 1-second delay for real-time update
  }
}