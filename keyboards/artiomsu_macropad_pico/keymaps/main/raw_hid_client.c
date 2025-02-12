#include "raw_hid_client.h"
                                    //vid, pid
//struct raw_hid_client trackball = {0x9000, 0x9001};

struct raw_hid_client pc = {0x0000, 0x0000};
struct raw_hid_client broadcast = {0xffff, 0xffff};

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if(length != RAW_EPSIZE){
        return;
    }
    struct hid_packet *packet = (struct hid_packet *)data;

    if(packet->header != HID_PACKET_HEADER){
        char c[8];
        SEND_STRING("header is bad for pico macropad ");
        snprintf(c, sizeof(c), "%X ", packet->header);
        SEND_STRING(c);

        for (int i = 0; i < length; i++){
            snprintf(c, sizeof(c), "%02X", data[i]);
            SEND_STRING(c);
        }
        return;
    }

    switch (packet->operation){
        case HID_RAW_OP_SIMPLE_KEY_2:
            SEND_STRING("received data at pico macro pad");
        break;
    }
}

void raw_hid_send_to_router(struct raw_hid_client *client,
    uint8_t operation,
    uint8_t *payload,
    uint8_t payload_len
){

    if(payload_len > HID_PACKET_PAYLOAD_LEN){
        return;
    }

    struct hid_packet pack;

    pack.header = HID_PACKET_HEADER;
    pack.to_vid = client->vid;
    pack.to_pid = client->pid;
    pack.operation = operation;
    pack.payload_length = payload_len;
    memset(pack.payload, 0, sizeof(pack.payload));
    memcpy(pack.payload, payload, payload_len);

    raw_hid_send((uint8_t *)&pack, RAW_EPSIZE);
}

void simple_hid_test_send_key(struct raw_hid_client *client, uint8_t key){
    uint8_t test[4] = {key, 0x02, 0x03, 0xff};
    raw_hid_send_to_router(
        client,
        HID_RAW_OP_SIMPLE_KEY_2,
        test,
        4
    );
}

void raw_hid_set_setting(struct raw_hid_client *client, uint8_t setting, uint8_t data){
    uint8_t s[2] = {setting, data};
    raw_hid_send_to_router(
        client,
        HID_RAW_SET_SETTING,
        s,
        2
    );
}

void raw_hid_custom_key(struct raw_hid_client *client, uint8_t key, bool pressed){
    uint8_t data[2] = {key, pressed};
    raw_hid_send_to_router(
        client,
        HID_RAW_CUSTOM_KEY,
        data,
        2
    );
}

void raw_hid_send_info(struct raw_hid_client *client, char* info, uint8_t length){
    raw_hid_send_to_router(
        client,
        HID_RAW_OP_INFO,
        (uint8_t *)info,
        length
    );
}
