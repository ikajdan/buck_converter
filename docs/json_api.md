# JSON API Specification

An API specification for communication between dedicated C# application and the device via UART interface.

## RECEIVE
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

## SEND
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
