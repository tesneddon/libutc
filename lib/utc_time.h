/*
**  FACILITY:   libutc
**
**  ABSTRACT:   libutc private definitions
**
**  MODULE DESCRIPTION:
**
**      ...
**
**  AUTHOR:     Tim Sneddon
**
**  Copyright (c) 2013, Endless Software Solutions
**
**  libutc is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  libutc is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
**
**  CREATION DATE:   09-SEP-2013
**
**  MODIFICATION HISTORY
**
**      09-SEP-2013  V1.0    Sneddon    Initial coding.
**--
*/
#ifndef utc_time_h__
#define utc_time_h__

#define SECSPERMIN      60
#define MINSPERHOUR     60
#define HOURSPERDAY     24
#define DAYSPERWEEK     7
#define DAYSPERNYEAR    365
#define DAYSPERLYEAR    366
#define SECSPERHOUR     (SECSPERMIN * MINSPERHOUR)
#define SECSPERDAY      ((long) SECSPERHOUR * HOURSPERDAY)
#define MONSPERYEAR     12

#define SECS_PER_MIN    SECSPERMIN
#define MINS_PER_HOUR   MINSPERHOUR
#define HOURS_PER_DAY   HOURSPERDAY
#define DAYS_PER_WEEK   DAYSPERWEEK
#define DAYS_PER_NYEAR  DAYSPERNYEAR
#define DAYS_PER_LYEAR  DAYSPERLYEAR
#define SECS_PER_HOUR   SECSPERHOUR
#define SECS_PER_DAY    SECSPERDAY
#define MONS_PER_YEAR   MONSPERYEAR

#define TM_SUNDAY       0
#define TM_MONDAY       1
#define TM_TUESDAY      2
#define TM_WEDNESDAY    3
#define TM_THURSDAY     4
#define TM_FRIDAY       5
#define TM_SATURDAY     6

#define TM_JANUARY      0
#define TM_FEBRUARY     1
#define TM_MARCH        2
#define TM_APRIL        3
#define TM_MAY          4
#define TM_JUNE         5
#define TM_JULY         6
#define TM_AUGUST       7
#define TM_SEPTEMBER    8
#define TM_OCTOBER      9
#define TM_NOVEMBER     10
#define TM_DECEMBER     11

#define TM_YEAR_BASE    1900

#define EPOCH_YEAR      1970
#define EPOCH_WDAY      TM_THURSDAY

#endif /* utc_time_h__ */
