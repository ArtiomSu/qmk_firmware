#include "sharedDefines.h"

#include "usb_descriptor.h"
//#include "hid_display.h"
#include "raw_hid.h"

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t response[RAW_EPSIZE];
    memset(response, 0, RAW_EPSIZE);
    response[0] = 0xfe;
    response[1] = 0xed;

    //if(data[0] == 'A') {
    raw_hid_send(response, RAW_EPSIZE);
    //}

    // if(data[0] == 0x01){
    //     SEND_STRING("Got 01 in hid");
    // }else if(data[0] == 0x1f){
    //     SEND_STRING("GOT 1f in hid");
    // }else{
    //     SEND_STRING("GOT something else");
    // }

}
