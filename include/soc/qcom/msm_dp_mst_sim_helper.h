/*
 * Copyright (c) 2019, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/*
 * Copyright � 2014 Red Hat.
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#ifndef _MSM_DP_MST_SIM_H_
#define _MSM_DP_MST_SIM_H_

#include <linux/types.h>
#include <drm/drmP.h>
#include <drm/drm_dp_helper.h>

/**
 * struct msm_dp_mst_sim_port - MST port configuration
 * @input: if this port is an input port.
 * @mcs: message capability status - DP 1.2 spec.
 * @ddps: DisplayPort Device Plug Status - DP 1.2
 * @pdt: Peer Device Type
 * @ldps: Legacy Device Plug Status
 * @dpcd_rev: DPCD revision of device on this port
 * @peer_guid: Peer GUID on this port
 * @num_sdp_streams: Number of simultaneous streams
 * @num_sdp_stream_sinks: Number of stream sinks
 * @full_pbn: Full bandwidth for this port.
 * @avail_pbn: Available bandwidth for this port.
 * @edid: EDID data on this port.
 * @edid_size: size of EDID data on this port.
 */
struct msm_dp_mst_sim_port {
	bool input;
	bool mcs;
	bool ddps;
	u8 pdt;
	bool ldps;
	u8 dpcd_rev;
	u8 peer_guid[16];
	u8 num_sdp_streams;
	u8 num_sdp_stream_sinks;
	u16 full_pbn;
	u16 avail_pbn;
	const u8 *edid;
	u32 edid_size;
};

/**
 * struct msm_dp_mst_sim_cfg - MST simulator configuration
 * @host_dev: host device pointer used in callback functions
 * @guid: GUID of the top MST branch.
 */
struct msm_dp_mst_sim_cfg {
	void *host_dev;
	u8 guid[16];

	/**
	 * @host_hpd_irq:
	 *
	 * This callback is invoked whenever simulator need to
	 * notify host that there is a HPD_IRQ.
	 * @host_dev: host_dev pointer
	 */
	void (*host_hpd_irq)(void *host_dev);

	/**
	 * @host_req:
	 *
	 * This callback is invoked whenever simulator's reply is ready
	 * to response downstream request. Host can use this function
	 * to replace the reply generated by simulator.
	 * @host_dev: host_dev pointer
	 * @in: pointer of downstream request buffer to simulator
	 * @in_size: size of downstream request buffer to simulator
	 * @out: pointer of downstream reply from simulator
	 * @out_size: pointer of size of downstream reply from simulator
	 *
	 * This callback is optional.
	 */
	void (*host_req)(void *host_dev, const u8 *in, int in_size,
			u8 *out, int *out_size);
};

/**
 * msm_dp_mst_sim_create - Create simulator context
 * @cfg: see msm_dp_mst_sim_cfg
 * @mst_sim_context: simulator context returned
 * return: 0 if successful
 */
int msm_dp_mst_sim_create(const struct msm_dp_mst_sim_cfg *cfg,
		void **mst_sim_context);

/**
 * msm_dp_mst_sim_destroy - Destroy simulator context
 * @mst_sim_context: simulator context
 * return: 0 if successful
 */
int msm_dp_mst_sim_destroy(void *mst_sim_context);

/**
 * msm_dp_mst_sim_transfer - Send aux message to simulator context
 * @mst_sim_context: simulator context
 * @msg: aux message
 * return: 0 if successful
 */
int msm_dp_mst_sim_transfer(void *mst_sim_context, struct drm_dp_aux_msg *msg);

/**
 * msm_dp_mst_sim_update - Update port configuration
 * @mst_sim_context: simulator context
 * @port_num: number of ports
 * @ports: ports configuration
 * return: 0 if successful
 */
int msm_dp_mst_sim_update(void *mst_sim_context, u32 port_num,
		struct msm_dp_mst_sim_port *ports);

#endif /* _MSM_DP_MST_SIM_H_ */

