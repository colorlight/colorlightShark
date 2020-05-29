/* packet-ff.h
 * FF-HSE definition
 *
 * FF-588-1.3: HSE Field Device Access Agent
 * 6. Field Device Access Agent Interface
 *
 * (c) Copyright 2008, Yukiyo Akisada <Yukiyo.Akisada@jp.yokogawa.com>
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

/*
 * /etc/services
 * ---------------------------------------------------------------------
 * ff-annunc    1089/tcp    # FF Annunciation
 * ff-annunc    1089/udp    # FF Annunciation
 * ff-fms       1090/tcp    # FF Fieldbus Message Specification
 * ff-fms       1090/udp    # FF Fieldbus Message Specification
 * ff-sm        1091/tcp    # FF System Management
 * ff-sm        1091/udp    # FF System Management
 * ff-lr-port   3622/tcp    # FF LAN Redundancy Port
 * ff-lr-port   3622/udp    # FF LAN Redundancy Port
 * ---------------------------------------------------------------------
 */

#ifndef __PACKET_FF_H__
#define __PACKET_FF_H__

#define UDP_PORT_FF_RANGE   "1089-1091,3622"
#define TCP_PORT_FF_ANNUNC  1089

#define TCP_PORT_FF_FMS     1090

#define TCP_PORT_FF_SM      1091

#define TCP_PORT_FF_LR_PORT 3622



/*
 * 6.3. Message Header
 */

/*
 * Options
 */

#define OPTION_MESSAGE_NUMBER_MASK  0x80    /* 10000000 */
#define OPTION_INVOKE_ID_MASK       0x40    /* 01000000 */
#define OPTION_TIME_STAMP_MASK      0x20    /* 00100000 */
#define OPTION_RESERVED_MASK        0x10    /* 00010000 */
#define OPTION_EXTENDED_CNTRL_MASK  0x08    /* 00001000 */
#define OPTION_PAD_LENGTH_MASK      0x07    /* 00000111 */

#define OPTION_PAD_4BYTE    0x03    /* 00000011 */
#define OPTION_PAD_8BYTE    0x07    /* 00000111 */

/*
 * Protocol Id And Confirmed Msg Type
 */

#define PROTOCOL_MASK   0xfc    /* 11111100 */
#define TYPE_MASK       0x03    /* 00000011 */

/*
 * Protocol Id
 */
#define PROTOCOL_FDA    0x04    /* 00000100 */
#define PROTOCOL_SM     0x08    /* 00001000 */
#define PROTOCOL_FMS    0x0c    /* 00001100 */
#define PROTOCOL_LAN    0x10    /* 00010000 */

/*
 * Confirmed Msg Type
 */
#define TYPE_REQUEST    0x00    /* 00000000 */
#define TYPE_RESPONSE   0x01    /* 00000001 */
#define TYPE_ERROR      0x02    /* 00000010 */

/*
 * Service
 */

#define SERVICE_CONFIRMED_FLAG_MASK 0x80    /* 10000000 */
#define SERVICE_SERVICE_ID_MASK     0x7f    /* 01111111 */

#define FDA_UNCONFIRMED_SERVICE 0x00    /* 00000000 */
#define FDA_CONFIRMED_SERVICE   0x80    /* 10000000 */



#define PROTOCOL_FDA_MSG    (PROTOCOL_FDA  << 8)
#define PROTOCOL_SM_MSG     (PROTOCOL_SM   << 8)
#define PROTOCOL_FMS_MSG    (PROTOCOL_FMS  << 8)
#define PROTOCOL_LAN_MSG    (PROTOCOL_LAN  << 8)



#define PROTOCOL_TYPE_REQ   (TYPE_REQUEST  << 8)
#define PROTOCOL_TYPE_RSP   (TYPE_RESPONSE << 8)
#define PROTOCOL_TYPE_ERR   (TYPE_ERROR    << 8)



/*
 * 6.5.1. FDA Session Management Services
 */

/* Confirmed Service Id */
#define FDA_OPEN_SESSION    1
#define FDA_IDLE            3

