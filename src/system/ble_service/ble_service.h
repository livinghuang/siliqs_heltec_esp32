#pragma once
#include "bsp.h"

#ifdef USE_BLE // 仅在启用 USE_BLE 时编译

#ifndef _BLE_SERVICE_H_
#define _BLE_SERVICE_H_

#include "siliqs_heltec_esp32.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <vector>
#include <algorithm>

#define UART_CHARACTERISTIC_UUID_TX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define UART_CHARACTERISTIC_UUID_RX "6E400004-B5A3-F393-E0A9-E50E24DCCA9E"

class SQ_BLEServiceClass
{
public:
  void init(unsigned long timeout, String namePrefix = "BLE-");
  void stop();
  void sendData(const char *data);
  void sendData(String data);
  void setReceivedData(const String &data); // 新增一个 setter 方法
  String getReceivedData();
  void scanDevices(int scanTime);                 // 新增方法，设置扫描时间
  void task(void *pvParameters);                  // FreeRTOS 任务函数
  static void bleTaskWrapper(void *pvParameters); // FreeRTOS 任务包装
  bool deviceConnected = false;
  bool oldDeviceConnected = false;
  // 声明一个设备列表
  std::vector<BLEAdvertisedDevice> discoveredDevices;

private:
  BLEServer *pServer = nullptr;
  BLECharacteristic *pTxCharacteristic;

  unsigned long waiting_connect_timeout = 30000; // 默认超时时间
  unsigned long startTime;

  const char *SERVICE_UUID; // it will be generated by generateDynamicUUID()
  const char *CHARACTERISTIC_UUID_TX = UART_CHARACTERISTIC_UUID_TX;
  const char *CHARACTERISTIC_UUID_RX = UART_CHARACTERISTIC_UUID_RX;
  String receivedData = "";
};

extern SQ_BLEServiceClass SQ_BLEService;

#endif
#endif // USE_BLE 结束