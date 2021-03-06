/*******************************************************************************
 * Copyright (c) 2014 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial API and implementation and/or initial documentation
 *    Benjamin Cabe - generic IPStack
 *******************************************************************************/

#if !defined(IPSTACK_H)
#define IPSTACK_H

#include <SPI.h>

#include <sim800Client.h>

class IPStack 
{
public:    
    IPStack(sim800Client& client) : client(&client)
    {

    }
    
    int connect(char* hostname, int port)
    {
      if (client->connect(hostname, port)) return 1;
      return 0;
    }

    int connect(uint32_t hostname, int port)
    {
      if (client->connect(hostname, port)) return 1;
      return 0;
    }

    int read(unsigned char* buffer, int len, unsigned long timeout)
    {
      //Serial.print("+ read timeout: ");
      //Serial.println(timeout);
      client->setTimeout(timeout);  
      int rc=(int)client->readBytes((char*)buffer, len);
      //Serial.print("+ read wanted: ");
      //Serial.println(len);
      //Serial.print("+ read getted: ");
      //Serial.println(rc);
      return rc;
    }
    
    int write(unsigned char* buffer, int len, unsigned long timeout)
    {
      //Serial.print("write timeout: ");
      //Serial.println(timeout);
      return client->write((uint8_t*)buffer, len);
    }
    
    int disconnect()
    {
        client->stop();
        return 1;
    }

private:

    sim800Client* client;
};

#endif


