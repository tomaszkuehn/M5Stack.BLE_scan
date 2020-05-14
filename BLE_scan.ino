
// ----------------------------------------------------------------------------
// Copyright (C) 2020, Tomasz Kuehn
//
// These coded instructions, statements, and computer programs are free 
// for personal use.
// Based on Neil Kolban example for IDF: 
// https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
// Ported to Arduino ESP32 by Evandro Copercini and modified by Tomasz Kuehn
//
// Maintainer: Tomasz Kuehn
//
// Description: Magic wand main code
// ----------------------------------------------------------------------------

#include <string>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEAddress.h>
#include <M5Stack.h>

int scan_time = 5; //In seconds
BLEScan* p_BLE_scan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(20, 0);
    M5.Lcd.printf("%s", advertisedDevice.toString().c_str());
  }
};

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.setBrightness(255);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(TFT_ORANGE , BLACK);
  M5.Lcd.setTextSize(2);

  M5.Lcd.setCursor(0, 10);
  M5.Lcd.printf("Start");
  
  //Serial.begin(115200);
  //Serial.println("Scanning...");
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Scanning");

  BLEDevice::init("");
  p_BLE_scan = BLEDevice::getScan(); //create new scan
  p_BLE_scan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  p_BLE_scan->setActiveScan(true); //active scan uses more power, but get results faster
  p_BLE_scan->setInterval(100);
  p_BLE_scan->setWindow(99);  // less or equal setInterval value
}

BLEAdvertisedDevice advertised_device;
int rssi;
std::string bleid;
std::string blename;
std::string bleaddr;

void loop() {
  // start scan
  BLEScanResults foundDevices = p_BLE_scan->start(scan_time, false);

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 50);
  M5.Lcd.printf("Found: %d", foundDevices.getCount());

  M5.Lcd.fillRect(0, 70, 320, 240, TFT_BLACK);
  for(int i = 0; i < foundDevices.getCount(); i++) {
    advertised_device = foundDevices.getDevice(i);
    blename = advertised_device.getName();
    rssi = advertised_device.getRSSI();
    bleaddr = advertised_device.getAddress().toString();
    //bleid = ba.toString();
    M5.Lcd.setCursor(0, 70 + 40 * i);
    M5.Lcd.printf(">%s", blename.c_str());
    M5.Lcd.setCursor(0, 70 + 40 * i + 19);
    M5.Lcd.printf("%s RSSI %d", bleaddr.c_str(), rssi);
  }
  p_BLE_scan->clearResults();   // delete results fromBLEScan buffer to release memory

  delay(10);
}
