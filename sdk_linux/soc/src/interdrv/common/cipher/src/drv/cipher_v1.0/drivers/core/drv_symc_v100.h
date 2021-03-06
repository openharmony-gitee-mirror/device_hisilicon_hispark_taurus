/*
 * Copyright (C) 2021 HiSilicon (Shanghai) Technologies CO., LIMITED.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef _DRV_SYMC_V100_H_
#define _DRV_SYMC_V100_H_

#include "drv_osal_lib.h"

/* Size of entry node */
#define ENTRY_NODE_SIZE             16

/* symmetric cipher max iv size */
#define SYMC_IV_MAX_SIZE            (SYMC_IV_MAX_SIZE_IN_WORD * 4)

/* Size of nodes list. */
#define CHN_LIST_SIZE               ((ENTRY_NODE_SIZE * 2 + SYMC_IV_MAX_SIZE) * SYMC_MAX_LIST_NUM)

/* Size of symc nodes list. */
#define SYMC_NODE_LIST_SIZE         (CHN_LIST_SIZE * CIPHER_HARD_CHANNEL_CNT)

/* Dump flag of node buffer, if set to 1, the SMMU will dump the page cache. */
#define SYMC_BUF_LIST_FLAG_DUMM     (0x01 << 20)

/* IV set flag of node buffer, if set to 1, the IV will update to hardware. */
#define SYMC_BUF_LIST_FLAG_IVSET    (0x01 << 21)

/* EOL flag of node buffer, set to 1 at the last node. */
#define SYMC_BUF_LIST_FLAG_EOL      (0x01 << 22)

/* Define the offset of reg. */
#define  REG_CHAN0_CIPHER_DOUT           0x0000
#define  reg_chan_cipher_ivout(id)       (0x0010 + (id) * 16)
#define  reg_cipher_key(id)              (0x0090 + (id) * 32)
#define  REG_SEC_CHN_CFG                 0x0824
#define  REG_HL_APP_LEN                  0x082C
#define  REG_CHAN0_CIPHER_CTRL           0x1000
#define  REG_CHAN0_CIPHER_DIN            0x1014
#define  reg_chann_ibuf_num(id)          (0x1000 + (id) * 128)
#define  reg_chann_ibuf_cnt(id)          (0x1000 + (id) * 128 + 0x4)
#define  reg_chann_iempty_cnt(id)        (0x1000 + (id) * 128 + 0x8)
#define  reg_chann_cipher_ctrl(id)       (0x1000 + (id) * 128 + 0x10)
#define  reg_chann_src_lst_saddr(id)     (0x1000 + (id) * 128 + 0x14)
#define  reg_chann_iage_cnt(id)          (0x1000 + (id) * 128 + 0x1C)
#define  reg_chann_src_lst_raddr(id)     (0x1000 + (id) * 128 + 0x20)
#define  chnn_src_addr(id)               (0x1000 + (id) * 128 + 0x24)
#define  reg_chann_obuf_num(id)          (0x1000 + (id) * 128 + 0x3C)
#define  reg_chann_obuf_cnt(id)          (0x1000 + (id) * 128 + 0x40)
#define  reg_chann_ofull_cnt(id)         (0x1000 + (id) * 128 + 0x44)
#define  reg_chann_int_ocntcfg(id)       (0x1000 + (id) * 128 + 0x48)
#define  reg_chann_dest_lst_saddr(id)    (0x1000 + (id) * 128 + 0x4C)
#define  reg_chann_oage_cnt(id)          (0x1000 + (id) * 128 + 0x54)
#define  reg_chann_dest_lst_raddr(id)    (0x1000 + (id) * 128 + 0x58)
#define  reg_chann_dest_addr(id)         (0x1000 + (id) * 128 + 0x5C)
#define  REG_INT_STATUS                  0x1400
#define  REG_INT_EN                      0x1404
#define  REG_INT_RAW                     0x1408
#define  CHN_N_RD_DAT_ADDR_SMMU_BYPASS   0x1418
#define  CHN_N_WR_DAT_ADDR_SMMU_BYPASS   0x141C

#define  REG_MMU_GLOBAL_CTR_ADDR         0x00
#define  REG_MMU_INTMAS_S                0x10
#define  REG_MMU_INTRAW_S                0x14
#define  REG_MMU_INTSTAT_S               0x18
#define  REG_MMU_INTCLR_S                0x1c
#define  REG_MMU_INTMASK_NS              0x20
#define  REG_MMU_INTRAW_NS               0x24
#define  REG_MMU_INTSTAT_NS              0x28
#define  REG_MMU_INTCLR_NS               0x2C

