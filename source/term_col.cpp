#include <sys/ioctl.h>
#include <unistd.h>

auto term_col() {
    winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    return ws.ws_col;
}
