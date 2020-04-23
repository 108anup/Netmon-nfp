#include <stdint.h>
#include <nfp/me.h>
#include <nfp/mem_atomic.h>
#include <pif_common.h>
#include "pif_plugin.h"

#define NUM_ROWS 300
#define NUM_COLS 2048
#define SKETCH_COLUMN_COUNT_MASK 1023

uint32_t hash_func0(uint32_t srcAddr, uint32_t dstAddr)
{
	return (srcAddr ^ dstAddr) % NUM_COLS; //& SKETCH_COLUMN_COUNT_MASK;
}

uint32_t hash_func1(uint32_t srcAddr, uint32_t dstAddr)
{
	return (srcAddr | dstAddr) % NUM_COLS; //& SKETCH_COLUMN_COUNT_MASK;
}

uint32_t hash_func2(uint32_t srcAddr, uint32_t dstAddr)
{
	return (srcAddr & dstAddr) % NUM_COLS; //& SKETCH_COLUMN_COUNT_MASK;
}

__intrinsic void
atomic_add(volatile __declspec(mem addr40) void  *addr, int x)
{
    unsigned int addr_hi, addr_lo;
    __declspec(write_reg) int xfer;
    SIGNAL my_signal;
    addr_hi = ((unsigned long long int)addr >> 8) & 0xff000000;
    addr_lo = (unsigned long long int)addr & 0xffffffff;

    if (__is_ct_const(x) && x == 1) {
        __asm {
            mem[incr, --, addr_hi, <<8, addr_lo, 1];
        }
    } else {
        xfer = x;
        __asm {
            mem[add, xfer, addr_hi, <<8, addr_lo, 1],   \
                ctx_swap[my_signal];
        }
    }
}

// __declspec(emem export scope(global))
// __export __mem
__declspec(imem export scope(global)) int32_t sketch[NUM_ROWS][NUM_COLS];

#define UPDATE_ROW(ROW_NUM, HASH_NUM)                                   \
    int pif_plugin_cms_update_##ROW_NUM##_##HASH_NUM(                   \
        EXTRACTED_HEADERS_T *headers,                                   \
        ACTION_DATA_T *action_data)                                     \
    {                                                                   \
                                                                        \
        __xread uint32_t in_xfer_sketch;                                \
        __gpr uint32_t out_reg_sketch;                                  \
        __xwrite uint32_t out_xfer_sketch;                              \
                                                                        \
                                                                        \
        PIF_PLUGIN_ipv4_T *ipv4_header = pif_plugin_hdr_get_ipv4(       \
            headers);                                                   \
        uint32_t srcAddr = PIF_HEADER_GET_ipv4___srcAddr(ipv4_header);  \
        uint32_t dstAddr = PIF_HEADER_GET_ipv4___dstAddr(ipv4_header);  \
        uint32_t hv = hash_func##HASH_NUM(srcAddr, dstAddr);            \
                                                                        \
        atomic_add(&sketch[ROW_NUM][hv], 1);                            \
                                                                        \
        return PIF_PLUGIN_RETURN_FORWARD;                               \
    }                                                                   \

/*

  mem_read_atomic(&in_xfer_sketch,                                \
  &sketch[ROW_NUM][hv], sizeof(uint32_t));                        \
  out_reg_sketch = in_xfer_sketch;                                \
  out_reg_sketch += 1;                                            \
  out_xfer_sketch = out_reg_sketch;                               \
  mem_write_atomic(&out_xfer_sketch,                              \
  &sketch[ROW_NUM][hv], sizeof(uint32_t));                        \

 */

