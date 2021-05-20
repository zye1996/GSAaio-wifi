#ifndef PAGES_H
#define PAGES_H

#include <SoftwareSerial.h>
#include <ELClient.h>
#include <ELClientWebServer.h>

extern SoftwareSerial mySerial;

extern ELClient esp;

// Initialize the Web-Server client
extern ELClientWebServer webServer;

void PIDInit();
void printloop();


#endif /* PAGES_H */