#include <Pages.h>

SoftwareSerial mySerial(5, 6);

ELClient esp(&mySerial, &mySerial);

// Initialize the Web-Server client
ELClientWebServer webServer(&esp);
