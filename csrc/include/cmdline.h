#ifndef __CMDLINE_H__
#define __CMDLINE_H__
namespace midas {

m_rcla(const string &option, const string &format, void *dataloc,
       const string &description);
m_process_command_line(int argc, char **argv, void *dataptr);

}
#endif