import os
import shutil

path_list = [
    '../ip/ahi/src/ahi.c',
    '../ip/ahi/src/ahi_task.c',
    '../ip/ea/src/ea.c',
    '../ip/hci/src/hci.c',
    '../ip/hci/src/hci_fc.c',
    '../ip/hci/src/hci_msg.c',
    '../ip/hci/src/hci_tl.c',
    '../ip/hci/src/hci_util.c',
    '../ip/ble/hl/src/gap/gapc/gapc.c',
    '../ip/ble/hl/src/gap/gapc/gapc_hci.c',
    '../ip/ble/hl/src/gap/gapc/gapc_sig.c',
    '../ip/ble/hl/src/gap/gapc/gapc_task.c',
    '../ip/ble/hl/src/gap/gapm/gapm.c',
    '../ip/ble/hl/src/gap/gapm/gapm_hci.c',
    '../ip/ble/hl/src/gap/gapm/gapm_task.c',
    '../ip/ble/hl/src/gap/gapm/gapm_util.c',
    '../ip/ble/hl/src/gap/smpc/smpc.c',
    '../ip/ble/hl/src/gap/smpc/smpc_api.c',
    '../ip/ble/hl/src/gap/smpc/smpc_crypto.c',
    '../ip/ble/hl/src/gap/smpc/smpc_util.c',
    '../ip/ble/hl/src/gap/smpm/smpm_api.c',
    '../ip/ble/hl/src/gatt/attc/attc.c',
    '../ip/ble/hl/src/gatt/attm/attm.c',
    '../ip/ble/hl/src/gatt/attm/attm_db.c',
    '../ip/ble/hl/src/gatt/atts/atts.c',
    '../ip/ble/hl/src/gatt/gattc/gattc.c',
    '../ip/ble/hl/src/gatt/gattc/gattc_task.c',
    '../ip/ble/hl/src/gatt/gattm/gattm.c',
    '../ip/ble/hl/src/gatt/gattm/gattm_task.c',
    '../ip/ble/hl/src/l2c/l2cc/l2cc.c',
    '../ip/ble/hl/src/l2c/l2cc/l2cc_lecb.c',
    '../ip/ble/hl/src/l2c/l2cc/l2cc_pdu.c',
    '../ip/ble/hl/src/l2c/l2cc/l2cc_sig.c',
    '../ip/ble/hl/src/l2c/l2cc/l2cc_task.c',
    '../ip/ble/hl/src/l2c/l2cm/l2cm.c',
    '../ip/ble/hl/src/rwble_hl/rwble_hl.c',
    '../ip/ble/ll/src/llc/llc.c',
    '../ip/ble/ll/src/llc/llc_ch_asses.c',
    '../ip/ble/ll/src/llc/llc_hci.c',
    '../ip/ble/ll/src/llc/llc_llcp.c',
    '../ip/ble/ll/src/llc/llc_task.c',
    '../ip/ble/ll/src/llc/llc_util.c',
    '../ip/ble/ll/src/lld/lld.c',
    '../ip/ble/ll/src/lld/lld_evt.c',
    '../ip/ble/ll/src/lld/lld_pdu.c',
    '../ip/ble/ll/src/lld/lld_util.c',
    '../ip/ble/ll/src/lld/lld_wlcoex.c',
    '../ip/ble/ll/src/llm/llm.c',
    '../ip/ble/ll/src/llm/llm_hci.c',
    '../ip/ble/ll/src/llm/llm_task.c',
    '../ip/ble/ll/src/llm/llm_util.c',
    '../ip/ble/ll/src/em/em_buf.c',
    '../ip/ble/ll/src/rwble/rwble.c',
]

mesh_path = '../freertos/app/mesh'

for path in path_list:
    os.remove(os.path.join(os.getcwd(),path))
    
shutil.rmtree(os.path.join(os.getcwd(),mesh_path))