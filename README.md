# Buck Converter

A buck converter is a DC-DC power electronics device which reduces input voltage to a desired level. The most basic implementation consists of a transistor, a diode, an inductor and output capacitor. The efficiency of a such circuit can often exceed 90 percent.

<br>
<div align="center">
  <img src="https://github.com/user-attachments/assets/03952dba-1115-4f39-b3f2-40408d530b9f" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
  <img src="https://github.com/user-attachments/assets/3d0e4ad5-9165-4b06-91ee-820d3c833942" width="45%">
  <br><br>
  <em>Device prototype assembled on a universal PCB.</em>
</div>
<br>

The goal of this project is to design and build a DC to DC buck converter. The system will perform cyclic, synchronous measurement of the output voltage and current (using a series shunt resistor) and adjust these parameters according to values set by the user. A maximum steady-state error should not exceed 1% of the control range (300 mV).

The device should be based on the STM32 Nucleo board, and should have the following set of features:

- input voltage: up to 30 V,
- variable output voltage: 0 up to Vcc (minus the losses across the diode, shunt resistor etc.),
- adjustable current limit (two modes of operation CC (Constant Current) and CV (Constant Voltage)),
- a rotary encoder for changing voltage and current limit values,
- preset buttons for switching between desired voltages,
- an LCD for showing voltage and current,
- a photoresistor for controlling the brightness of the LCD,
- an SD card for logging data over time,
- a serial port communication setting and reading the voltage and current limits,
- a dedicated C# desktop application as an additional graphical user interface.

## Hardware

This project implements a buck converter circuit controlled by an STM32 Nucleo board, which measures the output voltage and current and adjusts the MOSFET accordingly. Both measured quantities pass through a unity gain amplifier and are filtered using a second-order active filter based on the Sallen–Key topology. A 16x2 LCD display shows the output voltage, current, power, and energy delivered to the load, with the backlight controlled by a transistor, adjusting based on ambient brightness measured by a photoresistor. The desired voltage is set using a rotary encoder, and four preset buttons allow users to store and recall voltage settings.

For prototype purposes, the device was soldered on a universal PCB.

## Firmware

The regulation of the system is implemented using proportional and integral terms. The microcontroller compares the output current and voltage readings with the user-defined values, and based on this comparison, it adjusts the MOSFET duty cycle, either increasing or decreasing it to maintain the desired output.

## Communication API Specification

An API specification for communication between dedicated C# application and the device via UART interface.

### Receive

The following set of messages can be received from the device:

- Voltage - measured voltage in mV `[int]`.
- Current - measured current in mA `[int]`.
- TargetVoltage - reference voltage in mV `[int]`.
- CurrentLimit - current limit in mA `[int]`.
- OutputMode - working mode (either "cv" or "cc") `[string]`.
- Output - output status (either "on" or "off") `[string]`.

Example message:
```
{
  "Voltage": 3310,
  "Current": 26,
  "TargetVoltage": 3300,
  "CurrentLimit": 1000,
  "OutputMode": "cv",
  "Output": "on"
}
```

### Send

The following set of messages can be sent to the device:

- SetTargetVoltage - sets the reference voltage in mV `[int]`.
- SetCurrentLimit - sets the current limit in mA `[int]`.
- SetOutput - turns output on or off (either "on" or "off") `[string]`.

Example message:
```
{
  "SetTargetVoltage": 3300,
  "SetCurrentLimit": 500,
  "SetOutput": "on"
}
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE.md) file for details.
