/*
**++
**  utc_mkbintime()
**
**  Functional Description:
**
**      Converts timespecs into a 128-bit UTC time.
**
**  Inputs:
**
**      timesp - pointer to timespecs to provide time component of utc.
**      inaccsp - pointer to timespecs to provide inaccuracy component
**      tdf  - tdf, in seconds east of gmt, to place in 128-bit UTC time.
**
**  Implicit Inputs:
**
**
**  Outputs:
**
**      utc - pointer to 128-bit time resulting from timespecs.
**
**  Implicit Outputs:
**
**  Value Returned:
**
**      0 success, -1 failure
**
**  Side Effects:
**
**
**--
*/
int utc_mkbintime(utc_t *utc,
		  timespec_t *timesp,
		  timespec_t *inaccsp,
		  long tdf) {

    UTCValue timevalue, inaccvalue;

    if (inaccsp == NULL || (long)inaccsp->tv_sec < 0) {
        UTCassign (&inaccvalue, K_INFINITE_INACC_LO, K_INFINITE_INACC_HI);
    } else {
        uemul((unsigned long)inaccsp->tv_sec, K_100NS_PER_SEC,
              &inaccvalue);
        UTCiAdd(&inaccvalue, ((inaccsp->tv_nsec + 99)/100),
                &inaccvalue);
    };

    emul((long)timesp->tv_sec, K_100NS_PER_SEC, &timevalue);
    UTCiAdd(&timevalue, ((timesp->tv_nsec + 50)/100), &timevalue);
    UTCadd(&timevalue, &diff_UNIX_UTC_ticks, &timevalue);

    return(utc_mkcomptime(utc, &timevalue, &inaccvalue, tdf));

}