/* 6.5.1.1. FDA Open Session (Confirmed Service Id = 1) */
#define FDA_MSG_SESSION_OPEN_REQ \
    (PROTOCOL_FDA_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | FDA_OPEN_SESSION)
#define FDA_MSG_SESSION_OPEN_RSP \
    (PROTOCOL_FDA_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | FDA_OPEN_SESSION)
#define FDA_MSG_SESSION_OPEN_ERR \
    (PROTOCOL_FDA_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | FDA_OPEN_SESSION)

/* 6.5.1.2. FDA Idle (Confirmed Service Id = 3) */
#define FDA_MSG_SESSION_IDLE_REQ \
    (PROTOCOL_FDA_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | FDA_IDLE)
#define FDA_MSG_SESSION_IDLE_RSP \
    (PROTOCOL_FDA_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | FDA_IDLE)
#define FDA_MSG_SESSION_IDLE_ERR \
    (PROTOCOL_FDA_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | FDA_IDLE)



/*
 * 6.5.2. SM Services
 */

/* Unconfirmed Service Id */
#define HSE_SM_FIND_TAG_QUERY        1
#define HSE_SM_FIND_TAG_REPLY        2
#define HSE_SM_DEVICE_ANNUNCIATION  16

/* Confirmed Service Id */
#define HSE_SM_IDENTIFY              3
#define HSE_SM_CLEAR_ADDRESS        12
#define HSE_SM_SET_ASSIGNMENT       14
#define HSE_SM_CLEAR_ASSIGNMENT     15

/* 6.5.2.1. SM Find Tag Query (Unconfirmed Service Id = 1) */
#define SM_MSG_FIND_TAG_QUERY_REQ \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_REQ | \
        FDA_UNCONFIRMED_SERVICE | HSE_SM_FIND_TAG_QUERY)

/* 6.5.2.2. SM Find Tag Reply (Unconfirmed Service Id = 2) */
#define SM_MSG_FIND_TAG_REPLY_REQ \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_REQ | \
        FDA_UNCONFIRMED_SERVICE | HSE_SM_FIND_TAG_REPLY)

/* 6.5.2.3. SM Identify (Confirmed Service Id = 3) */
#define SM_MSG_IDENTIFY_REQ \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_SM_IDENTIFY)
#define SM_MSG_IDENTIFY_RSP \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_SM_IDENTIFY)
#define SM_MSG_IDENTIFY_ERR \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_SM_IDENTIFY)

/* 6.5.2.4. SM Clear Address (Confirmed Service Id = 12) */
#define SM_MSG_CLEAR_ADDRESS_REQ \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_SM_CLEAR_ADDRESS)
#define SM_MSG_CLEAR_ADDRESS_RSP \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_SM_CLEAR_ADDRESS)
#define SM_MSG_CLEAR_ADDRESS_ERR \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_SM_CLEAR_ADDRESS)

/* 6.5.2.5. SM Set Assignment Info (Confirmed Service Id = 14) */
#define SM_MSG_SET_ASSIGNMENT_REQ \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_SM_SET_ASSIGNMENT)
#define SM_MSG_SET_ASSIGNMENT_RSP \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_SM_SET_ASSIGNMENT)
#define SM_MSG_SET_ASSIGNMENT_ERR \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_SM_SET_ASSIGNMENT)

/* 6.5.2.6. SM Clear Assignment Info (Confirmed Service Id = 15) */
#define SM_MSG_CLEAR_ASSIGNMENT_REQ \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_SM_CLEAR_ASSIGNMENT)
#define SM_MSG_CLEAR_ASSIGNMENT_RSP \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_SM_CLEAR_ASSIGNMENT)
#define SM_MSG_CLEAR_ASSIGNMENT_ERR \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_SM_CLEAR_ASSIGNMENT)

/* 6.5.2.7. SM Device Annunciation (Unconfirmed Service Id = 16) */
#define SM_MSG_DEVICE_ANNUNCIATION_REQ \
    (PROTOCOL_SM_MSG | PROTOCOL_TYPE_REQ | \
        FDA_UNCONFIRMED_SERVICE | HSE_SM_DEVICE_ANNUNCIATION)



/*
 * 6.5.3. FMS Services
 */

