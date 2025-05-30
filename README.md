# 🌐 ESP32-Based Remote Sensor System with Excel Data Logging over Tailscale VPN

<p align="center">
  <img src="Img/Block_Diagram.png" alt="Project Banner" width="200"/>
</p>


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
$sudo apt install tailscale
$sudo tailscale up
```
- Compile and run the C server:
```
$ gcc server.c -o server -lxlsxwriter
./server
```
## 🖼️ Preview Images

| Gateway Device/PC-A | PC-B | Excell Data Logging |
|:---------:|:----------:|:---------:|
| ![Gateway](Img/PC-A.png) | ![PC-B](Img/PC-B.png) | ![Excell](Img/Excell.png) |

## 🔧 How to Use

1️⃣ Flash the ESP32 with the code in `/esp32_client/`  
2️⃣ Run the TCP server from `/linux_server/` on PC-A (Linux system)  
3️⃣ Ensure both ESP32 and Gateway Device are on the same local network  
4️⃣ Use Tailscale to connect PC-A securely via VPN  
5️⃣ Sensor data received is logged in `sensor_data.xlsx` using libxlsxwriter

