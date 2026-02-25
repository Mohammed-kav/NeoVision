# NeoVision

## Overview
NeoVision is a compact, low-cost, and portable assistive device that identifies colors without needing a dedicated color sensor. 

## How It Works
A bright white LED illuminates the target surface, and an LDR (Light Dependent Resistor) measures the reflected light. The custom Arduino firmware analyzes these light readings to classify the color and instantly displays the result on a side-mounted OLED screen.

## Hardware & Design
* **Microcontroller:** Arduino Nano
* **Components:** LDR, bright white LED, OLED screen
* **Enclosure:** Fully 3D-printed. It features precise LED/LDR alignment and built-in light shielding to ensure consistent and accurate sensor readings.