/* Unconfirmed Service Id */
#define HSE_FMS_INFORMATION_REPORT                            0
#define HSE_FMS_UNSOLICITED_STATUS                            1
#define HSE_FMS_EVENT_NOTIFICATION                            2
#define HSE_FMS_INFORMATION_REPORT_WITH_SUBINDEX             16
#define HSE_FMS_INFORMATION_REPORT_ON_CHANGE                 17
#define HSE_FMS_INFORMATION_REPORT_ON_CHANGE_WITH_SUBINDEX   18
#define HSE_FMS_ABORT                                       112

/* Confirmed Service Id */
#define HSE_FMS_STATUS                               0
#define HSE_FMS_IDENTIFY                             1
#define HSE_FMS_READ                                 2
#define HSE_FMS_WRITE                                3
#define HSE_FMS_GET_OD                               4
#define HSE_FMS_DEFINE_VARIABLE_LIST                 7
#define HSE_FMS_DELETE_VARIABLE_LIST                 8
#define HSE_FMS_INITIATE_DOWNLOAD_SEQUENCE           9
#define HSE_FMS_DOWNLOAD_SEGMENT                    10
#define HSE_FMS_TERMINATE_DOWNLOAD_SEQUENCE         11
#define HSE_FMS_INITIATE_UPLOAD_SEQUENCE            12
#define HSE_FMS_UPLOAD_SEGMENT                      13
#define HSE_FMS_TERMINATE_UPLOAD_SEQUENCE           14
#define HSE_FMS_REQUEST_DOMAIN_DOWNLOAD             15
#define HSE_FMS_REQUEST_DOMAIN_UPLOAD               16
#define HSE_FMS_CREATE_PROGRAM_INVOCATION           17
#define HSE_FMS_DELETE_PROGRAM_INVOCATION           18
#define HSE_FMS_START                               19
#define HSE_FMS_STOP                                20
#define HSE_FMS_RESUME                              21
#define HSE_FMS_RESET                               22
#define HSE_FMS_KILL                                23
#define HSE_FMS_ALTER_EVENT_CONDITION_MONITORING    24
#define HSE_FMS_ACKNOWLEDGE_EVENT_NOTIFICATION      25
#define HSE_FMS_INITIATE_PUT_OD                     28
#define HSE_FMS_PUT_OD                              29
#define HSE_FMS_TERMINATE_PUT_OD                    30
#define HSE_FMS_GENERIC_INITIATE_DOWNLOAD_SEQUENCE  31
#define HSE_FMS_GENERIC_DOWNLOAD_SEGMENT            32
#define HSE_FMS_GENERIC_TERMINATE_DOWNLOAD_SEQUENCE 33
#define HSE_FMS_READ_WITH_SUBINDEX                  82
#define HSE_FMS_WRITE_WITH_SUBINDEX                 83
#define HSE_FMS_INITIATE                            96

/* 6.5.3.1. FMS Reject */

/* 6.5.3.2. FMS Initiate (Confirmed Service Id = 96) */
#define FMS_MSG_INITIATE_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_INITIATE)
#define FMS_MSG_INITIATE_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_INITIATE)
#define FMS_MSG_INITIATE_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_INITIATE)

/* 6.5.3.3. FMS Abort (Unconfirmed Service Id = 112) */
#define FMS_MSG_ABORT_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_UNCONFIRMED_SERVICE | HSE_FMS_ABORT)

/* 6.5.3.4. FMS Status (Confirmed Service Id = 0) */
#define FMS_MSG_STATUS_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_STATUS)
#define FMS_MSG_STATUS_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_STATUS)
#define FMS_MSG_STATUS_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_STATUS)

/* 6.5.3.5. FMS Unsolicited Status (Unconfirmed Service Id = 1) */
#define FMS_MSG_UNSOLICITED_STATUS_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_UNCONFIRMED_SERVICE | HSE_FMS_UNSOLICITED_STATUS)

/* 6.5.3.6. FMS Identify (Confirmed Service Id = 1) */
#define FMS_MSG_IDENTIFY_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_IDENTIFY)
#define FMS_MSG_IDENTIFY_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_IDENTIFY)
#define FMS_MSG_IDENTIFY_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_IDENTIFY)

