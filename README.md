**Walky-Talky**

Walky-Talky is a custom **STM32-based** digital voice communication system built for long-range, low-bandwidth voice transmission over LoRa RF.

The project combines embedded firmware development, custom PCB design in KiCad, digital signal processing, and wireless communication into a fully self-contained handheld device.

Voice audio is captured using an INMP441 I2S microphone, compressed in real time using the Codec2 low-bitrate voice codec, and transmitted through a RYLR998 LoRa module operating at 915 MHz. On the receiving side, audio is decoded and played back through a 12-bit DAC and PAM8403 speaker amplifier.

To support continuous real-time streaming, STM32 DMA is used throughout both the audio and RF pipelines, minimizing CPU overhead while maintaining low-latency operation.

The hardware was designed entirely from scratch in KiCad and includes custom analog audio circuitry, rotary encoder channel selection, power regulation, and RF interfacing on a fully custom PCB.

**Features**
-Real-time digital voice communication over LoRa
-Codec2 low-bitrate voice compression
-STM32 DMA-driven audio streaming
-INMP441 I2S microphone input
-12-bit DAC audio playback
-PAM8403 speaker amplifier output
-Rotary encoder channel selection
-Fully custom KiCad PCB design
-Embedded real-time firmware architecture


**System Diagram**

<img width="1402" height="1122" alt="image" src="https://github.com/user-attachments/assets/073ec16c-0df7-4b26-91f8-ca09b7cb6f5c" />



**Hardware Overview**

Schematic:
<img width="4960" height="3507" alt="image" src="https://github.com/user-attachments/assets/a173bd1a-4492-41ed-adc8-7da184dea9a8" />


PCB Renderings: 
<img width="1724" height="930" alt="WalkieTalkieRnder2" src="https://github.com/user-attachments/assets/28902cd4-5a35-49b4-9b3b-6b5f1b0284fa" />
<img width="1724" height="930" alt="WalkieTalkie" src="https://github.com/user-attachments/assets/bcf0d2a1-a6f6-4391-ab37-932da6d82e94" />





**Technologies Used**
STM32
KiCad
LoRa / RYLR998
Codec2
I2S Audio
DMA Streaming
Embedded C
Digital Signal Processing
Custom PCB Design
