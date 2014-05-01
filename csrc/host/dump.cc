#include <iostream>
#include <primitive.h>
using namespace midas;
using namespace std;

typedef struct dump_command_line_tag {
    double start=0.0;
    double end=32.0;
    stinrg uri="file::localhost:/var/tmp/bogus.tmp";
} dump_command_line_t;

void* parse_command_line(int argc, char **argv)
{
    dump_command_line_t *cl = new dump_command_line_t();
    m_rcla("sv", "SD", &(cl->start), "Starting index");
    m_rcla("ev", "SD", &(cl->end), "Ending index");
    m_rcla("uri", "A", &(cl->uri), "Output product URI");
    return m_process_command_line(argc, argv, cl, sizeof(dump_command_line_t));
}

void mainroutine(void *cmdline_data)
{
    dump_command_line_t *cl = (*)cmdline_data;
    PMFileHandle hin;
    hin.inok(cl->uri);

    int64_t ngot, ntoget = cl->end - cl->start;
    vector<double> buf(ntoget);
    hin.skip(cl->start);
    hin.grabx_data(&buf[0]);
    for(int ii=0; ii<ngot; ii++) {
        cout << buf[ii];
        if (ii % 4) cout << ", ";
        else cout << endl;
    }
    hout.close();
    return;
}