/* 6.5.3.7. FMS Get OD (Confirmed Service Id = 4) */
#define FMS_MSG_GET_OD_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_GET_OD)
#define FMS_MSG_GET_OD_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_GET_OD)
#define FMS_MSG_GET_OD_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_GET_OD)

/* 6.5.3.8. FMS Initiate Put OD (Confirmed Service Id = 28) */
#define FMS_MSG_INITIATE_PUT_OD_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_INITIATE_PUT_OD)
#define FMS_MSG_INITIATE_PUT_OD_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_INITIATE_PUT_OD)
#define FMS_MSG_INITIATE_PUT_OD_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_INITIATE_PUT_OD)

/* 6.5.3.9. FMS Put OD (Confirmed Service Id = 29) */
#define FMS_MSG_PUT_OD_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_PUT_OD)
#define FMS_MSG_PUT_OD_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_PUT_OD)
#define FMS_MSG_PUT_OD_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_PUT_OD)

/* 6.5.3.10. FMS Terminate Put OD (Confirmed Service Id = 30) */
#define FMS_MSG_TERMINATE_PUT_OD_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_TERMINATE_PUT_OD)
#define FMS_MSG_TERMINATE_PUT_OD_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_TERMINATE_PUT_OD)
#define FMS_MSG_TERMINATE_PUT_OD_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_TERMINATE_PUT_OD)

/* 6.5.3.11. FMS Generic Initiate Download Sequence
             (Confirmed Service Id = 31) */
#define FMS_MSG_GENERIC_INITIATE_DOWNLOAD_SEQUENCE_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_GENERIC_INITIATE_DOWNLOAD_SEQUENCE)
#define FMS_MSG_GENERIC_INITIATE_DOWNLOAD_SEQUENCE_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_GENERIC_INITIATE_DOWNLOAD_SEQUENCE)
#define FMS_MSG_GENERIC_INITIATE_DOWNLOAD_SEQUENCE_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_GENERIC_INITIATE_DOWNLOAD_SEQUENCE)

/* 6.5.3.12. FMS Generic Download Segment (Confirmed Service Id = 32) */
#define FMS_MSG_GENERIC_DOWNLOAD_SEGMENT_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_GENERIC_DOWNLOAD_SEGMENT)
#define FMS_MSG_GENERIC_DOWNLOAD_SEGMENT_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_GENERIC_DOWNLOAD_SEGMENT)
#define FMS_MSG_GENERIC_DOWNLOAD_SEGMENT_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_GENERIC_DOWNLOAD_SEGMENT)

/* 6.5.3.13. FMS Generic Terminate Download Sequence
             (Confirmed Service Id = 33) */
#define FMS_MSG_GENERIC_TERMINATE_DOWNLOAD_SEQUENCE_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_GENERIC_TERMINATE_DOWNLOAD_SEQUENCE)
#define FMS_MSG_GENERIC_TERMINATE_DOWNLOAD_SEQUENCE_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_GENERIC_TERMINATE_DOWNLOAD_SEQUENCE)
#define FMS_MSG_GENERIC_TERMINATE_DOWNLOAD_SEQUENCE_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_GENERIC_TERMINATE_DOWNLOAD_SEQUENCE)

/* 6.5.3.14. FMS Initiate Download Sequence (Confirmed Service Id = 9) */
#define FMS_MSG_INITIATE_DOWNLOAD_SEQUENCE_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_INITIATE_DOWNLOAD_SEQUENCE)
#define FMS_MSG_INITIATE_DOWNLOAD_SEQUENCE_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_INITIATE_DOWNLOAD_SEQUENCE)
#define FMS_MSG_INITIATE_DOWNLOAD_SEQUENCE_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_INITIATE_DOWNLOAD_SEQUENCE)

/* 6.5.3.15. FMS Download Segment (Confirmed Service Id = 10) */
#define FMS_MSG_DOWNLOAD_SEGMENT_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_DOWNLOAD_SEGMENT)
#define FMS_MSG_DOWNLOAD_SEGMENT_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_DOWNLOAD_SEGMENT)
#define FMS_MSG_DOWNLOAD_SEGMENT_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_DOWNLOAD_SEGMENT)

