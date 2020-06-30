/*
  Licensed to the Apache Software Foundation (ASF) under one
  or more contributor license agreements.  See the NOTICE file
  distributed with this work for additional information
  regarding copyright ownership.  The ASF licenses this file
  to you under the Apache License, Version 2.0 (the
  "License"); you may not use this file except in compliance
  with the License.  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing,
  software distributed under the License is distributed on an
  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
  KIND, either express or implied.  See the License for the
  specific language governing permissions and limitations
  under the License.
*/

#include <stdio.h>
#include <plc4c/spi/read_buffer.h>
#include <plc4c/spi/write_buffer.h>
#include <plc4c/spi/evaluation_helper.h>
#include "tpkt_packet.h"

// Parse function.
plc4c_return_code plc4c_s7_read_write_tpkt_packet_parse(plc4c_spi_read_buffer* buf, plc4c_s7_read_write_tpkt_packet** _message) {
  uint16_t startPos = plc4c_spi_read_get_pos(buf);
  uint16_t curPos;
  plc4c_return_code _res = OK;

  // Allocate enough memory to contain this data structure.
  (*_message) = malloc(sizeof(plc4c_s7_read_write_tpkt_packet));
  if(*_message == NULL) {
    return NO_MEMORY;
  }

  // Const Field (protocolId)
  uint8_t protocolId = 0;
  _res = plc4c_spi_read_unsigned_short(buf, 8, &protocolId);
  if(_res != OK) {
    return _res;
  }
  if(protocolId != S7_READ_WRITE_TPKT_PACKET_PROTOCOL_ID) {
    return PARSE_ERROR;
    // throw new ParseException("Expected constant value " + S7_READ_WRITE_TPKT_PACKET_PROTOCOL_ID + " but got " + protocolId);
  }

  // Reserved Field (Compartmentalized so the "reserved" variable can't leak)
  {
    uint8_t _reserved = 0;
    _res = plc4c_spi_read_unsigned_short(buf, 8, _reserved);
    if(_res != OK) {
      return _res;
    }
    if(_reserved != 0x00) {
      printf("Expected constant value '%d' but got '%d' for reserved field.", 0x00, _reserved);
    }
  }

  // Implicit Field (len) (Used for parsing, but it's value is not stored as it's implicitly given by the objects content)
  uint16_t len = 0;
  _res = plc4c_spi_read_unsigned_int(buf, 16, &len);
  if(_res != OK) {
    return _res;
  }

  // Simple Field (payload)
  plc4c_s7_read_write_cotp_packet* payload;
  _res = plc4c_s7_read_write_cotp_packet_parse(buf, (len) - (4), (void*) &payload);
  if(_res != OK) {
    return _res;
  }
  (*_message)->payload = payload;

  return OK;
}

plc4c_return_code plc4c_s7_read_write_tpkt_packet_serialize(plc4c_spi_write_buffer* buf, plc4c_s7_read_write_tpkt_packet* _message) {
  plc4c_return_code _res = OK;

  // Const Field (protocolId)
  plc4c_spi_write_unsigned_short(buf, 8, S7_READ_WRITE_TPKT_PACKET_PROTOCOL_ID);

  // Reserved Field
  _res = plc4c_spi_write_unsigned_short(buf, 8, 0x00);
  if(_res != OK) {
    return _res;
  }

  // Implicit Field (len) (Used for parsing, but it's value is not stored as it's implicitly given by the objects content)
  _res = plc4c_spi_write_unsigned_int(buf, 16, (plc4c_s7_read_write_cotp_packet_length_in_bytes(_message->payload)) + (4));
  if(_res != OK) {
    return _res;
  }

  // Simple Field (payload)
  _res = plc4c_s7_read_write_cotp_packet_serialize(buf, "_message->payload");
  if(_res != OK) {
    return _res;
  }

  return OK;
}

uint8_t plc4c_s7_read_write_tpkt_packet_length_in_bytes(plc4c_s7_read_write_tpkt_packet* _message) {
  return plc4c_s7_read_write_tpkt_packet_length_in_bits(_message) / 8;
}

uint8_t plc4c_s7_read_write_tpkt_packet_length_in_bits(plc4c_s7_read_write_tpkt_packet* _message) {
  uint8_t lengthInBits = 0;

  // Const Field (protocolId)
  lengthInBits += 8;

  // Reserved Field (reserved)
  lengthInBits += 8;

  // Implicit Field (len)
  lengthInBits += 16;

  // Simple field (payload)
  lengthInBits += plc4c_s7_read_write_cotp_packet_length_in_bits(_message->payload);

  return lengthInBits;
}

