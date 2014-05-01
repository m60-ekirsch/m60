#ifndef __FILEIO_H__
#define __FILEIO_H__
#include <sys/types.h>
#include <header.h>
namespace midas
{
enum MFReadState {
    OK           = 0x001L,
    HCBUPDATE    = 0x002L,
    HCBDROP      = 0x004L,
    CRIUPDATE    = 0x008L,
    CRIDROP      = 0x010L,
    EOF          = 0x020L
};

class MFileHandle
{
public:
    MFileHandle();
    ~MFileHandle();
    // read methods
    void initialize(const string &format_allow, const string &type_allow);
    bool inok(const string &uri);
    void set_xfer(const int64_t xfer_len, const int64_t cons_len=-1);
    MFReadState grabx_data(double *buffer, int64_t &ngot);
    int64_t grabx_hcb(hcb_t &hcb)
    int64_t grabx_cri(type4000_t &t4);
    MFReadState skip(const int64_t &nskip);
    // write methods
    void initialize(hcb_t &hcb, type4000_t &cri=0);
    bool allocate(const string &uri, hcb_t &hcb);
    int64_t filad_data(double *buffer, int64_t nput);
    int64_t filad_hcb(const hcb_t &hcb);
    int64_t filad_cri(const type4000_t &t4);
    // other methods
    int64_t close();
private:
};

void m_init_hcb(hcb_t &hcb, int64_t type, const string &format,
                const int64_t &seconds_since_epoch, const double &frac_secs);
void m_init_hcb1000(hcb_t &hcb, const double &start, const double &sample_rate,
                    const int64_t &units);


}
#endif
