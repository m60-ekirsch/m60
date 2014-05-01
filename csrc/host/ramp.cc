#include <primitive.h>
using namespace midas;

typedef struct ramp_command_line_tag {
    double sample_rate=1e6;
    double start=0.0;
    double end=1000.0;
    double inc=1.0;
    string format="SD";
    int64_t nput;
    stinrg uri="file::localhost:/var/tmp/bogus.tmp";
} ramp_command_line_t;

void* parse_command_line(int argc, char **argv)
{
    ramp_command_line_t *rcl = new ramp_command_line_t();
    m_rcla("fs", "SD", &(rcl->sample_rate), "Sample rate");
    m_rcla("sv", "SD", &(rcl->start), "Start value");
    m_rcla("ev", "SD", &(rcl->end), "End value");
    m_rcla("dv", "SD", &(rcl->inc), "Value increment");
    m_rcla("fmt", "A", &(rcl->format), "Data format");
    m_rcla("uri", "A", &(rcl->uri), "Output product URI");
    m_rcla("nput", "SL", &(rcl->nput), "File length (if URI is disk file)");
    return m_process_command_line(argc, argv, rcl);
}

void mainroutine(void *cmdline_data)
{
    ramp_command_line_t *cl = (*)cmdline_data;
    hcb_t hcb;
    m_init_hcb(hcb, 1000, cl->format, 0, 0.0);
    m_init_hcb1000(hcb, 0.0, cl->sample_rate, Mc.units.seconds());
    PMFileHandle hout;
    hout.allocate(cl->uri, hcb, cl->nput);

    vector<double> buf(1024);
    if(cl->start > cl->end) {
        double temp = cl->end;
        cl->end = cl->start;
        cl->start = temp;
    }
    double next = (cl->inc > 0.0) ? cl->start : cl->end;

    do {
        for(int ii=0; ii<1024; ii++) {
            buf[ii] = next;
            next += cl->inc;
            if(cl->inc > 0.0) {
                if(next > cl->end) next = cl->start;
            } else {
                if(next < cl->start) next = cl->end;
            }
        }
        hout.filad_data(&buf[0], 1024);
    } while (m_keep_alive());

    hout.close();
    return;
}