# 🌐 ESP32-Based Remote Sensor System with Excel Data Logging over Tailscale VPN

![Project Banner](images/project_diagram.png)

This project demonstrates a robust **remote sensor monitoring system** using an **ESP32 microcontroller** that transmits sensor data over **TCP** to a **Linux-based server**. The data is received and logged in real-time to an **Excel (.xlsx)** file using `libxlsxwriter`. Communication is made possible across different networks via a **Tailscale VPN**, enabling secure and seamless connectivity.

---

## 🚀 Features

- 📡 **ESP32 TCP client** sending sensor data over Wi-Fi.
- 🖥️ **Linux server** logs data in Excel format.
- 📁 Saves `Date`, `Time`, and `Sensor Data` in structured `.xlsx`.
- 🧠 Gracefully handles disconnections and system interrupts.
- 🔐 Connects across Wi-Fi networks via **Tailscale** (P2P VPN).
- 🛜 Gateway acts as bridge between ESP32 and the VPN server.

---


## 🧪 How It Works

1. ESP32 connects to Wi-Fi and Tailscale network.
2. It sends sensor readings (e.g., temperature, pH) to a predefined IP/port.
3. The Linux server receives and logs the data into an Excel sheet.
4. Data is timestamped and organized in `sensor_data.xlsx`.

---

## 🚀 Getting Started

### ESP32 Setup
- Upload the TCP client code from `esp32_client/` using Arduino IDE or ESP-IDF.
- Connect to a Wi-Fi network.
- Ensure Tailscale is active on the ESP32 (via gateway forwarding or static IP).

### Linux Server Setup
- Install `libxlsxwriter`:  
  ```bash
  sudo apt install libxlsxwriter-dev

## 🧪 Prerequisites
### On Linux Server (Gateway or Remote)
- `libxlsxwriter`: Install using:
  ```bash
  sudo apt install libxlsxwriter-dev
- GCC Compiler
- Tailscale installed and authenticated:
 ```
sudo apt install tailscale
sudo tailscale up

