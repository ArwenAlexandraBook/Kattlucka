#include "WiFi.h"
#include "esp_wifi.h"
#include "esp_log.h"

static const char *TAG = "wifi";

void wifi_init_sta(void) {
    ESP_LOGI(TAG, "Connecting to wifi...");

   esp_netif_init();
   esp_event_loop_create_default();

    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "your-ssid",
            .password = "your-password",
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
            .pmf_cfg = {
                .capable = true, 
                .required = false,
        },
    },
};

esp_wifi_set_mode(WIFI_MODE_STA);
esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
esp_wifi_start();

ESP_LOGI(TAG, "Wifi is connected");
}