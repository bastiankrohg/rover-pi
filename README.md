# Rover-Pi Setup and Documentation

This guide provides comprehensive instructions for setting up the Rover-Pi module, which manages hardware control for the rover and its camera.

## 1. Prerequisites

Before proceeding, ensure you have the following:

- **Hardware:**
  - 4tronix M.A.R.S. Rover Kit [oai_citation_attribution:3‡4tronix](https://shop.4tronix.co.uk/products/marsrover)
  - Raspberry Pi Zero 2 W with headers
  - Four rechargeable AA batteries

- **Software:**
  - Raspberry Pi OS Bookworm (32-bit) [oai_citation_attribution:2‡Raspberry Pi](https://www.raspberrypi.com/software/operating-systems/)
  - `rover.py` library for hardware interaction
  - Or our recreated C++ components in the `rover-pi/test-cpp/` folder

## 2. Hardware Assembly

Follow the assembly instructions provided by 4tronix to build the M.A.R.S. Rover Kit. Detailed guidance can be found here: [oai_citation_attribution:1‡4tronix](https://4tronix.co.uk/blog/?p=2112&)

## 3. Operating System Installation

1. **Download Raspberry Pi Imager:**
   - Obtain the latest version from the official Raspberry Pi website. [oai_citation_attribution:0‡Raspberry Pi](https://www.raspberrypi.com/software/operating-systems/)

2. **Flash the OS:**
   - Use Raspberry Pi Imager to write the Raspberry Pi OS Bookworm (32-bit) to a microSD card.
   - Configure SSID and password for the local network to enable SSH access without peripherals.
   - Username and password can also be configured in the Imager.

3. **Initial Setup:**
   - Insert the microSD card into the Raspberry Pi Zero 2 W.
   - If the local network is configured, try to SSH directly into the Pi:
     ```bash
     ssh username@<ip address>
     ```
     Enter the password when prompted. Alternatively, use `ping` to verify the device is available:
     ```bash
     ping <ip address>
     ```
   - If SSH is unavailable:
     - Connect peripherals (keyboard, mouse, display) and power up the device.
     - Complete the on-screen setup, including Wi-Fi configuration and system updates.

## 4. Software Installation

1. **Update Package Lists:**
   ```bash
   sudo apt update
   ````

2. **Install Required Packages:**
To ensure compatibility, it's recommended to use a virtual environment:
   ```bash
   python -m venv myenv
   source myenv/bin/activate
   ````
Install dependencies:
   ```bash
   pip install -r requirements.txt
   ```
To deactivate the virtual environment:
   ```bash
   deactivate
   ```

Virtual environment documentation: Python venv Documentation - https://docs.python.org/3/library/venv.html


3.	**Clone the Rover-Pi Repository:**
   ```bash
   git clone https://github.com/bastiankrohg/rover-pi.git
   cd rover-pi
   ```

4. **Install Python Dependencies:**
   ```bash
   pip3 install -r requirements.txt
   ```

## 5. Potential Configuration
1. **Might need to Enable I2C and SPI Interfaces:**
- Run:   
   ```bash
   sudo raspi-config
   ```
- Navigate to Interface Options and enable both I2C and SPI interfaces.

2. **Configure the Camera Module (if required):**
- Enable the camera interface in raspi-config.
- Reboot the Raspberry Pi to apply changes.

## 6. Running the Control Script
1.	**Navigate to the Control Script Directory:**
   ```bash
   cd ~/rover-pi
   ```
2.	**Execute the Control Script:**
   ```bash
   python pi_v2.py
   ```

## 7. Controls

The pi_v2.py script exposes gRPC services for controlling the rover. Below is an overview of the available controls:
- Locomotion:
    - DriveForward - Move forward with adjustable speed.
    - Reverse - Move backward with adjustable speed.
    - TurnLeft - Rotate left at a specified angle.
    - TurnRight - Rotate right at a specified angle.
    - RotateOnSpot - Rotate on the spot by a given angle.
    - StopMovement - Halt all movement.
- Sensors:
    - GetUltrasoundMeasurement - Retrieve the distance measured by the ultrasound sensor.
    - GetLightIntensity - Retrieve the current light intensity.
- LED Control:
    - ControlHeadlights - Turn the headlights on or off
    - ControlWheelLEDs - Control individual wheel LEDs.
- Servo Control:
    - RotatePeriscope - Rotate the periscope to a specified angle.
    - CalibrateServo - Calibrate a servo to a specific position.

8. Future Improvements
- Autonomous Navigation:
    - Implement algorithms for obstacle detection and path planning.
- Telemetry Dashboard:
    - Build a web-based interface for remote monitoring and control.
- Enhanced Sensors:
    - Integrate additional sensors like GPS or accelerometers for navigation.
- Hardware Calibration:
    - Improve accuracy by calibrating movements with odometer readings.

9. References
- 4tronix M.A.R.S. Rover Kit Assembly Guide: https://4tronix.co.uk/blog/?p=2112
- Raspberry Pi OS Downloads: https://www.raspberrypi.com/software/operating-systems/
- Programming M.A.R.S. Rover on Raspberry Pi Zero: https://4tronix.co.uk/blog/?p=2409