//PIF_PLUGIN_HDR_T *pif_plugin_hdr_get_HDR(EXTRACTED_HEADERS_T *headers)
UPDATE_ROW(0, 0)
UPDATE_ROW(1, 1)
UPDATE_ROW(2, 2)
UPDATE_ROW(3, 0)
UPDATE_ROW(4, 1)
UPDATE_ROW(5, 2)
UPDATE_ROW(6, 0)
UPDATE_ROW(7, 1)
UPDATE_ROW(8, 2)
UPDATE_ROW(9, 0)
UPDATE_ROW(10, 1)
UPDATE_ROW(11, 2)
UPDATE_ROW(12, 0)
UPDATE_ROW(13, 1)
UPDATE_ROW(14, 2)
UPDATE_ROW(15, 0)
UPDATE_ROW(16, 1)
UPDATE_ROW(17, 2)
UPDATE_ROW(18, 0)
UPDATE_ROW(19, 1)
UPDATE_ROW(20, 2)
UPDATE_ROW(21, 0)
UPDATE_ROW(22, 1)
UPDATE_ROW(23, 2)
UPDATE_ROW(24, 0)
UPDATE_ROW(25, 1)
UPDATE_ROW(26, 2)
UPDATE_ROW(27, 0)
UPDATE_ROW(28, 1)
UPDATE_ROW(29, 2)
UPDATE_ROW(30, 0)
UPDATE_ROW(31, 1)
UPDATE_ROW(32, 2)
UPDATE_ROW(33, 0)
UPDATE_ROW(34, 1)
UPDATE_ROW(35, 2)
UPDATE_ROW(36, 0)
UPDATE_ROW(37, 1)
UPDATE_ROW(38, 2)
UPDATE_ROW(39, 0)
UPDATE_ROW(40, 1)
UPDATE_ROW(41, 2)
UPDATE_ROW(42, 0)
UPDATE_ROW(43, 1)
UPDATE_ROW(44, 2)
UPDATE_ROW(45, 0)
UPDATE_ROW(46, 1)
UPDATE_ROW(47, 2)
UPDATE_ROW(48, 0)
UPDATE_ROW(49, 1)
UPDATE_ROW(50, 2)
UPDATE_ROW(51, 0)
UPDATE_ROW(52, 1)
UPDATE_ROW(53, 2)
UPDATE_ROW(54, 0)
UPDATE_ROW(55, 1)
UPDATE_ROW(56, 2)
UPDATE_ROW(57, 0)
UPDATE_ROW(58, 1)
UPDATE_ROW(59, 2)
UPDATE_ROW(60, 0)
UPDATE_ROW(61, 1)
UPDATE_ROW(62, 2)
UPDATE_ROW(63, 0)
UPDATE_ROW(64, 1)
UPDATE_ROW(65, 2)
UPDATE_ROW(66, 0)
UPDATE_ROW(67, 1)
UPDATE_ROW(68, 2)
UPDATE_ROW(69, 0)
UPDATE_ROW(70, 1)
UPDATE_ROW(71, 2)
UPDATE_ROW(72, 0)
UPDATE_ROW(73, 1)
UPDATE_ROW(74, 2)
UPDATE_ROW(75, 0)
UPDATE_ROW(76, 1)
UPDATE_ROW(77, 2)
UPDATE_ROW(78, 0)
UPDATE_ROW(79, 1)
UPDATE_ROW(80, 2)
UPDATE_ROW(81, 0)
UPDATE_ROW(82, 1)
UPDATE_ROW(83, 2)
UPDATE_ROW(84, 0)
UPDATE_ROW(85, 1)
UPDATE_ROW(86, 2)
UPDATE_ROW(87, 0)
UPDATE_ROW(88, 1)
UPDATE_ROW(89, 2)
UPDATE_ROW(90, 0)
UPDATE_ROW(91, 1)
UPDATE_ROW(92, 2)
UPDATE_ROW(93, 0)
UPDATE_ROW(94, 1)
UPDATE_ROW(95, 2)
UPDATE_ROW(96, 0)
UPDATE_ROW(97, 1)
UPDATE_ROW(98, 2)
UPDATE_ROW(99, 0)
UPDATE_ROW(100, 1)
UPDATE_ROW(101, 2)
UPDATE_ROW(102, 0)
UPDATE_ROW(103, 1)
UPDATE_ROW(104, 2)
UPDATE_ROW(105, 0)
UPDATE_ROW(106, 1)
UPDATE_ROW(107, 2)
UPDATE_ROW(108, 0)
UPDATE_ROW(109, 1)
UPDATE_ROW(110, 2)
UPDATE_ROW(111, 0)
UPDATE_ROW(112, 1)
UPDATE_ROW(113, 2)
UPDATE_ROW(114, 0)
UPDATE_ROW(115, 1)
UPDATE_ROW(116, 2)
UPDATE_ROW(117, 0)
UPDATE_ROW(118, 1)
UPDATE_ROW(119, 2)
UPDATE_ROW(120, 0)
UPDATE_ROW(121, 1)
UPDATE_ROW(122, 2)
UPDATE_ROW(123, 0)
UPDATE_ROW(124, 1)
UPDATE_ROW(125, 2)
UPDATE_ROW(126, 0)
UPDATE_ROW(127, 1)
UPDATE_ROW(128, 2)
UPDATE_ROW(129, 0)
UPDATE_ROW(130, 1)
UPDATE_ROW(131, 2)
UPDATE_ROW(132, 0)
UPDATE_ROW(133, 1)
UPDATE_ROW(134, 2)
UPDATE_ROW(135, 0)
UPDATE_ROW(136, 1)
UPDATE_ROW(137, 2)
UPDATE_ROW(138, 0)
UPDATE_ROW(139, 1)
UPDATE_ROW(140, 2)
UPDATE_ROW(141, 0)
UPDATE_ROW(142, 1)
UPDATE_ROW(143, 2)
UPDATE_ROW(144, 0)
UPDATE_ROW(145, 1)
UPDATE_ROW(146, 2)
UPDATE_ROW(147, 0)
UPDATE_ROW(148, 1)
UPDATE_ROW(149, 2)
UPDATE_ROW(150, 0)
UPDATE_ROW(151, 1)
UPDATE_ROW(152, 2)
UPDATE_ROW(153, 0)
UPDATE_ROW(154, 1)
UPDATE_ROW(155, 2)
UPDATE_ROW(156, 0)
UPDATE_ROW(157, 1)
UPDATE_ROW(158, 2)
UPDATE_ROW(159, 0)
UPDATE_ROW(160, 1)
UPDATE_ROW(161, 2)
UPDATE_ROW(162, 0)
UPDATE_ROW(163, 1)
UPDATE_ROW(164, 2)
UPDATE_ROW(165, 0)
UPDATE_ROW(166, 1)
UPDATE_ROW(167, 2)
UPDATE_ROW(168, 0)
UPDATE_ROW(169, 1)
UPDATE_ROW(170, 2)
UPDATE_ROW(171, 0)
UPDATE_ROW(172, 1)
UPDATE_ROW(173, 2)
UPDATE_ROW(174, 0)
UPDATE_ROW(175, 1)
UPDATE_ROW(176, 2)
UPDATE_ROW(177, 0)
UPDATE_ROW(178, 1)
UPDATE_ROW(179, 2)
UPDATE_ROW(180, 0)
UPDATE_ROW(181, 1)
UPDATE_ROW(182, 2)
UPDATE_ROW(183, 0)
UPDATE_ROW(184, 1)
UPDATE_ROW(185, 2)
UPDATE_ROW(186, 0)
UPDATE_ROW(187, 1)
UPDATE_ROW(188, 2)
UPDATE_ROW(189, 0)
UPDATE_ROW(190, 1)
UPDATE_ROW(191, 2)
UPDATE_ROW(192, 0)
UPDATE_ROW(193, 1)
UPDATE_ROW(194, 2)
UPDATE_ROW(195, 0)
UPDATE_ROW(196, 1)
UPDATE_ROW(197, 2)
UPDATE_ROW(198, 0)
UPDATE_ROW(199, 1)
UPDATE_ROW(200, 2)
UPDATE_ROW(201, 0)
UPDATE_ROW(202, 1)
UPDATE_ROW(203, 2)
UPDATE_ROW(204, 0)
UPDATE_ROW(205, 1)
UPDATE_ROW(206, 2)
UPDATE_ROW(207, 0)
UPDATE_ROW(208, 1)
UPDATE_ROW(209, 2)
UPDATE_ROW(210, 0)
UPDATE_ROW(211, 1)
UPDATE_ROW(212, 2)
UPDATE_ROW(213, 0)
UPDATE_ROW(214, 1)
UPDATE_ROW(215, 2)
UPDATE_ROW(216, 0)
UPDATE_ROW(217, 1)
UPDATE_ROW(218, 2)
UPDATE_ROW(219, 0)
UPDATE_ROW(220, 1)
UPDATE_ROW(221, 2)
UPDATE_ROW(222, 0)
UPDATE_ROW(223, 1)
UPDATE_ROW(224, 2)
UPDATE_ROW(225, 0)
UPDATE_ROW(226, 1)
UPDATE_ROW(227, 2)
UPDATE_ROW(228, 0)
UPDATE_ROW(229, 1)
UPDATE_ROW(230, 2)
UPDATE_ROW(231, 0)
UPDATE_ROW(232, 1)
UPDATE_ROW(233, 2)
UPDATE_ROW(234, 0)
UPDATE_ROW(235, 1)
UPDATE_ROW(236, 2)
UPDATE_ROW(237, 0)
UPDATE_ROW(238, 1)
UPDATE_ROW(239, 2)
UPDATE_ROW(240, 0)
UPDATE_ROW(241, 1)
UPDATE_ROW(242, 2)
UPDATE_ROW(243, 0)
UPDATE_ROW(244, 1)
UPDATE_ROW(245, 2)
UPDATE_ROW(246, 0)
UPDATE_ROW(247, 1)
UPDATE_ROW(248, 2)
UPDATE_ROW(249, 0)
UPDATE_ROW(250, 1)
UPDATE_ROW(251, 2)
UPDATE_ROW(252, 0)
UPDATE_ROW(253, 1)
UPDATE_ROW(254, 2)
UPDATE_ROW(255, 0)
UPDATE_ROW(256, 1)
UPDATE_ROW(257, 2)
UPDATE_ROW(258, 0)
UPDATE_ROW(259, 1)
UPDATE_ROW(260, 2)
UPDATE_ROW(261, 0)
UPDATE_ROW(262, 1)
UPDATE_ROW(263, 2)
UPDATE_ROW(264, 0)
UPDATE_ROW(265, 1)
UPDATE_ROW(266, 2)
UPDATE_ROW(267, 0)
UPDATE_ROW(268, 1)
UPDATE_ROW(269, 2)
UPDATE_ROW(270, 0)
UPDATE_ROW(271, 1)
UPDATE_ROW(272, 2)
UPDATE_ROW(273, 0)
UPDATE_ROW(274, 1)
UPDATE_ROW(275, 2)
UPDATE_ROW(276, 0)
UPDATE_ROW(277, 1)
UPDATE_ROW(278, 2)
UPDATE_ROW(279, 0)
UPDATE_ROW(280, 1)
UPDATE_ROW(281, 2)
UPDATE_ROW(282, 0)
UPDATE_ROW(283, 1)
UPDATE_ROW(284, 2)
UPDATE_ROW(285, 0)
UPDATE_ROW(286, 1)
UPDATE_ROW(287, 2)
UPDATE_ROW(288, 0)
UPDATE_ROW(289, 1)
UPDATE_ROW(290, 2)
UPDATE_ROW(291, 0)
UPDATE_ROW(292, 1)
UPDATE_ROW(293, 2)
UPDATE_ROW(294, 0)
UPDATE_ROW(295, 1)
UPDATE_ROW(296, 2)
UPDATE_ROW(297, 0)
UPDATE_ROW(298, 1)
UPDATE_ROW(299, 2)