/* 6.5.3.16. FMS Terminate Download Sequence (Confirmed Service Id = 11) */
#define FMS_MSG_TERMINATE_DOWNLOAD_SEQUENCE_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_TERMINATE_DOWNLOAD_SEQUENCE)
#define FMS_MSG_TERMINATE_DOWNLOAD_SEQUENCE_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_TERMINATE_DOWNLOAD_SEQUENCE)
#define FMS_MSG_TERMINATE_DOWNLOAD_SEQUENCE_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_TERMINATE_DOWNLOAD_SEQUENCE)

/* 6.5.3.17. FMS Initiate Upload Sequence (Confirmed Service Id = 12) */
#define FMS_MSG_INITIATE_UPLOAD_SEQUENCE_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_INITIATE_UPLOAD_SEQUENCE)
#define FMS_MSG_INITIATE_UPLOAD_SEQUENCE_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_INITIATE_UPLOAD_SEQUENCE)
#define FMS_MSG_INITIATE_UPLOAD_SEQUENCE_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_INITIATE_UPLOAD_SEQUENCE)

/* 6.5.3.18. FMS Upload Segment (Confirmed Service Id = 13) */
#define FMS_MSG_UPLOAD_SEGMENT_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_UPLOAD_SEGMENT)
#define FMS_MSG_UPLOAD_SEGMENT_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_UPLOAD_SEGMENT)
#define FMS_MSG_UPLOAD_SEGMENT_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_UPLOAD_SEGMENT)

/* 6.5.3.19. FMS Terminate Upload Sequence (Confirmed Service Id = 14) */
#define FMS_MSG_TERMINATE_UPLOAD_SEQUENCE_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_TERMINATE_UPLOAD_SEQUENCE)
#define FMS_MSG_TERMINATE_UPLOAD_SEQUENCE_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_TERMINATE_UPLOAD_SEQUENCE)
#define FMS_MSG_TERMINATE_UPLOAD_SEQUENCE_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_TERMINATE_UPLOAD_SEQUENCE)

/* 6.5.3.20. FMS Request Domain Download (Confirmed Service Id = 15) */
#define FMS_MSG_REQUEST_DOMAIN_DOWNLOAD_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_REQUEST_DOMAIN_DOWNLOAD)
#define FMS_MSG_REQUEST_DOMAIN_DOWNLOAD_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_REQUEST_DOMAIN_DOWNLOAD)
#define FMS_MSG_REQUEST_DOMAIN_DOWNLOAD_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_REQUEST_DOMAIN_DOWNLOAD)

/* 6.5.3.21. FMS Request Domain Upload (Confirmed Service Id = 16) */
#define FMS_MSG_REQUEST_DOMAIN_UPLOAD_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_REQUEST_DOMAIN_UPLOAD)
#define FMS_MSG_REQUEST_DOMAIN_UPLOAD_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_REQUEST_DOMAIN_UPLOAD)
#define FMS_MSG_REQUEST_DOMAIN_UPLOAD_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_REQUEST_DOMAIN_UPLOAD)

/* 6.5.3.22. FMS Create Program Invocation (Confirmed Service Id = 17) */
#define FMS_MSG_CREATE_PI_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_CREATE_PROGRAM_INVOCATION)
#define FMS_MSG_CREATE_PI_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_CREATE_PROGRAM_INVOCATION)
#define FMS_MSG_CREATE_PI_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_CREATE_PROGRAM_INVOCATION)

/* 6.5.3.23. FMS Delete Program Invocation (Confirmed Service Id = 18) */
#define FMS_MSG_DELETE_PI_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_DELETE_PROGRAM_INVOCATION)
#define FMS_MSG_DELETE_PI_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_DELETE_PROGRAM_INVOCATION)
#define FMS_MSG_DELETE_PI_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_DELETE_PROGRAM_INVOCATION)

/* 6.5.3.24. FMS Start (Confirmed Service Id = 19) */
#define FMS_MSG_START_PI_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_START)
#define FMS_MSG_START_PI_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_START)
#define FMS_MSG_START_PI_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_START)

