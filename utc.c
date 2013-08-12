int utc_gettime(utc_t *utc) {

    struct timeval tv;
    struct timezone tz;
    struct timespec ts;

    gettimeofday(&tv, &rz);
    ts.tv_sec = tv.tv_sec;
    ts.tv_nsec = tv.tv_usec * 1000;

    return utc_mkbintime(utc, &ts, 0, -tz.tz_minuteswest*60);
}

