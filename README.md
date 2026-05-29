Robot Line Follower Berbasis Mikrokontroler

Octaviant Dwi Ananda
- 25032014026

Yudi Tira Nanda Adi Saputra
 - 25032014010

 
https://youtu.be/lRbP8LNZPcw?si=ubMDkeoNteLDEgX2

 Deskripsi Proyek
Proyek ini merupakan implementasi embedded system berupa Robot Line Follower yang dirancang dan difabrikasi menggunakan PCB kustom. Robot menggunakan mikrokontroler ATmega328P (kompatibel Arduino Uno) sebagai otak utama untuk memproses sinyal dari 4 sensor inframerah (IR) dan mengatur gerakan dua motor DC melalui driver motor L293D.
Fitur Utama

4 Sensor IR Analog — deteksi posisi garis dengan resolusi 4-titik (kiri luar, kiri dalam, kanan dalam, kanan luar)
Kontrol PWM Motor — kecepatan motor diatur secara presisi melalui sinyal PWM (pin 9 & 10)
Algoritma Logika Bertingkat — 8 kondisi sensor diterjemahkan ke manuver: lurus, belok halus, belok tajam, belok sangat tajam, dan berhenti
PCB Kustom — desain skematik dan layout PCB menggunakan EAGLE CAD (.sch & .brd)
Debug Serial — output status sensor real-time via Serial Monitor (9600 baud)
Deteksi Persimpangan — robot berhenti otomatis saat semua sensor aktif (ujung jalur / persimpangan)


Pemetaan Pin
KomponenPin ArduinoKeteranganSensor Kiri LuarA0LOW = deteksi garis hitamSensor Kiri DalamA1LOW = deteksi garis hitamSensor Kanan DalamA2LOW = deteksi garis hitamSensor Kanan LuarA3LOW = deteksi garis hitamIN1 (Motor Kiri Maju)D2Digital OutputIN2 (Motor Kiri Mundur)D3Digital OutputIN3 (Motor Kanan Maju)D4Digital OutputIN4 (Motor Kanan Mundur)D5Digital OutputENA (Enable Motor Kiri)D9PWM OutputENB (Enable Motor Kanan)D10PWM Output

 Desain PCB
File desain PCB tersedia di folder src/:

.sch — Skematik rangkaian (buka dengan EAGLE atau KiCad)
.brd — Layout PCB siap fabrikasi (export ke Gerber untuk produksi)