/* 6.5.3.25. FMS Stop (Confirmed Service Id = 20) */
#define FMS_MSG_STOP_PI_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_STOP)
#define FMS_MSG_STOP_PI_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_STOP)
#define FMS_MSG_STOP_PI_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_STOP)

/* 6.5.3.26. FMS Resume (Confirmed Service Id = 21) */
#define FMS_MSG_RESUME_PI_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_RESUME)
#define FMS_MSG_RESUME_PI_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_RESUME)
#define FMS_MSG_RESUME_PI_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_RESUME)

/* 6.5.3.27. FMS Reset (Confirmed Service Id = 22) */
#define FMS_MSG_RESET_PI_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_RESET)
#define FMS_MSG_RESET_PI_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_RESET)
#define FMS_MSG_RESET_PI_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_RESET)

/* 6.5.3.28. FMS Kill (Confirmed Service Id = 23) */
#define FMS_MSG_KILL_PI_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_KILL)
#define FMS_MSG_KILL_PI_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_KILL)
#define FMS_MSG_KILL_PI_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_KILL)

/* 6.5.3.29. FMS Read (Confirmed Service Id = 2) */
#define FMS_MSG_READ_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_READ)
#define FMS_MSG_READ_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_READ)
#define FMS_MSG_READ_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_READ)

/* 6.5.3.30. FMS Read with Subindex (Confirmed Service Id = 82) */
#define FMS_MSG_READ_SUBINDEX_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_READ_WITH_SUBINDEX)
#define FMS_MSG_READ_SUBINDEX_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_READ_WITH_SUBINDEX)
#define FMS_MSG_READ_SUBINDEX_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_READ_WITH_SUBINDEX)

/* 6.5.3.31. FMS Write (Confirmed Service Id = 3) */
#define FMS_MSG_WRITE_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_WRITE)
#define FMS_MSG_WRITE_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_WRITE)
#define FMS_MSG_WRITE_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_WRITE)

/* 6.5.3.32. FMS Write with Subindex (Confirmed Service Id = 83) */
#define FMS_MSG_WRITE_SUBINDEX_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_WRITE_WITH_SUBINDEX)
#define FMS_MSG_WRITE_SUBINDEX_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_WRITE_WITH_SUBINDEX)
#define FMS_MSG_WRITE_SUBINDEX_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_WRITE_WITH_SUBINDEX)

/* 6.5.3.33. FMS Define Variable List (Confirmed Service Id = 7) */
#define FMS_MSG_DEFINE_VARIABLE_LIST_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_DEFINE_VARIABLE_LIST)
#define FMS_MSG_DEFINE_VARIABLE_LIST_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_DEFINE_VARIABLE_LIST)
#define FMS_MSG_DEFINE_VARIABLE_LIST_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_DEFINE_VARIABLE_LIST)

/* 6.5.3.34. FMS Delete Variable List (Confirmed Service Id = 8) */
#define FMS_MSG_DELETE_VARIABLE_LIST_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_DELETE_VARIABLE_LIST)
#define FMS_MSG_DELETE_VARIABLE_LIST_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_DELETE_VARIABLE_LIST)
#define FMS_MSG_DELETE_VARIABLE_LIST_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_DELETE_VARIABLE_LIST)

/* 6.5.3.35. FMS Information Report (Unconfirmed Service Id = 0) */
#define FMS_MSG_INFO_REPORT_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_UNCONFIRMED_SERVICE | HSE_FMS_INFORMATION_REPORT)

/* 6.5.3.36. FMS Information Report with Subindex
    (Unconfirmed Service Id = 16) */
#define FMS_MSG_INFO_REPORT_SUBINDEX_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_UNCONFIRMED_SERVICE | HSE_FMS_INFORMATION_REPORT_WITH_SUBINDEX)

/* 6.5.3.37. FMS Information Report On Change (Unconfirmed Service Id = 17) */
#define FMS_MSG_INFO_REPORT_CHANGE_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_UNCONFIRMED_SERVICE | HSE_FMS_INFORMATION_REPORT_ON_CHANGE)

/* 6.5.3.38. FMS Information Report On Change with Subindex
    (Unconfirmed Service Id = 18) */
