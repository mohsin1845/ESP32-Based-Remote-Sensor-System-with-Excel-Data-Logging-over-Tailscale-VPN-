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

## 🛠️ System Architecture

