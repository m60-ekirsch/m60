#ifndef __HEADER_H__
#define __HEADER_H__
#include <sys/types.h>
namespace midas
{
    typedef struct root_tag {
        char version[8];
        int64_t type;
        char format[8];
        int64_t seconds_since_epoch;
        double fractional_seconds;
        char fence[88];
    } root_t;

    // vector adjunt
    typedef struct type1000_tag {
        char root[128];
        double xstart, xdelta;
        int64_t xunits;
        char fence[360];
    } type1000_t;

    // framed data adjunct
    typedef struct type2000_tag {
        char root[128];
        double xstart, xdelta;
        int64_t xunits, xdimension;
        double ystart, ydelta;
        int64_t yunits, zunits;
        char fence[320];
    } type2000_t;

    // matrix adjunct
    typedef struct type3000_tag {
        char root[128];
        double xstart, xdelta;
        int64_t xunits, xdimension;
        double ystart, ydelta;
        int64_t yunits, ydimension;
        int64_t zunits;
        char fence[312];
    } type3000_t;

    // collection related information adjunct
    typedef struct type4000_tag {
        char root[128];
        int64_t rx_rf, rx_if, rx_fs, rx_bits;
        double rx_alt, rx_lat, rx_lon;
        double rx_speed, rx_sdir;
        double rx_acceleration, rx_adir;
        double rx_jerk, rx_jdir;
        char fence[280];
    } type4000_t;

    // header control block
    typedef union hcb_tag {
        root_t r;
        type1000_t t1;
        type2000_t t2;
        type3000_t t3;
        type4000_t t4;
    } hcb_t;
}
#endif