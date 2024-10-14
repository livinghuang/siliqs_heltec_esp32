#include "bsp.h"
#pragma once
#ifdef USE_LORAWAN // Only compile when USE_LORAWAN is enabled

#include "siliqs_heltec_esp32.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class SQ_LoRaWanService
{
public:
  // Constructor and destructor
  SQ_LoRaWanService();
  ~SQ_LoRaWanService();

  // Methods to start and stop the FreeRTOS task
  void startTask();
  void stopTask();

private:
  TaskHandle_t loraTaskHandle = nullptr; // Handle for the FreeRTOS task

  // Task function that will be run as a FreeRTOS task
  static void LoRaWanTaskFunction(void *pvParameters);
};

#endif // USE_LORAWAN