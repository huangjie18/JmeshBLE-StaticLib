#ifndef JMESH_BLE_CALLBACK_H
#define JMESH_BLE_CALLBACK_H


extern void jmesh_ble_recv_adv_callback(unsigned char *mac, unsigned char rssi,unsigned char ad_type, unsigned char length,unsigned char *data);

extern void jmesh_ble_gatt_connected_callback(unsigned char *mac, unsigned char connect_id);
extern void jmesh_ble_gatt_disconnected_callback(unsigned char connect_id);

extern void jmesh_ble_exchange_mtu_callback(unsigned char connect_id,unsigned short mtu);
extern void jmesh_ble_disc_svc_callback(unsigned short connect_id,unsigned char *uuid,unsigned short handler);

extern void jmesh_ble_gatt_writed_callback(unsigned char connect_id, unsigned short char_handler, unsigned short length,unsigned char *data);
extern void jmesh_ble_gatt_notified_callback(unsigned char connect_id, unsigned short char_handler, unsigned short length,unsigned char *data);

#endif // JMESH_BLE_CALLBACK_H
