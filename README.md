**Walky-Talky**

Walky-Talky is a custom STM32-based digital voice communication system designed from the ground up for long-range, low-bandwidth audio transmission over LoRa RF. The project combines embedded firmware development, custom PCB design in KiCad, real-time audio processing, and wireless communication into a fully self-contained handheld device.

The system captures voice through an INMP441 I2S microphone, compresses audio using Codec2 voice encoding, and transmits data over a RYLR998 LoRa module operating at 915 MHz. On the receiving end, compressed audio is decoded and played back through a 12-bit DAC and PAM8403 speaker amplifier. All audio and RF data paths are driven using STM32 DMA to support continuous streaming with minimal CPU overhead.

Additional hardware features include a rotary encoder interface for FM-style channel selection, custom analog audio circuitry, and a fully custom-designed PCB developed in KiCad.

This project was created to explore embedded systems, digital signal processing, RF communication, and real-time firmware architecture in a practical end-to-end hardware platform.

<img width="4960" height="3507" alt="image" src="https://github.com/user-attachments/assets/dc4c3640-fc49-46a2-9dcd-3c16f4166c40" />


