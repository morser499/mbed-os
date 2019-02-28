/*
 * Copyright (c) 2018 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cmsis_os.h"

#include "wiced_emac.h"
#include "wwd_network_constants.h"
#include "wwd_buffer_interface.h"
#include "wiced_management.h"
#include "wiced_wifi.h"

#include "lwip/etharp.h"
#include "lwip/ethip6.h"
#include "mbed_shared_queues.h"

static bool powered_up = false;
static bool link_state = false;
static wiced_mac_t multicast_addr;

WICED_EMAC::WICED_EMAC()
    : emac_link_input_cb(NULL),
      emac_link_state_cb(NULL)
{
}

WICED_EMAC &WICED_EMAC::get_instance() {
    static WICED_EMAC emac;
    return emac;
}

uint32_t WICED_EMAC::get_mtu_size() const
{
    return WICED_PAYLOAD_MTU;
}

uint32_t WICED_EMAC::get_align_preference() const
{
    return 0;
}

void WICED_EMAC::add_multicast_group(const uint8_t *addr)
{
    memcpy(multicast_addr.octet, addr, sizeof(multicast_addr.octet));
    wwd_wifi_register_multicast_address(&multicast_addr);
}

void WICED_EMAC::remove_multicast_group(const uint8_t *addr)
{
    wwd_wifi_unregister_multicast_address(&multicast_addr);
}

void WICED_EMAC::set_all_multicast(bool all)
{
    wwd_wifi_set_iovar_value( IOVAR_STR_ALLMULTI, all, WWD_STA_INTERFACE );
}

void WICED_EMAC::power_down()
{
    powered_up = false;
    wiced_deinit();
}

bool WICED_EMAC::power_up()
{
    wiced_init();
    powered_up = true;
    if (link_state && emac_link_state_cb ) {
        emac_link_state_cb(link_state);
    }
    return true;
}

bool WICED_EMAC::get_hwaddr(uint8_t *addr) const
{
    wiced_mac_t mac;
    wiced_result_t res = wiced_wifi_get_mac_address(&mac);
    MBED_ASSERT(res == WICED_SUCCESS);
    memcpy(addr, mac.octet, sizeof(mac.octet));
    return true;
}

void WICED_EMAC::set_hwaddr(const uint8_t *addr)
{
  /* No-op at this stage */
}

uint8_t WICED_EMAC::get_hwaddr_size() const
{
    wiced_mac_t mac;
    return sizeof(mac.octet);
}

void WICED_EMAC::set_link_input_cb(emac_link_input_cb_t input_cb)
{
    emac_link_input_cb = input_cb;
}

void WICED_EMAC::set_link_state_cb(emac_link_state_change_cb_t state_cb)
{
    emac_link_state_cb = state_cb;
}

void WICED_EMAC::set_memory_manager(EMACMemoryManager &mem_mngr)
{
    memory_manager = &mem_mngr;
}

bool WICED_EMAC::link_out(emac_mem_buf_t *buf)
{
    uint16_t offset = 64;
    wiced_buffer_t buffer;

    uint16_t size = memory_manager->get_total_len(buf);

    wwd_result_t res = host_buffer_get(&buffer, WWD_NETWORK_TX, size+offset, WICED_TRUE);
    MBED_ASSERT(res == WICED_SUCCESS);

    host_buffer_add_remove_at_front(&buffer, offset);

    void *dest = host_buffer_get_current_piece_data_pointer(buffer);
    memory_manager->copy_from_buf(dest, size, buf);

    wwd_network_send_ethernet_data(buffer, WWD_STA_INTERFACE);
    memory_manager->free(buf);
    return true;
}

void WICED_EMAC::get_ifname(char *name, uint8_t size) const
{
    memcpy(name, "wl", size);
}

extern "C"
{
void host_network_process_ethernet_data(wiced_buffer_t buffer, wwd_interface_t interface)
{
	emac_mem_buf_t *mem_buf = NULL;
    MBED_ASSERT(interface == WWD_STA_INTERFACE);

    WICED_EMAC &emac = WICED_EMAC::get_instance();

    if (!powered_up && !emac.emac_link_input_cb) {
        // ignore any trailing packets
        host_buffer_release(buffer, WWD_NETWORK_RX);
        return;
    }

    void *data = host_buffer_get_current_piece_data_pointer(buffer);
    uint16_t size = host_buffer_get_current_piece_size(buffer);

    if (size > 0) {
        /* Allocate a memory buffer chain from buffer pool */
        mem_buf = emac.memory_manager->alloc_heap(size, 0);
        if (mem_buf != NULL) {
            memcpy(static_cast<uint8_t *>(emac.memory_manager->get_ptr(mem_buf)), static_cast<uint8_t *>(data), size);
            emac.emac_link_input_cb(mem_buf);
        }
    }
    host_buffer_release(buffer, WWD_NETWORK_RX);
}

void wiced_emac_wwd_wifi_link_state_changed(bool state_up)
{
    WICED_EMAC &emac = WICED_EMAC::get_instance();

    link_state = state_up;
    if (emac.emac_link_state_cb ) {
        emac.emac_link_state_cb(state_up);
    }
}

//Stubs
wiced_result_t wiced_network_deinit           (void) { return WICED_SUCCESS; }
wiced_result_t wiced_network_init             (void) { return WICED_SUCCESS; }
void wiced_wireless_link_down_handler         (void) {}
void wiced_wireless_link_renew_handler        (void) {}
void wiced_wireless_link_up_handler           (void) {}
wiced_result_t wiced_network_notify_link_up   (void) { return WICED_SUCCESS; }
wiced_result_t wiced_network_notify_link_down (void) { return WICED_SUCCESS; }
} // extern "C"


