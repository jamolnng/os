#pragma once

#ifdef __cplusplus
extern "C" {
#endif

unsigned char port_in_b(unsigned short port);
unsigned short port_in_w(unsigned short port);
void port_out_b(unsigned short port, unsigned char data);
void port_out_w(unsigned short port, unsigned short data);

#ifdef __cplusplus
}
#endif