#ifdef CHIP_SMMU_VER_V200
#define  REG_MMU_SCB_TTBR_H              0x2e0
#define  REG_MMU_SCB_TTBR                0x2e4
#define  REG_MMU_CB_TTBR_H               0x2e8
#define  REG_MMU_CB_TTBR                 0x2ec
#define  REG_MMU_ERR_RDADDR_H_S          0x2f0
#define  REG_MMU_ERR_RDADDR_S            0x2f4
#define  REG_MMU_ERR_WRADDR_H_S          0x2f8
#define  REG_MMU_ERR_WRADDR_S            0x2fc
#define  REG_MMU_ERR_RDADDR_H_NS         0x300
#define  REG_MMU_ERR_RDADDR_NS           0x304
#define  REG_MMU_ERR_WRADDR_H_NS         0x308
#define  REG_MMU_ERR_WRADDR_NS           0x30c
#else
#define  REG_MMU_SCB_TTBR                0x208
#define  REG_MMU_CB_TTBR                 0x20C
#define  REG_MMU_ERR_RDADDR_S            0x2f0
#define  REG_MMU_ERR_WRADDR_S            0x2f4
#define  REG_MMU_ERR_RDADDR_NS           0x304
#define  REG_MMU_ERR_WRADDR_NS           0x308
#endif

/* Define the union chann_cipher_ctrl */
typedef union {
    /* Define the struct bits */
    struct {
        hi_u32    decrypt         : 1; /* [0]  */
        hi_u32    mode            : 3; /* [3..1]  */
        hi_u32    alg_sel         : 2; /* [5..4]  */
        hi_u32    width           : 2; /* [7..6]  */
        hi_u32    reserved_1      : 1; /* [8]  */
        hi_u32    key_length      : 2; /* [10..9]  */
        hi_u32    reserved_2      : 2; /* [12..11]  */
        hi_u32    key_sel         : 1; /* [13]  */
        hi_u32    key_adder       : 3; /* [16..14]  */
        hi_u32    reserved_3      : 5; /* [21..17]  */
        hi_u32    weight          : 10; /* [31..22]  */
    } bits;

    hi_u32    u32;                        /* Define an unsigned member */
} chann_cipher_ctrl;

/* Define the union sec_chn_cfg */
typedef union {
    /* Define the struct bits */
    struct {
        hi_u32    sec_chn_cfg     : 8; /* [7..0]  */
        hi_u32    sec_chn_cfg_lock : 1; /* [8]  */
        hi_u32    reserved_1      : 23; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    hi_u32    u32;
} sec_chn_cfg;

/* Define the union chann_rd_dat_addr_smmu_bypass */
typedef union {
    /* Define the struct bits */
    struct {
        hi_u32    chann_rd_dat_addr_smmu_bypass     : 7; /* [6..0]  */
        hi_u32    reserved_1                        : 25; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    hi_u32    u32;
} chann_rd_dat_addr_smmu_bypass;

/* Define the union chann_wr_dat_addr_smmu_bypass */
typedef union {
    /* Define the struct bits */
    struct {
        hi_u32    chann_wr_dat_addr_smmu_bypass     : 7; /* [6..0]  */
        hi_u32    reserved_1                        : 25; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    hi_u32    u32;
} chann_wr_dat_addr_smmu_bypass;

/* Define the union int_status */
typedef union {
    /* Define the struct bits */
    struct {
        hi_u32    chn_ibuf_int           : 8; /* [7..0]  */
        hi_u32    chn_obuf_int           : 8; /* [15..8]  */
        hi_u32    tdes_key_error_int     : 1; /* [16]  */
        hi_u32    reserved_1             : 15; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    hi_u32    u32;
} int_status;

/* Define the union int_en */
typedef union {
    /* Define the struct bits */
    struct {
        hi_u32    chn_ibuf_en           : 8; /* [7..0]  */
        hi_u32    chn_obuf_en           : 8; /* [15..8]  */
        hi_u32    tdes_key_error_en     : 1; /* [16]  */
        hi_u32    reserved_1            : 13; /* [31..17]  */
        hi_u32    sec_int_en            : 1; /* [30]  */
        hi_u32    int_en                : 1; /* [31]  */
    } bits;

    /* Define an unsigned member */
    hi_u32    u32;
} int_en;

/* Define the union int_raw */
typedef union {
    /* Define the struct bits */
    struct {
        hi_u32    chn_ibuf_raw           : 8; /* [7..0]  */
        hi_u32    chn_obuf_raw           : 8; /* [15..8]  */
        hi_u32    tdes_key_error_raw     : 1; /* [16]  */
        hi_u32    reserved_1             : 15; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    hi_u32    u32;
} int_raw;

/* Define the union smmu_scr */
typedef union {
    /* Define the struct bits */
    struct {
        hi_u32    glb_bypass           : 1; /* [0]     */
        hi_u32    reserved_1           : 2;  /* [2..1]  */
        hi_u32    int_en               : 1; /* [3]     */
        hi_u32    reserved_2           : 28; /* [31..4] */
    } bits;

    /* Define an unsigned member */
    hi_u32    u32;
} smmu_scr;

/* Define the union smmu_int */
typedef union {
    /* Define the struct bits */
    struct {
        hi_u32    ints_tlbmiss         : 1; /* [0]  */
        hi_u32    ints_ptw_trans       : 1;  /* [1]  */
        hi_u32    ints_tlbinvalid      : 1; /* [2]  */
        hi_u32    reserved_2           : 29; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    hi_u32    u32;
} smmu_int;

/* Structure Definition end */
#endif
