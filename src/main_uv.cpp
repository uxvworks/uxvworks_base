#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#include <lcm/lcm.h>

#include "termbox.h"

// WARNING - this MUST satisfy (1 <= UV_TIMER_INTERVAL_MS <= 1000) or you have a serious bug
#define UV_TIMER_INTERVAL_MS  (1)

extern int process_cli_args(int argc, char* argv[]);

extern int dashboard_start(void);
extern int dashboard_run(void);
extern int dashboard_stop(void);
extern void sigwinch_handler(int ignored);

static int gDashboardStatus = -1;
static bool gShutdown = false;
static uv_loop_t* gLoop;


void idle_func(uv_idle_t* handle)
{
    // do nothing
}

void timer_func(uv_timer_t* handle)
{
    static uint32_t cnt = 0;

    if(cnt % (1000 / UV_TIMER_INTERVAL_MS) == 0)
        ;;//fprintf(stderr, "%14lu: %d ms cnt: %u\r", uv_hrtime(), UV_TIMER_INTERVAL_MS, cnt);
    cnt++;
}

void signal_handler(uv_signal_t* handle, int signum)
{
    fprintf(stderr, "%14lu: Signal received: %d\n\r", uv_hrtime(), signum);

    if (signum == SIGWINCH) {
        sigwinch_handler(signum);
    } else {
        uv_signal_stop(handle);
        gShutdown = true; //uv_stop(uv_default_loop());
        fprintf(stderr, "%14lu: shutting down...\n\r", uv_hrtime());
    }
}

int main(int argc, char* argv[])
{
    if (process_cli_args(argc, argv) < 0) return (1);

    fprintf(stdout,"\n\r%14lu: starting %s\n\r", uv_hrtime(), argv[0]);
    fprintf(stdout,    "%14lu: using libuv version %s\n\r", uv_hrtime(), uv_version_string());
    fprintf(stdout,    "%14lu: using lcm version %d.%d.%d\n\r", uv_hrtime(), LCM_MAJOR_VERSION, LCM_MINOR_VERSION, LCM_MICRO_VERSION);

    gLoop = (uv_loop_t*)malloc(sizeof(uv_loop_t));
    uv_loop_init(gLoop);

    uv_signal_t sigint;
    uv_signal_init(gLoop, &sigint);
    uv_signal_start(&sigint, signal_handler, SIGINT);

    uv_signal_t sighup;
    uv_signal_init(gLoop, &sighup);
    uv_signal_start(&sighup, signal_handler, SIGHUP);

    uv_idle_t idle_req;
    uv_idle_init(gLoop, &idle_req);
    uv_idle_start(&idle_req, idle_func);

    uv_timer_t timer_req;
    uv_timer_init(gLoop, &timer_req);
    uv_timer_start(&timer_req, timer_func, 1000, UV_TIMER_INTERVAL_MS);

    gDashboardStatus = dashboard_start();
    uv_signal_t sigwinch;
    uv_signal_init(gLoop, &sigwinch);
    uv_signal_start(&sigwinch, signal_handler, SIGWINCH);

    while (!gShutdown) {
        uv_run(gLoop, UV_RUN_NOWAIT);  //UV_RUN_DEFAULT
        if (gDashboardStatus >= 0 ) {
            gDashboardStatus = dashboard_run();
        }
    }

    if (gDashboardStatus >= 0 ) dashboard_stop();
    uv_loop_close(gLoop);
    uv_tty_reset_mode();
    free(gLoop);

    fprintf(stdout, "%14lu: exiting...\n\r", uv_hrtime());
    return (0);
}
