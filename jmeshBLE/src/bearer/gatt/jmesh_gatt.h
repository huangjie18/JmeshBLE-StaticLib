#ifndef JMESH_GATT_H
#define JMESH_GATT_H

#include"../../onchip_system/os_timer_event.h"



#define JMESH_GATT_ID_INVALID       0xff
#define JMESH_GATT_CONNECT_S        5
#define JMESH_GATT_ACTIVE_S         10
#define JMESH_GATT_SIZE             10

#define JMESH_GATT_CONNECT_LIMIT 6
#define JMESH_GATT_CONNECT_INTERVAL_S 5
#define JMESH_ROUTE_REMOVE_INTERVAL_S 60


#define JMESH_SVC_UUID {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x03,0xff,0x00,0x00}
#define JMESH_APP_SVC_UUID {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x04,0xff,0x00,0x00}
enum{
    JMESHS_IDX_PROV_SVC,

    JMESHS_IDX_MESH_PROVISIONING_DATA_IN_CHAR,
    JMESHS_IDX_MESH_PROVISIONING_DATA_IN_VAL,
	
    JMESHS_IDX_MESH_PROVISIONING_DATA_OUT_CHAR,
    JMESHS_IDX_MESH_PROVISIONING_DATA_OUT_VAL,
    JMESHS_IDX_MESH_PROVISIONING_DATA_OUT_NTF_CFG,

		JMESHS_IDX_MESH_NETWORK_TRANSMIT_IN_CHAR,
		JMESHS_IDX_MESH_NETWORK_TRANSMIT_IN_VAL,

		JMESHS_IDX_MESH_NETWORK_TRANSMIT_OUT_CHAR,
		JMESHS_IDX_MESH_NETWORK_TRANSMIT_OUT_VAL,
		JMESHS_IDX_MESH_NETWORK_TRANSMIT_OUT_NTF_CFG,

		JMESHS_IDX_MESH_PROXY_CONFIG_IN_CHAR,
		JMESHS_IDX_MESH_PROXY_CONFIG_IN_VAL,

		JMESHS_IDX_MESH_PROXY_CONFIG_OUT_CHAR,
		JMESHS_IDX_MESH_PROXY_CONFIG_OUT_VAL,
		JMESHS_IDX_MESH_PROXY_CONFIG_OUT_NTF_CFG,
		
		JMESHS_IDX_MESH_BEACON_IN_CHAR,
		JMESHS_IDX_MESH_BEACON_IN_VAL,

		JMESHS_IDX_MESH_BEACON_OUT_CHAR,
		JMESHS_IDX_MESH_BEACON_OUT_VAL,
		JMESHS_IDX_MESH_BEACON_OUT_NTF_CFG,
	
    JMESHS_IDX_PROV_NB,
};

enum{
		JMESHS_IDX_APP_SVC,
    JMESHS_IDX_MESH_SERIAL_TRANSMIT_CHAR,
    JMESHS_IDX_MESH_SERIAL_TRANSMIT_VAL,
    JMESHS_IDX_MESH_SERIAL_TRANSMIT_NTF_CFG,

    JMESHS_IDX_MESH_APP_ELEC_CHAR,
    JMESHS_IDX_MESH_APP_ELEC_VAL,
    JMESHS_IDX_MESH_APP_ELEC_NTF_CFG,

    JMESHS_IDX_MESH_APP_WATER_CHAR,
    JMESHS_IDX_MESH_APP_WATER_VAL,
    JMESHS_IDX_MESH_APP_WATER_NTF_CFG,

    JMESHS_IDX_MESH_APP_LIGHT_CHAR,
    JMESHS_IDX_MESH_APP_LIGHT_VAL,
    JMESHS_IDX_MESH_APP_LIGHT_NTF_CFG,

    JMESHS_IDX_APP_NB,
};

typedef struct st_jmesh_pdu jmesh_pdu_t;

typedef struct st_jmesh_gatt{
    unsigned char mac[6];
    unsigned char id;
    union{
        unsigned char flag;
        struct{
            unsigned char is_valid:1;
            unsigned char is_ready:1;
            unsigned char is_server:1;
        };
    };
    unsigned short mtu;
    unsigned short svc_instance;
    jmesh_pdu_t* recv_cache;
    os_timer_event_t drop_timer;
}jmesh_gatt_t;

void jmesh_gatt_init(void);

jmesh_gatt_t* jmesh_gatt_connect_server(unsigned char* mac);
jmesh_gatt_t* jmesh_gatt_connect_client(unsigned char* mac);

void jmesh_gatt_disconnect(jmesh_gatt_t* gatt);
int jmesh_gatt_ready_num(void);

jmesh_gatt_t* jmesh_gatt_get_by_mac(unsigned char* mac);
jmesh_gatt_t* jmesh_gatt_get_by_id(unsigned char id);
jmesh_gatt_t* jmesh_gatt_get_by_interface(unsigned char interface);
unsigned char jmesh_gatt_get_interface(jmesh_gatt_t* gatt);
jmesh_gatt_t* jmesh_gatt_next(jmesh_gatt_t* gatt);
int jmesh_gatt_is_ready(jmesh_gatt_t* gatt);

void jmesh_gatt_connected(unsigned char* mac,unsigned char id);
void jmesh_gatt_disconnected(unsigned char connect_id);
void jmesh_gatt_set_mtu(unsigned char connect_id, unsigned short mtu);
void jmesh_gatt_set_svc_instance(unsigned char connect_id,unsigned short instance);
void jmesh_gatt_recv(unsigned char connect_id,unsigned short instance,unsigned short length,unsigned char* data);

void jmesh_gatt_send(jmesh_gatt_t* gatt,unsigned short instance,unsigned char length,unsigned char* data);


#endif // JMESH_GATT_H
