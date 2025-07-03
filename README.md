# Smart Distance Reader (VL53L0X + OLED + Feedback)

A real-time distance measurement project using the **VL53L0X Time-of-Flight sensor**, an **OLED display**, **buzzer**, and **vibration motor**, designed for quick visual and physical feedback. Also integrates **RemoteXY** over Wi-Fi for remote monitoring.

---

## 🔧 Features
- 📏 Live distance display on OLED
- 💾 Stores up to 3 recorded measurements via button press
- 🔊 Buzzer + vibration alert for out-of-range
- 🌐 Wi-Fi access point via RemoteXY for mobile control
- 🧠 Centered OLED text with clean UI

---

## 📦 Hardware Used
- ESP32 Dev Board  
- VL53L0X Distance Sensor  
- SSD1306 128x64 OLED Display  
- Buzzer  
- Vibration Motor  
- Push Button  
- Optional: Power bank or LiPo for portability

---

## 🚀 How to Use
1. Upload `LaserDistanceMeter.ino` to the ESP32 board.
2. Connect to the Wi-Fi SSID: `RemoteXY` (Password: `12345678`)
3. Open RemoteXY app (port: 6377) to monitor values.
4. Press the button to record distance snapshots.
5. Watch the OLED screen for live and stored values.

---

## 🧠 Status Codes
- ✅ Normal distance: Value shown, no alerts  
- ❌ Out of range: Buzzer + vibration motor activated

---

## 📜 License
MIT – Feel free to build on this!

---

## 👨‍💻 Author
**Mohamed Sameh**  
[GitHub](https://github.com/M7md0010) • [LinkedIn](https://www.linkedin.com/in/mohamedsameh0/)
