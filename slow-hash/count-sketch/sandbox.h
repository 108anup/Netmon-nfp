#ifndef SANDBOX_H
#define SANDBOX_H

#include <stdint.h>
#include <nfp/me.h>
#include <nfp/mem_atomic.h>
#include <pif_common.h>
#include "pif_plugin.h"

// For index
__declspec(cls shared) uint32_t index_a[100] = {
    25085448, 26371706, 26306928, 11082950, 16257233, 24249164, 23913393,
    22322291, 12232351, 28599341, 12863766, 21773806, 20090795, 24452341,
    27809432, 1868185,  38536760, 28591158, 20251234, 17790482, 2760755,
    35957295, 21302287, 14591986, 6160141,  18328736, 20803970, 3183546,
    26331909, 19061217, 1735628,  172089,   14804029, 29473911, 10600365,
    23490381, 21727778, 25686083, 31336961, 38602110, 25353970, 34760911,
    23254117, 33826242, 21570841, 11331328, 8824534,  22331460, 25696282,
    14212368, 2170654,  16061792, 18467312, 15210904, 31901457, 24344927,
    13584611, 14092110, 22096063, 27971323, 12343060, 17672426, 31041797,
    14549970, 28337825, 6303500,  5461407,  334334,   29090866, 1697779,
    24714480, 6900730,  23914598, 39361342, 28430051, 32772731, 5666631,
    7997095,  8401327,  9733658,  37400920, 23816223, 38499765, 5711703,
    31908845};

__declspec(cls shared) uint32_t index_b[100] = {
    7977416,  26521849, 23928002, 5650086,  27256962, 25567821, 21372645,
    13901931, 16414653, 4162211,  11940106, 21479132, 17294823, 22293892,
    26994091, 37708534, 25798880, 35688053, 25984157, 5632978,  21509546,
    21936907, 39170800, 32566126, 34335890, 11290146, 17407470, 30474195,
    22843448, 32308258, 24745825, 26679090, 22912091, 4771631,  35938117,
    18449300, 35465525, 5467154,  8122148,  29617392, 24472611, 7470620,
    2044408,  21841775, 157755,   17682032, 33950155, 37875779, 3453372,
    30342338, 7866920,  31787020, 28179227, 13632985, 17746559, 31374862,
    9453629,  4735466,  3513314,  24446624, 30183506, 27048920, 19216283,
    33512553, 15204124, 7479030,  23035105, 14317370, 23782476, 8518427,
    586577,   3056333,  20476350, 1361315,  22888486, 24025638, 26277431,
    35159039, 28385493, 18937297, 30975576, 16436357, 27294132, 18008324,
    7769053};

// For filter
__declspec(cls shared) uint32_t filter_a[100] = {
    12355415, 36854215, 30409442, 34998215, 34669208, 22054142, 16433352,
    39006519, 7626789,  764781,   35284908, 38075273, 30532847, 23354441,
    15184745, 3754288,  21421882, 19496302, 34268969, 726036,   36698570,
    11745793, 31276038, 14716055, 36476544, 15502287, 31937398, 6683883,
    36145629, 8225115,  17873898, 14215589, 25502357, 2000741,  10192398,
    9240002,  29361457, 32416340, 32727436, 13508414, 6359381,  35262511,
    5375655,  10888454, 10505807, 2674128,  16392022, 17731509, 3449335,
    18516581, 12923484, 12778440, 12667559, 33164414, 34580040, 2449919,
    23390509, 3319300,  15978644, 24444614, 3034758,  25984317, 16022781,
    21151192, 26441588, 36088147, 39109781, 31031384, 26217765, 33186952,
    19863708, 26127780, 8941686,  21457871, 17549433, 33422141, 23302798,
    27235301, 13640761, 30996034, 25900557, 24535220, 10960931, 30739777,
    22806246};

__declspec(cls shared) uint32_t filter_b[100] = {
    17101256, 17795405, 39054780, 38338085, 14949931, 18438298, 7573374,
    6049234,  28137403, 22815689, 31143218, 23271398, 9561289,  32467632,
    10682824, 30709524, 23473481, 26800098, 16009886, 29443260, 5568991,
    31238353, 39156756, 24624182, 14751657, 18825185, 281340,   7797622,
    20726610, 36126898, 34670525, 29798333, 26075283, 29883605, 24225171,
    6056924,  30127653, 1616950,  31928823, 8151042,  11453931, 10963908,
    30564488, 7647453,  16582173, 2939725,  5652184,  17129976, 3038619,
    35391848, 33477005, 18876380, 21362693, 23691745, 38879357, 23102402,
    8382631,  7944962,  31135903, 31946057, 35162423, 39326181, 39316161,
    4083899,  2157881,  15999332, 24420561, 16254088, 31176152, 10071412,
    15607916, 24243616, 344825,   4446906,  10790303, 28178230, 39669213,
    29498658, 32712164, 39023243, 4507026,  37569896, 20524038, 558176,
    27410321};

__declspec(cls shared) uint32_t p = 39916801;
int compute_hash(uint32_t x, uint32_t range, uint32_t aParam, uint32_t bParam)
{
  return ((aParam * x + bParam) % p) % range;
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

__intrinsic void
atomic_sub(volatile __declspec(mem addr40) void  *addr, int x)
{
  unsigned int addr_hi, addr_lo;
  __declspec(write_reg) int xfer;
  SIGNAL my_signal;
  addr_hi = ((unsigned long long int)addr >> 8) & 0xff000000;
  addr_lo = (unsigned long long int)addr & 0xffffffff;

  if (__is_ct_const(x) && x == 1) {
    __asm {
      mem[decr, --, addr_hi, <<8, addr_lo, 1];
    }
  } else {
    xfer = x;
    __asm {
      mem[sub, xfer, addr_hi, <<8, addr_lo, 1],   \
        ctx_swap[my_signal];
    }
  }
}


#endif // SANDBOX_H