#define FMS_MSG_INFO_REPORT_CHANGE_SUBINDEX_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | FDA_UNCONFIRMED_SERVICE | \
        HSE_FMS_INFORMATION_REPORT_ON_CHANGE_WITH_SUBINDEX)

/* 6.5.3.39. FMS Event Notification (Unconfirmed Service Id = 2) */
#define FMS_MSG_EVENT_NOTIFICATION_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_UNCONFIRMED_SERVICE | HSE_FMS_EVENT_NOTIFICATION)

/* 6.5.3.40. FMS Alter Event Condition Monitoring (Confirmed Service Id = 24) */
#define FMS_MSG_ALTER_EVENT_CONDITION_MONITORING_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_ALTER_EVENT_CONDITION_MONITORING)
#define FMS_MSG_ALTER_EVENT_CONDITION_MONITORING_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_ALTER_EVENT_CONDITION_MONITORING)
#define FMS_MSG_ALTER_EVENT_CONDITION_MONITORING_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_ALTER_EVENT_CONDITION_MONITORING)

/* 6.5.3.41. FMS Acknowledge Event Notification (Confirmed Service Id = 25) */
#define FMS_MSG_ACKNOWLEDGE_EVENT_NOTIFICATION_REQ \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_ACKNOWLEDGE_EVENT_NOTIFICATION)
#define FMS_MSG_ACKNOWLEDGE_EVENT_NOTIFICATION_RSP \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_ACKNOWLEDGE_EVENT_NOTIFICATION)
#define FMS_MSG_ACKNOWLEDGE_EVENT_NOTIFICATION_ERR \
    (PROTOCOL_FMS_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | HSE_FMS_ACKNOWLEDGE_EVENT_NOTIFICATION)



/*
 * 6.5.4 LAN Redundancy Services
 */

/* Unconfirmed Service Id */
#define LAN_DIAG    1

/* Confirmed Service Id */
#define LAN_GET_INFO        1
#define LAN_PUT_INFO        2
#define LAN_GET_STATISTICS  3

/* 6.5.4.1. LAN Redundancy Get Information (Confirmed Service Id = 1) */
#define LAN_MSG_GET_INFO_REQ \
    (PROTOCOL_LAN_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | LAN_GET_INFO)
#define LAN_MSG_GET_INFO_RSP \
    (PROTOCOL_LAN_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | LAN_GET_INFO)
#define LAN_MSG_GET_INFO_ERR \
    (PROTOCOL_LAN_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | LAN_GET_INFO)

/* 6.5.4.2. LAN Redundancy Put Information (Confirmed Service Id = 2) */
#define LAN_MSG_PUT_INFO_REQ \
    (PROTOCOL_LAN_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | LAN_PUT_INFO)
#define LAN_MSG_PUT_INFO_RSP \
    (PROTOCOL_LAN_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | LAN_PUT_INFO)
#define LAN_MSG_PUT_INFO_ERR \
    (PROTOCOL_LAN_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | LAN_PUT_INFO)

/* 6.5.4.3. LAN Redundancy Get Statistics (Confirmed Service Id = 3) */
#define LAN_MSG_GET_STATISTICS_REQ \
    (PROTOCOL_LAN_MSG | PROTOCOL_TYPE_REQ | \
        FDA_CONFIRMED_SERVICE | LAN_GET_STATISTICS)
#define LAN_MSG_GET_STATISTICS_RSP \
    (PROTOCOL_LAN_MSG | PROTOCOL_TYPE_RSP | \
        FDA_CONFIRMED_SERVICE | LAN_GET_STATISTICS)
#define LAN_MSG_GET_STATISTICS_ERR \
    (PROTOCOL_LAN_MSG | PROTOCOL_TYPE_ERR | \
        FDA_CONFIRMED_SERVICE | LAN_GET_STATISTICS)

/* 6.5.4.4. Diagnostic Message (Unconfirmed Service Id = 1) */
#define LAN_MSG_DIAG_REQ \
    (PROTOCOL_LAN_MSG | PROTOCOL_TYPE_REQ | \
        FDA_UNCONFIRMED_SERVICE | LAN_DIAG)
#endif  /* __PACKET_FF_H__ */
